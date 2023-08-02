#pragma once
#include <vector>
#include <cmath>
#include <cstdlib>
#include <limits>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

class Triangle_ZBuffer
{
public:
	static void Triangle(Vec3f* pts, float* zbuffer, TGAImage& image, float intensity, int width, TGAColor* vertColors);

private:

	static Vec3f barycentric(Vec3f* pts, Vec3f p);
};