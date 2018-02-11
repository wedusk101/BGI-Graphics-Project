#include <iostream>
#include "graphics.h"
#include "primitives.h"
#include "matrix.h"
#include "windows.h"

int main()
{
	Line l;
	primitives::Point scaleFactor;
	std::cout << "Please enter the coordinates for the end points of a line (x,y)." << std::endl;
	std::cin >> l.src.x >> l.src.y >> l.dst.x >> l.dst.y;
	initwindow(800, 600, "First Sample");
	setcolor(12);
	line(l.src.x, l.src.y, l.dst.x, l.dst.y);
	std::cout << "Please enter the scaling values for the axes (sx, sy)." << std::endl;
	std::cin >> scaleFactor.x >> scaleFactor.y;
	scale(l.src, scaleFactor.x, scaleFactor.y);
	scale(l.dst, scaleFactor.x, scaleFactor.y);
	line(l.src.x, l.src.y, l.dst.x, l.dst.y);
	system("pause"); // windows only feature
	closegraph();
	return 0;
}