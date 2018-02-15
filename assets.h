#ifndef OBJECTS__H_
#define OBJECTS__H_

#include "primitives.h"

namespace primitives
{
	typedef struct
	{
		Circle head;
		Rectangle neck;
		Rectangle torso;
		Rectangle rHand;
	  	Rectangle lHand;
		Rectangle rLeg;
		Rectangle lLeg;
	} Humanoid;

	typedef struct
	{
	    Point center;
	    Line uString;
	    Line lString;
	} Bow;

	Humanoid genHumanoid(Point p); //centre of the circle constituting the head is passed as argument
	Bow genBow(Point P); // the argument is the point at which the arc is centered at

}

#endif
