#include <iostream>
#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "assets.h"
#include "fx.h"
#include "Mmsystem.h"
#include "physics.h"

#define TRUE 1
#define FALSE 0

int main()
{
	int flag = 0;
	const double stepSize = 0.5, footBallSpeed = 3; // arbitrary acceleration value - for g take 9.8
	double theta = 0.0;
	initwindow(1024,960, "Pong");
	int xMax = getmaxx();
	int yMax = getmaxy();
	primitives::Circle ball;
	primitives::Rectangle upRod, downRod;
	primitives::Point nextPoint,locus;
	primitives::AABB ballBB, prevBB, upRodBB, downRodBB, prevUpRodBB, prevDownRodBB;


	upRod.tL.x = 10; upRod.tL.y = 150;
	upRod.bR.x = 30; upRod.bR.y = 300;
	downRod.tL.x = xMax-40; downRod.tL.y = 150;
	downRod.bR.x = xMax-20; downRod.bR.y = 300;
	downRod.width = downRod.bR.x - downRod.tL.x;
	downRod.height = downRod.bR.y - downRod.tL.y;//WIDTH AND HEIGHT OF RODS
	downRod.center = midPoint(downRod.bR, downRod.tL);//MIDPOINT OF RODS
	upRod.width = upRod.bR.x - upRod.tL.x;
	upRod.height = upRod.bR.y - upRod.tL.y;
	upRod.center = midPoint(upRod.bR, upRod.tL);
	
	primitives::Acceleration acceleration;

	ball.center.x = 400;
	ball.center.y = 400;
	ball.radius = 30;
	circle(ball.center.x, ball.center.y,ball.radius);
	drawRods(upRod, downRod);
	nextPoint.x = ball.center.x + 1;
	nextPoint.y = ball.center.y - 2 ;


	while (1) // main game loop
	{
		ball.center.x = 400;
		ball.center.y = 400;
		ball.radius = 30;
		ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius); // binds the axis aligned bounding box to the ball for the first time
		upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);
		downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);

		prevUpRodBB = upRodBB;
		prevDownRodBB = downRodBB;
		circle(ball.center.x, ball.center.y, ball.radius);
		drawRods(upRod, downRod);
		nextPoint.x = ball.center.x + 1;
		nextPoint.y = ball.center.y + 2;
		while (flag!=1 || !ismouseclick(WM_LBUTTONDOWN)) // ball movement Loop
		{
			//line(l.src.x, l.src.y, l.dst.x, l.dst.y); for testing collisions
			//outtextxy(100, 200, "Ghus Gya");
			delay(2);
			cleardevice();
			locus = getNextPositionVerlet(ball.center, nextPoint, acceleration, stepSize, theta); // locus is the next position of the center of the ball along the direction of motion
			circle(ball.center.x, ball.center.y, ball.radius);
			//genFootball(locus, ball.radius); // primary draw call for the ball
			primitives::drawRods(upRod, downRod);
			//primitives::genGoalPost();
			//genFootball(locus, ball.radius); // primary draw call for the ball

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////----------> debugging

			/*
			setcolor(12);
			rectangle(upRodBB.topLeft.x, upRodBB.topLeft.y, upRodBB.bottomRight.x, upRodBB.bottomRight.y);
			rectangle(downRodBB.topLeft.x, downRodBB.topLeft.y, downRodBB.bottomRight.x, downRodBB.bottomRight.y);
			rectangle(ballBB.topLeft.x, ballBB.topLeft.y, ballBB.bottomRight.x, ballBB.bottomRight.y);
			circle(downRod.center.x, downRod.center.y, 5);
			*/

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////----------> debugging

			prevBB = ballBB; // backs up the ball's bounding box
			prevUpRodBB = upRodBB; prevDownRodBB = downRodBB;

			ballBB = updateAABB(locus, 2 * ball.radius, 2 * ball.radius); // updates the axis aligned bounding box for the ball with every iteration

			if ((GetAsyncKeyState(VK_NUMPAD2)) && downRod.bR.y <= yMax)
			{
				downRod.tL.y += 2;
				downRod.bR.y += 2;
				downRod.width = downRod.bR.x - downRod.tL.x;
				downRod.height = downRod.bR.y - downRod.tL.y;//WIDTH AND HEIGHT OF RODS
				downRod.center = midPoint(downRod.bR, downRod.tL);//MIDPOINT OF RODS
				downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);
				prevDownRodBB = downRodBB;


			}

			if ((GetAsyncKeyState(VK_NUMPAD8)) && downRod.tL.y >= 0)
			{
				downRod.tL.y -= 2;
				downRod.bR.y -= 2;
				downRod.width = downRod.bR.x - downRod.tL.x;
				downRod.height = downRod.bR.y - downRod.tL.y;//WIDTH AND HEIGHT OF RODS
				downRod.center = midPoint(downRod.bR, downRod.tL);//MIDPOINT OF RODS
				downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);
				prevDownRodBB = downRodBB;
			}

			if ((GetAsyncKeyState(VK_UP)) && upRod.tL.y >= 0)
			{
				upRod.tL.y -= 2;
				upRod.bR.y -= 2;
				upRod.width = upRod.bR.x - upRod.tL.x;
				upRod.height = upRod.bR.y - upRod.tL.y;
				upRod.center = midPoint(upRod.bR, upRod.tL);
				prevUpRodBB = upRodBB;
				upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);
			}

			if ((GetAsyncKeyState(VK_DOWN)) && upRod.bR.y <=yMax)
			{
				upRod.tL.y += 2;
				upRod.bR.y += 2;
				upRod.width = upRod.bR.x - upRod.tL.x;
				upRod.height = upRod.bR.y - upRod.tL.y;
				upRod.center = midPoint(upRod.bR, upRod.tL);
				prevUpRodBB = upRodBB;
				upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);
			}

			if (collideCircleScreenPong(ball, ballBB, prevBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
				//genFootball(locus, ball.radius);
				 // primary draw call for the ball
				PlaySound(TEXT("media/ball.wav"), NULL, SND_ASYNC);
				circle(ball.center.x, ball.center.y, ball.radius);
				drawRods(upRod, downRod);		 // system("pause");
			}

			if (collideCircleRectangle(ball, upRod, ballBB, prevBB, upRodBB, prevUpRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
				//genFootball(locus, ball.radius);
				 // primary draw call for the ball
				PlaySound(TEXT("media/ball.wav"), NULL, SND_ASYNC);
				circle(ball.center.x, ball.center.y, ball.radius);
				drawRods(upRod, downRod);					 // system("pause");
			}

			if (collideCircleRectangle(ball, downRod, ballBB, prevBB, downRodBB, prevDownRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
			{
				//genFootball(locus, ball.radius);
				 // primary draw call for the ball
				PlaySound(TEXT("media/ball.wav"), NULL, SND_ASYNC);
				circle(ball.center.x, ball.center.y, ball.radius);
				drawRods(upRod, downRod);							 // system("pause");
			}
			if (ball.center.x > xMax || ball.center.x < 0 )
			{
				flag = 1;
			}

			swapbuffers();
		}
		clearmouseclick(WM_LBUTTONDOWN);
		outtextxy(100, 200, "Ghus mmmmGya");

	}
	
	system("pause");
	closegraph();
	return 0;
}