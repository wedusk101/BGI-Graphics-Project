//matrix.h
#ifndef MATRIX__H_
#define MATRIX__H_

#include <cmath>
#include "primitives.h"

void rotate(Point &p, const double &theta); // rotates a ray about the origin by an angle of theta radians
void translate(Point &p, const int &tx, const int &ty); // translates a point P(x,y) by tx and ty 
void scale(Point &p, const int &sx, const int &sy); // scales a point P(x,y) by sx and sy

#endif