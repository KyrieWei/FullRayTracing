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

Vector3D cross(const Vector3D& u, const Vector3D& v)
{
	return Vector3D(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

Vector3D unit_vector(const Vector3D& vec)
{
	float len = length(vec);
	return vec / len;
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

float m_clamp(float a, float min, float max)
{
	if (a < min) return min;
	if (a > max) return max;
	return a;
}

// v is the incident direction, n is the unit normal;
// reflect direction = v + 2b 
// b = dot(-v, n) * n;
Vector3D reflect(const Vector3D& v, const Vector3D& n)
{
	return v - 2 * dot(v, n) * n;
}

Vector3D refract(const Vector3D& uv, const Vector3D& n, float etai_over_etat)
{
	auto cos_theta = fmin(dot(-uv, n), 1.0);
	Vector3D r_out_perp = etai_over_etat * (uv + cos_theta * n);
	Vector3D r_out_parallel = -sqrt(fabs(1.0 - length_squared(r_out_perp))) * n;
	return r_out_perp + r_out_parallel;
}

float reflectance(float cosine, float ref_idx)
{
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}


Vector3D random_unit_vector()
{
	float a = random_float(0, 2 * M_PI);
	float b = random_float(-1, 1);
	float c = sqrt(1 - b * b);
	return Vector3D(c * cos(a), c * sin(a), b);
}

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

Vector3D random_in_hemisphere(const Vector3D& normal)
{
	Vector3D in_unit_sphere = random_in_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0)
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}



void print(const Vector3D& vec)
{
	std::cout << "( " << vec.x << " " << vec.y << " " << vec.z << " )" << std::endl;
}

void print(const Vector4D& vec)
{
	std::cout << "( " << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << " )" << std::endl;
}