#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open (filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            for (int i=0;i<3;i++) iss >> v[i];
            verts_.push_back(v);
        } 
        else if (!line.compare(0, 2, "f ")) {
            std::vector<int> f;
            std::vector<int> ft;
            int itrash, idx, texidx;
            iss >> trash;
            //f x/x/x
            while (iss >> idx >> trash >> texidx >> trash >> itrash) {
                idx--; // in wavefront obj all indices start at 1, not zero
                f.push_back(idx);
                ft.push_back(texidx);
            }
            faces_.push_back(f);
            faces_tex_.push_back(ft);
        }
        else if (!line.compare(0, 3, "vt ")) {
            iss >> trash;
            iss >> trash;
            Vec3f vt;
            for (int i = 0; i < 3; i++) iss >> vt[i];
            texcoords_.push_back(vt);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
}

Model::~Model() {
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx) {
    return faces_[idx];
}

//返回一个面三个顶点对应的纹理坐标序号
std::vector<int> Model::faceTex(int idx)
{
    return faces_tex_[idx];
}

//返回对应纹理坐标序号的纹理坐标
Vec2f Model::texcoord(int texidx)
{
    return Vec2f(texcoords_[texidx - 1][0], texcoords_[texidx - 1][1]);
}



Vec3f Model::vert(int i) {
    return verts_[i];
}

