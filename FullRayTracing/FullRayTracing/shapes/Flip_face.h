#pragma once
#include "Object.h"

class Flip_face : public Object 
{
public:
	shared_ptr<Object> ptr;

public:
	Flip_face(shared_ptr<Object> p) : ptr(p) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override
	{
		if (!ptr->hit(r, rec, t_min, t_max))
			return false;

		rec.front_face = !rec.front_face;
		return true;
	}

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override
	{
		return ptr->bounding_box(time0, time1, output_box);
	}
};

