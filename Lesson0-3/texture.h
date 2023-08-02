#pragma once

#include "geometry.h"
#include "tgaimage.h"

class Texture {

private:
	TGAImage texture;
	int width;
	int height;


public:
	Texture(const char* filename);
	~Texture() {};

	TGAColor texColor(Vec2f texcoord);
};