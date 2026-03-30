#ifndef GEOM_VISUALIZER_VISUALIZER_HPP
#define GEOM_VISUALIZER_VISUALIZER_HPP

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "sim.hpp"

namespace visual {

    class Visualizer {
    public:
        unsigned int width, height;

        Visualizer(int width, int height, const char* title);
        ~Visualizer();

        void init(const std::unique_ptr<float []> &vertices, simulation::Simulator& sim);

    private:
        GLFWwindow* window;
        unsigned int VAO, VBO, shaderProgram;

        // FOV
        float fov = 45.0f;

        // Camera
        float cameraZ = 50.0f;

        // Model rotation
        float modelYaw   = 0.0f;
        float modelPitch = 0.0f;

        // Mouse state
        bool  isDragging = false;
        float lastMouseX = 0.0f;
        float lastMouseY = 0.0f;

        // Pause or Continue simulation
        bool paused = false;

        // Callbacks — static to be compatible with GLFW's C function pointers
        static void scrollCallback     (GLFWwindow* window, double xOffset, double yOffset);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void cursorPosCallback  (GLFWwindow* window, double xPos, double yPos);
        static void keyCallback        (GLFWwindow* window, int key, int scancode, int action, int mods);
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

        [[nodiscard]] glm::mat4 calculateMVP() const;
    };
}; // namespace

#endif //GEOM_VISUALIZER_VISUALIZER_HPP