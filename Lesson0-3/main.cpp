#include "Lesson3.h"
#include "texture.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
Model* model = NULL;
const int width = 800;
const int height = 800;

Vec3f light_dir(0, 0, -1);

Vec3f world2screen(Vec3f v) {
	return Vec3f(int((v.x + 1.) * width / 2. + .5), int((v.y + 1.) * height / 2. + .5), v.z);
}

int main(int argc, char** argv) {
	if (2 == argc) {
		model = new Model(argv[1]);
	}
	else {
		model = new Model("obj/african_head.obj");
	}
	//初始化深度缓冲
	float* zbuffer = new float[width * height];
	for (int i = width * height; i--; zbuffer[i] = -std::numeric_limits<float>::max());

	TGAImage image(width, height, TGAImage::RGB);
	//初始化纹理
	Texture tex("obj/african_head/african_head_diffuse.tga");

	for (int i = 0; i < model->nfaces(); i++)
	{
		//面对应的顶点序号
		std::vector<int> face = model->face(i);
		//面对应的纹理序号
		std::vector<int> faceTex = model->faceTex(i);
		//顶点坐标
		Vec3f pts[3];
		//三个顶点的纹理坐标
		Vec2f ptstex[3];
		Vec3f world_coords[3];
		TGAColor vertColors[3];
		for (int j = 0; j < 3; j++)
		{
			pts[j] = world2screen(model->vert(face[j]));
			ptstex[j] = model->texcoord(faceTex[j]);
			world_coords[j] = model->vert(face[j]);

			vertColors[j] = tex.texColor(ptstex[j]);
		}
		Vec3f normal = cross(Vec3f(world_coords[2] - world_coords[0]), Vec3f(world_coords[1] - world_coords[0])).normalize();
		float intensity = normal * light_dir;

		if(intensity > 0)
			Triangle_ZBuffer::Triangle(pts, zbuffer, image, intensity, width, vertColors);
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	
	delete model;
	return 0;
}