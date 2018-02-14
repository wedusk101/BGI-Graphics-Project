#ifndef ASSETS__H_
#define ASSETS__H_

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

	Humanoid genHumanoid(Point p); //centre of the circle constituting the head is passed as argument
}

#endif
