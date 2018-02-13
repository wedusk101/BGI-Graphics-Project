//matrix.h
#ifndef MATRIX__H_
#define MATRIX__H_

#include <cmath>
#include "primitives.h"

namespace primitives
{
	void rotateRay(Point &, const double &, const int &, const int &); // rotates a ray about a given pivot by an angle of theta radians
	void translatePoint(Point &, const int &, const int &); // translates a point P(x,y) by tx and ty 
	void scaleRay(Point &, const int &, const int &); // scales a point P(x,y) by sx and sy

	Point getTranslatedPoint(const Point &, const int &, const int &); // returns a point P(x,y) translated by tx and ty
	Point getRotatedRay(const Point &, const double &, const int &, const int &); // returns a ray rotated about a given pivot by an angle of theta radians
}

#endif