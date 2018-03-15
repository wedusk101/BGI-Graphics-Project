//vector.cpp
#include "primitives.h"
#include "vector.h"

namespace primitives
{
	Vec2 getNormalized(const Vec2 &v) // normalizes a vector
	{
		Vec2 result;
		double mag = getMagnitude(v);
		result.x = v.x / mag;
		result.y = v.y / mag;
		return result;
	}

	Vec2 point2Vec(const Point &src, const Point &dst) // returns a vector from a source point towards a destination point
	{
		return Vec2(dst.x - src.x, dst.y - src.y);
	}

	Point vec2Point(const Vec2 &v)
	{
		return Point(round(v.x), round(v.y));
	}

	Vec2 getNormaltoCircle(const Point &p, const Circle &circle) // returns the outward unit normal vector at a given point on circumference of a circle
	{
		return point2Vec(p, circle.center) / circle.radius;
	}
}