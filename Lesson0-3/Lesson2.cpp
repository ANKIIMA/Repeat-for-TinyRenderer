#include "Lesson2.h"
#include "Lession1.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);

void Triangle::old_DrawTriangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage& image, TGAColor color)
{
	if (t0.y == t1.y && t0.y == t2.y) return; // I dont care about degenerate triangles 
	if (t0.y > t1.y) std::swap(t0, t1);
	if (t0.y > t2.y) std::swap(t0, t2);
	if (t1.y > t2.y) std::swap(t1, t2);

	int height = t2.y - t0.y;
	for (int i = 0; i < height; i++)
	{
		bool second_half = i >= t1.y - t0.y;
		int currentHeight = second_half ? t2.y - t1.y : t1.y - t0.y;

		//alpha:t0-t2
		//beta:second_half时，i应减去第一段高度并除以第二段的高度
		float alpha = (float)i / height;
		float beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / currentHeight;
		Vec2i A = t0 + (t2 - t0) * alpha;
		Vec2i B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;

		if (A.x > B.x)
		{
			std::swap(A, B);
		}

		for (int j = A.x; j <= B.x; j++)
		{
			image.set(j, t0.y + i, color);
		}
	}

}

void Triangle::new_DrawTriangle(Vec2i* pts, TGAImage& image, TGAColor color)
{
	Vec2i bboxmin(image.get_width() - 1, image.get_height() - 1);
	Vec2i bboxmax(0, 0);
	Vec2i clamp(image.get_width() - 1, image.get_height() - 1);
	//找到bounding box的大小
	for (int i = 0; i < 3; i++)
	{
		bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
		bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));

		bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
		bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
	}

	//逐个判断bbox中的像素是否在三角形中
	Vec2i p;
	for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++)
	{
		for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++)
		{
			Vec3f bc_screen = barycentric(pts, p);
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
			image.set(p.x, p.y, color);
		}
	}

}

Vec3f Triangle::barycentric(Vec2i* pts, Vec2i p)
{
	int ABx = (pts[1].x - pts[0].x);
	int ABy = (pts[1].y - pts[0].y);
	int ACx = (pts[2].x - pts[0].x);
	int ACy = (pts[2].y - pts[0].y);
	int PAx = (pts[0].x - p.x);
	int PAy = (pts[0].y - p.y);

	Vec3f s1 = Vec3f(ABx, ACx, PAx);
	Vec3f s2 = Vec3f(ABy, ACy, PAy);

	Vec3f u = cross(s1, s2);
	//z小于1即z=0，此时三角形退化，AB AC在一条直线上
	if (std::abs(u.z) < 1) return Vec3f(-1, 1, 1);

	return Vec3f(1.f - (u.x + u.y) / u.z, u.x / u.z, u.y / u.z);

}


