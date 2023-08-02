#pragma once
//Draw Line
#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

class DrawLine
{
public:
	DrawLine();
	~DrawLine();

	static void firstAttempt(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
	static void secondAttempt(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
	static void thirdAttempt(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
	static void fourthAttempt(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
	static void fifthAttempt(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
private:

};