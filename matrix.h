//matrix.h
#ifndef MATRIX__H_
#define MATRIX__H_

#include <cmath>
#include "primitives.h"

namespace primitives
{
	void rotate(Point &, const double &, const int &, const int &); // rotates a ray about a given pivot by an angle of theta radians
	void translate(Point &, const int &, const int &); // translates a point P(x,y) by tx and ty 
	void scale(Point &, const int &, const int &); // scales a point P(x,y) by sx and sy

	Point getTranslatedPoint(const Point &, const int &, const int &); // returns a point P(x,y) translated by tx and ty
}

#endif