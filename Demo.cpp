#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"


int main()
{
	srand(time(NULL));
	int score = 0;
	std::string points; // for displaying the score
	const double acceleration = 0.0, stepSize = 1.0; // arbitrary acceleration value - for g take 9.8
	primitives::Point locus, nextPoint, mouse;
	primitives::Circle ball;
	AABB ballBB;
	std::cout << "Please enter the coordinates for the initial position of the ball (x,y)." << std::endl;
	std::cin >> ball.center.x >> ball.center.y;
	std::cout << "Please enter the radius of the ball." << std::endl;
	std::cin >> ball.radius;
	std::cout << "Please enter the coordinates for the next point along the path of the ball (x,y)." << std::endl;
	std::cin >> nextPoint.x >> nextPoint.y; // the closer this point is to the center of the ball, the lower the velocity and vice versa
	initwindow(800, 600, "First Sample");
	setcolor(12); // Pink 
	int xMax = getmaxx(), yMax = getmaxy();
	std::cout << "X = " << xMax << " Y = " << yMax << std::endl;
	circle(ball.center.x, ball.center.y, ball.radius);
	while (1) // check this
	{
		locus = getPosition(ball.center, nextPoint, acceleration, stepSize); // nextPoint is the next position of the center of the ball
		circle(locus.x, locus.y, ball.radius);
		ballBB = updateAABB(locus, 2 * ball.radius, 2 * ball.radius); // axis aligned bounding box for the ball
		std::cout << "AABB topleft: " << ballBB.topLeft.x << "," << ballBB.topLeft.y << " bottomRight: " << ballBB.bottomRight.x << "," << ballBB.bottomRight.y << std::endl; // debugging
		points = std::to_string(score);
		const char *pstr = points.c_str();
		outtextxy(xMax - 170, 50, "SCORE: ");
		outtextxy(xMax - 100, 50, (char*)pstr); // displays the current score 
		if (ismouseclick(WM_LBUTTONDOWN)) // checks if a mouse click event has occurred
		{
			getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y); // gets the location of the mouse pointer when the mouse is clicked 
			if (locus.x - mouse.x < 10 && locus.y - mouse.y < 10) // registers a hit
			{
				outtextxy(mouse.x, mouse.y, "HIT! +10"); // displays the hit confirmation
				score += 10;
				delay(1000); // pauses for a second after a successful hit
			}
		}
		if (ballBB.topLeft.x < 0 || ballBB.bottomRight.x > xMax || ballBB.topLeft.y < 0 || ballBB.bottomRight.y > yMax) // <----this doesn't work but this one does ---> if (locus.x > xMax || locus.x < 0 || locus.y > yMax || locus.y < 0)
		{
			
			// this part is working as expected
			// nextPoint.x = rand() % xMax; 
			// nextPoint.y = rand() % yMax; // right now the ball just runs around in random directions at random speeds upon hitting the edge of the screen

			//this part has bugs --- particle eventually gets stuck at a corner
			std::cout << "COLLISION DETECTED!" << std::endl;
			nextPoint = getCollisionVector(locus, ball.center, stepSize, xMax, yMax); // returns the next point in the particle's path right after collision
			locus = getPosition(locus, nextPoint, acceleration, stepSize); // in getPosition(), locus is the point pf collision of the particle with the box 
			circle(locus.x, locus.y, ball.radius);
			std::cout << "After Collision Current: " << ball.center.x << " " << ball.center.y << std::endl; // for debugging
			std::cout << "After Collision Next: " << locus.x << " " << locus.y << std::endl; // for debugging
			system("pause");
			//ballBB = updateAABB(locus, ball.radius, ball.radius);
		}
		std::cout << "Current: " << ball.center.x << " " << ball.center.y << std::endl; // for debugging
		std::cout << "Next: " << locus.x << " " << locus.y << std::endl; // for debugging
		delay(33); // 16ms = 60 FPS, 33 ms = 30 FPS 
		cleardevice();
	}
	system("pause"); // windows only feature
	closegraph();
	return 0;
}