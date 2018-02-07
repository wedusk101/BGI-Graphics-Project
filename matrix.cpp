//matrix.cpp
#include "matrix.h"

void rotate(Point &p, const double &theta) 
{
	Point bak = p; 
	p.x = (int) bak.x * cos(theta) - bak.y * sin(theta);
	p.y = (int) bak.x * sin(theta) + bak.y * cos(theta);
}

void translate(Point &p, const int &tx, const int &ty) 
{
	p.x = p.x + tx;
	p.y = p.y + ty;
}