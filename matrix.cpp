//matrix.cpp
#include <cmath>
#include "primitives.h"
#include "matrix.h"

void rotate(Point & p, double theta) 
{
	Point bak = p; 
	p.x = (int) bak.x * cos(theta) - bak.y * sin(theta);
	p.y = (int) bak.x * sin(theta) + bak.y * cos(theta);
}

void translate(Point & p, int tx, int ty) 
{
	p.x = p.x + tx;
	p.y = p.y + ty;
}