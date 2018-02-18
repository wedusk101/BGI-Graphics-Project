//assets.h
#pragma once

#ifndef ASSETS__H_
#define ASSETS__H_

#include "primitives.h"

namespace primitives
{
	typedef struct
	{
		Point center;
		Line uString;
		Line lString;
	} Bow;
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
    
    
        Humanoid genHumanoid(const Point &); //centre of the circle constituting the head is passed as argument
        void football(const Circle &)
        void Rods(const int &,const int &);

	  
	Bow genBow(const Point &);
}

#endif
