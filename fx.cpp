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
		int x = 0, y = 0, tx = 0, ty = 0, i = 0, j = 0;
		double theta = 0.0, dummy = 0.0;

		// containers should be used here instead of traditional arrays
		// this is just for legacy purposes and will change soon
		Point *locus = new Point[particleCount];
		Point *currentPosition = new Point[particleCount];
		Rectangle *confetti = new Rectangle[particleCount];

		for (i = 0; i != particleCount - 1; i++) // spawns the particles
		{
			confetti[i].tL.x = rand() % xMax; // use a bias value if needed
			confetti[i].tL.y = 0;
			confetti[i].bR.x = confetti[i].tL.x + width;
			confetti[i].bR.y = height;


			theta = (rand() % 180) / 57.3; // generates a random angle between 0 and pi radians
			ty = rand() % (yMax / 50); // controls the velocity of the particles - where 0 <= ty < yMax
			rotateRay(confetti[i].tL, theta, 0, 0); // rotates individual confettis randomly
			rotateRay(confetti[i].bR, theta, 0, 0);
			rectangle(confetti[i].tL.x, confetti[i].tL.y, confetti[i].bR.x, confetti[i].bR.y);


			currentPosition[i].x = confetti[i].bR.x;
			currentPosition[i].y = confetti[i].bR.y + ty;


			locus[i] = getNextPositionVerlet(confetti[i].bR, currentPosition[i], acceleration, stepSize, dummy);
		}
		
		
		// for(i = 0; locus[i].y <= yMax; i++) // creates the shower of particles
		while (locus[j].y <= yMax)
		{
			for (i = 0, j = i; i != particleCount - 1; i++)
			{
				rectangle(confetti[i].bR.x - width, confetti[i].bR.y - height, confetti[i].bR.x, confetti[i].bR.y);
				locus[i] = getNextPositionVerlet(confetti[i].bR, currentPosition[i], acceleration, stepSize, dummy);
				//cleardevice();
			}
		}

		delete [] locus, currentPosition, confetti; // cleanup
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