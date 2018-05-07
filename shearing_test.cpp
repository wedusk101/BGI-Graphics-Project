#include <iostream>
#include "graphics.h"
#include "primitives.h"
#include "matrix.h"
#include "windows.h"

int main() // performs shearing along the x axis
{
	primitives::Rectangle box;
	primitives::Point shearFactor;
	initwindow(800, 600, "First Sample");
	setcolor(12);
	std::cout << "Please enter the coordinates for the vertices of a rectangle (x,y)." << std::endl;
	std::cin >> box.tL.x >> box.tL.y >> box.bR.x >> box.bR.y;
	// rectangle(box.tL.x, box.tL.y, box.bR.x, box.bR.y); 
	// draws the rectangle using individual lines
	line(box.tL.x, box.tL.y, box.bR.x, box.tL.y);
	line(box.tL.x, box.tL.y, box.tL.x, box.bR.y);
	line(box.tL.x, box.bR.y, box.bR.x, box.bR.y);
	line(box.bR.x, box.tL.y, box.bR.x, box.bR.y);
	std::cout << "Please enter the shearing values for the axes (shX, shY)." << std::endl;
	std::cin >> shearFactor.x >> shearFactor.y;
	primitives::Point p1(box.bR.x, box.bR.y), p2(box.tL.x, box.bR.y);
	shearRay(p1, shearFactor.x, shearFactor.y);
	shearRay(p2, shearFactor.x, shearFactor.y);	
	setcolor(14);
	// draws the rectangle after shearing
	line(box.tL.x, box.tL.y, box.bR.x, box.tL.y);
	line(box.tL.x, box.tL.y, p2.x, p2.y);
	line(p2.x, p2.y, p1.x, p1.y);
	line(box.bR.x, box.tL.y, p1.x, p1.y);
	system("pause"); // windows only feature
	closegraph();
	return 0;
}