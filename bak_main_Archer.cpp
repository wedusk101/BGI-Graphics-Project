#include <iostream>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
#include "matrix.h"
#include "assets.h"
#include "windows.h"

int main()
{
    const double acceleration = 0.0, stepSize = 0.5; // arbitrary acceleration value - for g take 9.8
	double theta = 0.0;
    primitives :: Point bowCord,targetCord,arrowCord,nextPosition,nextPoint,nextPointArrow,nextPositionArrow;
    primitives :: Bow bow,prevBow;
    primitives :: Target target;
    primitives :: Arrow arrow;
    /*std::cout << "Please enter the coordinates for the initial position of the bow (x,y)." << std::endl;
	std::cin >> bowCord.x >> bowCord.y;
    std::cout << "Please enter the coordinates for the initial position of the target (x,y)." << std::endl;
	std::cin >> targetCord.x >> targetCord.y;*/
	bowCord.x=100; bowCord.y=150;//Initialization of Bow
	targetCord.x=600;targetCord.y=150;//Initialization of Target
	arrowCord.x=bowCord.x;arrowCord.y=bowCord.y;//Placing Arrow on Bow
	int size=15;
	nextPoint.x=100;nextPoint.y=155;//Next Point of movement of Bow Difference in y Axis is speed
	nextPointArrow.x=115;nextPointArrow.y=155;//Next Point of movement of Arrow Difference in x Axis is speed
	initwindow(800, 480, "First Sample");
	int xMax = getmaxx(), yMax = getmaxy();
	setcolor(12); // Light Red
	bow=primitives::genBow(bowCord);
	drawBow(bow);
	target=genTarget(targetCord);
	drawTarget(target);
	arrow=genArrow(arrowCord,size);
	drawArrow(arrow);
	while(1)
    {
        delay(20);
        cleardevice();
        nextPosition=getNextPositionVerlet(bowCord,nextPoint,acceleration,stepSize,theta);
        prevBow=bow;
        bow=genBow(nextPosition);
        arrow=genArrow(nextPosition,size);
        drawBow(bow);
        drawTarget(target);
        drawArrow(arrow);
        if(collideBowScreen(bow,prevBow,nextPoint,bowCord,nextPosition,size,xMax,yMax,acceleration,stepSize,theta))
        {
            bow=genBow(nextPosition);
            arrow=genArrow(nextPosition,size);
            drawBow(bow);
            drawTarget(target);
            drawArrow(arrow);
        }
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            nextPointArrow.y=nextPosition.y;
            arrowCord.y=nextPosition.y;
            while(nextPointArrow.x+30<=xMax)        //Need Changes
            {
                delay(20);
                cleardevice();
                bow=genBow(nextPosition);
                drawBow(bow);
                drawTarget(target);
                nextPositionArrow=getNextPositionVerlet(arrowCord,nextPointArrow,acceleration,stepSize,theta);
                arrow=genArrow(nextPositionArrow,size);
                drawArrow(arrow);
                swapbuffers();
            }
            clearmouseclick(WM_LBUTTONDOWN);
            targetCord.y=rand() % yMax;//New Position of Target || Not set Accurately Need Changes
            target=genTarget(targetCord);
        }
        arrowCord.x=100;nextPointArrow.x=115;
        swapbuffers();
    }
    system("pause");
    closegraph();
	return 0;
}
