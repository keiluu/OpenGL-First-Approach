#include <gtest/gtest.h>
#include <geom.hpp>
#include <print>
#include <string>

TEST(Geometry_Class, Vec3_Constructor) {
    try {
        geom::Vec3<double> pt(1.0, 2.0, 3.0);
        std::println("Construct Point3 coords -> x: {}   y: {}   z: {}", pt.x, pt.y, pt.z);

        geom::Vec3<double> pt2;
        pt2.x = 5.5;
        std::println("Construct Point3 coords -> x: {}   y: {}   z: {}", pt2.x, pt2.y, pt2.z);
        SUCCEED();

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
        FAIL();
    }
    catch (...) {
        FAIL();
    }
}

TEST(Geometry_Class, Vec3_sum) {
    try {
        constexpr geom::Vec3<double> pt(1.0, 2.0, 3.0);
        constexpr geom::Vec3<double> pt2(6.0, 7.0, 8.0);
        constexpr geom::Vec3<double> pt3 = pt + pt2;

        std::println("Sum Point3 coords -> x: {}   y: {}   z: {}", pt3.x, pt3.y, pt3.z);

        SUCCEED();

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
        FAIL();
    }
    catch (...) {
        FAIL();
    }
}

TEST(Geometry_Class, Vec3_diff) {
    try {
        constexpr geom::Vec3<double> pt(1.0, 2.0, 3.0);
        constexpr geom::Vec3<double> pt2(6.0, 7.0, 8.0);
        constexpr geom::Vec3<double> pt3 = pt - pt2;

        std::println("Diff Point3 coords -> x: {}   y: {}   z: {}", pt3.x, pt3.y, pt3.z);

        SUCCEED();

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
        FAIL();
    }
    catch (...) {
        FAIL();
    }
}

TEST(Geometry_Class, Vec3_prod) {
    try {
        constexpr geom::Vec3<double> pt(1.0, 2.0, 3.0);
        constexpr geom::Vec3<double> pt3 = pt * 4;

        std::println("Prod Point3 coords -> x: {}   y: {}   z: {}", pt3.x, pt3.y, pt3.z);

        SUCCEED();

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
        FAIL();
    }
    catch (...) {
        FAIL();
    }
}

TEST(Geometry_Class, Vec3_div) {
    try {
        constexpr geom::Vec3<double> pt(1.0, 2.0, 3.0);
        constexpr geom::Vec3<double> pt3 = pt / 4;

        std::println("Div Point3 coords -> x: {}   y: {}   z: {}", pt3.x, pt3.y, pt3.z);

        SUCCEED();

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
        FAIL();
    }
    catch (...) {
        FAIL();
    }
}

TEST(Geometry_Class, Vec3_sumeq) {
    try {
        geom::Vec3<double> pt(1.0, 2.0, 3.0);
        pt += geom::Vec3<double>(1.0, 2.0, 3.0);

        std::println("SumEq Point3 coords -> x: {}   y: {}   z: {}", pt.x, pt.y, pt.z);

        SUCCEED();

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
        FAIL();
    }
    catch (...) {
        FAIL();
    }
}


TEST(Matrix_Class, Mat3_Constructor) {
    try {
        std::array<int, 9> a {1,2,3};
        geom::Mat3x3<int> m(a);
        std::println("Without mdspan");
        for (int i = 0; i < 9; i++) {
            std::print("{} ",m[i]);
        }
        std::print("\n");

        std::println("With mdspan");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::print("{} ",m[i, j]);
            }
            std::print("\n");
        }

        SUCCEED();

    } catch (const std::exception& e) {
        std::println("Error: {}", e.what());
        FAIL();
    }
    catch (...) {
        FAIL();
    }
}