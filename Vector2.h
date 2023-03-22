#pragma once
#include <cmath>
#include <iostream>
#include <string>

class Vector2 {

public:
	float x;
	float y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

#pragma region Operator Overloading.

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

#pragma endregion

#pragma region Utility Functions

    float magnitude() const {
        return sqrt(x * x + y * y);
    }

    Vector2 normalized() const {
        float mag = magnitude();
        return Vector2(x / mag, y / mag);
    }

    void normalize() {
        float mag = magnitude();
        x /= mag;
        y /= mag;
    }

    float distance(const Vector2& other) const {
        return (*this - other).magnitude();
    }

    Vector2 lerp(const Vector2& other, float t) const {
        return *this + (other - *this) * t;
    }

    Vector2 rotate(float angle) const {
        return Vector2(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }

#pragma endregion

    
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
        os << "(" << vector.x << ", " << vector.y << ")";
        return os;
    }


};
