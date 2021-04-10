#pragma once

#include "Utility.h"

float degrees_to_radians(float vfov)
{
	return vfov * M_PI / 180.0;
}

float length_squared(const Vector3D& vec)
{
	return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

float length(const Vector3D& vec)
{
	return std::sqrt(length_squared(vec));
}

Vector3D normalize(const Vector3D& vec)
{
	float len = length(vec);
	return vec / len;
}

extern Vector3D cross(const Vector3D& u, const Vector3D& v)
{
	return Vector3D(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

float length_squared(const Vector4D& vec)
{
	if (vec.w != 1)
	{
		float fac = 1 / vec.w;
		return (vec.x * fac) * (vec.x * fac) + (vec.y * fac) * (vec.y * fac) + (vec.z * fac) * (vec.z * fac);
	}
	else
	{
		return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	}
}

void print(const Vector3D& vec)
{
	std::cout << "( " << vec.x << " " << vec.y << " " << vec.z << " )" << std::endl;
}

void print(const Vector4D& vec)
{
	std::cout << "( " << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << " )" << std::endl;
}