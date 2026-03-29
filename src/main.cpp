#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "visualizer.hpp"
#include <vector>
#include "geom.hpp"
#include "sim.hpp"


int main() {

    std::vector<geom::Vec3<float>> particles;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                geom::Vec3<float> particle(k*0.1f - 0.5f, j*0.1f - 0.5f, i*0.1f - 0.5f);
                particles.push_back(particle);
            }
        }
    }

    simulation::SmoothBrownianMotion brown(particles);
    auto ptr = std::make_unique<float []>(brown.size());

    visual::Visualizer my_vis(800, 600, "Hello bro");
    my_vis.init(ptr, brown);

    return 0;
}