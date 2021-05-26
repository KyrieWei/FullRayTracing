#pragma once
#include "PDF.h"
#include "Object.h"

class Object_PDF : public PDF
{
public:
	Vector3D o;
	shared_ptr<Object> ptr;

public:
	Object_PDF(shared_ptr<Object> p, const Vector3D& origin) : ptr(p), o(origin) {}

	virtual float value(const Vector3D& direction) const override
	{
		return ptr->pdf_value(o, direction);
	}

	virtual Vector3D generate() const override
	{
		return ptr->random(o);
	}
};

