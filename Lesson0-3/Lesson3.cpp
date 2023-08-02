#include "Lesson3.h"

void Triangle_ZBuffer::Triangle(Vec3f* pts, float* zbuffer, TGAImage& image, float intensity, int width, TGAColor* vertColors)
{
	Vec2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	Vec2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
	Vec2f clamp(image.get_width() - 1, image.get_height() - 1);
	//�ҵ�bounding box�Ĵ�С
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++) {
			bboxmin[j] = std::max(0.f, std::min(bboxmin[j], pts[i][j]));
			bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], pts[i][j]));
		}
	}

	//����ж�bbox�е������Ƿ�����������
	Vec3f p;
	for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++)
	{
		for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++)
		{
			//p����������
			Vec3f bc_screen = barycentric(pts, p);
			//������������
			if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) continue;
			p.z = 0;
			TGAColor curColor(0, 0, 0, 255);
			int count = 0;
			//��ֵ����p����Ⱥ���ɫ
			for (int i = 0; i < 3; i++)
			{
				p.z += pts[i][2] * bc_screen[i];
				curColor = curColor + vertColors[i] * bc_screen[i];

			}

			//���ֵ���ڵ�ǰ����ֵ
			if (zbuffer[int(p.x + p.y * width)] < p.z)
			{
				zbuffer[int(p.x + p.y * width)] = p.z;
				image.set(p.x, p.y, curColor * intensity);
			}
		}
	}
}

Vec3f Triangle_ZBuffer::barycentric(Vec3f* pts, Vec3f p)
{
	Vec3f s[2];
	for (int i = 2; i--; ) {
		s[i][0] = pts[2][i] - pts[0][i];//AC
		s[i][1] = pts[1][i] - pts[0][i];//AB
		s[i][2] = pts[0][i] - p[i];//PA
	}
	//AC AB�����(w2,w3,1)
	Vec3f u = cross(s[0], s[1]);
	if (std::abs(u[2]) > 1e-2) // dont forget that u[2] is integer. If it is zero then triangle ABC is degenerate
		return Vec3f(1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z);
	return Vec3f(-1, 1, 1); // in this case generate negative coordinates, it will be thrown away by the rasterizator

}
