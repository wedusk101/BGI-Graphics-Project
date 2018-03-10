#include <iostream>
#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "assets.h"
#include "physics.h"
#include "fx.h"
#include "gameplay.h"


int main()
{
	int score = 0;
	std::string points; // for displaying the score
	const double acceleration = 0.0, stepSize = 0.5; // arbitrary acceleration value - for g take 9.8
	double theta = 0.0, dirArrowTheta = 4.8, dirArrowRadius = 0.0, dirArrowStep = 0.005;

	

	primitives::Point locus, nextPoint, mouse;
	primitives::Circle ball;
	primitives::Rectangle box;
	primitives::AABB ballBB, prevBB, boxBB, prevBoxBB;
	primitives::Line l; // direction arrow testing for football

	
	std::cout << "Please enter the coordinates for the initial position of the ball (x,y)." << std::endl;
	std::cin >> ball.center.x >> ball.center.y;
	std::cout << "Please enter the radius of the ball." << std::endl;
	std::cin >> ball.radius;
	std::cout << "Please enter the coordinates for the next point along the path of the ball (x,y)." << std::endl;
	std::cin >> nextPoint.x >> nextPoint.y; // the closer this point is to the center of the ball, the lower the velocity and vice versa
	
	
	box = primitives::getRectangle(100, 100, 300, 300);


	initwindow(400, 400, "First Sample");
	setcolor(12); // Light Red 
	int xMax = getmaxx(), yMax = getmaxy();
	std::cout << "X = " << xMax << " Y = " << yMax << std::endl; // for debugging
	l.src.x = xMax / 2, l.src.y = yMax, l.dst.x = xMax / 2, l.dst.y = yMax - 50; // hardcoded values for the direction arrow 

	dirArrowRadius = getEuclideanDistance(l.src.x, l.src.y, l.dst.x, l.dst.y);
	circle(ball.center.x, ball.center.y, ball.radius);
	rectangle(box.tL.x, box.tL.y, box.bR.x, box.bR.y);
	ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius); // binds the axis aligned bounding box to the ball for the first time
	boxBB = updateAABB(box.center, box.width, box.height);
	std::cout << "Box Center : " << box.center.x << ", " << box.center.y << " Width : " << box.width << " Height : " << box.height << std::endl; // debugging
	
	while (1) // check this
	{
		cleardevice();
		// line(l.src.x, l.src.y, l.dst.x, l.dst.y); // direction arrow testing for football
		//drawDirectionArrow(l);
		locus = getNextPositionVerlet(ball.center, nextPoint, acceleration, stepSize, theta); // locus is the next position of the center of the ball along the direction of motion
		circle(locus.x, locus.y, ball.radius); // primary draw call for the ball
		rectangle(box.tL.x, box.tL.y, box.bR.x, box.bR.y);
		prevBB = ballBB; // backs up the ball's bounding box
		ballBB = updateAABB(locus, 2 * ball.radius, 2 * ball.radius); // updates the axis aligned bounding box for the ball with every iteration
		prevBoxBB = boxBB;
		boxBB = updateAABB(box.center, box.width, box.height);
		std::cout << "AABB topleft: " << ballBB.topLeft.x << "," << ballBB.topLeft.y << " bottomRight: " << ballBB.bottomRight.x << "," << ballBB.bottomRight.y << std::endl; // debugging
		std::cout << "Box AABB topleft: " << boxBB.topLeft.x << "," << boxBB.topLeft.y << " bottomRight: " << boxBB.bottomRight.x << "," << boxBB.bottomRight.y << std::endl; // debugging
		points = std::to_string(score);
		const char *pstr = points.c_str();
		outtextxy(xMax - 170, 50, "SCORE: ");
		outtextxy(xMax - 100, 50, (char*)pstr); // displays the current score 
		if (GetAsyncKeyState(VK_SPACE)) //keyboard input
			system("pause");

		if (dirArrowTheta <= 0 || dirArrowTheta >= 1.570796) // pi / 2 radians
			dirArrowStep *= -1; // changes the direction of rotation
		rotateRay(l.dst, dirArrowTheta, l.src.x, l.src.y);
		line(l.src.x, l.src.y, l.dst.x, l.dst.y);
		dirArrowTheta += dirArrowStep;

		//setactivepage(int page), setvisualpage(int page), swapbuffers()
		if (ismouseclick(WM_LBUTTONDOWN)) // checks if a mouse click event has occurred
		{
			getmouseclick(WM_LBUTTONDOWN, mouse.x, mouse.y); // gets the location of the mouse pointer when the mouse is clicked 
			if (locus.x - mouse.x < 10 && locus.y - mouse.y < 10) // registers a hit
			{
				outtextxy(mouse.x, mouse.y, "HIT! +10"); // displays the hit confirmation
				swapbuffers();
				score += 10;
				delay(1000); // pauses for a second after a successful hit
				// primitives::showerConfetti(xMax, yMax, acceleration, stepSize, 6, 3, 25); // Work in progress - ignore this function call unless you're working on this
			}
		}
		
		// a posteriori collision detection

		if (collideCircleScreen(ball, ballBB, prevBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
		{
			circle(locus.x, locus.y, ball.radius);
			//system("pause"); // for debugging
			shockWave(locus, ball.radius, ball.radius + 40);
		}

		if (collideCircleRectangle(ball, box, ballBB, prevBB, boxBB, prevBoxBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
		{
			circle(locus.x, locus.y, ball.radius);
			// system("pause"); // for debugging
			shockWave(locus, ball.radius, ball.radius + 40);
		}
		std::cout << "Current: " << ball.center.x << " " << ball.center.y << std::endl; // for debugging
		std::cout << "Next: " << locus.x << " " << locus.y << std::endl; // for debugging
		swapbuffers(); // double buffering to reduce flicker		
	}
	//system("pause"); // windows only feature
	closegraph();
	return 0;
}