//physics.h
#ifndef PHYSICS__H_
#define PHYSICS__H_

#include <cmath>
#include "primitives.h"

Point getPosition(Point &prevPosition, Point &currentPosition, const double &initialVelocity, const double &acceleration, const double &timeStep);
Point getReflectionVector(const Point &collisionPosition, const Point &prevPosition, const double &stepSize, const int &xMax, const int &yMax);

inline double getEuclideanDistance(const int &x1, const int &y1, const int &x2, const int &y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); // returns the euclidean distance between two points
}

#endif