#pragma once

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

#include "scenes/Scene.h"
#include "systems/Rendering.h"

int main()
{
	const char* filename = "../pbrt/three.jpg";

	int width = 600;
	int height = 600;
	int channel = 4;
	int depth = 50;
	int samples_per_pixel = 50;

	Vector3D background(0.6, 0.8, 0.9);

	//--------------------------------------------------------------------
	//camera setting
	Vector3D camera_pos(278, 278, -800);
	Vector3D camera_lookat(278, 278, 0);
	Vector3D camera_up(0, 1, 0);
	float vfov = 40;
	float focal_dist = 10.0;
	float aspect_ratio = float(width) / height;
	float aperture = 0.1;

	//--------------------------------------------------------------------
	//scene setting
	Scene scene;
	scene.initializeScene();

	std::shared_ptr<Object> lights;
	
	Camera camera(camera_pos, camera_lookat, camera_up, vfov, aspect_ratio, aperture, focal_dist, 0.0, 1.0);


	Rendering render;
	render.initialize(width, height, channel, depth, samples_per_pixel);
	render.render(filename, camera, scene, lights, background);

	return 0;
}