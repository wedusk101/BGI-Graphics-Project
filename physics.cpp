//physics.cpp
#include "physics.h"
#include "matrix.h"

namespace primitives
{

	AABB updateAABB(const Point &objPosition, const int &objWidth, const int &objHeight) // objPosition = center of the object, width = x axis, height = y axis
	{
		AABB bbox;
		bbox.topLeft.x = objPosition.x - objWidth/2;
		bbox.topLeft.y = objPosition.y - objHeight/2;
		bbox.bottomRight.x = objPosition.x + objWidth/2;
		bbox.bottomRight.y = objPosition.y + objHeight/2;
		bbox.bottomleft.x = bbox.bottomRight.x - objWidth;
		bbox.bottomleft.y = bbox.bottomRight.y;
		bbox.topRight.x = bbox.topLeft.x + objWidth;
		bbox.topRight.y = bbox.topLeft.y;
		bbox.topMid.x = (bbox.topLeft.x + bbox.topRight.x) / 2;
		bbox.topMid.y = bbox.topLeft.y;
		bbox.bottomMid.x = (bbox.bottomleft.x + bbox.bottomRight.x) / 2;
		bbox.bottomMid.y = bbox.bottomRight.y;
		bbox.leftMid.x = bbox.topLeft.x;
		bbox.leftMid.y = (bbox.topLeft.y + bbox.bottomleft.y) / 2;
		bbox.rightMid.x = bbox.bottomRight.x;
		bbox.rightMid.y = (bbox.topRight.y + bbox.bottomRight.y) / 2;
		return bbox;
	}

	Point getNextPositionVerlet(Point &prevPosition, Point &currentPosition, const double &acceleration, const double &timeStep, double &theta)
	{
		// Verlet Integration code for calculating the next position of a particle in motion
		// acceleration is constant as we are ignoring the third order derivative of position(jerk) 
		// the velocity will be calculated using Stormer-Verlet method ---- this feature hasn't been implemented here
		double dy = 0.0, dx = 0.0;
		Point finalPosition;
		dy = prevPosition.y - currentPosition.y;
		dx = prevPosition.x - currentPosition.x;
		theta = atan2(dy, dx);
		finalPosition.x = (int) round(2 * currentPosition.x + acceleration *  pow(timeStep, 2) - prevPosition.x); // cos(theta)
		finalPosition.y = (int) round(2 * currentPosition.y + acceleration * pow(timeStep, 2) - prevPosition.y); //  sin(theta)
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

		// object collides with the screen

		if (dy == dx || dy == -dx) // screen corners
		{
			nextPosition = prevPosition;
			return nextPosition;
		}

		if (collisionPosition.x <= 0 || collisionPosition.x >= xMax) // screen edges
		{	// reduce the velocity and trace the following conditions to fix bugs
			if (dy == 0) // object moving parallel to x axis
			{
				nextPosition = prevPosition;
				return nextPosition;
			}
			if (dy < 0) // object moving towards yMax
			{
				nextPosition.x = prevPosition.x;
				nextPosition.y = prevPosition.y + 2 * (collisionPosition.y - prevPosition.y);
				return nextPosition;
			}
			if (dy > 0) // object moving towards yMin
			{
				nextPosition.x = prevPosition.x;
				nextPosition.y = prevPosition.y - 2 * (prevPosition.y - collisionPosition.y);
				return nextPosition;
			}
		}

		if (collisionPosition.y <= 0 || collisionPosition.y >= yMax) // screen edges
		{
			if (dx == 0) // object moving parallel to y axis
			{
				nextPosition = prevPosition;
				return nextPosition;
			}
			if (dx < 0) // object moving towards xMax
			{
				nextPosition.x = prevPosition.x + 2 * (collisionPosition.x - prevPosition.x);
				nextPosition.y = prevPosition.y;
				return nextPosition;
			}
			if (dx > 0) // object moving towards xMin
			{
				nextPosition.x = prevPosition.x - 2 * (prevPosition.x - collisionPosition.x);
				nextPosition.y = prevPosition.y;
				return nextPosition;
			}
		}

		// object collides with other objects

		if (dy == 0 || dx == 0) // object moving parallel to x axis
		{
			nextPosition = prevPosition;
			return nextPosition;
		}

		if (dy < 0) // object moving towards yMax
		{
			nextPosition.x = prevPosition.x;
			nextPosition.y = prevPosition.y + 2 * (collisionPosition.y - prevPosition.y);
			return nextPosition;
		}

		if (dy > 0) // object moving towards yMin
		{
			nextPosition.x = prevPosition.x;
			nextPosition.y = prevPosition.y - 2 * (prevPosition.y - collisionPosition.y);
			return nextPosition;
		}

		if (dx < 0) // object moving towards xMax
		{
			nextPosition.x = prevPosition.x + 2 * (collisionPosition.x - prevPosition.x);
			nextPosition.y = prevPosition.y;
			return nextPosition;
		}

		if (dx > 0) // object moving towards xMin
		{
			nextPosition.x = prevPosition.x - 2 * (prevPosition.x - collisionPosition.x);
			nextPosition.y = prevPosition.y;
			return nextPosition;
		}
	}

	bool collideCircleScreen(Circle &circle, const AABB &circleBB, const AABB &circlePrevBB, const double & stepSize, const int &xMax, const int &yMax, Point &locus, Point &nextPoint, const double &acceleration, double &theta)
	{
		if (circleBB.topLeft.x <= 0) // left side of the AABB collides
		{
			nextPoint = getCollisionVector(circleBB.leftMid, circlePrevBB.leftMid, stepSize, xMax, yMax);
			translatePoint(nextPoint, circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.leftMid, circle.radius, 0);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}

		if (circleBB.topLeft.y <= 0) // top side of the AABB collides
		{
			nextPoint = getCollisionVector(circleBB.topMid, circlePrevBB.topMid, stepSize, xMax, yMax);
			translatePoint(nextPoint, 0, circle.radius);
			circle.center = getTranslatedPoint(circleBB.topMid, 0, circle.radius);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}

		if (circleBB.bottomRight.x >= xMax) // right side of the AABB collides
		{
			nextPoint = getCollisionVector(circleBB.rightMid, circlePrevBB.rightMid, stepSize, xMax, yMax);
			translatePoint(nextPoint, -circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.rightMid, -circle.radius, 0);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}

		if (circleBB.bottomRight.y >= yMax) // bottom side of the AABB collides
		{
			nextPoint = getCollisionVector(circleBB.bottomMid, circlePrevBB.bottomMid, stepSize, xMax, yMax);
			translatePoint(nextPoint, 0, -circle.radius);
			circle.center = getTranslatedPoint(circleBB.bottomMid, 0, -circle.radius);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}
		return false;
	}

	bool collideCircleRectangle(Circle &circle, Rectangle &rectangle, const AABB &circleBB, const AABB &circlePrevBB, const AABB &rectangleBB, const AABB &rectanglePrevBB, const double & stepSize, const int &xMax, const int &yMax, Point &circleLocus, Point &circleNextPoint, const double &acceleration, double &theta)
	{
		if (circleBB.topLeft.x <= rectangleBB.bottomRight.x && circleBB.bottomRight.x >= rectangleBB.bottomRight.x) // left side of the circle AABB collides with the right side of the rectangle AABB
		{			
			circleNextPoint = getCollisionVector(circleBB.leftMid, circlePrevBB.leftMid, stepSize, xMax, yMax);
			translatePoint(circleNextPoint, circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.leftMid, circle.radius, 0);
			circleLocus = getNextPositionVerlet(circle.center, circleNextPoint, acceleration, stepSize, theta);
			return true;
		}

		if(circleBB.topLeft.y <= rectangleBB.bottomRight.y && circleBB.bottomRight.y >= rectangleBB.bottomRight.y) // top side of the circle AABB collides with the bottom side of the rectangle AABB
		{
			circleNextPoint = getCollisionVector(circleBB.topMid, circlePrevBB.topMid, stepSize, xMax, yMax);
			translatePoint(circleNextPoint, 0, circle.radius);
			circle.center = getTranslatedPoint(circleBB.topMid, 0, circle.radius);
			circleLocus = getNextPositionVerlet(circle.center, circleNextPoint, acceleration, stepSize, theta);
			return true;
		}

		/*if (circleBB.bottomRight.x >= rectangleBB.topLeft.x) // right side of the circle AABB collides with the left side of the rectangle AABB
		{
			circleNextPoint = getCollisionVector(circleBB.rightMid, circlePrevBB.rightMid, stepSize, xMax, yMax);
			translatePoint(circleNextPoint, -circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.rightMid, -circle.radius, 0);
			circleLocus = getNextPositionVerlet(circle.center, circleNextPoint, acceleration, stepSize, theta);
			return true;
		}*/

		/*if (circleBB.bottomRight.y >= rectangleBB.topLeft.y) // bottom side of the circle AABB collides with the top side of the rectangle AABB
		{
			circleNextPoint = getCollisionVector(circleBB.bottomMid, circlePrevBB.bottomMid, stepSize, xMax, yMax);
			translatePoint(circleNextPoint, 0, -circle.radius);
			circle.center = getTranslatedPoint(circleBB.bottomMid, 0, -circle.radius);
			circleLocus = getNextPositionVerlet(circle.center, circleNextPoint, acceleration, stepSize, theta);
			return true;
		}*/
		return false;
	}
}