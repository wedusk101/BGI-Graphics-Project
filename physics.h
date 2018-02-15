//physics.h
#ifndef PHYSICS__H_
#define PHYSICS__H_

#include <cmath>
#include "primitives.h"

namespace primitives
{
	typedef struct
	{
		Point topLeft;
		Point topRight;
		Point bottomleft;
		Point bottomRight;
		Point topMid;
		Point bottomMid;
		Point leftMid;
		Point rightMid;
	} AABB; // Axis Aligned Bounding Box required for physics calculations

	Point getNextPositionVerlet(Point &, Point &, const double &, const double &, double &);
	Point getCollisionVector(const Point &, const Point &, const double &, const int &, const int &);
	AABB updateAABB(const Point&, const int&, const int&);
}

inline double getEuclideanDistance(const int &x1, const int &y1, const int &x2, const int &y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); // returns the euclidean distance between two points
}

#endif