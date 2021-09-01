#pragma once
#include "Ray.h"
#include "../maths/Vector3D.h"
#include "../tools/Utility.h"
#include "../accelerators/AABB.h"
#include <memory>

using std::shared_ptr;

class Material;

struct hit_record
{
	Vector3D pos;
	Vector3D normal;
	float t;

	//uv coordinate
	float u;
	float v;

	bool front_face;

	shared_ptr<Material> mat_ptr;

	inline void set_face_normal(const Ray& r, const Vector3D& outward_normal)
	{
		front_face = dot(r.direction, outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}

};

class Object
{
public:
	virtual bool hit(const Ray& r, hit_record& rec, float t_min, float t_max) const = 0;
	virtual bool bounding_box(float time0, float time1, AABB& output_box) const = 0;
	virtual float pdf_value(const Vector3D& o, const Vector3D& v) const
	{
		return 0.0;
	}

	virtual Vector3D random(const Vector3D& o) const
	{
		return Vector3D(1, 0, 0);
	}
};

