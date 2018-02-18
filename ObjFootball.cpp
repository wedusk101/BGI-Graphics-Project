/*#include <iostream>
#include <windows.h>
#include <string>*/


//#include "assets.h"
#include "graphics.h"
#include "physics.h"
#include <cstdio>

namespace primitives
{
    void football(const Circle &ball)
    {

    Point point,poly1,poly2,poly3,poly4,poly5,poly6;
        setcolor(15); // Light Red
	circle(ball.center.x, ball.center.y, ball.radius); //Circle drawn

	poly1.x=ball.center.x-8;
	poly1.y=ball.center.y-(ball.radius-1);
	poly2.x=ball.center.x-4;
	poly2.y=ball.center.y-(ball.radius-8);
	poly3.x=ball.center.x+4;
	poly3.y=ball.center.y-(ball.radius-8);
	poly4.x=ball.center.x+8;
	poly4.y=ball.center.y-(ball.radius-1);
	int polygon2[8]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y};
	drawpoly(4,polygon2);

	poly1.x=ball.center.x+(ball.radius-1);
	poly1.y=ball.center.y-8;
	poly2.x=ball.center.x+(ball.radius-8);
	poly2.y=ball.center.y-4;
	poly3.x=ball.center.x+(ball.radius-8);
	poly3.y=ball.center.y+4;
	poly4.x=ball.center.x+(ball.radius-1);
	poly4.y=ball.center.y+8;

	int polygon3[8]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y};
	drawpoly(4,polygon3);


    poly1.x=ball.center.x-(ball.radius-1);
	poly1.y=ball.center.y-8;
	poly2.x=ball.center.x-(ball.radius-8);
	poly2.y=ball.center.y-4;
	poly3.x=ball.center.x-(ball.radius-8);
	poly3.y=ball.center.y+4;
	poly4.x=ball.center.x-(ball.radius-1);
	poly4.y=ball.center.y+8;

	int polygon4[8]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y};
	drawpoly(4,polygon4);

    poly1.x=ball.center.x-8;
	poly1.y=ball.center.y+(ball.radius-1);
	poly2.x=ball.center.x-4;
	poly2.y=ball.center.y+(ball.radius-8);
	poly3.x=ball.center.x+4;
	poly3.y=ball.center.y+(ball.radius-8);
	poly4.x=ball.center.x+8;
	poly4.y=ball.center.y+(ball.radius-1);
	int polygon5[8]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y};
	drawpoly(4,polygon5);

    setfillstyle(SOLID_FILL,LIGHTGRAY);
	floodfill(ball.center.x, ball.center.y,15);

    poly1.x=ball.center.x-4;
	poly1.y=ball.center.y-8;
	poly2.x=ball.center.x+4;
	poly2.y=ball.center.y-8;
	poly3.x=ball.center.x+8;
	poly3.y=ball.center.y;
	poly4.x=ball.center.x+4;
	poly4.y=ball.center.y+8;
	poly5.x=ball.center.x-4;
	poly5.y=ball.center.y+8;
	poly6.x=ball.center.x-8;
	poly6.y=ball.center.y;
	int polygon[14]={poly1.x,poly1.y,poly2.x,poly2.y,poly3.x,poly3.y,poly4.x,poly4.y,poly5.x,poly5.y,poly6.x,poly6.y,poly1.x,poly1.y};
	drawpoly(7,polygon);

	 setfillstyle(SOLID_FILL,RED);
	floodfill(ball.center.x, ball.center.y,15);

    }
}
 /* int main()
{
    initwindow(480,480);
    primitives::Circle ball;
    std::cout << "Please enter the coordinates for the initial position of the ball (x,y)." << std::endl;
	std::cin >> ball.center.x >> ball.center.y;
	std::cout << "Please enter the radius of the ball." << std::endl;
	std::cin >> ball.radius;
    football(ball);
	system("pause");
}

