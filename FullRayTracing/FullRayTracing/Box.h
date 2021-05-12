#pragma once
#include "Object.h"
#include "Scene.h"

class Box : public Object
{
public:
	Box() {}
	Box(const Vector3D& p0, const Vector3D& p1, shared_ptr<Material> ptr);

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const override;

	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override
	{
		output_box = AABB(box_min, box_max);
		return true;
	}


public:
	Vector3D box_min;
	Vector3D box_max;
	Scene sides;
};

