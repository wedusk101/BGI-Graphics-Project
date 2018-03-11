#include <iostream>
#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
#include "matrix.h"
#include "assets.h"
#include "fx.h"

#define TRUE 1
#define FALSE 0

int main()                    //Test Arrow and Bow
{
	initwindow(800, 800);
	int xmax = getmaxx();
    int ymax = getmaxy();
	int y_inc = 1, lives = 7;
	int score = 0, addScore = 0, lastScore = 0;	//Variable for scoring
	int divison = 0;					//Variable to divide the target into fixed no. of zones.
	std::string points;					// for displaying the score
	std::string earnedPoint;			// for displaying the current earned point
	std::string livesStr;
	primitives::Point arrowHitPos;		//Point Variable to store the arrow position.

	/**Init calls objects are initialised in accordance to the resolution**/
	primitives::Bow bow = primitives::genInitBow();                             //By default a stretched bow.
	primitives::Arrow arrow = primitives::genArrow(bow.radius,bow.center);        //scaled in accordance to bow radius origin at bow.center
	primitives::Target target = primitives::genInitTarget(bow.center);

	/**initial draw calls**/
    drawBow(bow,TRUE);
	drawArrow(arrow.size, bow.center);
	drawTarget(target);

	while (lives != 0)                 //main game loop
	{
		cleardevice();
		if ((bow.center.y - (bow.radius + 10)) <= 5)                  //bound checking for bow  (upper screen) 
			y_inc = 1;
		if ((bow.center.y + bow.radius + 10) >= (ymax - 5))           //bound checking for bow  (lower screen)
			y_inc = -1;

		bow.center.y += y_inc;            //bow translation by modifying bow center
		genBow(bow);                      // regenerating the co-ordinates in response to modified Bow center
		drawBow(bow, TRUE); 
		drawArrow(arrow.size, bow.center);
		//target.horiz.src.y = rand() % ymax;
		//target.horiz.dst.y = target.horiz.src.y;
		//genInitTarget(target.horiz.src);
		drawTarget(target);

		/**Score Display**/
		points = std::to_string(score);                                                   
		const char *pstr = points.c_str();
		livesStr = std::to_string(lives);
		const char *plives = livesStr.c_str();
		outtextxy(xmax - 170, 50, "Points: ");
		outtextxy(xmax - 100, 50, (char*)pstr); // displays the current score 

		earnedPoint = std::to_string(lastScore);
		const char *pstrAdd = earnedPoint.c_str();
		outtextxy(xmax - 250, 70, "Last Point Earned :");
		outtextxy(xmax - 100, 70, (char*)pstrAdd); // displays the current earned score

		outtextxy(xmax - 250, 90, "Lives :");
		outtextxy(xmax - 100, 90, (char*)plives);
		
		arrow.arrowLocus.x = bow.center.x;
		arrow.arrowLocus.y = bow.center.y;
		
		

		if(ismouseclick(WM_LBUTTONDOWN))                    //occurrence of event is checked
		{
			while (arrow.arrowLocus.x + (8*arrow.size) <= target.vert.src.x)
			{
				cleardevice();
				arrow.arrowLocus.x = arrow.arrowLocus.x + 5;
				genBow(bow);
				drawBow(bow, FALSE);
				drawArrow(arrow.size, arrow.arrowLocus);
				drawTarget(target);
				points = std::to_string(score);
				const char *pstr = points.c_str();
				outtextxy(xmax - 170, 50, "Points: ");
				outtextxy(xmax - 100, 50, (char*)pstr); // displays the current score 

				earnedPoint = std::to_string(lastScore);
				const char *pstrAdd = earnedPoint.c_str();
				outtextxy(xmax - 250, 70, "Last Point Earned :");
				outtextxy(xmax - 100, 70, (char*)pstrAdd); // displays the current earned score

				outtextxy(xmax - 250, 90, "Lives :");
				outtextxy(xmax - 100, 90, (char*)plives); // displays the no. of lives left
				swapbuffers();
			}
			clearmouseclick(WM_LBUTTONDOWN);    //event is released
			
			arrowHitPos = arrow.arrowLocus;		//Stores the final position of the array
			divison = (target.horiz.src.y - target.vert.src.y) / 4;  //Divide the target into 4 zones for scoring
			
			if (arrowHitPos.y < target.vert.src.y || arrowHitPos.y > target.vert.dst.y)		//If arrow doesn't hit the target
			{
				lastScore = 0;
				--lives;
			}
			else
			{
				if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + divison))		//If the arrow hits the upper first divided zone of the target
				{
					outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+1");
					shockWave(target.horiz.src, 20, 50);
					swapbuffers();
					lastScore = addScore = 1;
				}
				else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - divison))		//If the arrow hits the lower first divided zone of the target
				{
					outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+1");
					shockWave(target.horiz.src, 20, 50);
				    swapbuffers();
					lastScore = addScore = 1;
				}				
				else if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + 2 * divison))//If the arrow hits the upper second divided zone of the target
				{
					outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+3");
					shockWave(target.horiz.src, 20, 50);
					swapbuffers();
					lastScore = addScore = 3;
				}
				else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - 2 * divison))	//If the arrow hits the lower second divided zone of the target
				{
					outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+3");
					shockWave(target.horiz.src, 20, 50);
					swapbuffers();
					lastScore = addScore = 3;
				}
				else if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + 3 * divison))//If the arrow hits the upper third divided zone of the target
				{
					outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+5");
					shockWave(target.horiz.src, 20, 50);
					swapbuffers();
					lastScore = addScore = 5;
				}
				else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - 3 * divison))	//If the arrow hits the lower third divided zone of the target
				{
					outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+5");
					shockWave(target.horiz.src, 20, 50);
					swapbuffers();
					lastScore = addScore = 5;
				}
				else //If the arrow hits the center
				{
					outtextxy(arrowHitPos.x, arrowHitPos.y + 20, "+7");
					shockWave(target.horiz.src, 20, 50);
					swapbuffers();
					lastScore = addScore = 7;
				}
			}
			score += addScore;
			addScore = 0;
			delay(700);
		}
		swapbuffers();
	}
	outtextxy(xmax / 2, ymax / 2, "Game Over!");
	swapbuffers();
	system("pause"); // windows only feature
	closegraph();
}