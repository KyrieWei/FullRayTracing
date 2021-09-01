#pragma once
#include "PDF.h"
#include "../tools/Utility.h"
using namespace std;

class Mixture_PDF : public PDF
{
public:
	shared_ptr<PDF> p[2];

public:
	Mixture_PDF(shared_ptr<PDF> p0, shared_ptr<PDF> p1)
	{
		p[0] = p0;
		p[1] = p1;
	}

	virtual float value(const Vector3D& direction) const override
	{
		return 0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction);
	}

	virtual Vector3D generate() const override
	{
		if (random_float() < 0.5)
			return p[0]->generate();
		else
			return p[1]->generate();
	}
};

