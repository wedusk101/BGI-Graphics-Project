#include <iostream>
#include "graphics.h"
#include "primitives.h"
#include "matrix.h"
#include "windows.h"

int main()
{
	primitives::Circle ball;
	primitives::Point t;
	std::cout << "Please enter the coordinates for the center of a circle (x,y)." << std::endl;
	std::cin >> ball.center.x >> ball.center.y;
	initwindow(800, 600, "First Sample");
	setcolor(12);
	circle(ball.center.x, ball.center.y, 10);
	std::cout << "Please enter the translation values for the center the circle (tx, ty)." << std::endl;
	std::cin >> t.x >> t.y;
	translatePoint(ball.center, t.x, t.y);
	circle(ball.center.x, ball.center.y, 10);
	system("pause"); // windows only feature
	closegraph();
	return 0;
}