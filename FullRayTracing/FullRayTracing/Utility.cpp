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

float dot(const Vector3D& u, const Vector3D& v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
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

inline float random_float()
{
	//srand((unsigned)time(NULL));
	return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max)
{
	return min + (max - min) * random_float();
}

float clamp(float a, float min, float max)
{
	if (a < min) return min;
	if (a > max) return max;
	return a;
}

//Vector3D random_unit_vector()
//{
//
//}

Vector3D random_in_unit_sphere()
{
	while (true)
	{
		Vector3D p(random_float(-1, 1), random_float(-1, 1), random_float(-1, 1));
		if (length_squared(p) >= 1)
			continue;
		return p;
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