#include <iostream>
#include "graphics.h"
#include "primitives.h"
#include "matrix.h"
#include "windows.h"

int main()
{
	double theta = 0.0;
	primitives::Line l;
	std::cout << "Please enter the coordinates for the end points of a line (x,y)." << std::endl;
	std::cin >> l.src.x >> l.src.y >> l.dst.x >> l.dst.y;
	initwindow(800, 600, "First Sample");
	setcolor(12);
	line(l.src.x, l.src.y, l.dst.x, l.dst.y);
	std::cout << "Please enter the rotation angle in radians." << std::endl;
	std::cin >> theta;
	rotateRay(l.dst, theta, 0, 0);
	line(l.src.x, l.src.y, l.dst.x, l.dst.y);
	system("pause"); // windows only feature
	closegraph();
	return 0;
}