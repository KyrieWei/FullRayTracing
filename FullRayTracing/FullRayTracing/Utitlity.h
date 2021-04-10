#pragma once
#include "Vector3D.h"
#include <cmath>

float length_squared(const Vector3D& vec)
{
	return vec.x* vec.x + vec.y * vec.y + vec.z * vec.z;
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