#include "texture.h"

//读取纹理图片
Texture::Texture(const char* filename)
{
	texture.read_tga_file(filename);
	texture.flip_vertically();
	width = texture.get_width();
	height = texture.get_height();
}

//返回纹理颜色
TGAColor Texture:: texColor(Vec2f texcoord)
{
	return texture.get(int(texcoord.x * (width)), int(texcoord.y * (height)));
}
