#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
// #include <string>
#include <vector>
#include <SFML/Graphics.hpp>

static void framebuffer_size_callback(GLFWwindow*, int w, int h)
{
    glViewport(0, 0, w, h);
}

static GLuint compileShader(GLenum type, const char* src)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Check compile status
    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        GLint logLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
        std::vector<char> log(logLen);
        glGetShaderInfoLog(shader, logLen, nullptr, log.data());

        std::cerr << "Shader compile failed:\n" << log.data() << "\n";
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static GLuint createProgram(const char* vsSrc, const char* fsSrc)
{
    GLuint vs = compileShader(GL_VERTEX_SHADER, vsSrc);
    if (!vs) return 0;

    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSrc);
    if (!fs) { glDeleteShader(vs); return 0; }

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    // Check compile

    // Check link status
    GLint ok = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        GLint logLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
        std::vector<char> log(logLen);
        glGetProgramInfoLog(program, logLen, nullptr, log.data());

        std::cerr << "Program link failed:\n" << log.data() << "\n";
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

int main()
{
    // 1) Init GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to init GLFW\n";
        return 1;
    }

    // 2) Request OpenGL 4.6 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 3) Create window + context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Point + Line + Rectangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window (maybe your driver doesn't support 4.6)\n";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // 4) Load OpenGL functions (must happen after context is current)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return 1;
    }

    // 5) Set viewport + resize callback
    int fbW = 0, fbH = 0;
    glfwGetFramebufferSize(window, &fbW, &fbH);
    glViewport(0, 0, fbW, fbH);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Optional: print actual OpenGL version
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << "\n";

    // 6) Shaders (embedded strings)
    const char* vsSrc = R"GLSL(
        #version 460 core
        layout (location = 0) in vec2 aPos;

        void main()
        {
            gl_Position = vec4(aPos, 0.0, 1.0);
            gl_PointSize = 12.0; // point size in pixels
        }
    )GLSL";

    const char* fsSrc = R"GLSL(
        #version 460 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 1.0, 1.0, 1.0); // white
        }
    )GLSL";

    GLuint program = createProgram(vsSrc, fsSrc);
    if (!program)
    {
        glfwTerminate();
        return 1;
    }

    // 7) Vertex data (vec2 positions)
    // Layout:
    // vertex 0: point
    // vertex 1-2: line
    // vertex 3-8: rectangle (two triangles)
    float vertices[] = {
        // point (top-center)
         0.0f,  0.6f,

        // line (middle)
        -0.6f,  0.0f,
         0.6f,  0.0f,

        // rectangle (bottom) as 2 triangles
        -0.6f, -0.4f,
         0.6f, -0.4f,
         0.6f, -0.8f,

        -0.6f, -0.4f,
         0.6f, -0.8f,
        -0.6f, -0.8f
    };

    // 8) VAO + VBO
    GLuint VAO = 0, VBO = 0;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // attribute 0 = vec2 position
    glVertexAttribPointer(
        0,                  // location in shader
        2,                  // vec2
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),  // stride
        (void*)0            // offset
    );
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // Needed on some drivers for gl_PointSize in the shader
    glEnable(GL_PROGRAM_POINT_SIZE);

    // 9) Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Close on ESC
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);

        // Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw
        glUseProgram(program);
        glBindVertexArray(VAO);

        // Draw 1 point from vertex 0
        glDrawArrays(GL_POINTS, 0, 1);

        // Draw 1 line from vertices 1..2
        glDrawArrays(GL_LINES, 1, 2);

        // Draw rectangle (2 triangles) from vertices 3..8 (6 vertices)
        glDrawArrays(GL_TRIANGLES, 3, 6);

        glBindVertexArray(0);

        // Present + events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 10) Cleanup
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(program);

    glfwTerminate();
    return 0;
}
