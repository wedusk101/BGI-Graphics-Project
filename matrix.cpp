//matrix.cpp
#include <cmath>
#include "primitives.h"
#include "matrix.h"

void rotate(Point & p, double theta)
{
	p.x = (int) p.x * cos(theta) - p.y * sin(theta);
	p.y = (int) p.x * sin(theta) + p.y * cos(theta);
}

void translate(Point & p, int tx, int ty)
{
	p.x = p.x + tx;
	p.y = p.y + ty;
}