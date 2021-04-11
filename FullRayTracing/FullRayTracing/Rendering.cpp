#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Rendering.h"

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

void Rendering::render(const char* filename, const Camera& camera, const Scene& scene, int depth)
{

	for (int row = height - 1; row >= 0; row--)
	{
		for (int col = 0; col < width; col++)
		{
			float s = float(col) / width;
			float t = float(row) / height;

			Ray r = camera.get_ray(s, t);
			Vector3D color = rayColor(r, scene, depth);
			drawPixel(row, col, color);
		}
	}

	stbi_write_jpg(filename, width, height, channel, m_image, 100);

}

void Rendering::drawPixel(int row, int col, const Vector3D& color)
{
	if (row < 0 || row >= height || col < 0 || col >= width)
		return;

	unsigned int index = ((height - row - 1) * width + col) * channel;
	m_image[index] = static_cast<unsigned char>(color.x * 255);
	m_image[index + 1] = static_cast<unsigned char>(color.y * 255);
	m_image[index + 2] = static_cast<unsigned char>(color.z * 255);
	m_image[index + 3] = static_cast<unsigned char>(255);
}

Vector3D Rendering::rayColor(const Ray& r, const Scene& scene, int depth)
{
	hit_record rec;

	if (scene.hit(r, rec, 0.001, INFINITY))
	{
		Ray scattered;
		Vector3D attenuation; 
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * rayColor(scattered, scene, depth - 1);
		return Vector3D(0, 0, 0);
	}
	
	float t = 0.5;
	return (1.0 - t) * Vector3D(1.0, 1.0, 1.0) + t * Vector3D(0.5, 0.7, 1.0);
}
