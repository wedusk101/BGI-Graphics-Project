//physics.h
#ifndef PHYSICS__H_
#define PHYSICS__H_

#include <cmath>
#include "primitives.h"

Point getPosition(Point &prevPosition, Point &currentPosition, const double &initialVelocity, const double &acceleration, const double &timeStep); 

#endif