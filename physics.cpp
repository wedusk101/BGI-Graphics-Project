//physics.cpp
//#include <iostream>
#include "physics.h"
#include "matrix.h"

Point getPosition(Point &prevPosition, Point &currentPosition, const double &initialVelocity, const double &acceleration, const double &timeStep) 
{
	// Verlet Integration code for calculating the next position of a particle in motion
	// acceleration is constant as we are ignoring the third order derivative of position(jerk) 
	// the velocity will be calculated using Stormer-Verlet method ---- this feature hasn't been implemented yet
	Point finalPosition;
	finalPosition.x = (int) 2 * currentPosition.x + acceleration * pow(timeStep, 2) - prevPosition.x;
	finalPosition.y = (int) 2 * currentPosition.y + acceleration * pow(timeStep, 2) - prevPosition.y;
	prevPosition = currentPosition;
	currentPosition = finalPosition;
	return finalPosition;
}

void getCollisionVector(const Point &collisionPosition, const Point &prevPosition, Point &nextPosition, const double &stepSize, const int &xMax, const int &yMax)
{
	// returns a point along the direction of the particle's motion vector after collision using the laws of reflection
	double dy = 0.0, dx = 0.0, thetaInitial = 0.0, thetaReflected = 0.0;
	nextPosition = prevPosition;
	dy = prevPosition.y - collisionPosition.y;
	dx = prevPosition.x - collisionPosition.x;
	thetaInitial = atan2(dy, dx); // returns the principal value of theta by calculating the correct quadrant
	thetaReflected = 3.141592653 - 2 * thetaInitial; // pi - 2 * theta
	// std::cout << thetaInitial << std::endl; ----- for debugging
	rotate(nextPosition, thetaReflected); // maybe requires a translation to the origin first?
}