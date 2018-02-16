//vector.cpp
#include "vector.h"

namespace primitives
{
	Vec2 getNormalized(const Vec2 &v)
	{
		Vec2 result;
		double mag = getMagnitude(v);
		result.x /= mag;
		result.y /= mag;
		return result;
	}
}
