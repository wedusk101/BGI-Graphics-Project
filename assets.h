#ifndef ASSETS__H_
#define ASSETS__H_

#include "primitives.h"

using namespace primitives;

/*
typedef struct
{

} HEAD;

typedef struct
{

} NECK;

typedef struct
{

} TORSO;

typedef struct
{
	Point tl;
	Point rb;
} HAND;

typedef struct
{

} LEG;
*/

typedef struct
{
	Circle head;
	primitives::Rectangle neck;
	primitives::Rectangle torso;
	primitives::Rectangle rHand;
	primitives::Rectangle lHand;
	primitives::Rectangle rLeg;
	primitives::Rectangle lLeg;
} Humanoid;

Humanoid genHumanoid(Point p); //centre of the circle constituting the head is passed as argument

#endif
