#include <iostream>
#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"


int main()
{
	int score = 0;
	std::string points; // for displaying the score
	const double acceleration = 0.0, stepSize = 1.0; // arbitrary acceleration value - for g take 9.8
	primitives::Point locus, nextPoint, mouse;
	primitives::Circle ball;
	primitives::AABB ballBB, prevBB;
	//primitives::Line l;
	std::cout << "Please enter the coordinates for the initial position of the ball (x,y)." << std::endl;
	std::cin >> ball.center.x >> ball.center.y;
	std::cout << "Please enter the radius of the ball." << std::endl;
	std::cin >> ball.radius;
	std::cout << "Please enter the coordinates for the next point along the path of the ball (x,y)." << std::endl;
	std::cin >> nextPoint.x >> nextPoint.y; // the closer this point is to the center of the ball, the lower the velocity and vice versa
	//std::cout << "Please enter the coordinates for the end points of the line." << std::endl;
	//std::cin >> l.src.x >> l.src.y >> l.dst.x >> l.dst.y;
	initwindow(800, 600, "First Sample");
	setcolor(12); // Pink 
	int xMax = getmaxx(), yMax = getmaxy();
	std::cout << "X = " << xMax << " Y = " << yMax << std::endl; // for debugging
	circle(ball.center.x, ball.center.y, ball.radius);
	ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius);
	while (1) // check this
	{
		//line(l.src.x, l.src.y, l.dst.x, l.dst.y); for testing collisions
		locus = getPosition(ball.center, nextPoint, acceleration, stepSize); // nextPoint is the next position of the center of the ball
		circle(locus.x, locus.y, ball.radius);
		prevBB = ballBB;
		ballBB = updateAABB(locus, 2 * ball.radius, 2 * ball.radius); // axis aligned bounding box for the ball
		std::cout << "AABB topleft: " << ballBB.topLeft.x << "," << ballBB.topLeft.y << " bottomRight: " << ballBB.bottomRight.x << "," << ballBB.bottomRight.y << std::endl; // debugging
		points = std::to_string(score);
		const char *pstr = points.c_str();
		outtextxy(xMax - 170, 50, "SCORE: ");
		outtextxy(xMax - 100, 50, (char*)pstr); // displays the current score 
		//if (GetAsyncKeyState(VK_LEFT)) //keyboard input
		//setactivepage(int page), setvisualpage(int page), swapbuffers()
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
		/*if (ballBB.bottomRight.x >= l.dst.x) // line collision --- just one case
		{
			nextPoint = getCollisionVector(ballBB.bottomMid, ball.center, stepSize, xMax, yMax); // returns the next point in the particle's path right after collision
			locus = getPosition(ballBB.bottomMid, nextPoint, acceleration, stepSize); // in getPosition(), locus is the point pf collision of the particle with the box 
			circle(locus.x, locus.y, ball.radius);
		}*/
		if (ballBB.topLeft.x <= 0) // left side of the AABB collides
		{
			nextPoint = getCollisionVector(ballBB.leftMid, prevBB.leftMid, stepSize, xMax, yMax);
			locus = getPosition(ballBB.leftMid, nextPoint, acceleration, stepSize); 
			circle(locus.x, locus.y, ball.radius);
			std::cout << "CASE 1" << std::endl;
			std::cout << "After Collision locus: " << locus.x << " " << locus.y << std::endl; // for debugging
			std::cout << "After Collision nextPoint: " << nextPoint.x << " " << nextPoint.y << std::endl; // for debugging
			system("pause");
		}
		if (ballBB.topLeft.y <= 0) // top side of the AABB collides
		{
			nextPoint = getCollisionVector(ballBB.topMid, prevBB.topMid, stepSize, xMax, yMax);
			locus = getPosition(ballBB.topMid, nextPoint, acceleration, stepSize);
			circle(locus.x, locus.y, ball.radius);
			std::cout << "CASE 2" << std::endl;
			std::cout << "After Collision locus: " << locus.x << " " << locus.y << std::endl; // for debugging
			std::cout << "After Collision nextPoint: " << nextPoint.x << " " << nextPoint.y << std::endl; // for debugging
			system("pause");
		}
		if (ballBB.bottomRight.x >= xMax) // right side of the AABB collides
		{
			nextPoint = getCollisionVector(ballBB.rightMid, prevBB.rightMid, stepSize, xMax, yMax);
			locus = getPosition(ballBB.rightMid, nextPoint, acceleration, stepSize);
			circle(locus.x, locus.y, ball.radius);
			std::cout << "CASE 3" << std::endl;
			std::cout << "After Collision locus: " << locus.x << " " << locus.y << std::endl; // for debugging
			std::cout << "After Collision nextPoint: " << nextPoint.x << " " << nextPoint.y << std::endl; // for debugging
			system("pause");
		}
		if (ballBB.bottomRight.y >= yMax) // bottom side of the AABB collides
		{
			nextPoint = getCollisionVector(ballBB.bottomMid, prevBB.bottomMid, stepSize, xMax, yMax);
			locus = getPosition(ballBB.bottomMid, nextPoint, acceleration, stepSize);
			circle(locus.x, locus.y, ball.radius);
			std::cout << "CASE 4" << std::endl;
			std::cout << "After Collision locus: " << locus.x << " " << locus.y << std::endl; // for debugging
			std::cout << "After Collision nextPoint: " << nextPoint.x << " " << nextPoint.y << std::endl; // for debugging
			system("pause");
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