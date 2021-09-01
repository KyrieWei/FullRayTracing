#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>

#include "../maths/Vector3D.h"
#include "../maths/Vector4D.h"
#include "../accelerators/AABB.h"

float degrees_to_radians(float vfov);
float length_squared(const Vector3D& vec);
float length(const Vector3D& vec);
float dot(const Vector3D& u, const Vector3D& v);

Vector3D normalize(const Vector3D& vec);
Vector3D cross(const Vector3D& u, const Vector3D& v);
Vector3D unit_vector(const Vector3D& vec);


float length_squared(const Vector4D& vec);

void print(const Vector3D& vec);
void print(const Vector4D& vec);


inline float random_float();
inline float random_float(float min, float max);

float m_clamp(float a, float min, float max);


Vector3D reflect(const Vector3D& v, const Vector3D& n);
Vector3D refract(const Vector3D& uv, const Vector3D& n, float etai_over_etat);
float reflectance(float cosine, float ref_idx);

Vector3D random();
Vector3D random(float min, float max);
Vector3D random_unit_vector();
Vector3D random_in_unit_sphere();
Vector3D random_in_hemisphere(const Vector3D& normal);
Vector3D random_in_unit_disk();
Vector3D random_cosine_direction();

int random_int(int min, int max);

AABB surrounding_box(const AABB& box0, const AABB& box1);
