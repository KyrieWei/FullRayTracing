#pragma once

#include <iostream>

#include "Rendering.h"
#include "Camera.h"
#include "Sphere.h"
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
	Sphere third_sphere(Vector3D(0, -0.3, -1), 0.2, material_third);
	Sphere plane(Vector3D(0, -100.5, -1), 100, material_ground);


	scene.add(make_shared<Sphere>(first_sphere));
	scene.add(make_shared<Sphere>(second_sphere));
	scene.add(make_shared<Sphere>(third_sphere));
	scene.add(make_shared<Sphere>(plane));

}

int main()
{
	const char* filename = "../result/seven.jpg";

	const int width = 1280;
	const int height = 720;
	const int channel = 4;
	const int depth = 50;
	const int samples_per_pixel = 50;

	//--------------------------------------------------------------------
	//camera setting
	Vector3D camera_pos(13, 2, 3);
	Vector3D camera_lookat(0, 0, 0);
	Vector3D camera_up(0, 1, 0);
	float vfov = 45;
	float focal_dist = 1.0;
	float aspect_ratio = float(width) / height;

	Camera camera(camera_pos, camera_lookat, camera_up, vfov, aspect_ratio, focal_dist);

	//--------------------------------------------------------------------
	//scene setting
	Scene scene;
	initializeScene(scene);



	Rendering render;
	render.initialize(width, height, channel, depth, samples_per_pixel);
	render.render(filename, camera, scene);

	return 0;
}