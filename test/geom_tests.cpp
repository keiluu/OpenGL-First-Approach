#include <gtest/gtest.h>
#include <geom.hpp>
#include <print>
#include <string>

TEST(Geometry_Class, Point3_Constructor) {
    try {
        geom::Point3<double> pt(1.0, 2.0, 3.0);
        std::println("Point3 coords -> x: {}   y: {}   z: {}", pt.x, pt.y, pt.z);
        SUCCEED();

    } catch (const std::invalid_argument& e) {
        std::println("Error: {}", e.what());
        FAIL();
    }
    catch (...) {
        FAIL();
    }
}