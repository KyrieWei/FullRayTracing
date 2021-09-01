#pragma once
#include "PDF.h"
#include "../core/ONB.h"
#include "../tools/Utility.h"

class Cosine_pdf : public PDF
{
public:
	ONB uvw;

	Cosine_pdf(const Vector3D& w) { uvw.build_from_w(w); }

	virtual float value(const Vector3D& direction) const override
	{
		auto cosine = dot(unit_vector(direction), uvw.w());
		return (cosine <= 0) ? 0 : cosine / M_PI;
	}

	virtual Vector3D generate() const override
	{
		return uvw.local(random_cosine_direction());
	}
};

