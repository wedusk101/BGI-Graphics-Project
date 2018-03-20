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

	struct Acceleration
	{
		double x;
		double y;

		Acceleration() : x(0), y(0) {}
		Acceleration(const double &x_, const double &y_) : x(x_), y(y_) {}
	};

	Point getNextPositionVerlet(Point &, Point &, Acceleration &, const double &, double &);
	Point getCollisionVector(const Point &, const Point &, const double &, const int &, const int &, const int &);
	AABB updateAABB(const Point&, const int&, const int&);

	int sign(const double &);

	bool collideCircleScreen(Circle &, AABB &, const AABB &, const double &, const int &, const int &, Point &, Point &, Acceleration &, double &);
	bool collideCircleRectangle(Circle &, Rectangle &, AABB &, const AABB &, AABB &, const AABB &, const double &, const int &, const int &, Point &, Point &, Acceleration &, double &);
	bool collideCircleLine(Point &, Point &, Circle &, Line &, AABB &, const double &, const int &, const int &, Acceleration &, double &);

	bool collideBowScreen(const Bow &, const Bow &, Point &, Point &, Point &, const int &, const int &, Acceleration &, const double &, double &);
	bool collideCircleScreenPong(Circle &, AABB &, const AABB &, const double &, const int &, const int &, Point &, Point &, Acceleration &, double &);

}

inline double getEuclideanDistance(const int &x1, const int &y1, const int &x2, const int &y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)); // returns the euclidean distance between two points
}

#endif