#pragma once
#include "Ray.h"
#include "Vector3D.h"
#include "Utility.h"
#include "Material.h"
#include "AABB.h"
#include <memory>

using std::shared_ptr;

class Material;

struct hit_record
{
	Vector3D pos;
	Vector3D normal;
	float t;
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
};

