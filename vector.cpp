//vector.cpp
#include "vector.h"

namespace primitives
{
	Vec2 getNormalized(const Vec2 &v) // normalizes a vector
	{
		Vec2 result;
		double mag = getMagnitude(v);
		result.x = static_cast<int>(v.x / mag);
		result.y = static_cast<int>(v.y / mag);
		return result;
	}

	Vec2 point2Vec(const Point &src, const Point &dst) // returns a vector from a source point towards a destination point
	{
		Vec2 vec;
		vec.x = dst.x - src.x;
		vec.y = dst.y - src.y;
		return vec;
	}

	Vec2 getNormaltoCircle(const Point &p, const Circle &circle) // returns the normal vector to a circle at a given point on its circumference
	{
		return point2Vec(p, circle.center) / circle.radius;
	}
}