//vector.h
#ifndef VECTOR__H_
#define VECTOR__H_

#include <cmath>
#include "primitives.h"

namespace primitives
{
	typedef struct
	{
		int x;
		int y;
	} Vec2;

	inline double getMagnitude(const Vec2 &v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	inline double dotProduct(const Vec2 &v1, const Vec2 &v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	Vec2 getNormalized(const Vec2 &);
}

#endif