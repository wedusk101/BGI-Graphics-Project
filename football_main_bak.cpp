#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
#include "matrix.h"
#include "assets.h"
#include <iostream>
#include "vector.h"
#include "leaderboard.h"
#include <time.h>

int main()
{
	const double stepSize = 0.5, footBallSpeed = 5; 
	double theta = 0.0;
	int score = 0, addScore = 0, lastScore = 0;	// Variable for scoring
	int lives = 3;//player lives
	bool ready = false, mainMenu = false;

	primitives::Ray arrowRay;
	primitives::Line top, rear;
	primitives::Point locus, nextPoint, arrowHead, arrowTail, origin;
	primitives::Circle ball;
	primitives::AABB ballBB, prevBB, upRodBB, downRodBB, prevUpRodBB, prevDownRodBB;
	primitives::Rectangle upRod, downRod;
	
	primitives::Acceleration acceleration;

	std::string points;					// for displaying the score
	std::string earnedPoint;			// for displaying the current earned point
	std::string livesStr;
	std::string leader; // top score
	//std::cout << "Please enter the coordinates for the next point along the path of the ball (x,y)." << std::endl;
	//std::cin >> nextPoint.x >> nextPoint.y; // the closer this point is to the center of the ball, the lower the velocity and vice versa

	Leaderboard profile, best;

	// x-y components for acceleration - useful for parabolic motion
	acceleration.x = 0;
	acceleration.y = 0; // change this value for gravity - note that footBallSpeed also needs to be changed correspondingly
	
	initwindow(1280, 720, "Football");
	setcolor(12); // Light Red

	int xMax = getmaxx(), yMax = getmaxy();
	while (1) // game loop
	{
		cleardevice();
		loadLeaderBoard("DBF.DAT", best); // loads profile dat
		if (!mainMenu)
		{
			PlaySound(TEXT("menu.wav"), NULL, SND_ASYNC);
			mainMenu = true;
		}
	    // displayLeaderBoard(best); // debugging
		lives = 3, score = 0, addScore = 0, lastScore = 0;
		ready = false;

		ball = primitives::genBall(); // BALL POSITIONING AND RADIUS ball generating function
		arrowTail.x = ball.center.x;
		arrowTail.y = ball.center.y;
		arrowHead.x = arrowTail.x + 70;
		arrowHead.y = arrowTail.y;		// ARROW POSITIONING

		primitives::genRods(upRod, downRod);

		primitives::genFootball(ball.center, ball.radius); //BALL DRAWING FUNCTION
		primitives::drawRods(upRod, downRod);	//ROD DRAWING FUNCTION
		primitives::genGoalPost(top, rear);	//GOALPOST DRAWING FUNCTION

		line(arrowHead.x, arrowHead.y, arrowTail.x, arrowTail.y);


		outtextxy(xMax / 2 - 75, yMax / 2, "Press Space to Play!");
		outtextxy(xMax / 2 - 75, yMax / 2 + 25, "Left click to shoot the ball.");
		if (GetAsyncKeyState(VK_SPACE))
		{
			PlaySound(TEXT("whistle.wav"), NULL, SND_ASYNC);
			delay(1000);
			ready = true;
		}

		while (ready && lives != 0) // main gameplay loop
		{
			double duration = 0.0; //For timer
			bool flag = false, takeShot = false;
			ball = primitives::genBall(); // BALL POSITIONING AND RADIUS ball generating function
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

			primitives::genFootball(ball.center, ball.radius); //BALL DRAWING FUNCTION
			primitives::drawRods(upRod, downRod);	//ROD DRAWING FUNCTION
			primitives::genGoalPost(top, rear);	//GOALPOST DRAWING FUNCTION

			//primitives :: drawArrowFootball(arrowHead,arrowTail);
			//primitives :: arrowMovement(arrowHead,arrowTail);
			//arrowHead.x=300;arrowHead.y=300;arrowTail.x=350;arrowTail.y=300;

			double deg = -0.78539;
			double state = 0.01;
			double radius = getEuclideanDistance(arrowTail.x, arrowTail.y, arrowHead.x, arrowHead.y);
					

			//clock_t before = clock();
			while (!ismouseclick(WM_LBUTTONDOWN)) // pointer arrow movement and checking for lives if positive it will continue
			{
				if (!takeShot)
				{
					PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC);
					takeShot = true;
				}
				cleardevice();
				if (deg <= -1.57079 || deg >= 0)
					state *= -1;
				primitives::genFootball(ball.center, ball.radius);  // comment out for debugging the direction vector for the ball
				primitives::drawRods(upRod, downRod);
				primitives::genGoalPost(top, rear);
				setlinestyle(0, 0, 1);
				arrowHead.x = arrowTail.x + static_cast<int>(radius*cos(deg));
				arrowHead.y = arrowTail.y + static_cast<int>(radius*sin(deg));
				line(arrowHead.x, arrowHead.y, arrowTail.x, arrowTail.y);
				points = std::to_string(score);
				const char *pstr = points.c_str();
				livesStr = std::to_string(lives);
				const char *plives = livesStr.c_str();
				outtextxy(70, 50, "Goal: ");
				outtextxy(140, 50, (char*)pstr); // displays the current score 


				outtextxy(70, 90, "Lives :");
				outtextxy(140, 90, (char*)plives); // displays the lives left


				////////////////////////////////////////////////////////////////////////////////////////////////////////////////----------> debugging
				/*
				setcolor(12);
				rectangle(upRodBB.topLeft.x, upRodBB.topLeft.y, upRodBB.bottomRight.x, upRodBB.bottomRight.y);
				rectangle(downRodBB.topLeft.x, downRodBB.topLeft.y, downRodBB.bottomRight.x, downRodBB.bottomRight.y);
				rectangle(ballBB.topLeft.x, ballBB.topLeft.y, ballBB.bottomRight.x, ballBB.bottomRight.y);
				*/
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////----------> debugging

				deg += state;
				swapbuffers();
			}

			clearmouseclick(WM_LBUTTONDOWN);
			

			arrowRay.o = point2Vec(origin, arrowTail);		// this code could possibly be cleaner but this works for now
			arrowRay.d = point2Vec(arrowTail, arrowHead);	// direction vector for the ball

			nextPoint = vec2Point(arrowRay.o + (getNormalized(arrowRay.d) * footBallSpeed));
			// r = o + tD ----> t controls the speed of the ball; here t = footballSpeed

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////// ------> debugging the direction vector for the ball
			/*
			primitives::Vec2 test = getNormalized(arrowRay.d);

			std::cout << "Arrow Tail x y " << arrowTail.x << " " << arrowTail.y << std::endl;
			std::cout << "Arrow Head x y " << arrowHead.x << " " << arrowHead.y << std::endl;
			std::cout << "Next Point x y " << nextPoint.x << " " << nextPoint.y << std::endl;
			std::cout << "Normalized Direction Vector x y " << test.x << " " << test.y << std::endl;

			cleardevice();
			line(arrowHead.x, arrowHead.y, arrowTail.x, arrowTail.y);
			circle(nextPoint.x, nextPoint.y, 5);
			setcolor(12);
			rectangle(upRodBB.topLeft.x, upRodBB.topLeft.y, upRodBB.bottomRight.x, upRodBB.bottomRight.y);
			rectangle(downRodBB.topLeft.x, downRodBB.topLeft.y, downRodBB.bottomRight.x, downRodBB.bottomRight.y);
			rectangle(ballBB.topLeft.x, ballBB.topLeft.y, ballBB.bottomRight.x, ballBB.bottomRight.y);
			swapbuffers();
			system("pause");
			*/
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////// ------> debugging the direction vector for the ball
			
			ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius); // binds the axis aligned bounding box to the ball for the first time
			upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);
			downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);
			clock_t start = clock(); // starts a timer
			while (duration <= 2) // ball movement Loop ----> duration is the value returned the timer 
			{
				cleardevice();
				locus = getNextPositionVerlet(ball.center, nextPoint, acceleration, stepSize, theta); // locus is the next position of the center of the ball along the direction of motion
				genFootball(locus, ball.radius); // primary draw call for the ball
				primitives::drawRods(upRod, downRod);
				primitives::genGoalPost(top, rear);
				points = std::to_string(score);
				const char *pstr = points.c_str();
				livesStr = std::to_string(lives);
				const char *plives = livesStr.c_str();
				outtextxy(70, 50, "Goal: ");
				outtextxy(140, 50, (char*)pstr); // displays the current score 


				outtextxy(70, 90, "Lives :");
				outtextxy(140, 90, (char*)plives); // displays the lives left

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
				prevUpRodBB = upRodBB;
				prevDownRodBB = downRodBB;

				ballBB = updateAABB(locus, 2 * ball.radius, 2 * ball.radius); // updates the axis aligned bounding box for the ball with every iteration

				if (collideCircleScreen(ball, ballBB, prevBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
				{
					genFootball(locus, ball.radius);
					primitives::drawRods(upRod, downRod);
					primitives::genGoalPost(top, rear);
					PlaySound(TEXT("football.wav"), NULL, SND_ASYNC);
				}

				if (collideCircleRectangle(ball, upRod, ballBB, prevBB, upRodBB, prevUpRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
				{
					genFootball(locus, ball.radius);
					primitives::drawRods(upRod, downRod);
					primitives::genGoalPost(top, rear);
					PlaySound(TEXT("football.wav"), NULL, SND_ASYNC);
				}

				if (collideCircleRectangle(ball, downRod, ballBB, prevBB, downRodBB, prevDownRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
				{
					genFootball(locus, ball.radius);
					primitives::drawRods(upRod, downRod);
					primitives::genGoalPost(top, rear);
					PlaySound(TEXT("football.wav"), NULL, SND_ASYNC);
				}

				if (collideCircleLine(locus, nextPoint, ball, rear, ballBB, stepSize, xMax, yMax, acceleration, theta)) // rear of the goal
				{
					// handles collisions with the back of the goal post
					circle(locus.x, locus.y, ball.radius);
					PlaySound(TEXT("football.wav"), NULL, SND_ASYNC);
				}

				if (collideCircleLine(locus, nextPoint, ball, top, ballBB, stepSize, xMax, yMax, acceleration, theta)) // top of the goal post
				{
					// handles collisions with the back of the goal post
					circle(locus.x, locus.y, ball.radius);
					PlaySound(TEXT("football.wav"), NULL, SND_ASYNC);
				}

				if (ball.center.x >= top.src.x && ball.center.x <= top.dst.x && ball.center.y > top.src.y && !flag) //to check whether the ball has crossed the starting pole points(goal post) if yes then update the score
				{
					score += 1;
					flag = true;
					PlaySound(TEXT("goal.wav"), NULL, SND_ASYNC);
					// PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC); // sound mixing won't work
				}

				clock_t difference = clock() - start;  // ends the timer
				duration = difference / (double)CLOCKS_PER_SEC; // calculates the duration
				swapbuffers();
			}
			--lives; //decrementing the player life after every shot taken

			if (lives == 0) // if lives = 0 then game over
			{
				outtextxy(xMax / 2 - 75, yMax / 2, "Game Over!");
				outtextxy(xMax / 2 - 75, yMax / 2 + 20, "Top Score is ");
				profile.topScore = score;
				if (profile.topScore > best.topScore)
				{
					best = profile;
					saveLeaderBoard("DBF.DAT", best); // save profile data
				}
				leader = std::to_string(best.topScore);
				const char *ptop = leader.c_str();
				outtextxy(xMax / 2 + 25, yMax / 2 + 20, (char*)ptop); // displays top score
				mainMenu = false;
				swapbuffers();
				delay(3000);
			}
			// std::cout << "X = " << duration ; // debugging - displays the timer output

			clearmouseclick(WM_LBUTTONDOWN);
			swapbuffers();
		}
		swapbuffers();
	}

 	// std::cout << "X = " << xMax << " Y = " << yMax << std::endl; // for debugging

    system("pause");
    closegraph();
	return 0;
}