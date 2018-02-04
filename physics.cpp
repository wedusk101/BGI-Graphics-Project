//physics.cpp
#include <cmath>
#include "primitives.h"

Point getPosition(Point & prevPosition, Point & currentPosition, double initialVelocity, const double & acceleration, const double & timeStep) 
{
	// Verlet Integration code for calculating the next position of a particle in motion
	// acceleration is constant as we are ignoring the third order derivative of position(jerk) 
	// the velocity will be calculated using Stormer-Verlet method
	Point finalPosition;
	finalPosition.x =(int) 2 * currentPosition.x + acceleration * pow(timeStep, 2) - prevPosition.x;
	finalPosition.y =(int) 2 * currentPosition.y + acceleration * pow(timeStep, 2) - prevPosition.y;
	prevPosition = currentPosition;
	currentPosition = finalPosition;
	return finalPosition;
}