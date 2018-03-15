//physics.h
#pragma once

#ifndef PHYSICS__H_
#define PHYSICS__H_

#include <cmath>
#include "primitives.h"
#include "assets.h"

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
		Point center;
		int faceID;	// Object AABB collision faces -  1 = bottom face, 2 = right face, 3 = top face, 4 = left face
	} AABB; // Axis Aligned Bounding Box required for physics calculations

	Point getNextPositionVerlet(Point &, Point &, const double &, const double &, double &);
	Point getCollisionVector(const Point &, const Point &, const double &, const int &, const int &, const int &);
	AABB updateAABB(const Point&, const int&, const int&);

	bool collideCircleScreen(Circle &, AABB &, const AABB &, const double &, const int &, const int &, Point &, Point &, const double &, double &);
	bool collideCircleRectangle(Circle &, Rectangle &, AABB &, const AABB &, AABB &, const AABB &, const double &, const int &, const int &, Point &, Point &, const double &, double &);
	bool collideCircleLine(Point &, Circle &, Line &, AABB &, const double &, const int &, const int &, Point &, Point &, const double &, double &);

	bool fastCollideCircleLine(Point &, Circle &, Line &, AABB &, const double &, const int &, const int &, Point &, Point &, const double &, double &);

	bool collideBowScreen(const Bow &, const Bow &, Point &, Point &, Point &, const int &, const int &, const double &, const double &, double &);
	
}

inline double getEuclideanDistance(const int &x1, const int &y1, const int &x2, const int &y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); // returns the euclidean distance between two points
}

#endif