//matrix.h
#pragma once

#ifndef MATRIX__H_
#define MATRIX__H_

#include <cmath>
#include "primitives.h"

namespace bgilib
{
	void rotateRay(Point &, const double &, const int &, const int &); // rotates a ray about a given pivot by an angle of theta radians
	void translatePoint(Point &, const int &, const int &); // translates a point P(x,y) by tx and ty 
	void scaleRay(Point &, const int &, const int &); // scales a point P(x,y) by sx and sy
	void shearRay(Point &, const int &, const int &); // shears a point P(x,y) by shX and shY

	Point getTranslatedPoint(const Point &, const int &, const int &); // returns a point P(x,y) translated by tx and ty
	Point getRotatedPoint(const Point &, const double &, const int &, const int &); // rotates a ray about a given pivot by an angle of theta radians
}

#endif