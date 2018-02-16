//vector.cpp
#include "vector.h"

namespace primitives
{
	Vec2 getNormalized(const Vec2 &v) // normalizes a vector
	{
		Vec2 result;
		double mag = getMagnitude(v);
		result.x /= mag;
		result.y /= mag;
		return result;
	}

	Vec2 point2Vec(const Point &src, const Point &dst) // returns a vector from a source point towards a destination point
	{
		Vec2 vec;
		vec.x = dst.x - src.x;
		vec.y = dst.y - src.y;
		return vec;
	}	
}