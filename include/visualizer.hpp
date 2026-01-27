#ifndef GEOM_VISUALIZER_VISUALIZER_HPP
#define GEOM_VISUALIZER_VISUALIZER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace visual {
    static void framebuffer_size_callback(GLFWwindow*, int w, int h);

    static GLuint compileShader(GLenum type, const char* src);

    static GLuint createProgram(const char* vsSrc, const char* fsSrc);

}; // namespace

#endif //GEOM_VISUALIZER_VISUALIZER_HPP