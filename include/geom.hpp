#ifndef GEOM_VISUALIZER_GEOM_HPP
#define GEOM_VISUALIZER_GEOM_HPP

#include <experimental/mdspan>

namespace  geom {
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

        constexpr T dotProduct(const Vec3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        constexpr Vec3 crossProduct(const Vec3& other) const {
            return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
        }

        constexpr T magnitude() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        constexpr Vec3 unitVector() const {
            return *this / this->magnitude();
        }

    }; // Vec3


    template<typename T>
    class Mat3x3 {
    private:
        std::array<T, 9> array;
        std::mdspan<T, std::extents<size_t, 3, 3>> matrix;

    public:
        Mat3x3() : array{}, matrix(array.data()) {}
        explicit Mat3x3(const std::array<T, 9> &other) : array(other), matrix(array.data()) {}

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

        Mat3x3& operator+= (const Mat3x3& other) {
            for (std::size_t i = 0; i < 9; i++) {
                array[i] += other.array[i];
            }
            return *this;
        }

        Mat3x3& operator-= (const Mat3x3& other) {
            for (std::size_t i = 0; i < 9; i++) {
                array[i] -= other.array[i];
            }
            return *this;
        }

        Mat3x3& operator*= (const T scalar) {
            for (std::size_t i = 0; i < 9; i++) {
                array[i] *= scalar;
            }
            return *this;
        }

        Mat3x3& operator/= (const T scalar) {
            for (std::size_t i = 0; i < 9; i++) {
                array[i] /= scalar;
            }
            return *this;
        }

        Mat3x3& operator= (const Mat3x3& other) {
            std::copy_n(other.array.data(), 9, array.data());
            return *this;
        }

        constexpr Vec3<T> operator* (const Vec3<T>& other) const {
            Vec3<T> result;

            result.x = matrix[0, 0] * other.x + matrix[0, 1] * other.y + matrix[0, 2] * other.z;
            result.y = matrix[1, 0] * other.x + matrix[1, 1] * other.y + matrix[1, 2] * other.z;
            result.z = matrix[2, 0] * other.x + matrix[2, 1] * other.y + matrix[2, 2] * other.z;

            return result;
        }

    }; // Mat3x3
}; // namespace

#endif //GEOM_VISUALIZER_GEOM_HPP