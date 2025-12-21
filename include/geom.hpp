//
// Created by batman on 12/20/25.
//

#ifndef GEOM_VISUALIZER_GEOM_HPP
#define GEOM_VISUALIZER_GEOM_HPP

namespace  geom {

    template<typename T>
    class Point3 {
    public:
        T x;
        T y;
        T z;

        Point3() : x(0), y(0), z(0) {}
        Point3(T x, T y, T z) : x(x), y(y), z(z) {}
    };

}; // namespace

#endif //GEOM_VISUALIZER_GEOM_HPP