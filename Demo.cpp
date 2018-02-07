#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
//#include "matrix.h"

int main()
{
	srand(time(NULL));
	double initialVelocity = 0.005; // set according to situation - not needed here as of now
	const double acceleration = 0.0, stepSize = 1.0; // arbitrary acceleration value - for g take 9.8
	Point locus, nextPoint, mouse;
	Circle ball;
	std::cout << "Please enter the coordinates for the center of the ball (x,y)." << std::endl;
	std::cin >> ball.center.x >> ball.center.y;
	std::cout << "Please enter the radius of the ball." << std::endl;
	std::cin >> ball.radius;
	std::cout << "Please enter the coordinates for the nextPoint point along the path of the ball (x,y)." << std::endl;
	std::cin >> nextPoint.x >> nextPoint.y;
	initwindow(800, 600, "First Sample");
	setcolor(12); // Pink 
	int xMax = getmaxx(), yMax = getmaxy();
	std::cout << "X = " << xMax << " Y = " << yMax << std::endl;
	circle(ball.center.x, ball.center.y, ball.radius);
	while (1) // check this
	{
		if (ismouseclick(WM_LBUTTONDOWN)) // checks if a mouse click event has occurred
		{
			getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y); // gets the location of the mouse pointer when the mouse is clicked 
			if (locus.x - mouse.x < 10 && locus.y - mouse.y < 10)
			{
				outtextxy(mouse.x, mouse.y, "HIT!");
				system("pause");
			}
		}
		locus = getPosition(ball.center, nextPoint, initialVelocity, acceleration, stepSize); // nextPoint position of the center of the ball
		if (locus.x > xMax || locus.x < 0 || locus.y > yMax || locus.y < 0) // collision detection needs work - this is very crude and is for testing purposes only
		{
			// this part is working as expected
			/*
			nextPoint.x = rand() % xMax; // reflection needs to be set up
			nextPoint.y = rand() % yMax; // right now the ball just runs around in random directions upon hitting the edge of the screen
			*/
			
			// this part has bugs
			nextPoint = getReflectionVector(locus, ball.center, stepSize);
			locus = getPosition(ball.center, nextPoint, initialVelocity, acceleration, stepSize);
			
			
		}
		std::cout << "Current: " << ball.center.x << " " << ball.center.y << std::endl; // for debugging
		std::cout << "nextPoint: " << locus.x << " " << locus.y << std::endl; // for debugging
		circle(locus.x, locus.y, ball.radius);
		delay(250); // 60 FPS but the speed of the ball needs to be adjusted
		cleardevice();		
	}
	system("pause"); // windows only feature
	closegraph();
	return 0;
}