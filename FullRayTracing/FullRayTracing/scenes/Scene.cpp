#include "Scene.h"

bool Scene::hit(const Ray& r, hit_record& rec, float t_min, float t_max) const
{
	hit_record temp_rec;
	float closet_so_far = t_max;
	bool hit_anything = false;

	for (const shared_ptr<Object>& obj : objects)
	{
		if (obj->hit(r, temp_rec, t_min, closet_so_far))
		{
			hit_anything = true;
			closet_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

bool Scene::bounding_box(float time0, float time1, AABB& output_box) const
{
	if (objects.empty()) return false;

	AABB temp_box;
	bool first_box = true;

	for (const auto& object : objects)
	{
		if (!object->bounding_box(time0, time1, temp_box)) return false;
		output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
		first_box = false;
	}

	return true;
}

void Scene::initializeScene()
{
	
	std::shared_ptr<Lambertian> sphere_mat(make_shared<Lambertian>(Vector3D(0.5, 0.3, 0.9)));
	Sphere first_sphere(Vector3D(0, 0, -2), 1.0, sphere_mat);

	this->add(make_shared<Sphere>(first_sphere));
}

