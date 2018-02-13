//matrix.cpp
#include "matrix.h"

namespace primitives
{
	void rotateRay(Point &p, const double &theta, const int &pivotX, const int &pivotY)
	{
		Point bak = p;
		p.x = (int)pivotX + (bak.x - pivotX) * cos(theta) - (bak.y - pivotY) * sin(theta);
		p.y = (int)pivotY + (bak.x - pivotX) * sin(theta) + (bak.y - pivotY) * cos(theta);
	}


	void translatePoint(Point &p, const int &tx, const int &ty)
	{
		p.x = p.x + tx;
		p.y = p.y + ty;
	}

	void scaleRay(Point &p, const int &sx, const int &sy)
	{
		p.x = sx * p.x;
		p.y = sy * p.y;
	}

	Point getTranslatedPoint(const Point &p, const int &tx, const int &ty)
	{
		Point translatedPoint;
		translatedPoint.x = p.x + tx;
		translatedPoint.y = p.y + ty;
		return translatedPoint;
	}

	Point getRotatedPoint(const Point &p, const double &theta, const int &pivotX, const int &pivotY)
	{
		Point rotatedPoint;
		rotatedPoint.x = (int)pivotX + (p.x - pivotX) * cos(theta) - (p.y - pivotY) * sin(theta);
		rotatedPoint.y = (int)pivotY + (p.x - pivotX) * sin(theta) + (p.y - pivotY) * cos(theta);
		return rotatedPoint;
	}

	Point getScaledRay(const Point &p, const int &sx, const int &sy)
	{
	    Point scaledRay;
	    scaledRay.x = sx * p.x;
	    scaledRay.y = sy * p.y;
	    return scaledRay;
	}
}

