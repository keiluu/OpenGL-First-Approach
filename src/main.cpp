#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "visualizer.hpp"
#include <vector>


int main() {
    std::vector<float> vertices;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                vertices.push_back(k*0.1f - 0.5f);
                vertices.push_back(j*0.1f - 0.5f);
                vertices.push_back(i*0.1f - 0.5f);
            }
        }
    }

    visual::Visualizer my_vis(800, 600, "Hello bro");
    my_vis.init(vertices);

    return 0;
}