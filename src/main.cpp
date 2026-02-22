#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "visualizer.hpp"
#include <vector>


int main() {

    const std::vector<float> vertices = {
        1.0f, 2.0f, 2.0f,  // Representation of (1, 1, 0)
        0.8f, 0.4f, 0.4f   // Representation of (20, 10, 10) scaled down
    };

    visual::Visualizer my_vis(800, 600, "Hello bro");
    my_vis.init(vertices);

    return 0;
}