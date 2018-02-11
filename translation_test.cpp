#include <iostream>
#include "graphics.h"
#include "primitives.h"
#include "matrix.h"
#include "windows.h"

int main()
{
	primitives::Line l, tl;
	std::cout << "Please enter the coordinates for the end points of a line (x,y)." << std::endl;
	std::cin >> l.src.x >> l.src.y >> l.dst.x >> l.dst.y;
	initwindow(800, 600, "First Sample");
	setcolor(12);
	line(l.src.x, l.src.y, l.dst.x, l.dst.y);
	std::cout << "Please enter the translation values for the end points of the line (tx, ty)." << std::endl;
	std::cin >> tl.src.x >> tl.src.y >> tl.dst.x >> tl.dst.y;
	translate(l.src, tl.src.x, tl.src.y);
	translate(l.dst, tl.dst.x, tl.dst.y);
	line(l.src.x, l.src.y, l.dst.x, l.dst.y);
	system("pause"); // windows only feature
	closegraph();
	return 0;
}