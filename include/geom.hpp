#ifndef GEOM_VISUALIZER_GEOM_HPP
#define GEOM_VISUALIZER_GEOM_HPP

#include <print>
#include <experimental/mdspan>

namespace  geom {
    template<typename T>
    class Mat3x3 {
    private:
        std::array<T, 9> array;
        std::mdspan<T, std::extents<size_t, 3, 3>> matrix;

    public:
        Mat3x3() : array{}, matrix(array.data()) {}
        explicit Mat3x3(std::array<T, 9> &other) : array(other), matrix(array.data()) {}

        T& operator[](std::size_t i, std::size_t j) {
            if (3*i + j >= 9) {
                throw std::out_of_range("Mat3x3 index out of range");
            }
            return matrix[i, j];
        }

        const T& operator[](std::size_t i, std::size_t j) const {
            if (3*i + j >= 9) {
                throw std::out_of_range("Mat3x3 index out of range");
            }
            return matrix[i, j];
        }

        T& operator[](std::size_t i) {
            if (i >= 9) {
                throw std::out_of_range("Mat3x3 index out of range");
            }
            return array[i];
        }

        const T& operator[](std::size_t i) const {
            if (i >= 9) {
                throw std::out_of_range("Mat3x3 index out of range");
            }
            return array[i];
        }

        Mat3x3 operator+ (const Mat3x3& other) const {
            Mat3x3 result;
            for (std::size_t i = 0; i < 9; i++) {result[i] = array[i] + other[i];}
            return result;
        }

        Mat3x3 operator- (const Mat3x3& other) const {
            Mat3x3 result;
            for (std::size_t i = 0; i < 9; i++) {result[i] = array[i] - other[i];}
            return result;
        }

        Mat3x3 operator* (const T scalar) const {
            Mat3x3 result;
            for (std::size_t i = 0; i < 9; i++) {result[i] = array[i] * scalar;}
            return result;
        }

        Mat3x3 operator/ (const T scalar) const {
            Mat3x3 result;
            for (std::size_t i = 0; i < 9; i++) {result[i] = array[i] / scalar;}
            return result;
        }

    };


    template<typename T>
    class Vec3 {
    public:
        T x;
        T y;
        T z;

        constexpr Vec3() : x(0), y(0), z(0) {}
        constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

        constexpr Vec3 operator+ (const Vec3& other) const {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }

        constexpr Vec3 operator- (const Vec3& other) const {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }

        constexpr Vec3 operator* (const T scalar) const {
            return Vec3(x * scalar, y * scalar, z * scalar);
        }

        constexpr Vec3 operator/ (const T scalar) const {
            return Vec3(x / scalar, y / scalar, z / scalar);
        }

        constexpr Vec3& operator+= (const Vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        constexpr Vec3& operator-= (const Vec3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        constexpr Vec3& operator*= (const T scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        constexpr Vec3& operator/= (const T scalar) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        constexpr Vec3& operator= (const Vec3& other) = default;
    };
}; // namespace

#endif //GEOM_VISUALIZER_GEOM_HPP