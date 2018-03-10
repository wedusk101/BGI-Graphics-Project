//gameplay.cpp
#include "gameplay.h"
#include "physics.h"
#include "graphics.h"

namespace primitives
{
	void drawDirectionArrow(Line &l)
	{
		int state = 5;
		double arrowTheta = 4.8, radius = getEuclideanDistance(l.src.x, l.src.y, l.dst.x, l.dst.y); // radians
		while (1)
		{
			cleardevice();
			if (arrowTheta == 0 || arrowTheta == 1.570796) // pi / 2 radians
				state *= -1;
			l.dst.x = radius * cos(arrowTheta);
			l.dst.y = radius * sin(arrowTheta);
			line(l.src.x, l.src.y, l.dst.x, l.dst.y);
			arrowTheta += state;
			delay(33);
			// swapbuffers();			
		}
	}
	
}