//Draw Triangles
#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

class Triangle
{
public:

	static void old_DrawTriangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color);
	static void new_DrawTriangle(Vec2i* pts, TGAImage& image, TGAColor color);

private:

	static Vec3f barycentric(Vec2i* pts, Vec2i p);

};