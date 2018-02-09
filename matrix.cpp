//matrix.cpp
#include "matrix.h"

void rotate(Point &p, const double &theta, const int &pivotX, const int &pivotY) 
{
	Point bak = p; 
	p.x = (int)pivotX + (bak.x - pivotX) * cos(theta) - (bak.y - pivotY) * sin(theta);
	p.y = (int)pivotY + (bak.x - pivotX) * sin(theta) + (bak.y - pivotY) * cos(theta);
}

void translate(Point &p, const int &tx, const int &ty) 
{
	p.x = p.x + tx;
	p.y = p.y + ty;
}

void scale(Point &p, const int &sx, const int &sy)
{
	p.x = sx * p.x;
	p.y = sy * p.y;
}