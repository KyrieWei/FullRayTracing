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

int main()
{
	const char* filename = "../result/thirteen.jpg";

	const int width = 640;
	const int height = 480;
	const int channel = 4;
	const int depth = 50;
	const int samples_per_pixel = 50;

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

	switch (2)
	{
	case 1:
		RandomScene(scene);
		camera_pos = Vector3D(13, 2, 3);
		camera_lookat = Vector3D(0, 0, 0);
		vfov = 20.0;
		aperture = 0.1;
		break;

	case 2:
		two_Spheres(scene);
		camera_pos = Vector3D(13, 2, 3);
		camera_lookat = Vector3D(0, 0, 0);
		vfov = 20.0;
		break;

	case 3:
		two_Perlin_Spheres(scene);
		camera_pos = Vector3D(13, 2, 3);
		camera_lookat = Vector3D(0, 0, 0);
		vfov = 20.0;
		break;

	default:
		break;
	}
	
	Camera camera(camera_pos, camera_lookat, camera_up, vfov, aspect_ratio, aperture, focal_dist, 0.0, 1.0);


	Rendering render;
	render.initialize(width, height, channel, depth, samples_per_pixel);
	render.render(filename, camera, scene);

	return 0;
}