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
	primitives::Bow bow;
	primitives::Arrow arrow;
	primitives::Target target;

	/**Init calls objects are initialised in accordance to the resolution**/
	bow = primitives::genInitBow();                             //By default a stretched bow.
	arrow = primitives::genArrow(bow.radius,bow.center);        //scaled in accordance to bow radius origin at bow.center
    target = primitives::genInitTarget(bow.center);

	/**initial draw calls**/
    drawBow(bow,TRUE);
	drawArrow(arrow.size, bow.center);
	drawTarget(target);

	while (1)                 //main game loop
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
		drawTarget(target);
		swapbuffers();

		arrow.arrowLocus.x = bow.center.x;
		arrow.arrowLocus.y = bow.center.y;


		if(ismouseclick(WM_LBUTTONDOWN) == true)                    //occurence of event is checked
		{
				
			
			while (arrow.arrowLocus.x + (8*arrow.size) <= target.vert.src.x)
			{
				delay(5);
				cleardevice();
	
				arrow.arrowLocus.x = arrow.arrowLocus.x + 4;
				genBow(bow);
				drawBow(bow, FALSE);
				drawArrow(arrow.size, arrow.arrowLocus);
				drawTarget(target);
				swapbuffers();
			}


			clearmouseclick(WM_LBUTTONDOWN);    //event is released
			Sleep(1000);
			printf("\nExited");
		}	
	
	}
	system("pause"); // windows only feature
}
