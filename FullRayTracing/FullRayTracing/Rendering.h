#pragma once
#include "Vector4D.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Camera.h"
#include "Ray.h"


class Rendering
{

	int width, height, channel, maxDepth;

	unsigned char* m_image;

public:
	Rendering() {};
	~Rendering()
	{
		delete[] m_image;
	}

	void initialize(int w, int h, int c = 4, int depth = 50);

	void render(const char* filename, const Camera& camera);

	void drawPixel(int x, int y, const Vector3D& color);

	Vector3D rayColor(const Ray& r);

};

void Rendering::initialize(int w, int h, int c, int depth)
{
	width = w;
	height = h;
	channel = c;
	maxDepth = depth;

	if (m_image != nullptr)
		delete[] m_image;

	m_image = new unsigned char[width * height * channel];
}

void Rendering::render(const char* filename, const Camera& camera)
{
	
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			float s = float(row) / height;
			float t = float(col) / width;
			Ray r = camera.get_ray(s, t);
			Vector3D color = rayColor(r);
			drawPixel(row, col, color);
		}
	}

	stbi_write_jpg(filename, width, height, channel, m_image, 100);

}

void Rendering::drawPixel(int row, int col, const Vector3D& color)
{
	if (row < 0 || row >= height || col < 0 || col >= width)
		return;

	unsigned int index = (row * width + col) * channel;
	m_image[index] = static_cast<unsigned char>(color.x * 255);
	m_image[index + 1] = static_cast<unsigned char>(color.y * 255);
	m_image[index + 2] = static_cast<unsigned char>(color.z * 255);
	m_image[index + 3] = static_cast<unsigned char>(255);
}

Vector3D Rendering::rayColor(const Ray& r)
{ 
	return normalize(r.direction);
}

