#pragma once

#include <iostream>

#include "Rendering.h"
#include "Camera.h"
#include "Sphere.h"
#include "MovingSphere.h"
#include "Scene.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "Diffuse_light.h"
#include "XY_Rect.h"
#include "YZ_Rect.h"
#include "XZ_Rect.h"
#include "Box.h"
#include "Rotate_y.h"
#include "Translate.h"
#include "Constant_medium.h"
#include "BVHNode.h"

void initializeScene(Scene& scene)
{

	shared_ptr<Lambertian> material_first = make_shared<Lambertian>(Vector3D(0.7, 0.3, 0.3));
	shared_ptr<Metal> material_second = make_shared<Metal>(Vector3D(0.8, 0.8, 0.8), 0.3);
	shared_ptr<Dielectric> material_third = make_shared<Dielectric>(1.5);
	shared_ptr<Lambertian> material_ground = make_shared<Lambertian>(Vector3D(0.8, 0.8, 0.0));


	Sphere first_sphere(Vector3D(0.6, 0, -2), 0.5, material_first);
	Sphere second_sphere(Vector3D(-0.6, 0, -2), 0.5, material_second);
	Sphere third_sphere(Vector3D(0, -0.1, -1), 0.2, material_third);
	Sphere fourth_sphere(Vector3D(0, -0.1, -1), -0.2, material_third);
	Sphere plane(Vector3D(0, -100.5, -1), 100, material_ground);


	scene.add(make_shared<Sphere>(first_sphere));
	scene.add(make_shared<Sphere>(second_sphere));
	scene.add(make_shared<Sphere>(third_sphere));
	scene.add(make_shared<Sphere>(fourth_sphere));
	scene.add(make_shared<Sphere>(plane));

}

void RandomScene(Scene& scene)
{
	//set ground
	shared_ptr<Lambertian> ground_material = make_shared<Lambertian>(Vector3D(0.5, 0.5, 0.5));
	shared_ptr<check_texture> checker = make_shared<check_texture>(Vector3D(0.2, 0.3, 0.1), Vector3D(0.9, 0.9, 0.9));

	Sphere ground(Vector3D(0, -1000, 0), 1000, make_shared<Lambertian>(checker));
	scene.add(make_shared<Sphere>(ground));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = random_float();
			Vector3D center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

			if (length((center - Vector3D(4, 0.2, 0))) > 0.9)
			{
				shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) //diffuse
				{
					Vector3D albedo = random() * random();
					sphere_material = make_shared<Lambertian>(albedo);
					Vector3D center2 = center + Vector3D(0, random_float(0, 0.5), 0);

					scene.add(make_shared<MovingSphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) //metal
				{
					Vector3D albedo = random(0.5, 1);
					float fuzz = random_float(0, 0.5);
					sphere_material = make_shared<Metal>(albedo, fuzz);
					scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else
				{
					sphere_material = make_shared<Dielectric>(1.5);
					scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	shared_ptr<Material> material1 = make_shared<Dielectric>(1.5);
	scene.add(make_shared<Sphere>(Vector3D(0, 1, 0), 1.0, material1));

	shared_ptr<Material> material2 = make_shared<Lambertian>(Vector3D(0.4, 0.2, 0.1));
	scene.add(make_shared<Sphere>(Vector3D(-4, 1, 0), 1.0, material2));

	shared_ptr<Material> material3 = make_shared<Metal>(Vector3D(0.7, 0.6, 0.5), 0.0);
	scene.add(make_shared<Sphere>(Vector3D(4, 1, 0), 1.0, material3));

}

void two_Spheres(Scene& scene)
{
	shared_ptr<check_texture> checker = make_shared<check_texture>(Vector3D(0.2, 0.3, 0.1), Vector3D(0.9, 0.9, 0.9));

	scene.add(make_shared<Sphere>(Vector3D(0, -10, 0), 10, make_shared<Lambertian>(checker)));
	scene.add(make_shared<Sphere>(Vector3D(0, 10, 0), 10, make_shared<Lambertian>(checker)));
}

void two_Perlin_Spheres(Scene& scene)
{
	shared_ptr<noise_texture> pertext = make_shared<noise_texture>(4);
	
	scene.add(make_shared<Sphere>(Vector3D(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
	scene.add(make_shared<Sphere>(Vector3D(0, 2, 0), 2, make_shared<Lambertian>(pertext)));
}

void earth(Scene& scene)
{
	auto earth_texture = make_shared<image_texture>("textures/earthmap.jpg");
	auto earth_surface = make_shared<Lambertian>(earth_texture);
	auto globe = make_shared<Sphere>(Vector3D(0, 0, 0), 2, earth_surface);
	scene.add(globe);
}

Scene simple_light()
{
	Scene objects;

	auto pertext = make_shared<noise_texture>(4);
	objects.add(make_shared<Sphere>(Vector3D(0, -1000, 0), 1000, make_shared<Lambertian>(pertext)));
	objects.add(make_shared<Sphere>(Vector3D(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

	auto difflight = make_shared<Diffuse_light>(Vector3D(4, 4, 4));
	objects.add(make_shared<XY_Rect>(3, 5, 1, 3, -2, difflight));

	return objects;
}

Scene cornell_box()
{
	Scene objects;

	auto red = make_shared<Lambertian>(Vector3D(0.65, 0.05, 0.05));
	auto white = make_shared<Lambertian>(Vector3D(0.73, 0.73, 0.73));
	auto green = make_shared<Lambertian>(Vector3D(0.12, 0.45, 0.15));
	auto light = make_shared<Diffuse_light>(Vector3D(15, 15, 15));

	objects.add(make_shared<YZ_Rect>(0, 555, 0, 555, 555, green));
	objects.add(make_shared<YZ_Rect>(0, 555, 0, 555, 0, red));
	objects.add(make_shared<XZ_Rect>(213, 343, 227, 332, 554, light));
	objects.add(make_shared<XZ_Rect>(0, 555, 0, 555, 0, white));
	objects.add(make_shared<XZ_Rect>(0, 555, 0, 555, 555, white));
	objects.add(make_shared<XY_Rect>(0, 555, 0, 555, 555, white));

	objects.add(make_shared<Box>(Vector3D(130, 0, 65), Vector3D(295, 165, 230), white));
	objects.add(make_shared<Box>(Vector3D(265, 0, 295), Vector3D(430, 330, 460), white));

	shared_ptr<Object> box1 = make_shared<Box>(Vector3D(0, 0, 0), Vector3D(165, 330, 165), white);
	box1 = make_shared<Rotate_y>(box1, 15);
	box1 = make_shared<Translate>(box1, Vector3D(265, 0, 295));
	objects.add(box1);

	shared_ptr<Object> box2 = make_shared<Box>(Vector3D(0, 0, 0), Vector3D(165, 165, 165), white);
	box2 = make_shared<Rotate_y>(box2, -18);
	box2 = make_shared<Translate>(box2, Vector3D(130, 0, 65));
	objects.add(box2);

	return objects;
}

Scene cornell_smoke()
{
	Scene objects;

	auto red = make_shared<Lambertian>(Vector3D(.65, .05, .05));
	auto white = make_shared<Lambertian>(Vector3D(.73, .73, .73));
	auto green = make_shared<Lambertian>(Vector3D(.12, .45, .15));
	auto light = make_shared<Diffuse_light>(Vector3D(7, 7, 7));

	objects.add(make_shared<YZ_Rect>(0, 555, 0, 555, 555, green));
	objects.add(make_shared<YZ_Rect>(0, 555, 0, 555, 0, red));
	objects.add(make_shared<XZ_Rect>(113, 443, 127, 432, 554, light));
	objects.add(make_shared<XZ_Rect>(0, 555, 0, 555, 555, white));
	objects.add(make_shared<XZ_Rect>(0, 555, 0, 555, 0, white));
	objects.add(make_shared<XY_Rect>(0, 555, 0, 555, 555, white));

	shared_ptr<Object> box1 = make_shared<Box>(Vector3D(0, 0, 0), Vector3D(165, 330, 165), white);
	box1 = make_shared<Rotate_y>(box1, 15);
	box1 = make_shared<Translate>(box1, Vector3D(265, 0, 295));
	

	shared_ptr<Object> box2 = make_shared<Box>(Vector3D(0, 0, 0), Vector3D(165, 165, 165), white);
	box2 = make_shared<Rotate_y>(box2, -18);
	box2 = make_shared<Translate>(box2, Vector3D(130, 0, 65));
	
	objects.add(make_shared<Constant_medium>(box1, 0.01, Vector3D(0, 0, 0)));
	objects.add(make_shared<Constant_medium>(box2, 0.01, Vector3D(1, 1, 1)));

	return objects;
}

Scene final_scene()
{
	Scene boxes1;

	auto ground = make_shared<Lambertian>(Vector3D(0.48, 0.83, 0.53));

	const int boxes_per_side = 20;

	for (int i = 0; i < boxes_per_side; i++)
	{
		for (int j = 0; j < boxes_per_side; j++)
		{
			auto w = 100.0;
			auto x0 = -1000.0 + i * w;
			auto z0 = -1000.0 + j * w;
			auto y0 = 0.0;
			auto x1 = x0 + w;
			auto y1 = random_float(1, 101);
			auto z1 = z0 + w;

			boxes1.add(make_shared<Box>(Vector3D(x0, y0, z0), Vector3D(x1, y1, z1), ground));
		}
	}

	Scene objects;

	objects.add(make_shared<BVHNode>(boxes1, 0, 1));

	auto light = make_shared<Diffuse_light>(Vector3D(7, 7, 7));
	objects.add(make_shared<XZ_Rect>(123, 423, 147, 412, 554, light));

	auto center1 = Vector3D(400, 400, 200);
	auto center2 = center1 + Vector3D(30, 0, 0);
	auto moving_sphere_material = make_shared<Lambertian>(Vector3D(0.7, 0.3, 0.1));
	objects.add(make_shared<MovingSphere>(center1, center2, 0, 1, 50, moving_sphere_material));

	objects.add(make_shared<Sphere>(Vector3D(260, 150, 45), 50, make_shared<Dielectric>(1.5)));
	objects.add(make_shared<Sphere>(Vector3D(0, 150, 145), 50, make_shared<Metal>(Vector3D(0.8, 0.8, 0.9), 1.0)));

	auto boundary = make_shared<Sphere>(Vector3D(360, 150, 145), 70, make_shared<Dielectric>(1.5));
	objects.add(boundary);
	objects.add(make_shared<Constant_medium>(boundary, 0.2, Vector3D(0.2, 0.4, 0.9)));
	boundary = make_shared<Sphere>(Vector3D(0, 0, 0), 5000, make_shared<Dielectric>(1.5));
	objects.add(make_shared<Constant_medium>(boundary, .0001, Vector3D(1, 1, 1)));

	auto emat = make_shared<Lambertian>(make_shared<image_texture>("earthmap.jpg"));
	objects.add(make_shared<Sphere>(Vector3D(400, 200, 400), 100, emat));
	auto pertext = make_shared<noise_texture>(0.1);
	objects.add(make_shared<Sphere>(Vector3D(220, 280, 300), 80, make_shared<Lambertian>(pertext)));

	Scene boxes2;
	auto white = make_shared<Lambertian>(Vector3D(.73, .73, .73));
	int ns = 1000;
	for (int j = 0; j < ns; j++)
	{
		boxes2.add(make_shared<Sphere>(random(0, 165), 10, white));
	}

	objects.add(make_shared<Translate>(make_shared<Rotate_y>(make_shared<BVHNode>(boxes2, 0.0, 1.0), 15), Vector3D(-100, 270, 395)));

	return objects;

}

int main()
{
	const char* filename = "../result/seventeen.jpg";

	int width = 1920;
	int height = 1080;
	int channel = 4;
	int depth = 50;
	int samples_per_pixel = 50;

	Vector3D background(0, 0, 0);

	//--------------------------------------------------------------------
	//camera setting
	Vector3D camera_pos(13, 2, 3);
	Vector3D camera_lookat(0, 0, 0);
	Vector3D camera_up(0, 1, 0);
	float vfov = 45;
	float focal_dist = 10.0;
	float aspect_ratio = float(width) / height;
	float aperture = 0.1;

	//--------------------------------------------------------------------
	//scene setting
	Scene scene;

	switch (6)
	{
	case 1:
		RandomScene(scene);
		background = Vector3D(0.7, 0.8, 1.0);
		camera_pos = Vector3D(13, 2, 3);
		camera_lookat = Vector3D(0, 0, 0);
		vfov = 20.0;
		aperture = 0.1;
		break;

	case 2:
		two_Spheres(scene);
		background = Vector3D(0.7, 0.8, 1.0);
		camera_pos = Vector3D(13, 2, 3);
		camera_lookat = Vector3D(0, 0, 0);
		vfov = 20.0;
		break;

	case 3:
		two_Perlin_Spheres(scene);
		background = Vector3D(0.7, 0.8, 1.0);
		camera_pos = Vector3D(13, 2, 3);
		camera_lookat = Vector3D(0, 0, 0);
		vfov = 20.0;
		break;

	case 4:
		earth(scene);
		background = Vector3D(0.7, 0.8, 1.0);
		camera_pos = Vector3D(13, 2, 3);
		camera_lookat = Vector3D(0, 0, 0);
		vfov = 20.0;
		break;

	case 5:
		scene = simple_light();
		samples_per_pixel = 400;
		background = Vector3D(0.0, 0.0, 0.0);
		camera_pos = Vector3D(26, 3, 6);
		camera_lookat = Vector3D(0, 2, 0);
		vfov = 20.0;
		break;
	case 6:
		scene = cornell_box();
		width = 800;
		height = 800;
		aspect_ratio = width / height;
		samples_per_pixel = 200;
		background = Vector3D(0, 0, 0);
		camera_pos = Vector3D(278, 278, -800);
		camera_lookat = Vector3D(278, 278, 0);
		vfov = 40.0;
		break;

	case 7:
		scene = cornell_smoke();
		width = 800;
		height = 800;
		aspect_ratio = width / height;
		samples_per_pixel = 200;
		background = Vector3D(0, 0, 0);
		camera_pos = Vector3D(278, 278, -800);
		camera_lookat = Vector3D(278, 278, 0);
		vfov = 40.0;
		break;

	case 8:
		scene = final_scene();
		width = 800;
		height = 800;
		aspect_ratio = width / height;
		samples_per_pixel = 10000;
		background = Vector3D(0, 0, 0);
		camera_pos = Vector3D(478, 278, -600);
		camera_lookat = Vector3D(278, 278, 0);
		vfov = 40.0;
	default:
		break;
	}
	
	Camera camera(camera_pos, camera_lookat, camera_up, vfov, aspect_ratio, aperture, focal_dist, 0.0, 1.0);


	Rendering render;
	render.initialize(width, height, channel, depth, samples_per_pixel);
	render.render(filename, camera, scene, background);

	return 0;
}