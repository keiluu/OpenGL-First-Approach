//
// Created by batman on 2/22/26.
//

#ifndef GEOM_VISUALIZER_SIM_HPP
#define GEOM_VISUALIZER_SIM_HPPi

#include "geom.hpp"

namespace simulation{
    class Simulator {

    public:
        virtual void update() = 0;
        virtual void process_key(char key) = 0;
        virtual void export_buffer(const float* vertices) = 0;
    };


}

#endif //GEOM_VISUALIZER_SIM_HPP