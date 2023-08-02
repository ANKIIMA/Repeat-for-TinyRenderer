#include "texture.h"

//��ȡ����ͼƬ
Texture::Texture(const char* filename)
{
	texture.read_tga_file(filename);
	texture.flip_vertically();
	width = texture.get_width();
	height = texture.get_height();
}

//����������ɫ
TGAColor Texture:: texColor(Vec2f texcoord)
{
	return texture.get(int(texcoord.x * (width)), int(texcoord.y * (height)));
}
