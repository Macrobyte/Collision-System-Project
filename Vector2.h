#pragma once
#include <iostream>
#include <string>
#include <cmath>

class Vector2 
{

public:
	float x;
	float y;

	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}

    /// <summary>
	/// Overloads the + operator to add two vectors.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

	/// <summary>
	/// Overloads the + operator to add a vector and a scalar.
	/// </summary>
	/// <param name="scalar"></param>
	/// <returns></returns>
	Vector2 operator+(float scalar) const {
		return Vector2(x + scalar, y + scalar);
	}

    /// <summary>
	/// Overloads the - operator to subtract two vectors.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }
    
    /// <summary>
	/// Overloads the unary - operator to negate a vector.
    /// </summary>
    /// <returns></returns>
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }
    
    /// <summary>
	/// Overloads the * operator to multiply a vector by a scalar.
    /// </summary>
    /// <param name="scalar"></param>
    /// <returns></returns>
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }
    
    /// <summary>
	/// Overloads the * operator to multiply a scalar by a vector.
    /// </summary>
    /// <param name="scalar"></param>
    /// <param name="vector"></param>
    /// <returns></returns>
    friend Vector2 operator*(float scalar, const Vector2& vector) {
        return vector * scalar;
    }
    
	/// <summary>
	/// Overloads the * operator to multiply two vectors.
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	float operator*(const Vector2& other) const {
		return x * other.x + y * other.y;
	}
    
    /// <summary>
	/// Overloads the / operator to divide a vector by a scalar.
    /// </summary>
    /// <param name="scalar"></param>
    /// <returns></returns>
    Vector2 operator/(float scalar) const {
        return Vector2(x / scalar, y / scalar);
    }

    /// <summary>
	/// Overloads the += operator to return the original vector plus the added vector.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    /// <summary>
	/// Overloads the -= operator to return the original vector minus the subtracted vector.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    /// <summary>
	/// Overloads the *= operator to return the original vector multiplied by the scalar.
    /// </summary>
    /// <param name="scalar"></param>
    /// <returns></returns>
    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    /// <summary>
	/// Overloads the /= operator to return the original vector divided by the scalar.
    /// </summary>
    /// <param name="scalar"></param>
    /// <returns></returns>
    Vector2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    /// <summary>
	/// Overloads the == operator to check if two vectors are equal.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    /// <summary>
	/// Overloads the != operator to check if two vectors are not equal.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    /// <summary>
	/// Returns the magnitude of a vector.
    /// </summary>
    /// <returns></returns>
    float magnitude() const {
        return sqrt(x * x + y * y);
    }

    /// <summary>
	/// Returns the squared magnitude of a vector.
    /// </summary>
    /// <returns></returns>
    float magnitude_squared() const{
        return x * x + y * y;     
    }

    /// <summary>
	/// Returns the normalized vector of a vector.
    /// </summary>
    /// <returns></returns>
    Vector2 normalized() const {
        float mag = magnitude();
        return Vector2(x / mag, y / mag);
    }

    /// <summary>
	/// Normalizes the vector by dividing the x and y values by the magnitude.
    /// </summary>
    /// <returns></returns>
    Vector2 normalize() {
		float mag = magnitude();
		x /= mag;
		y /= mag;
		return *this;
    }

    /// <summary>
	/// Returns the perpendicular vector of a vector.
    /// </summary>
    /// <returns></returns>
    Vector2 perp() const{
        return Vector2(-y, x);
    }

    /// <summary>
	/// Returns the distance between two vectors.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    float distance(const Vector2& other) const {
        return (*this - other).magnitude();
    }

    /// <summary>
	/// Returns the squared distance between two vectors.
    /// </summary>
    /// <param name="normal"></param>
    Vector2 reflect(const Vector2& normal) const
    {
        return *this - 2.0f * dot(*this, normal) * normal;
    }

	/// <summary>
	/// Returns the dot product of two vectors.
    /// </summary>
    /// <param name="a"></param>
    /// <param name="b"></param>
	static float dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}
    
	//Vector.zero
	static Vector2 Zero() {
		return Vector2(0, 0);
	}

    /// <summary>
	/// Overloads the << operator to print a vector.
    /// </summary>
    /// <param name="os"></param>
    /// <param name="vector"></param>
    /// <returns></returns>
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
        os << "(" << vector.x << ", " << vector.y << ")";
        return os;
    }


};

