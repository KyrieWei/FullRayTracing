#pragma once
#include "Vector3D.h"

class Vector4D
{

public:
	float x, y, z, w;

	Vector4D() : x(0), y(0), z(0), w(0) {}
	Vector4D(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4D(const Vector4D& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
	Vector4D(const Vector3D& vec) : x(vec.x), y(vec.y), z(vec.z), w(1.0) {}

	Vector4D operator+(const Vector4D& vec) const
	{
		return Vector4D(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
	}

	Vector4D operator-(const Vector4D& vec) const
	{
		return Vector4D(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
	}

	Vector4D operator*(const float fac) const
	{
		return Vector4D(x * fac, y * fac, z * fac, w * fac);
	}

	Vector4D operator/(const float fac) const
	{
		if (fac == 0)
		{
			std::cerr << "dividing with zero.\n" << std::endl;
			exit(1);
		}

		return Vector4D(x / fac, y / fac, z / fac, w / fac);
	}

	Vector4D& operator+=(const Vector4D& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;

		return *this;
	}

	Vector4D& operator-=(const Vector4D& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;

		return *this;
	}

	Vector4D& operator*=(const float fac)
	{
		x *= fac;
		y *= fac;
		z *= fac;
		w *= fac;

		return *this;
	}

	Vector4D& operator/=(const float fac)
	{
		if (fac == 0)
		{
			std::cerr << "dividing with zero.\n" << std::endl;
			exit(1);
		}

		float f = 1 / fac;
		return *this *= f;
	}

	friend Vector4D operator*(const float fac, const Vector4D& vec)
	{
		return vec * fac;
	}
};

