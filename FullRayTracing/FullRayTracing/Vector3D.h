#pragma once
#include <iostream>

class Vector3D
{
public:
	float x, y, z;

	Vector3D() : x(0), y(0), z(0) {}
	Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3D(const Vector3D& vec) : x(vec.x), y(vec.y), z(vec.z) {}

	Vector3D operator+(const Vector3D& vec) const
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}
	
	Vector3D operator-(const Vector3D& vec) const
	{
		return Vector3D(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3D operator*(const float fac) const
	{
		return Vector3D(x * fac, y * fac, z * fac);
	}

	Vector3D operator*(const Vector3D& vec) const
	{
		return Vector3D(x * vec.x, y * vec.y, z * vec.z);
	}

	Vector3D operator/(const float fac) const
	{
		if(fac == 0)
		{
			std::cerr << "error of dividing zero.\n" << std::endl;
			exit(1);
		}

		return *this * (1 / fac);
	}
	
	Vector3D operator-() const
	{
		return Vector3D(-x, -y, -z);
	}

	Vector3D& operator+=(const Vector3D& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	Vector3D& operator-=(const Vector3D& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	Vector3D& operator*=(const float fac)
	{
		x *= fac;
		y *= fac;
		z *= fac;

		return *this;
	}

	Vector3D& operator/=(const float fac)
	{
		if (fac == 0)
		{
			std::cerr << "error of dividing zero.\n" << std::endl;
			exit(1);
		}
		else
		{
			return *this *= 1 / fac;
		}
	}

	bool near_zero() const
	{
		const auto s = 1e-8;
		return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
	}

	friend Vector3D operator*(float fac, const Vector3D& vec)
	{
		return vec * fac;
	}

};

