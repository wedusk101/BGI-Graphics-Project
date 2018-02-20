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
    
	typedef struct
	{
	    Line vert;
	    Line horiz;
	}Target;
    
    	Humanoid genHumanoid(const Point &); //center of the circle constituting the head is passed as argument
	Bow genBow(const Point &);

	Rectangle getRectangle(const int &, const int &, const int &, const int &);
	
    	void genFootball(const Circle &);
    	void genRods(const int &, const int &);
	void genGoalPost();
	Target genTarget(const Point &);    //Function to generate coordinates for the Target
	void drawTarget(Target);            //Function to draw the Target
}

#endif
