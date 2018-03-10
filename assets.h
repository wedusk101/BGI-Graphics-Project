//assets.h
#pragma once

#ifndef ASSETS__H_
#define ASSETS__H_

#include "primitives.h"
#include "matrix.h"

namespace primitives
{
	// we intend on defining an inheritance hierarchy for easier code organization, especially for collision detection functions
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
	} Bow;
    
    typedef struct
    {
       	Point p;
       	int size;
    } Arrow;
    
    typedef struct
	{
	    	Line vert;
	    	Line horiz;
	} Target;		
    
	
	
    Humanoid genHumanoid(const Point &); //center of the circle constituting the head is passed as argument
	Rectangle getRectangle(const int &, const int &, const int &, const int &);
	Bow genBow(const Point &);            //Function to generate coordinates for the Bow
	Arrow genArrow(const Point&, int &);   //Function to generate coordinates for the Arrow
	Target genTarget(const Point &);      //Function to generate coordinates for the Target


    void genFootball(const Circle &);
    void genRods(const int &, const int &);
	void genGoalPost();
	void drawBow(Bow);                    //Function to draw the Bow - please pass by reference, const or otherwise - this is quite slow as it copies the object
	void drawArrow(Arrow);                //Function to draw the Arrow - please pass by reference, const or otherwise - this is quite slow as it copies the object
	void drawTarget(Target);              //Function to draw the Target - please pass by reference, const or otherwise - this is quite slow as it copies the object
}

#endif