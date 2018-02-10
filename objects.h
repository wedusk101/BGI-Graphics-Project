#ifndef OBJECTS__H_
#define OBJECTS__H_

#include "primitives.h"

typedef struct
{
	Circle head;
	Rect neck;
	Rect torso;
	Rect rHand;
	Rect lHand;
	Rect rLeg;
	Rect lLeg;
} Humanoid;

Humanoid genHumanoid(Point p); //centre of the circle constituting the head is passed as argument

#endif
