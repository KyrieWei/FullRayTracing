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