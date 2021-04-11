#pragma once
#define _USE_MATH_DEFINES

#include "Vector3D.h"
#include "Vector4D.h"
#include <math.h>
#include <iostream>



float degrees_to_radians(float vfov);
float length_squared(const Vector3D& vec);
float length(const Vector3D& vec);
float dot(const Vector3D& u, const Vector3D& v);

Vector3D normalize(const Vector3D& vec);
Vector3D cross(const Vector3D& u, const Vector3D& v);


float length_squared(const Vector4D& vec);

void print(const Vector3D& vec);
void print(const Vector4D& vec);


inline float random_float();
inline float random_float(float min, float max);

Vector3D random_unit_vector();
Vector3D random_in_unit_sphere();


