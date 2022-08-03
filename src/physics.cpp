//physics.cpp
#include "physics.h"
#include "matrix.h"
#include "vector.h"
#include <iostream> // debugging


namespace bgilib
{

	AABB updateAABB(const Point &objPosition, const int &objWidth, const int &objHeight) // objPosition = center of the object, width = x axis, height = y axis
	{
		AABB bbox;
		bbox.topLeft.x = objPosition.x - objWidth/2;
		bbox.topLeft.y = objPosition.y - objHeight/2;
		bbox.bottomRight.x = objPosition.x + objWidth/2;
		bbox.bottomRight.y = objPosition.y + objHeight/2;
		bbox.bottomLeft.x = bbox.bottomRight.x - objWidth;
		bbox.bottomLeft.y = bbox.bottomRight.y;
		bbox.topRight.x = bbox.topLeft.x + objWidth;
		bbox.topRight.y = bbox.topLeft.y;
		bbox.topMid.x = (bbox.topLeft.x + bbox.topRight.x) / 2;
		bbox.topMid.y = bbox.topLeft.y;
		bbox.bottomMid.x = (bbox.bottomLeft.x + bbox.bottomRight.x) / 2;
		bbox.bottomMid.y = bbox.bottomRight.y;
		bbox.leftMid.x = bbox.topLeft.x;
		bbox.leftMid.y = (bbox.topLeft.y + bbox.bottomLeft.y) / 2;
		bbox.rightMid.x = bbox.bottomRight.x;
		bbox.rightMid.y = (bbox.topRight.y + bbox.bottomRight.y) / 2;
		bbox.center.x = (bbox.topLeft.x + bbox.bottomRight.x) / 2;
		bbox.center.y = (bbox.topLeft.y + bbox.bottomRight.y) / 2;
		return bbox;
	}

	int sign(const double &val)
	{
		if (val < 0)
			return -1;
		else if (val > 0)
			return 1;
		else
			return 0;
	}

	Point getNextPositionVerlet(Point &prevPosition, Point &currentPosition, Acceleration &acceleration, const double &timeStep, double &theta)
	{
		// Verlet Integration code for calculating the next position of a particle in motion
		// acceleration is constant as we are ignoring the third order derivative of position(jerk)
		// the velocity will be calculated using Stormer-Verlet method ---- this feature hasn't been implemented here
		double dy = 0.0, dx = 0.0;
		Point finalPosition;
		dy = prevPosition.y - currentPosition.y;
		dx = prevPosition.x - currentPosition.x;
		// theta = atan2(dy, dx);                        // atan2() returns the principal value of the arc tangent of y/x , expressed in radians.
		finalPosition.x = static_cast<int> (round(2 * currentPosition.x + acceleration.x *  pow(timeStep, 2) - prevPosition.x)); // cos(theta)
		finalPosition.y = static_cast<int> (round(2 * currentPosition.y + acceleration.y * pow(timeStep, 2) - prevPosition.y)); //  sin(theta) 
		prevPosition = currentPosition;
		currentPosition = finalPosition;
		return finalPosition;
	}

	Point getCollisionVector(const Point &collisionPosition, const Point &prevPosition, const double &stepSize, const int &xMax, const int &yMax, const int &faceID)
	{
		// returns a point along the direction of the particle's motion vector after collision with an AABB object
		double dy = 0.0, dx = 0.0;
		Point nextPosition;
		dy = prevPosition.y - collisionPosition.y;
		dx = prevPosition.x - collisionPosition.x;

		// object collides with the screen

		if (dy == dx || dy == -dx) // screen corners - needs additional tweaking for cases where the point of collision is not a corner
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

		if (dy < 0 && (faceID == 2 || faceID == 4)) // object moving towards yMax
		{
			nextPosition.x = prevPosition.x;
			nextPosition.y = prevPosition.y + 2 * (collisionPosition.y - prevPosition.y);
			return nextPosition;
		}

		if (dy > 0 && (faceID == 2 || faceID == 4)) // object moving towards yMin
		{
			nextPosition.x = prevPosition.x;
			nextPosition.y = prevPosition.y - 2 * (prevPosition.y - collisionPosition.y);
			return nextPosition;
		}

		if (dx < 0 && (faceID == 1 || faceID == 3)) // object moving towards xMax
		{
			nextPosition.x = prevPosition.x + 2 * (collisionPosition.x - prevPosition.x);
			nextPosition.y = prevPosition.y;
			return nextPosition;
		}

		if (dx > 0 && (faceID == 1 || faceID == 3)) // object moving towards xMin
		{
			nextPosition.x = prevPosition.x - 2 * (prevPosition.x - collisionPosition.x);
			nextPosition.y = prevPosition.y;
			return nextPosition;
		}
	}

	bool collideCircleScreen(Circle &circle, AABB &circleBB, const AABB &circlePrevBB, const double & stepSize, const int &xMax, const int &yMax, Point &locus, Point &nextPoint, Acceleration &acceleration, double &theta)
	{
		// Object AABB collision faces -  1 = bottom face, 2 = right face, 3 = top face, 4 = left face
		/*if (circleBB.topLeft.x >= 0 && circleBB.topLeft.x <= 3)
		{

		}*/

		if (circleBB.topLeft.x <= 0) // left side of the AABB collides
		{
			circleBB.faceID = 4;
			nextPoint = getCollisionVector(circleBB.leftMid, circlePrevBB.leftMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(nextPoint, circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.leftMid, circle.radius, 0);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}

		if (circleBB.topLeft.y <= 0) // top side of the AABB collides
		{
			circleBB.faceID = 3;
			nextPoint = getCollisionVector(circleBB.topMid, circlePrevBB.topMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(nextPoint, 0, circle.radius);
			circle.center = getTranslatedPoint(circleBB.topMid, 0, circle.radius);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}

		if (circleBB.bottomRight.x >= xMax) // right side of the AABB collides
		{
			circleBB.faceID = 2;
			nextPoint = getCollisionVector(circleBB.rightMid, circlePrevBB.rightMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(nextPoint, -circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.rightMid, -circle.radius, 0);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}

		if (circleBB.bottomRight.y >= yMax) // bottom side of the AABB collides
		{
			circleBB.faceID = 1;
			nextPoint = getCollisionVector(circleBB.bottomMid, circlePrevBB.bottomMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(nextPoint, 0, -circle.radius);
			circle.center = getTranslatedPoint(circleBB.bottomMid, 0, -circle.radius);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}

		
		return false;
	}

	bool collideCircleRectangle(Circle &circle, Rectangle &rectangle, AABB &circleBB, const AABB &circlePrevBB, AABB &rectangleBB, const AABB &rectanglePrevBB, const double & stepSize, const int &xMax, const int &yMax, Point &circleLocus, Point &circleNextPoint, Acceleration &acceleration, double &theta)
	{
		/*if (abs(circleBB.)
		{


		}*/

if (((circleBB.topLeft.x <= rectangleBB.bottomRight.x + 2) && (circleBB.topLeft.x >= rectangleBB.bottomRight.x - 2)) &&
			(((circleBB.topLeft.y <= rectangleBB.bottomRight.y) && (circleBB.topLeft.y >= rectangleBB.topLeft.y))
				|| ((circleBB.bottomLeft.y <= rectangleBB.bottomRight.y) && (circleBB.bottomLeft.y >= rectangleBB.topLeft.y))))
				{	// left side of the circle AABB collides with the right side of the rectangle AABB
			circleBB.faceID = 4;
			rectangleBB.faceID = 2;
			// std::cout << "\nCASE 1" << std::endl; // debugging
			circleNextPoint = getCollisionVector(circleBB.leftMid, circlePrevBB.leftMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(circleNextPoint, circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.leftMid, circle.radius, 0);
			circleLocus = getNextPositionVerlet(circle.center, circleNextPoint, acceleration, stepSize, theta);
			return true;
		}

		if(circleBB.topLeft.y <= rectangleBB.bottomRight.y && circleBB.bottomRight.y >= rectangleBB.bottomRight.y && (circleBB.bottomRight.x >= rectangleBB.topLeft.x && circleBB.bottomRight.x <= rectangleBB.bottomRight.x || circleBB.topLeft.x >= rectangleBB.topLeft.x && circleBB.topLeft.x <= rectangleBB.bottomRight.x))
		{	// top side of the circle AABB collides with the bottom side of the rectangle AABB
			circleBB.faceID = 3;
			rectangleBB.faceID = 1;
			// std::cout << "\nCASE 2" << std::endl; // debugging
			circleNextPoint = getCollisionVector(circleBB.topMid, circlePrevBB.topMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(circleNextPoint, 0, circle.radius);
			circle.center = getTranslatedPoint(circleBB.topMid, 0, circle.radius);
			circleLocus = getNextPositionVerlet(circle.center, circleNextPoint, acceleration, stepSize, theta);
			return true;
		}

if (((circleBB.topRight.x <= rectangleBB.bottomLeft.x + 2) && (circleBB.topRight.x >= rectangleBB.bottomLeft.x - 2)) &&
			(((circleBB.topRight.y <= rectangleBB.bottomLeft.y) && (circleBB.topRight.y >= rectangleBB.topLeft.y))
				|| ((circleBB.bottomRight.y <= rectangleBB.bottomLeft.y) && (circleBB.bottomRight.y >= rectangleBB.topLeft.y))))
				{	// right side of the circle AABB collides with the left side of the rectangle AABB
			circleBB.faceID = 2;
			rectangleBB.faceID = 4;
			// std::cout << "\nCASE 3" << std::endl; // debugging
			circleNextPoint = getCollisionVector(circleBB.rightMid, circlePrevBB.rightMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(circleNextPoint, -circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.rightMid, -circle.radius, 0);
			circleLocus = getNextPositionVerlet(circle.center, circleNextPoint, acceleration, stepSize, theta);
			return true;
		}

		if (circleBB.bottomRight.y >= rectangleBB.topLeft.y && circleBB.topLeft.y <= rectangleBB.topLeft.y && (circleBB.bottomRight.x >= rectangleBB.topLeft.x && circleBB.bottomRight.x <= rectangleBB.bottomRight.x || circleBB.topLeft.x >= rectangleBB.topLeft.x && circleBB.topLeft.x <= rectangleBB.bottomRight.x))
		{	// bottom side of the circle AABB collides with the top side of the rectangle AABB
			circleBB.faceID = 1;
			rectangleBB.faceID = 3;
			// std::cout << "\nCASE 4" << std::endl; // debugging
			circleNextPoint = getCollisionVector(circleBB.bottomMid, circlePrevBB.bottomMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(circleNextPoint, 0, -circle.radius);
			circle.center = getTranslatedPoint(circleBB.bottomMid, 0, -circle.radius);
			circleLocus = getNextPositionVerlet(circle.center, circleNextPoint, acceleration, stepSize, theta);
			return true;
		}
		return false;
	}

	bool collideCircleScreenPong(Circle &circle, AABB &circleBB, const AABB &circlePrevBB, const double & stepSize, const int &xMax, const int &yMax, Point &locus, Point &nextPoint, Acceleration &acceleration, double &theta)
	{
		// Object AABB collision faces -  1 = bottom face, 2 = right face, 3 = top face, 4 = left face
		/*if (circleBB.topLeft.x <= 0) // left side of the AABB collides
		{
			circleBB.faceID = 4;
			nextPoint = getCollisionVector(circleBB.leftMid, circlePrevBB.leftMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(nextPoint, circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.leftMid, circle.radius, 0);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}*/

		if (circleBB.topLeft.y <= 0) // top side of the AABB collides
		{
			circleBB.faceID = 3;
			nextPoint = getCollisionVector(circleBB.topMid, circlePrevBB.topMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(nextPoint, 0, circle.radius);
			circle.center = getTranslatedPoint(circleBB.topMid, 0, circle.radius);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}

		/*if (circleBB.bottomRight.x >= xMax) // right side of the AABB collides
		{
			circleBB.faceID = 2;
			nextPoint = getCollisionVector(circleBB.rightMid, circlePrevBB.rightMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(nextPoint, -circle.radius, 0);
			circle.center = getTranslatedPoint(circleBB.rightMid, -circle.radius, 0);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}*/

		if (circleBB.bottomRight.y >= yMax) // bottom side of the AABB collides
		{
			circleBB.faceID = 1;
			nextPoint = getCollisionVector(circleBB.bottomMid, circlePrevBB.bottomMid, stepSize, xMax, yMax, circleBB.faceID);
			translatePoint(nextPoint, 0, -circle.radius);
			circle.center = getTranslatedPoint(circleBB.bottomMid, 0, -circle.radius);
			locus = getNextPositionVerlet(circle.center, nextPoint, acceleration, stepSize, theta);
			return true;
		}
		return false;
	}
	
	bool collideBowScreen(const Bow &bow, const Bow &prevBow, Point &nextPoint, Point &bowCord, Point &nextPosition, const int &xMax, const int &yMax, Acceleration &acceleration, const double &stepSize, double &theta)
    {

        if(bowCord.y + bow.radius >= yMax)
        {
            nextPoint = prevBow.center;
            translatePoint(nextPoint, 0, -bow.radius);
			bowCord = getTranslatedPoint(bow.center, 0, -bow.radius);
			nextPosition = getNextPositionVerlet(bowCord, nextPoint, acceleration, stepSize, theta);
            return true;
        }

        if(bowCord.y - bow.radius <= 0)
        {
            nextPoint = prevBow.center;
            translatePoint(nextPoint, 0, bow.radius);
			bowCord = getTranslatedPoint(bow.center, 0, bow.radius);
			nextPosition = getNextPositionVerlet(bowCord, nextPoint, acceleration, stepSize, theta);
            return true;
        }
        return false;
    }

	// this routine utilizes a-priori collision detection unlike the previous cases and uses ray marching - WIP
	bool collideCircleLine(Point &locus, Point &circleNextPoint, Circle &circle, Line &line, AABB &circleBB, const double & stepSize, const int &xMax, const int &yMax, Acceleration &acceleration, double &theta)
	{
		// double dx = locus.x - circle.center.x, dy = locus.y - circle.center.y, magnitude = sqrt(pow(dx, 2) + pow(dy, 2));  // magnitude = sqrt(dx ^ 2 + dy ^ 2)----> considers the magnitude of the velocity
		double circleRayParameter = 0.0, lineRayParameter = 0.0, det = 0.0, collisionTestParameter = 0.0, lineLen = getEuclideanDistance(line.src.x, line.src.y, line.dst.x, line.dst.y);
		const double epsilon = 0.02; // needed for dealing with floating point errors during comparison

		Point origin, collisionPoint;
		Ray circleRay, lineRay, reflectedRay;

		circleRay.o = point2Vec(origin, circle.center); // constructs a ray along the circle's current path
		circleRay.d = getNormalized(point2Vec(circle.center, locus)); // unit direction vector for circleRay

		lineRay.o = point2Vec(origin, line.src); // constructs a ray along the line
		lineRay.d = getNormalized(point2Vec(line.src, line.dst)); // unit direction vector for lineRay

		Vec2 lineNormal = getNormal(point2Vec(line.src, line.dst));

		//////////////////////////////////////////////////////////////////////////////////////////////// -------------> debugging
		/*
		std::cout << "Circle prevCenter x y " << circle.center.x << " " << circle.center.y << std::endl;
		std::cout << "Circle center x y " << locus.x << " " << locus.y << std::endl;
		
		std::cout << "Circle Ray O x y " << circleRay.o.x << " " << circleRay.o.y << std::endl;
		std::cout << "Circle Ray D x y " << circleRay.d.x << " " << circleRay.d.y << std::endl;
		std::cout << "Line Ray O x y " << lineRay.o.x << " " << lineRay.o.y << std::endl;
		std::cout << "Line Ray D x y " << lineRay.d.x << " " << lineRay.d.y << "\n" << std::endl;
		*/
		//////////////////////////////////////////////////////////////////////////////////////////////// -------------> debugging

		det = circleRay.d.x * lineRay.d.y - lineRay.d.x * circleRay.d.y;
		// std::cout << "Determinant " << det << std::endl;

		// ray marching steps 
		if (fabs(det) <= epsilon) // doesn't collide ----> fast reject 
		{
			// this part has bugs as it traces the ray from the center of the circle, meaning the edges of the circle could still collide
			// std::cout << "NO RAY MARCHED COLLISION" << std::endl; // debugging
			return false;
		}

		else // collides somewhere ----> now we check for the actual point of collision
		{
			circleRayParameter = (lineRay.o.x * lineRay.d.y + circleRay.o.y * lineRay.d.x - (lineRay.o.y * lineRay.d.x + circleRay.o.x * lineRay.d.y)) / det;
			// lineRayParameter = (lineRay.o.x * circleRay.d.y + circleRay.o.y * lineRay.d.x - (circleRay.o.x * circleRay.d.y + lineRay.o.y * circleRay.d.x)) / det; // buggy - this needs to be fixed

			collisionPoint = vec2Point(circleRay.o + (circleRay.d * circleRayParameter)); // could also be done using circleRayParamter
			collisionTestParameter = lineLen - (getEuclideanDistance(line.src.x, line.src.y, collisionPoint.x, collisionPoint.y) + getEuclideanDistance(collisionPoint.x, collisionPoint.y, line.dst.x, line.dst.y));

			// std::cout << "circleRayParameter " << circleRayParameter << " lineRayParameter " << lineRayParameter << std::endl; // debugging
			// std::cout << "\ncollisionTestParameter " << collisionTestParameter << "\n" << std::endl; // debugging

			if (fabs(collisionTestParameter) > epsilon)
			{
				// checks if the point of collision lies between the end points of the line - quite slow, 0 <= lineRayParamter <= 1 is a much better test
				// std::cout << "COLLISION OUTSIDE RANGE" << std::endl; // debugging
				return false;
			}
			
			reflectedRay.o = point2Vec(origin, circle.center);
			reflectedRay.d = circleRay.d - (lineNormal * (2 * dotProduct(lineNormal, circleRay.d))); // R = L - 2(N.L)N

			// Vec2 test = lineNormal * (2 * dotProduct(lineNormal, circleRay.d));

			// std::cout << "\nreflectedRay.d x y " << reflectedRay.d.x << " " << reflectedRay.d.y << std::endl; // debugging
			// std::cout << "circleRay.d x y " << circleRay.d.x << " " << circleRay.d.y << "\n\n" << std::endl; // debugging
			// std::cout << "lineNormal x y " << lineNormal.x << " " << lineNormal.y << "\n\n" << std::endl; // debugging
			// std::cout << "test x y " << test.x << " " << test.y << "\n\n" << std::endl; // debugging
			// std::cout << "\ninitial locus x y " << locus.x << " " << locus.y << " " << "initial nextPoint x y " << circleNextPoint.x << " " << circleNextPoint.y << "\n" << std::endl; // debugging

			if (getEuclideanDistance(locus.x, locus.y, collisionPoint.x, collisionPoint.y) <= circle.radius) // collision has actually taken place ----> this part isn't physically accurate as of now
			{
				// std::cout << "\nRAY MARCHED COLLISION" << std::endl; // debugging
				circleNextPoint = vec2Point(reflectedRay.o + reflectedRay.d * 0.5); // 0.5 works but feels like a hack
				locus = getNextPositionVerlet(locus, circleNextPoint, acceleration, stepSize, theta); // NOT physically acuurate ---> has a bug somewhere, reflection not working properly
				// std::cout << "collisionPoint x y " << collisionPoint.x << " " << collisionPoint.y << std::endl; // debugging
				// std::cout << "\ncollision locus x y " << locus.x << " " << locus.y << " " << "collision nextPoint x y " << circleNextPoint.x << " " << circleNextPoint.y << "\n" << std::endl; // debugging
				return true;
			}
			else
			{
				// std::cout << "HASN'T COLLIDED YET" << std::endl; // debugging
				return false;
			}
		}
	}
}
