//matrix.h
#ifndef MATRIX__H_
#define MATRIX__H_

#include <cmath>
#include "primitives.h"

void rotate(Point &p, double theta); // rotates a ray about the origin by an angle of theta radians
void translate(Point &p, int tx, int ty); // translates a point P(x,y) by tx and ty 

#endif