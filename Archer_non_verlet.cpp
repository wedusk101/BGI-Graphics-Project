#include <iostream>
#include <windows.h>
#include <string>
#include "graphics.h"
#include "primitives.h"
#include "physics.h"
#include "matrix.h"
#include "assets.h"

#define TRUE 1
#define FALSE 0

int main()                    //Test Arrow and Bow
{
	initwindow(1366,700);
	int xmax = getmaxx();
    	int ymax = getmaxy();
	int y_inc = 1;
	int score = 0 , addScore = 0;		//Variable for scoring
	int divison = 0;			//Variable to divide the target into fixed no. of zones.
	std::string points;			// for displaying the score
	std::string earnedPoint;		// for displaying the current earned point
	primitives::Point arrowHitPos;		//Point Variable to store the arrow position.

	/**Init calls objects are initialised in accordance to the resolution**/
	primitives::Bow bow = primitives::genInitBow();                             	//By default a stretched bow.
	primitives::Arrow arrow = primitives::genArrow(bow.radius,bow.center);        	//scaled in accordance to bow radius origin at bow.center
	primitives::Target target = primitives::genInitTarget(bow.center);

	/**initial draw calls**/
    	drawBow(bow,TRUE);
	drawArrow(arrow.size, bow.center);
	drawTarget(target);

	while (1)                 //main game loop
	{
		cleardevice();
		if ((bow.center.y - (bow.radius + 10)) <= 5)                  		//bound checking for bow  (upper screen) 
			y_inc = 1;
		if ((bow.center.y + bow.radius + 10) >= (ymax - 5))          		//bound checking for bow  (lower screen)
			y_inc = -1;

		bow.center.y += y_inc;            					//bow translation by modifying bow center
		genBow(bow);                      					// regenerating the co-ordinates in response to modified Bow center
		
		/*Drawing the objects at new co-ordinates*/
		drawBow(bow, TRUE); 
		drawArrow(arrow.size, bow.center);
		drawTarget(target);

		/**Score Display**/
		points = std::to_string(score);                                                   
		const char *pstr = points.c_str();
		outtextxy(xmax - 170, 50, "Points: ");
		outtextxy(xmax - 100, 50, (char*)pstr); 				// displays the current score 

		earnedPoint = std::to_string(addScore);
		const char *pstrAdd = earnedPoint.c_str();
		outtextxy(xmax - 250, 70, "Last Point Earned :");
		outtextxy(xmax - 100, 70, (char*)pstrAdd); 				// displays the current earned score
		
		/*Update the locus of arrow according to the bow's center*/
		arrow.arrowLocus.x = bow.center.x;
		arrow.arrowLocus.y = bow.center.y;
		
		if(ismouseclick(WM_LBUTTONDOWN) == true)                    		//occurence of event is checked
		{
			while (arrow.arrowLocus.x + (8*arrow.size) <= target.vert.src.x)//moves arrow until it collides with target
			{
				cleardevice();
				arrow.arrowLocus.x = arrow.arrowLocus.x + 5;		//moves the arrow forward
				genBow(bow);
				drawBow(bow, FALSE);					//drawing an unstretched bow
				drawArrow(arrow.size, arrow.arrowLocus);
				drawTarget(target);
				
				/**Score Display**/
				points = std::to_string(score);
				const char *pstr = points.c_str();
				outtextxy(xmax - 170, 50, "Points: ");
				outtextxy(xmax - 100, 50, (char*)pstr); 		// displays the current score 

				earnedPoint = std::to_string(addScore);
				const char *pstrAdd = earnedPoint.c_str();
				outtextxy(xmax - 250, 70, "Last Point Earned :");
				outtextxy(xmax - 100, 70, (char*)pstrAdd); 		// displays the current earned score
				swapbuffers();
			}
			clearmouseclick(WM_LBUTTONDOWN);    				//event is released
			
			arrowHitPos = arrow.arrowLocus;					//Stores the final position of the array
			divison = (target.horiz.src.y - target.vert.src.y) / 4;  	//Divide the target into 4 zones for scoring
			
			if (arrowHitPos.y < target.vert.src.y || arrowHitPos.y > target.vert.dst.y)	//If arrow dosen't hit the target
				addScore = 0;
			else
			{
				if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + divison))		//If the arrow hits the upper first divided zone of the target
					addScore = 1;
				else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - divison))	//If the arrow hits the lower first divided zone of the target
					addScore = 1;
				else if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + 2 * divison))//If the arrow hits the upper second divided zone of the target
					addScore = 3;
				else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - 2 * divison))	//If the arrow hits the lower second divided zone of the target
					addScore = 3;
				else if (arrowHitPos.y > target.vert.src.y && arrowHitPos.y < (target.vert.src.y + 3 * divison))//If the arrow hits the upper third divided zone of the target
					addScore = 5;
				else if (arrowHitPos.y < target.vert.dst.y && arrowHitPos.y >(target.vert.dst.y - 3 * divison))	//If the arrow hits the lower third divided zone of the target
					addScore = 5;
				else																							//If the arrow hits the center
					addScore = 7;
			}
			score += addScore;
			delay(700);
		}	
		swapbuffers();
	}
	system("pause"); // windows only feature
}
