//
// Created by batman on 2/22/26.
//

#ifndef GEOM_VISUALIZER_SIM_HPP
#define GEOM_VISUALIZER_SIM_HPP

#include "geom.hpp"

namespace simulation{
    class Simulator {

    public:
        virtual ~Simulator() = default;

        virtual void update() = 0;
        virtual void export_buffer(float* vertices) = 0;
        virtual size_t size() = 0;

    };

    class BrownianMotion : public Simulator {
    private:
        std::vector<geom::Vec3<float>> particles;

    public:
        explicit BrownianMotion(std::vector<geom::Vec3<float>>& particles) : particles(std::move(particles)) {}
        void update() override;
        void export_buffer(float* vertices) override;
        size_t size() override;
    };

    struct Particle {
        geom::Vec3<float> position;
        geom::Vec3<float> velocity;
        geom::Vec3<float> acceleration;
    };

    class SmoothBrownianMotion : public Simulator {
    private:
        std::vector<Particle> particles;

    public:
        explicit SmoothBrownianMotion(const std::vector<geom::Vec3<float>>& positions) {
            for (auto& pos : positions) {
                Particle p;
                p.position = pos;
                particles.push_back(p);
            }
        }
        void update() override;
        void export_buffer(float* vertices) override;
        size_t size() override;
    };


}

#endif //GEOM_VISUALIZER_SIM_HPP