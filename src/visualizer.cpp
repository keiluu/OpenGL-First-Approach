#include "visualizer.hpp"
#include <print>
#include <vector>

namespace visual {
    static void framebuffer_size_callback(GLFWwindow*, const int w, const int h)
    {
        glViewport(0, 0, w, h);
    }

    static GLuint compileShader(const GLenum type, const char* src)
    {
        const GLuint shader = glCreateShader(type);
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

            std::println(stderr, "Shader compile failed:\n {}", log.data());
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    static GLuint createProgram(const char* vsSrc, const char* fsSrc)
    {
        const GLuint vs = compileShader(GL_VERTEX_SHADER, vsSrc);
        if (!vs) return 0;

        const GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsSrc);
        if (!fs) { glDeleteShader(vs); return 0; }

        const GLuint program = glCreateProgram();
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        // Check link status
        GLint ok = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &ok);
        if (!ok)
        {
            GLint logLen = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
            std::vector<char> log(logLen);
            glGetProgramInfoLog(program, logLen, nullptr, log.data());

            std::println(stderr, "Program link failed:\n {}", log.data());
            glDeleteProgram(program);
            return 0;
        }

        return program;
    }


}; // namespace
