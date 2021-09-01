#pragma once
#include "Object.h"

class MovingSphere : public Object
{
public:
	Vector3D center0, center1;
	float time0, time1;
	float radius;
	shared_ptr<Material> mat_ptr;

	MovingSphere() {}
	MovingSphere(Vector3D cen0, Vector3D cen1, float _time0, float _time1, float r, shared_ptr<Material> m) :
		center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m) {}

	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max ) const override;
	virtual bool bounding_box(float time0, float time1, AABB& output_box) const override;

	Vector3D center(float time) const;
};

