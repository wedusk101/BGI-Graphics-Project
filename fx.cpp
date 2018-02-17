//fx.cpp
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "graphics.h"
#include "fx.h"

namespace primitives
{
	void shockWave(const Point &center, const int &minRadius, const int &maxRadius)
	{
		srand(time(NULL));
		double theta = 0.0;
		int x = 0, y = 0, radius = 0;
		for (radius = minRadius; radius != maxRadius; radius += 5)
		{
			for (int i = 0; i != 50; i++)
			{
				theta = (rand() % 360 + 1) / 57.3;

				x  = radius * cos(theta) + center.x;
				y  = radius * sin(theta) + center.y;

				putpixel(x, y, 12);
				//delay(10);
			}
		}
	}
}

void boxBlur(const int &xpx, const int &ypx, const int &xMax, const int &yMax, const int &radius)
{
	int sample = 0;

	if (xpx < 0 || xpx > xMax)
		return;
	if (ypx < 0 || ypx > yMax)
		return;
}