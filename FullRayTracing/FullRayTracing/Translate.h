#pragma once
#include "Object.h"

class Translate : public Object
{
public:
	shared_ptr<Object> ptr;
	Vector3D offset;

public:
	Translate(shared_ptr<Object> p, const Vector3D& displacement) : ptr(p), offset(displacement) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;

};

