#pragma once
#include "pch.h"
//struct Vector3 {
//	Vector3(float x, float y, float z)
//		:x(x), y(y), z(z) {}
//	Vector3()
//		:x(0.0f), y(0.0f), z(0.0f) {}
//	const Vector3 operator+(Vector3& First) {
//		return Vector3(x + First.x, y + First.y, z + First.z);
//	}
//	const Vector3 operator-(Vector3& First) {
//		return Vector3(x - First.x, y - First.y, z - First.z); //check
//	}
//	const Vector3 operator-(const Vector3& First) {
//		return Vector3(x - First.x, y - First.y, z - First.z); //check
//	}
//	float x, y, z;
//};
//struct Angle {
//	Angle(float yaw, float pitch, float roll)
//		:yaw(yaw), pitch(pitch), roll(roll) {}
//	Angle()
//		:yaw(0.0f), pitch(0.0f), roll(0.0f) {}
//	const Angle operator+(Angle& First) {
//		return Angle(yaw + First.yaw, pitch + First.pitch, roll + First.roll);
//	}
//	const Angle operator-(Angle& First) {
//		return Angle(yaw - First.yaw, pitch - First.pitch, roll - First.roll); //check
//	}
//	float yaw, pitch, roll;
//};

struct Vector2 {
	float x, y;
	Vector2(float x, float y)
		:x(x), y(y) {}
	Vector2()
		:x(0.0f), y(0.0f) {}
	const Vector2 operator+(Vector2& First) {
		return Vector2(x + First.x, y + First.y);
	}
	const Vector2 operator-(Vector2& First) {
		return Vector2(First.x - x, First.y - y); //check
	}
};


class Vec3 {
public:
    // Member variables
    float x, y, z;

    // Constructors
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Operator overloads for basic arithmetic
    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator/(float scalar) const {
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    // Compound assignment operators
    Vec3& operator+=(const Vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vec3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vec3& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    // Magnitude (length) of the vector
    float Length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    bool operator<(const Vec3& v) const {
        return this->Length() < v.Length();
    }

    bool operator>(const Vec3& v) const {
        return this->Length() > v.Length();
    }

    // Normalize the vector (make it unit length)
    Vec3 Normalized() const {
        float len = Length();
        if (len == 0) return Vec3(0, 0, 0);
        return *this / len;
    }

    // Dot product
    float Dot(const Vec3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // Cross product
    Vec3 Cross(const Vec3& v) const {
        return Vec3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    // Distance between two vectors
    float Distance(const Vec3& v) const {
        return (*this - v).Length();
    }

    // Check for equality
    bool operator==(const Vec3& v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator!=(const Vec3& v) const {
        return !(*this == v);
    }

    // Linear interpolation between two vectors
    static Vec3 Lerp(const Vec3& a, const Vec3& b, float t) {
        return a + (b - a) * t;
    }
};

struct Vector4 {
	Vector4(float x, float y, float z, float w)
		:x(x), y(y), z(z), w(w){}
	Vector4()
		:x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	const Vector4 operator+(Vector4& First) {
		return Vector4(x + First.x, y + First.y, z + First.z, w+ First.w);
	}
	const Vector4 operator-(Vector4& First) {
		return Vector4(First.x - x, First.y - y, First.z - z, First.w - w); //check
	}
	float x, y, z, w;
};

struct Angle {
    // Member variables
    float yaw, pitch, roll;

    // Constructors
    Angle(float yaw, float pitch, float roll)
        : yaw(yaw), pitch(pitch), roll(roll) {}

    Angle() : yaw(0.0f), pitch(0.0f), roll(0.0f) {}

    // Addition operator
    const Angle operator+(const Angle& other) const {
        return Angle(yaw + other.yaw, pitch + other.pitch, roll + other.roll);
    }

    // Subtraction operator
    const Angle operator-(const Angle& other) const {
        return Angle(yaw - other.yaw, pitch - other.pitch, roll - other.roll);
    }

    // Compound assignment operators
    Angle& operator+=(const Angle& other) {
        yaw += other.yaw;
        pitch += other.pitch;
        roll += other.roll;
        return *this;
    }

    Angle& operator-=(const Angle& other) {
        yaw -= other.yaw;
        pitch -= other.pitch;
        roll -= other.roll;
        return *this;
    }

    // Magnitude (used for comparison)
    float Magnitude() const {
        return std::sqrt(yaw * yaw + pitch * pitch + roll * roll);
    }

    // Comparison operators based on the magnitude of the angles
    bool operator<(const Angle& other) const {
        return this->Magnitude() < other.Magnitude();
    }

    bool operator>(const Angle& other) const {
        return this->Magnitude() > other.Magnitude();
    }

    // Equality operators
    bool operator==(const Angle& other) const {
        return yaw == other.yaw && pitch == other.pitch && roll == other.roll;
    }

    bool operator!=(const Angle& other) const {
        return !(*this == other);
    }
};

typedef Vec3 vec3;
typedef Vec3 Vector3;
typedef Vec3 vector3;

typedef Vector4 vec4;
typedef Vector4 Vec4;
typedef Vector4 vector4;

typedef Vector2 vec2;
typedef Vector2 Vec2;
typedef Vector2 vector2;



