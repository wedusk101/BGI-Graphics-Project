#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
#include "matrix.h"
#include "assets.h"
#include <iostream>
#include "vector.h"

int main()
{

	const double acceleration = 0.0, stepSize = 0.5, footBallSpeed = 2.25; // arbitrary acceleration value - for g take 9.8
	double theta = 0.0;

	primitives::Ray arrowRay;
	
	primitives::Point locus, nextPoint, arrowHead, arrowTail, origin;
	primitives :: Circle ball;
	primitives :: AABB ballBB, prevBB, upRodBB, downRodBB,prevUpRodBB,prevDownRodBB;
	primitives :: Rectangle upRod, downRod;
	//std::cout << "Please enter the coordinates for the next point along the path of the ball (x,y)." << std::endl;
	//std::cin >> nextPoint.x >> nextPoint.y; // the closer this point is to the center of the ball, the lower the velocity and vice versa

	initwindow(800, 450, "First Sample");
	setcolor(12); // Light Red

	int xMax = getmaxx(), yMax = getmaxy();
	while(1) // main game loop
    {
		ball = primitives::genBall(); // BALL POSITIONING AND RADIUS
		arrowTail.x = ball.center.x;
		arrowTail.y = ball.center.y;
		arrowHead.x = arrowTail.x + 70;
		arrowHead.y = arrowTail.y;		// ARROW POSITIONING

		primitives::genRods(upRod, downRod);

		ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius); // binds the axis aligned bounding box to the ball for the first time
		upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);
		downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);

	    prevUpRodBB = upRodBB;
		prevDownRodBB = downRodBB;

		primitives :: genFootball(ball.center,ball.radius);
		primitives :: drawRods(upRod,downRod);
		primitives :: genGoalPost();

		//primitives :: drawArrowFootball(arrowHead,arrowTail);
		//primitives :: arrowMovement(arrowHead,arrowTail);
		//arrowHead.x=300;arrowHead.y=300;arrowTail.x=350;arrowTail.y=300;
		double deg = -0.78539;
	    double state = 0.01;
		double radius = getEuclideanDistance(arrowTail.x, arrowTail.y, arrowHead.x, arrowHead.y);

                             
		while(!ismouseclick(WM_LBUTTONDOWN)) // pointer arrow movement
		{
			delay(33);
			cleardevice();
			if(deg<=-1.57079 || deg>=0)
				state*=-1;
			primitives :: genFootball(ball.center,ball.radius);  // comment out for debugging the direction vector for the ball
			primitives :: drawRods(upRod,downRod);
			primitives :: genGoalPost();
			setlinestyle(0,0,1);
			arrowHead.x=arrowTail.x + static_cast<int>(radius*cos(deg));
			arrowHead.y=arrowTail.y + static_cast<int>(radius*sin(deg));
			line(arrowHead.x,arrowHead.y,arrowTail.x,arrowTail.y);
			deg += state;
			swapbuffers();
		}
     
		clearmouseclick(WM_LBUTTONDOWN);

		arrowRay.o = point2Vec(origin, arrowTail);		// this code could possibly be cleaner but this works for now
		arrowRay.d = point2Vec(arrowTail, arrowHead);	// direction vector for the ball

		nextPoint = vec2Point(arrowRay.o + (getNormalized(arrowRay.d) * footBallSpeed)); // r = o + tD ----> t controls the speed of the ball; here t = footballSpeed

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////// ----- debugging the direction vector for the ball
		/*
		primitives::Vec2 test = getNormalized(arrowRay.d);

		std::cout << "Arrow Tail x y " << arrowTail.x << " " << arrowTail.y << std::endl;
		std::cout << "Arrow Head x y " << arrowHead.x << " " << arrowHead.y << std::endl;
		std::cout << "Next Point x y " << nextPoint.x << " " << nextPoint.y << std::endl;
		std::cout << "Normalized Direction Vector x y " << test.x << " " << test.y << std::endl;

		cleardevice();
		line(arrowHead.x, arrowHead.y, arrowTail.x, arrowTail.y); 
		circle(nextPoint.x, nextPoint.y, 5); 
		swapbuffers(); 
		system("pause"); 
		*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////// ------ debugging the direction vector for the ball

	    //primitives :: drawArrowFootball(arrowHead,arrowTail);
		ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius); // binds the axis aligned bounding box to the ball for the first time
		upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);
		downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);

		while (!ismouseclick(WM_LBUTTONDOWN)) // ball movement Loop
		{
			//line(l.src.x, l.src.y, l.dst.x, l.dst.y); for testing collisions
			outtextxy(100,200,"Ghus Gya");
			cleardevice();
			locus = getNextPositionVerlet(ball.center, nextPoint, acceleration, stepSize, theta); // locus is the next position of the center of the ball along the direction of motion
			genFootball(locus, ball.radius); // primary draw call for the ball
			primitives :: drawRods(upRod, downRod);
			primitives :: genGoalPost();


			prevBB = ballBB; // backs up the ball's bounding box
			prevUpRodBB = upRodBB; prevDownRodBB = downRodBB;

			ballBB = updateAABB(locus, 2 * ball.radius, 2 * ball.radius); // updates the axis aligned bounding box for the ball with every iteration

	        if (collideCircleScreen(ball, ballBB, prevBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
				genFootball(locus, ball.radius);
				primitives :: drawRods(upRod,downRod);
			    primitives :: genGoalPost();
				// system("pause");
			}

			if (collideCircleRectangle(ball, upRod, ballBB, prevBB, upRodBB, prevUpRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
				genFootball(locus, ball.radius);
				primitives :: drawRods(upRod,downRod);
				primitives :: genGoalPost();
				// system("pause");
			}

			if (collideCircleRectangle(ball, downRod, ballBB, prevBB, downRodBB, prevDownRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
			    genFootball(locus, ball.radius);
				primitives :: drawRods(upRod,downRod);
		        primitives :: genGoalPost();
				// system("pause");
			}
			swapbuffers();
	}
	clearmouseclick(WM_LBUTTONDOWN);
	swapbuffers();
}

 //   genGoalPost();
	std::cout << "X = " << xMax << " Y = " << yMax << std::endl; // for debugging

    system("pause");
    closegraph();
	return 0;
}
