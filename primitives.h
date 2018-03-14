//primitives.h
#pragma once

#ifndef PRIMITIVES__H_
#define PRIMITIVES__H_

namespace primitives
{

	struct Point
	{
		int x;
		int y;

		Point() : x(0), y(0) {}
		Point(const int &x_, const int &y_) : x(x_), y(y_) {}
	};

	typedef struct
	{
		Point src;
		Point dst;
	} Line;

	typedef struct
	{
		Point center;
		int radius;
	} Circle;

	typedef struct
	{
		Point tL;
		Point bR;
		Point center; // mid point of the diagonal
		int width;
		int height;
	} Rectangle;

	inline Point midPoint(const Point &start, const Point &end)
	{
		return Point((start.x + end.x) / 2, (start.y + end.y) / 2);
	}

	Rectangle getRectangle(const int &topLeftX, const int &topLeftY, const int &bottomRightX, const int &bottomRightY)
	{
		Rectangle rect;
		rect.tL.x = topLeftX;
		rect.tL.y = topLeftY;
		rect.bR.x = bottomRightX;
		rect.bR.y = bottomRightY;
		rect.center.x = (topLeftX + bottomRightX) / 2; // potential overflow bug
		rect.center.y = (topLeftY + bottomRightY) / 2;
		rect.width = bottomRightX - topLeftX;
		rect.height = bottomRightY - topLeftY;
		return rect;
	}
}

#endif