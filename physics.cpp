//physics.cpp
#include "physics.h"

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

Point getReflectionVector(const Point &collisionPosition, const Point &prevPosition, const double &stepSize)
{
	// returns a point along the direction of the particle's motion vector after collision using the laws of reflection
	double dy = 0.0, dx = 0.0, thetaInitial = 0.0, thetaReflected = 0.0;
	Point nextPosition;
	if (collisionPosition.x == prevPosition.x || collisionPosition.y == prevPosition.y) // particle moves perpendicular to either axis
		return prevPosition;
	dy = prevPosition.y - collisionPosition.y;
	dx = prevPosition.x - collisionPosition.x;
	thetaInitial = atan2(dy, dx); // returns the principal value of theta by calculating the correct quadrant
	thetaReflected = 3.141592653589 - thetaInitial; // pi - theta
	nextPosition.x = (int) prevPosition.x + stepSize;
	nextPosition.y = (int) tan(thetaReflected) * (prevPosition.y + stepSize); // tan(thetaReflected) is the slope of the reflected ray
	return nextPosition;
}