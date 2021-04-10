#pragma once
#define _USE_MATH_DEFINES

#include "Vector3D.h"
#include "Vector4D.h"
#include <math.h>
#include <iostream>



float degrees_to_radians(float vfov);
float length_squared(const Vector3D& vec);
float length(const Vector3D& vec);

Vector3D normalize(const Vector3D& vec);
Vector3D cross(const Vector3D& u, const Vector3D& v);

float length_squared(const Vector4D& vec);

void print(const Vector3D& vec);
void print(const Vector4D& vec);


