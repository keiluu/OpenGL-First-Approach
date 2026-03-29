#include "sim.hpp"
#include <sim.hpp>
#include <random>

#define MOVEMENT_SCALE 0.01
#define MAX_VELOCITY 1

namespace simulation {

    void BrownianMotion::update() {
        thread_local std::mt19937 gen{std::random_device{}()};
        std::bernoulli_distribution coin_flip{0.5};

        for (auto& p : particles) {
            p.x += MOVEMENT_SCALE * (coin_flip(gen) ? -1 : 1);
            p.y += MOVEMENT_SCALE * (coin_flip(gen) ? -1 : 1);
            p.z += MOVEMENT_SCALE * (coin_flip(gen) ? -1 : 1);
        }
    }

    void BrownianMotion::export_buffer(float *vertices) {
        for (int i = 0; i < particles.size(); i++) {
            vertices[3*i] = particles[i].x;
            vertices[3*i + 1] = particles[i].y;
            vertices[3*i + 2] = particles[i].z;
        }
    }

    size_t BrownianMotion::size() { // Returns amout of floats NOT PARTICLES defining the data
        return 3*particles.size();
    }


    void SmoothBrownianMotion::update() {
        thread_local std::mt19937 gen{std::random_device{}()};
        std::bernoulli_distribution coin_flip{0.5};

        for (auto& p : particles) {
            p.velocity.x += MOVEMENT_SCALE * (coin_flip(gen) ? -1 : 1);
            p.velocity.y += MOVEMENT_SCALE * (coin_flip(gen) ? -1 : 1);
            p.velocity.z += MOVEMENT_SCALE * (coin_flip(gen) ? -1 : 1);

            if (p.velocity.x < -MAX_VELOCITY) {
                p.velocity.x = -MAX_VELOCITY;
            }
            if (p.velocity.y < -MAX_VELOCITY) {
                p.velocity.y = -MAX_VELOCITY;
            }
            if (p.velocity.z < -MAX_VELOCITY) {
                p.velocity.z = -MAX_VELOCITY;
            }

            if (p.velocity.x > MAX_VELOCITY) {
                p.velocity.x = MAX_VELOCITY;
            }
            if (p.velocity.y > MAX_VELOCITY) {
                p.velocity.y = MAX_VELOCITY;
            }
            if (p.velocity.z > MAX_VELOCITY) {
                p.velocity.z = MAX_VELOCITY;
            }

            p.position += p.velocity;
        }
    }

    void SmoothBrownianMotion::export_buffer(float *vertices) {
        for (int i = 0; i < particles.size(); i++) {
            vertices[3*i] = particles[i].position.x;
            vertices[3*i + 1] = particles[i].position.y;
            vertices[3*i + 2] = particles[i].position.z;
        }
    }

    size_t SmoothBrownianMotion::size() { // Returns amout of floats NOT PARTICLES defining the data
        return 3*particles.size();
    }


};
