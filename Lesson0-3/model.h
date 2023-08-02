#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int> > faces_;
	std::vector<std::vector<int> > faces_tex_;
	std::vector<Vec3f> texcoords_;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	std::vector<int> face(int idx);
	//根据面序号返回面的三个纹理序号
	std::vector<int> faceTex(int idx);
	//根据纹理坐标序号返回纹理坐标
	Vec2f texcoord(int texidx);
};

#endif //__MODEL_H__
