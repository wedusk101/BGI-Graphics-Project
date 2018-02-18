//fx.cpp
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "graphics.h"
#include "fx.h"
#include "matrix.h"
#include "physics.h"

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
				theta = (rand() % 360 + 1) / 57.3; // generates a random angle between 0 and 2 * pi radians

				x  = radius * cos(theta) + center.x;
				y  = radius * sin(theta) + center.y;

				putpixel(x, y, 12);
				//delay(10);
			}
		}
	}

	void showerConfetti(const int &xMax, const int &yMax, const double &acceleration, const double &stepSize, const int &width, const int &height, const int &particleCount) // maybe this needs to be multithreaded - WIP
	{
		srand(time(NULL));
		int x = 0, y = 0, tx = 0, ty = 0, i = 0;
		double theta = 0.0, dummy = 0.0;

		for (i = 0; i != particleCount; i++)
		{
			Point locus, currentPosition;
			Rectangle confetti;
			confetti.tL.x = rand() % xMax - 10; // 10 is a bias value
			confetti.tL.y = 0;
			confetti.bR.x = confetti.tL.x + width;
			confetti.bR.y = height;
			theta = (rand() % 180) / 57.3; // generates a random angle between 0 and pi radians
			ty = rand() % (yMax / 50);
			rotateRay(confetti.tL, theta, 0, 0);
			rotateRay(confetti.bR, theta, 0, 0);
			rectangle(confetti.tL.x, confetti.tL.y, confetti.bR.x, confetti.bR.y);
			currentPosition.x = confetti.bR.x;
			currentPosition.y = confetti.bR.y + ty;


			locus = getNextPositionVerlet(confetti.bR, currentPosition, acceleration, stepSize, dummy);
			while (locus.y <= yMax)
			{
				rectangle(confetti.bR.x - width, confetti.bR.y - height, confetti.bR.x, confetti.bR.y);
				locus = getNextPositionVerlet(confetti.bR, currentPosition, acceleration, 0.5, dummy);
				//cleardevice();
			}

		}
	}
}

void boxBlur(const int &xpx, const int &ypx, const int &xMax, const int &yMax, const int &radius) // WIP
{
	int sample = 0;

	if (xpx < 0 || xpx > xMax)
		return;
	if (ypx < 0 || ypx > yMax)
		return;
}