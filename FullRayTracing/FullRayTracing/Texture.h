#pragma once
#include "Vector3D.h"
#include "Perlin.h"


class Texture
{
public:
	virtual Vector3D value(float u, float v, const Vector3D& p) const = 0;
};

class solid_color : public Texture
{
public:
	Vector3D color_value;
public:
	solid_color();
	solid_color(Vector3D c) : color_value(c) {}

	solid_color(float red, float green, float blue) : solid_color(Vector3D(red, green, blue)) {}

	virtual Vector3D value(float u, float v, const Vector3D& p) const override
	{
		return color_value;
	}
};

class check_texture : public Texture
{
public:
	std::shared_ptr<Texture> even;
	std::shared_ptr<Texture> odd;

public:
	check_texture() {};

	check_texture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd) : even(_even), odd(_odd) {}
	check_texture(Vector3D c1, Vector3D c2) : even(std::make_shared<solid_color>(c1)), odd(std::make_shared<solid_color>(c2)) {}

	virtual Vector3D value(float u, float v, const Vector3D& p) const override
	{
		auto sines = sin(10 * p.x) * sin(10 * p.y) * sin(10 * p.z);
		if (sines < 0)
			return odd->value(u, v, p);
		else
			return even->value(u, v, p);
	}
};

class noise_texture : public Texture
{
public:

	Perlin noise;
	float scale;


	noise_texture() {}
	noise_texture(float sc) : scale(sc) {}

	virtual Vector3D value(float u, float v, const Vector3D& p) const override
	{
		return Vector3D(1, 1, 1) * noise.turb(scale * p);
	}
};

class image_texture : public Texture
{
public:
	const static int bytes_per_pixel = 3;

	image_texture() : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

	image_texture(const char* filename);

	~image_texture()
	{
		delete data;
	}

	virtual Vector3D value(float u, float v, const Vector3D& p) const override
	{
		if (data == nullptr)
			return Vector3D(0, 1, 1);

		u = m_clamp(u, 0.0, 1.0);
		v = 1.0 - m_clamp(v, 0.0, 1.0);

		auto i = static_cast<int>(u * width);
		auto j = static_cast<int>(v * height);

		if (i >= width) i = width - 1;
		if (j >= height) j = height - 1;

		const auto color_scale = 1.0 / 255.0;
		auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

		return Vector3D(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
	}

private:
	unsigned char* data;
	int width, height;
	int bytes_per_scanline;
};

