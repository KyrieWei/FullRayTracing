#pragma once
#include "Vector3D.h"

class PDF
{
public:
	virtual ~PDF() {}

	virtual float value(const Vector3D& direction) const = 0;
	virtual Vector3D generate() const = 0;
};

