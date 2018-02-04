#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
//#include "matrix.h" or "vector.h"

int main()
{
	srand(time(NULL));
	int i = 0;
	double initialVel = 0.005; // set according to situation - not needed here as of now
	const double acceleration = 0.0, stepSize = 1.0; // arbitrary acceleration value - for g take 9.8
	Point locus, next, mouse;
	Circle ball;
	std::cout << "Please enter the coordinates for the center (x,y)." << std::endl;
	std::cin >> ball.center.x >> ball.center.y;
	std::cout << "Please enter the coordinates for the next point (x,y)." << std::endl;
	std::cin >> next.x >> next.y;
	initwindow(800, 600, "First Sample");
	int xMax = getmaxx(), yMax = getmaxy();
	std::cout << "X = " << xMax << " Y = " << yMax << std::endl;
	setcolor(12);
	circle(ball.center.x, ball.center.y, 20);
	while(1) // check this
	{
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y);
			if (locus.x - mouse.x < 10 && locus.y - mouse.y < 10)
			{
				outtextxy(mouse.x, mouse.y, "HIT!");
				system("pause");
			}
		}
		locus = getPosition(ball.center, next, initialVel, acceleration, stepSize);
		if (locus.x > xMax  || locus.x < 0 || locus.y > yMax || locus.y < 0)
		{
			//break;
			next.x = rand() % xMax;
			next.y = rand() % yMax;
		}
		circle(locus.x, locus.y, 20);
		delay(16);
		cleardevice();		
	}
	//system("pause"); // windows only feature
	closegraph();
	return 0;
}