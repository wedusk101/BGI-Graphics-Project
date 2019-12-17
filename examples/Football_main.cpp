/*****************************************************************************************************************************
The following code implements the Football game. This piece of code has the following components and dependencies.

loadLeaderBoard() - Returns void - read leader board object player data from <DBF.DAT> and load it into object <best>.

PlaySound() - Returns bool - Plays audio track(for main menu, game play etc).

genBall()- Returns center and radius of Ball - This function is used to generate the coordinates of the circle which will be
used to draw a Ball. The coordinates are generated with respect to the resolution of the window.

genBallArrow()- Returns the coordinate of Arrow on ball used to aim - This function is used to generate the initial coordinates
of the Arrow on Ball which will be used for aiming.

drawBallArrow()- Returns void - This function is used to draw the Arrow on screen from the points generated from
"genBallArrow()".

genRods()- Returns void - This function is used to generate the coordinates of the up and down Rods with respect to the
resolution of the window.

genFootball() - Returns void - This function is used to draw the Football on the screen.

drawRods() - Returns void - This function is used to draw the 2 Rods.

genGoalPost()- Returns void - This function is used to generate the coordinates of the Goal Post and draw it on the screen.

GetAsyncKeyState() - Returns bool – Starts the game when the SPACE key is tapped.

updateAABB() – Returns coordinate of Bounding Box – This function is used to create a bounding box for the object which
will be used for collision detection.

getEuclideanDistance – Returns the Euclidean distance between two points.

ismouseclick() -  Returns bool – This function is used to capture mouse click events. Here left click of mouse.

swapbuffers() – Returns void – This function is used to swap the front and the back buffer.

point2Vec() – Returns Vec2 – This function is used to return vector from source point to destination point.

Vec2Point() – Returns Point – This function is used to return Point from Vector.

getNextPositionVerlet() – Returns Point – This function is used to calculate next position of object using Verlet Integration.

collideCircleScreen() – Returns a Boolean value – This function is used

collideCircleRectangle() – Returns a Boolean value – This function is used to

collideCircleLine() – Returns a Boolean value – This function is used to

**********************************************************************************************************************/

#include "windows.h"
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
#include "matrix.h"
#include "assets.h"
#include <iostream>
#include "vector.h"
#include "leaderboard.h"
#include <ctime>

int main()
{
	const double stepSize = 0.5, footBallSpeed = 3;			//footballSpeed for manipulating Speed of the ball
	double theta = 0.0;										//theta
	int score = 0, addScore = 0;							// Variable for scoring
	int lives = 10;											//player lives
	bool ready = false, mainMenu = false;					//ready for inner Game Loop and mainMenu for game restart 
															//Initializing Assets and datatypes
	primitives::Ray arrowRay;
	primitives::Line top, rear;				
	primitives::Point locus, nextPoint, arrowHead, arrowTail, origin;
	primitives::Circle ball;
	primitives::AABB ballBB, prevBB, upRodBB, downRodBB, prevUpRodBB, prevDownRodBB;
	primitives::Rectangle upRod, downRod;
	primitives::BallArrow ballArrow;
	primitives::Acceleration acceleration;

	std::string points;					// for displaying the score
	std::string earnedPoint;			// for displaying the current earned point
	std::string livesStr;
	std::string leader;					// top score
	std::string name;
	Leaderboard best;

										// x-y components for acceleration - useful for parabolic motion
	acceleration.x = 0;
	acceleration.y = 0;					// change this value for gravity - note that footBallSpeed also needs to be changed correspondingly
	
	initwindow(1024, 600, "Football");	//Screen Resolution
	setcolor(12);						// Light Red

	int xMax = getmaxx(), yMax = getmaxy();
	while (1)							//Loop1-Outer game loop (Can be Removed)
	{
		cleardevice();		
		if (!mainMenu)
		{
			try
			{
				loadLeaderBoard("saves/DBF.DAT", best); // loads profile data
			}
			catch (std::exception &err)
			{
				std::cout << err.what() << std::endl;
				std::cout << "Error occured while loading player data!" << std::endl;
			}

			PlaySound(TEXT("media/menu.wav"), NULL, SND_ASYNC|SND_LOOP);
			mainMenu = true;			
			std::cout << "Please enter your player avatar name." << std::endl;
			std::getline(std::cin, name);			
		}
		char *avatarName = new char[name.length() + 1];
		strcpy(avatarName, name.c_str());
		Leaderboard profile(avatarName);

		lives = 5, score = 0;
		ready = false;

		ball = primitives::genBall();								//Ball Positioning and ball generating function
		ballArrow = primitives::genBallArrow(ball.center);			//Generates coordinates for arrow initially
		primitives::drawBallArrow(ballArrow);						//Draw arrow on the ball
		primitives::genRods(upRod, downRod);						//Generates Coordinates for the Rod

		primitives::genFootball(ball.center, ball.radius);			//Ball Draw Call
		primitives::drawRods(upRod, downRod);						//Rod Draw Call
		primitives::genGoalPost(top, rear);							//Goal Post draw Call

		outtextxy(xMax / 2 - 75, yMax / 2, "Press Space to Play!");
		outtextxy(xMax / 2 - 75, yMax / 2 + 25, "Left click to shoot the ball.");
		if (GetAsyncKeyState(VK_SPACE))								//Space Key Starts the game with audio
		{
			PlaySound(TEXT("media/whistle.wav"), NULL, SND_ASYNC);
			delay(1000);
			ready = true;
		}

		while (ready && lives != 0)									//Nested Loop 2-Main gameplay loop
		{
			double duration = 0.0;													//For timer
			bool flag = false, takeShot = false;
			ball = primitives::genBall();											//Ball Positioning and ball generating function
			ballArrow = primitives::genBallArrow(ball.center);						//Generates coordinates for arrow initially
			primitives::drawBallArrow(ballArrow);									//Draw arrow on ball
			ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius);		// binds the axis aligned bounding box to the ball for the first time
			upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);			// binds the axis aligned bounding box to the upperRod for the first time
			downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);	// binds the axis aligned bounding box to the lowerRod for the first time

			prevUpRodBB = upRodBB;													//Copying the position of the upperRod
			prevDownRodBB = downRodBB;												//Copying the position of the lowerRod

			primitives::genFootball(ball.center, ball.radius);						//Ball Draw Call
			primitives::drawRods(upRod, downRod);									//Rods Draw Call
			primitives::genGoalPost(top, rear);										//GoalPost Draw Call

			double deg = -0.78539;													//Arrow Points to the x-axis
			double state = 0.01;
			double radius = getEuclideanDistance(ballArrow.tail.x, ballArrow.tail.y, ballArrow.head.x, ballArrow.head.y);
					
			while (!ismouseclick(WM_LBUTTONDOWN))									// pointer arrow movement and checking for lives if positive it will continue
			{
				if (!takeShot)
				{
					PlaySound(TEXT("media/crowd.wav"), NULL, SND_ASYNC);
					takeShot = true;
				}
				cleardevice();
				if (deg <= -1.57079 || deg >= 0)
					state *= -1;
				primitives::genFootball(ball.center, ball.radius);  
				primitives::drawRods(upRod, downRod);
				primitives::genGoalPost(top, rear);
				
				ballArrow.head.x = ballArrow.tail.x + static_cast<int>(radius*cos(deg));
				ballArrow.head.y = ballArrow.tail.y + static_cast<int>(radius*sin(deg));
				primitives::drawBallArrow(ballArrow);								//Draw arrow on screen
				
				points = std::to_string(score);
				const char *pstr = points.c_str();
				livesStr = std::to_string(lives);
				const char *plives = livesStr.c_str();
				outtextxy(70, 50, "Goal: ");
				outtextxy(140, 50, (char*)pstr);									// displays the current score 
				outtextxy(70, 90, "Lives :");
				outtextxy(140, 90, (char*)plives);									// displays the lives left
				deg += state;
				swapbuffers();
			}
			clearmouseclick(WM_LBUTTONDOWN);
			
			arrowRay.o = point2Vec(origin, ballArrow.tail);							// this code could possibly be cleaner but this works for now
			arrowRay.d = point2Vec(ballArrow.tail, ballArrow.head);					// direction vector for the ball
			nextPoint = vec2Point(arrowRay.o + (getNormalized(arrowRay.d) * footBallSpeed));
			
			ballBB = updateAABB(ball.center, 2 * ball.radius, 2 * ball.radius);		// binds the axis aligned bounding box to the ball
			upRodBB = updateAABB(upRod.center, upRod.width, upRod.height);			// binds the axis aligned bounding box to the upperRod
			downRodBB = updateAABB(downRod.center, downRod.width, downRod.height);	// binds the axis aligned bounding box to the lowerRod
			clock_t start = clock();												// starts a timer
			while (duration <= 2)			// ball movement Loop ----> duration is the value returned the timer 
			{
				cleardevice();
				locus = getNextPositionVerlet(ball.center, nextPoint, acceleration, stepSize, theta); // locus is the next position of the center of the ball along the direction of motion
				genFootball(locus, ball.radius);									// primary draw call for the ball
				primitives::drawRods(upRod, downRod);								// primary draw call for the Rods
				primitives::genGoalPost(top, rear);									// primary draw call for the goalPost
				points = std::to_string(score);
				const char *pstr = points.c_str();
				livesStr = std::to_string(lives);
				const char *plives = livesStr.c_str();
				outtextxy(70, 50, "Goal: ");
				outtextxy(140, 50, (char*)pstr);									// displays the current score 
				outtextxy(70, 90, "Lives :");
				outtextxy(140, 90, (char*)plives);									// displays the lives left

				prevBB = ballBB;													// backs up the ball's bounding box
				prevUpRodBB = upRodBB;												// backs up the upperRod's bounding box
				prevDownRodBB = downRodBB;											// backs up the lowerRod's bounding box

				ballBB = updateAABB(locus, 2 * ball.radius, 2 * ball.radius);		// updates the axis aligned bounding box for the ball with every iteration

				if (collideCircleScreen(ball, ballBB, prevBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
				{																	//Checking Collision with Screen
					genFootball(locus, ball.radius);
					primitives::drawRods(upRod, downRod);
					primitives::genGoalPost(top, rear);
					PlaySound(TEXT("media/football.wav"), NULL, SND_ASYNC);
				}

				if (collideCircleRectangle(ball, upRod, ballBB, prevBB, upRodBB, prevUpRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
				{																	//Checking ball's Collision with UpperRod using Bounding Box
					genFootball(locus, ball.radius);
					primitives::drawRods(upRod, downRod);
					primitives::genGoalPost(top, rear);
					PlaySound(TEXT("media/football.wav"), NULL, SND_ASYNC);
				}

				if (collideCircleRectangle(ball, downRod, ballBB, prevBB, downRodBB, prevDownRodBB, stepSize, xMax, yMax, locus, nextPoint, acceleration, theta))
				{																	//Checking ball's Collision with lowerRod using Bounding Box
					genFootball(locus, ball.radius);
					primitives::drawRods(upRod, downRod);
					primitives::genGoalPost(top, rear);
					PlaySound(TEXT("media/football.wav"), NULL, SND_ASYNC);
				}

				if (collideCircleLine(locus, nextPoint, ball, rear, ballBB, stepSize, xMax, yMax, acceleration, theta)) // rear of the goal
				{																	//Checking ball's Collision with back Post of the goalPost using Ray Marching
					circle(locus.x, locus.y, ball.radius);
					PlaySound(TEXT("media/football.wav"), NULL, SND_ASYNC);
				}

				if (collideCircleLine(locus, nextPoint, ball, top, ballBB, stepSize, xMax, yMax, acceleration, theta)) // top of the goal post
				{																	//Checking ball's Collision with top Post of the goalPost using Ray Marching
					circle(locus.x, locus.y, ball.radius);
					PlaySound(TEXT("media/football.wav"), NULL, SND_ASYNC);
				}

				if (ball.center.x >= top.src.x && ball.center.x <= top.dst.x && ball.center.y > top.src.y && !flag) 
				{																	//to check whether the ball has crossed the starting pole points(goal post) if yes then update the score
					score += 1;
					flag = true;
					PlaySound(TEXT("media/goal.wav"), NULL, SND_ASYNC);
					// PlaySound(TEXT("crowd.wav"), NULL, SND_ASYNC); // sound mixing won't work
				}
				clock_t difference = clock() - start;								// ends the timer
				duration = difference / (double)CLOCKS_PER_SEC;						// calculates the duration
				swapbuffers();
			}
			--lives;																//decrementing the player life after every shot taken

			if (lives == 0)															// if lives = 0 then game over
			{
				outtextxy(xMax / 2 - 75, yMax / 2, "Game Over!");
				outtextxy(xMax / 2 - 75, yMax / 2 + 20, "Top Score is ");
				profile.topScore = score;
				if (profile.topScore > best.topScore)
				{
					best = profile;
					try
					{
						saveLeaderBoard("saves/DBF.DAT", best); // save profile data
					}
					catch (std::exception &err)
					{
						std::cout << err.what() << std::endl;
						std::cout << "Error occured while saving score!" << std::endl;
					}					
				}
				leader = std::to_string(best.topScore);
				const char *ptop = leader.c_str();
				outtextxy(xMax / 2 + 25, yMax / 2 + 20, (char*)ptop); // displays top score
				outtextxy(xMax / 2 - 75, yMax / 2 + 40, "Player name: ");
				outtextxy(xMax / 2 + 25, yMax / 2 + 40, best.playerName);
				mainMenu = false;
				swapbuffers();
				delay(3000);
				delete[] avatarName;
			}												//End ball Movement	
			clearmouseclick(WM_LBUTTONDOWN);
			upRod.tL.x = rand() % ((static_cast<int>(xMax * 2 / 3) - 250)- (static_cast<int>(xMax * 2 / 3) - 150)) + (static_cast<int>(xMax * 2 / 3) - 150);	//	Randomizing Rods Position
			upRod.bR.y = rand() % ((static_cast<int>(yMax - 100))-100) + 100;										//	Randomizing Rods Position
			updateRods(upRod, downRod);																				//	Update Bounding Box for new Rod Position 
			swapbuffers();
		}													//End Inner Game Loop
		swapbuffers();
	}														//End Outer Main Loop
    system("pause");
    closegraph();
	return 0;
}														//End Main