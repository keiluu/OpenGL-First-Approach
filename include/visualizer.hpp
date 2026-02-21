#ifndef GEOM_VISUALIZER_VISUALIZER_HPP
#define GEOM_VISUALIZER_VISUALIZER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace visual {
    class Visualizer {
    public:
        Visualizer(int width, int height, const char* title);
        ~Visualizer();

        void init(const std::vector<float>& vertices);

    private:
        GLFWwindow* window;
        unsigned int VAO, VBO, shaderProgram;
    };
}; // namespace

#endif //GEOM_VISUALIZER_VISUALIZER_HPP