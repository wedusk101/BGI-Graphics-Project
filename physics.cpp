#include "physics.h"

using namespace primitives;

AABB updateAABB(const Point &objPosition, const int &objWidth, const int &objHeight) // objPosition = center of the object, width = x axis, height = y axis
{
	AABB bbox;
	bbox.topLeft.x = objPosition.x - objWidth/2;
	bbox.topLeft.y = objPosition.y - objHeight/2;
	bbox.bottomRight.x = objPosition.x + objWidth/2;
	bbox.bottomRight.y = objPosition.y + objHeight/2;
	return bbox;
}

Point getPosition(Point &prevPosition, Point &currentPosition, const double &acceleration, const double &timeStep)
{
	// Verlet Integration code for calculating the next position of a particle in motion
	// acceleration is constant as we are ignoring the third order derivative of position(jerk) 
	// the velocity will be calculated using Stormer-Verlet method ---- this feature hasn't been implemented here
	Point finalPosition;
	finalPosition.x = (int)2 * currentPosition.x + acceleration * pow(timeStep, 2) - prevPosition.x;
	finalPosition.y = (int)2 * currentPosition.y + acceleration * pow(timeStep, 2) - prevPosition.y;
	prevPosition = currentPosition;
	currentPosition = finalPosition;
	return finalPosition;
}

Point getCollisionVector(const Point &collisionPosition, const Point &prevPosition, const double &stepSize, const int &xMax, const int &yMax)
{
	// returns a point along the direction of the particle's motion vector after collision 
	double dy = 0.0, dx = 0.0;
	Point nextPosition;
	dy = prevPosition.y - collisionPosition.y;
	dx = prevPosition.x - collisionPosition.x;
	if (collisionPosition.x < 0 || collisionPosition.x > xMax)
	{	// reduce the velocity and trace the following conditions to fix bugs
		if (dy == 0)
		{
			nextPosition = prevPosition;
			return nextPosition;
		}
		if (dy < 0)
		{
			nextPosition.x = prevPosition.x;
			nextPosition.y = prevPosition.y + 2 * (collisionPosition.y - prevPosition.y);
			return nextPosition;
		}
		if (dy > 0)
		{
			nextPosition.x = prevPosition.x;
			nextPosition.y = prevPosition.y - 2 * (prevPosition.y - collisionPosition.y);
			return nextPosition;
		}
	}
	if (collisionPosition.y < 0 || collisionPosition.y > yMax)
	{
		if (dx == 0)
		{
			nextPosition = prevPosition;
			return nextPosition;
		}
		if (dx < 0)
		{
			nextPosition.x = prevPosition.x + 2 * (collisionPosition.x - prevPosition.x);
			nextPosition.y = prevPosition.y;
			return nextPosition;
		}
		if (dx > 0)
		{
			nextPosition.x = prevPosition.x - 2 * (prevPosition.x - collisionPosition.x);
			nextPosition.y = prevPosition.y;
			return nextPosition;
		}
	}
}