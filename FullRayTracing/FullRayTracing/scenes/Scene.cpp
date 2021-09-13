#include "Scene.h"
#include "../shapes/Sphere.h"
#include "../shapes/Box.h"
#include "../shapes/XZ_Rect.h"
#include "../shapes/YZ_Rect.h"
#include "../shapes/XY_Rect.h"
#include "../shapes/Rotate_y.h"
#include "../shapes/Translate.h"

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
	
	std::shared_ptr<Lambertian> sphere_mat(make_shared<Lambertian>(Vector3D(1.0, 0.0, 0.0)));
	
	std::shared_ptr<Lambertian> red_mat(make_shared<Lambertian>(Vector3D(0.65, 0.05, 0.05)));
	std::shared_ptr<Lambertian> green_mat(make_shared<Lambertian>(Vector3D(0.12, 0.45, 0.15)));
	std::shared_ptr<Lambertian> white_mat(make_shared<Lambertian>(Vector3D(0.73, 0.73, 0.73)));
	std::shared_ptr<Lambertian> box_mat(make_shared<Lambertian>(Vector3D(0.9, 0.3, 0.6)));

	std::shared_ptr<Object> box = make_shared<Box>(Vector3D(0.0, 0.0, 0.0), Vector3D(165, 330, 165), box_mat);
	box = make_shared<Rotate_y>(box, 30);
	box = make_shared<Translate>(box, Vector3D(265, 0, 295));

	std::shared_ptr<Object> first_sphere = make_shared<Sphere>(Vector3D(190, 90, 190), 90.0, sphere_mat);
	
	this->add(box);
	this->add(first_sphere);

	this->add(make_shared<YZ_Rect>(0, 555, 0, 555, 555, green_mat));
	this->add(make_shared<YZ_Rect>(0, 555, 0, 555, 0, red_mat));
	this->add(make_shared<XZ_Rect>(0, 555, 0, 555, 555, white_mat));
	this->add(make_shared<XZ_Rect>(0, 555, 0, 555, 0, white_mat));
	this->add(make_shared<XY_Rect>(0, 555, 0, 555, 555, white_mat));

}

