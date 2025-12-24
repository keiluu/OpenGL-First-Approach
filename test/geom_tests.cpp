#include <gtest/gtest.h>
#include <geom.hpp>
#include <print>

#include <array>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

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

        m[0, 0] = 50;
        std::println("\nAfter change with mdspan");
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

// ---------------------------
// Helpers ChatGPT
// ---------------------------
namespace {
template <typename T>
constexpr bool eq(T a, T b) {
    if constexpr (std::is_floating_point_v<T>) {
        // Use gtest EXPECT_NEAR in tests; this is only for constexpr/static_assert contexts.
        return a == b;
    } else {
        return a == b;
    }
}
} // namespace

// ===========================
// Vec3<T> Test Suite
// ===========================

TEST(Vec3, DefaultConstructorZeros) {
    constexpr geom::Vec3<int> v{};
    static_assert(v.x == 0 && v.y == 0 && v.z == 0);

    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
}

TEST(Vec3, ValueConstructorSetsMembers) {
    constexpr geom::Vec3<double> v(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(v.x, 1.0);
    EXPECT_DOUBLE_EQ(v.y, 2.0);
    EXPECT_DOUBLE_EQ(v.z, 3.0);
}

TEST(Vec3, PlusOperatorProducesNewVec) {
    constexpr geom::Vec3<double> a(1.0, 2.0, 3.0);
    constexpr geom::Vec3<double> b(6.0, 7.0, 8.0);
    constexpr auto c = a + b;

    static_assert(eq(c.x, 7.0) && eq(c.y, 9.0) && eq(c.z, 11.0));
    EXPECT_DOUBLE_EQ(c.x, 7.0);
    EXPECT_DOUBLE_EQ(c.y, 9.0);
    EXPECT_DOUBLE_EQ(c.z, 11.0);

    // Ensure operands unchanged
    EXPECT_DOUBLE_EQ(a.x, 1.0);
    EXPECT_DOUBLE_EQ(a.y, 2.0);
    EXPECT_DOUBLE_EQ(a.z, 3.0);
    EXPECT_DOUBLE_EQ(b.x, 6.0);
    EXPECT_DOUBLE_EQ(b.y, 7.0);
    EXPECT_DOUBLE_EQ(b.z, 8.0);
}

TEST(Vec3, MinusOperatorProducesNewVec) {
    constexpr geom::Vec3<double> a(1.0, 2.0, 3.0);
    constexpr geom::Vec3<double> b(6.0, 7.0, 8.0);
    constexpr auto c = a - b;

    static_assert(eq(c.x, -5.0) && eq(c.y, -5.0) && eq(c.z, -5.0));
    EXPECT_DOUBLE_EQ(c.x, -5.0);
    EXPECT_DOUBLE_EQ(c.y, -5.0);
    EXPECT_DOUBLE_EQ(c.z, -5.0);
}

TEST(Vec3, ScalarMultiplyDivide) {
    constexpr geom::Vec3<double> a(1.0, 2.0, 3.0);

    constexpr auto b = a * 4.0;
    static_assert(eq(b.x, 4.0) && eq(b.y, 8.0) && eq(b.z, 12.0));
    EXPECT_DOUBLE_EQ(b.x, 4.0);
    EXPECT_DOUBLE_EQ(b.y, 8.0);
    EXPECT_DOUBLE_EQ(b.z, 12.0);

    constexpr auto c = a / 4.0;
    EXPECT_DOUBLE_EQ(c.x, 0.25);
    EXPECT_DOUBLE_EQ(c.y, 0.5);
    EXPECT_DOUBLE_EQ(c.z, 0.75);
}

TEST(Vec3, CompoundPlusEquals) {
    geom::Vec3<double> a(1.0, 2.0, 3.0);
    a += geom::Vec3<double>(6.0, 7.0, 8.0);
    EXPECT_DOUBLE_EQ(a.x, 7.0);
    EXPECT_DOUBLE_EQ(a.y, 9.0);
    EXPECT_DOUBLE_EQ(a.z, 11.0);
}

TEST(Vec3, CompoundMinusEquals) {
    geom::Vec3<double> a(10.0, 20.0, 30.0);
    a -= geom::Vec3<double>(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(a.x, 9.0);
    EXPECT_DOUBLE_EQ(a.y, 18.0);
    EXPECT_DOUBLE_EQ(a.z, 27.0);
}

TEST(Vec3, CompoundTimesEquals) {
    geom::Vec3<double> a(1.0, 2.0, 3.0);
    a *= 5.0;
    EXPECT_DOUBLE_EQ(a.x, 5.0);
    EXPECT_DOUBLE_EQ(a.y, 10.0);
    EXPECT_DOUBLE_EQ(a.z, 15.0);
}

TEST(Vec3, CompoundDivideEquals) {
    geom::Vec3<double> a(10.0, 20.0, 30.0);
    a /= 10.0;
    EXPECT_DOUBLE_EQ(a.x, 1.0);
    EXPECT_DOUBLE_EQ(a.y, 2.0);
    EXPECT_DOUBLE_EQ(a.z, 3.0);
}

TEST(Vec3, DefaultedAssignmentCopies) {
    geom::Vec3<int> a(1, 2, 3);
    geom::Vec3<int> b;
    b = a;
    EXPECT_EQ(b.x, 1);
    EXPECT_EQ(b.y, 2);
    EXPECT_EQ(b.z, 3);
}

// ===========================
// Mat3x3<T> Test Suite
// Assumption per your request:
// - "matrix[i, j]" works correctly
// - "m[i, j]" works correctly and is 2D indexing
// ===========================

TEST(Mat3x3, DefaultConstructorZeroInitializes) {
    geom::Mat3x3<int> m;

    for (std::size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(m[i], 0) << "Flat index i=" << i;
    }

    // Spot-check some 2D indices map to the same underlying storage
    EXPECT_EQ((m[0, 0]), 0);
    EXPECT_EQ((m[2, 2]), 0);
}

TEST(Mat3x3, ConstructFromArrayCopiesValues) {
    std::array<int, 9> a{1,2,3,4,5,6,7,8,9};
    geom::Mat3x3<int> m(a);

    for (std::size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(m[i], a[i]) << "Flat index i=" << i;
    }

    // Check 2D access returns expected values (row-major mapping assumed by your bounds formula 3*i + j)
    EXPECT_EQ((m[0, 0]), 1);
    EXPECT_EQ((m[0, 1]), 2);
    EXPECT_EQ((m[0, 2]), 3);
    EXPECT_EQ((m[1, 0]), 4);
    EXPECT_EQ((m[1, 1]), 5);
    EXPECT_EQ((m[1, 2]), 6);
    EXPECT_EQ((m[2, 0]), 7);
    EXPECT_EQ((m[2, 1]), 8);
    EXPECT_EQ((m[2, 2]), 9);
}

TEST(Mat3x3, TwoDAccessWritesAndReflectsInFlatStorage) {
    geom::Mat3x3<int> m;

    m[0, 0] = 11;
    m[1, 2] = 22;
    m[2, 1] = 33;

    // Using your mapping 3*i + j
    EXPECT_EQ(m[0], 11); // (0,0)
    EXPECT_EQ(m[5], 22); // (1,2) -> 3*1+2 = 5
    EXPECT_EQ(m[7], 33); // (2,1) -> 3*2+1 = 7

    // Read back via 2D
    EXPECT_EQ((m[0, 0]), 11);
    EXPECT_EQ((m[1, 2]), 22);
    EXPECT_EQ((m[2, 1]), 33);
}

TEST(Mat3x3, FlatAccessWritesAndReflectsInTwoDStorage) {
    geom::Mat3x3<int> m;

    m[0] = 101;
    m[4] = 202;
    m[8] = 303;

    EXPECT_EQ((m[0, 0]), 101);
    EXPECT_EQ((m[1, 1]), 202);
    EXPECT_EQ((m[2, 2]), 303);
}

TEST(Mat3x3, ConstOverloadsWorkForReadOnlyAccess) {
    std::array<int, 9> a{1,2,3,4,5,6,7,8,9};
    const geom::Mat3x3<int> m(a);

    // Flat const access
    EXPECT_EQ(m[0], 1);
    EXPECT_EQ(m[8], 9);

    // 2D const access
    EXPECT_EQ((m[0, 2]), 3);
    EXPECT_EQ((m[2, 0]), 7);

    // Compile-time check that const overload returns const ref
    static_assert(std::is_same_v<decltype(m[0]), const int&>);
    static_assert(std::is_same_v<decltype(m[0, 0]), const int&>);
}

TEST(Mat3x3, FlatOutOfRangeThrows) {
    geom::Mat3x3<int> m;
    EXPECT_THROW((void)m[9], std::out_of_range);
    EXPECT_THROW((void)m[1000], std::out_of_range);
}

TEST(Mat3x3, TwoDOutOfRangeThrows_ByBoundsFormula) {
    geom::Mat3x3<int> m;

    // Your check is: if (3*i + j >= 9) throw
    // So these should throw:
    EXPECT_THROW((void)(m[3, 0]), std::out_of_range); // 3*3 + 0 = 9
    EXPECT_THROW((void)(m[0, 9]), std::out_of_range); // 0 + 9 = 9
    EXPECT_THROW((void)(m[2, 3]), std::out_of_range); // 6 + 3 = 9

    // These should not throw:
    EXPECT_NO_THROW((void)(m[2, 2])); // 6 + 2 = 8
}

TEST(Mat3x3, AdditionIsElementWiseAndNonMutating) {
    std::array<int, 9> a{1,2,3,4,5,6,7,8,9};
    std::array<int, 9> b{9,8,7,6,5,4,3,2,1};
    geom::Mat3x3<int> A(a);
    geom::Mat3x3<int> B(b);

    auto C = A + B;

    for (std::size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(C[i], a[i] + b[i]) << "i=" << i;
    }

    // Ensure A and B unchanged
    for (std::size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(A[i], a[i]) << "i=" << i;
        EXPECT_EQ(B[i], b[i]) << "i=" << i;
    }
}

TEST(Mat3x3, SubtractionIsElementWiseAndNonMutating) {
    std::array<int, 9> a{10,11,12,13,14,15,16,17,18};
    std::array<int, 9> b{1,2,3,4,5,6,7,8,9};
    geom::Mat3x3<int> A(a);
    geom::Mat3x3<int> B(b);

    auto C = A - B;

    for (std::size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(C[i], a[i] - b[i]) << "i=" << i;
    }
}

TEST(Mat3x3, ScalarMultiplyIsElementWiseAndNonMutating) {
    std::array<int, 9> a{1,2,3,4,5,6,7,8,9};
    geom::Mat3x3<int> A(a);

    auto C = A * 3;

    for (std::size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(C[i], a[i] * 3) << "i=" << i;
        EXPECT_EQ(A[i], a[i])     << "i=" << i; // A unchanged
    }
}

TEST(Mat3x3, ScalarDivideIsElementWiseAndNonMutating) {
    std::array<int, 9> a{9,8,7,6,5,4,3,2,1};
    geom::Mat3x3<int> A(a);

    auto C = A / 2; // integer division

    for (std::size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(C[i], a[i] / 2) << "i=" << i;
        EXPECT_EQ(A[i], a[i])     << "i=" << i;
    }
}

TEST(Mat3x3, DivisionByZeroBehavior_IsNotTested) {
    // NOTE:
    // Your operator/(scalar) does not guard against scalar==0.
    // For integral T, dividing by 0 is UB.
    // For floating T, it yields inf/nan depending on IEEE behavior.
    // So we do NOT test division-by-zero here.
    SUCCEED();
}