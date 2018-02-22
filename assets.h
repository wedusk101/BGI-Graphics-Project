//assets.h
#pragma once

#ifndef ASSETS__H_
#define ASSETS__H_

#include "primitives.h"
#include "matrix.h"

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
		int radius;
		int midy;
	}Bow;
    
    	typedef struct
    	{
        	Point p;
        	int size;
    	}Arrow;
    
    	typedef struct
	{
	    	Line vert;
	    	Line horiz;
	}Target;		
    
	
	
    	Humanoid genHumanoid(const Point &); //center of the circle constituting the head is passed as argument
	Rectangle getRectangle(const int &, const int &, const int &, const int &);
    	void genFootball(const Circle &);
    	void genRods(const int &, const int &);
	void genGoalPost();
	
	Bow genBow(const Point &);            //Function to generate coordinates for the Bow
	void drawBow(Bow);                    //Function to draw the Bow
	Arrow genArrow(const Point&,int &);   //Function to generate coordinates for the Arrow
	void drawArrow(Arrow);                //Function to draw the Arrow
	Target genTarget(const Point &);      //Function to generate coordinates for the Target
	void drawTarget(Target);              //Function to draw the Target
}

#endif
