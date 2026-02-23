#include "visualizer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <vector>
#include <print>


static auto vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 MVP;

    void main() {
        gl_Position = MVP * vec4(aPos, 1.0);
        gl_PointSize = 3.0;
    }
)";

static auto fragmentShaderSource = R"(
    #version 460 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.65, 0.0, 1.0);
    }
)";

namespace visual {

    Visualizer::Visualizer(const int width, const int height, const char* title)
        : window(nullptr), VAO(0), VBO(0), shaderProgram(0), width(width), height(height)
    {
        if (!glfwInit())
            throw std::runtime_error("GLFW init failed");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Window creation failed");
        }

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwTerminate();
            throw std::runtime_error("GLAD init failed");
        }

        // Store 'this' so callbacks can retrieve the Visualizer instance
        glfwSetWindowUserPointer(window, this);

        // Associate each event type with its handler function
        glfwSetScrollCallback     (window, scrollCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback  (window, cursorPosCallback);
        glfwSetKeyCallback        (window, keyCallback);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    }

    Visualizer::~Visualizer() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
        glfwTerminate();
    }

    //Event handling functions

    void Visualizer::scrollCallback(GLFWwindow* window, const double xOffset, const double yOffset) {
        auto* viz = static_cast<Visualizer*>(glfwGetWindowUserPointer(window));
        viz->cameraZ -= static_cast<float>(yOffset) * 2.0f;
        viz->cameraZ = glm::max(1.0f, viz->cameraZ);
    }

    void Visualizer::mouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods) {
        auto* viz = static_cast<Visualizer*>(glfwGetWindowUserPointer(window));
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            viz->isDragging = (action == GLFW_PRESS);
    }

    void Visualizer::cursorPosCallback(GLFWwindow* window, const double xPos, const double yPos) {
        auto* viz = static_cast<Visualizer*>(glfwGetWindowUserPointer(window));

        if (!viz->isDragging) {
            // Not dragging — just update last position so we don't get a jump
            // when dragging starts
            viz->lastMouseX = static_cast<float>(xPos);
            viz->lastMouseY = static_cast<float>(yPos);
            return;
        }

        const float dx = static_cast<float>(xPos) - viz->lastMouseX;
        const float dy = static_cast<float>(yPos) - viz->lastMouseY;
        viz->lastMouseX = static_cast<float>(xPos);
        viz->lastMouseY = static_cast<float>(yPos);

        viz->modelYaw   += dx * 0.3f;
        viz->modelPitch += dy * 0.3f;

        if (viz->modelPitch > 90.0f){ viz->modelPitch = 90.0f; }
        else if (viz->modelPitch < -90.0f){ viz->modelPitch = -90.0f; }
    }

    void Visualizer::keyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
        auto* viz = static_cast<Visualizer*>(glfwGetWindowUserPointer(window));
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void Visualizer::framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
        const auto* viz = static_cast<Visualizer*>(glfwGetWindowUserPointer(window));

        // Compute the largest viewport that preserves aspect ratio
        const float targetAspect = static_cast<float>(viz->width) / static_cast<float>(viz->height);
        int viewWidth, viewHeight, offsetX, offsetY;

        if (static_cast<float>(width) / static_cast<float>(height) > targetAspect) {
            // Window is too wide — letterbox on sides
            viewHeight = height;
            viewWidth  = height * static_cast<int>(targetAspect);
            offsetX    = (width - viewWidth) / 2;
            offsetY    = 0;
        } else {
            // Window is too tall — letterbox on top/bottom
            viewWidth  = width;
            viewHeight = static_cast<int>(width / targetAspect);
            offsetX    = 0;
            offsetY    = (height - viewHeight) / 2;
        }

        glViewport(offsetX, offsetY, viewWidth, viewHeight);
    }

    glm::mat4 Visualizer::calculateMVP() const {
        const glm::mat4 view = glm::lookAt(
            glm::vec3(0, 0, cameraZ),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0)
        );

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(modelPitch), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(modelYaw),   glm::vec3(0, 1, 0));

        const glm::mat4 projection = glm::perspective(
            glm::radians(fov),
            static_cast<float>(width) / static_cast<float>(height),
            0.01f, 100.0f
        );

        return projection * view * model;

    }

    void Visualizer::init(const std::vector<float>& vertices) {
        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnable(GL_DEPTH_TEST);

        // Compile vertex shader
        const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        // Compile fragment shader
        const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);

        // Link shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        int success;
        char infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::println(stderr, "Vertex shader error: {}", infoLog);
        }

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            std::println(stderr, "Shader link error: {}", infoLog);
        }

        // Shaders are linked, no longer needed
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Upload vertex data
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        const int MVPLocation = glGetUniformLocation(shaderProgram, "MVP");

        // Render loop
        while (!glfwWindowShouldClose(window)) {

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), nullptr, GL_STREAM_DRAW);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STREAM_DRAW);

            glm::mat4 MVP = calculateMVP();

            glClearColor(0.01f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
            glBindVertexArray(VAO);
            glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(vertices.size())/3);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

} // namespace visual