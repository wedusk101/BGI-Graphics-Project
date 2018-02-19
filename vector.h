//vector.h
#pragma once

#ifndef VECTOR__H_
#define VECTOR__H_

#include <cmath>
#include "primitives.h"

namespace primitives
{
	struct Vec2
	{
		int x;
		int y;

		// Vec2() : x(0), y(0) {}		
		// Vec2(int x_, int y_) : x(x_), y(y_) {} // member initialization list

		Vec2 operator+ (const Vec2 &v) const
		{
			Vec2 result;
			result.x = x + v.x;
			result.y = y + v.y;
			return result;
		}

		Vec2 operator- (const Vec2 &v) const
		{
			Vec2 result;
			result.x = x - v.x;
			result.y = y - v.y;
			return result;
		}

		Vec2 operator* (const double &c) const // scalar multiplication
		{
			Vec2 result;
			result.x = x * c;
			result.y = y * c;
			return result;
		}

		Vec2 operator/ (const double &c) const // scalar division
		{
			Vec2 result;
			result.x = x / c;
			result.y = y / c;
			return result;
		}

	};
	
	typedef struct
	{
		Vec2 o;
		Vec2 d;
	} Ray;

	inline double getMagnitude(const Vec2 &v)
	{
		return sqrt(v.x * v.x + v.y * v.y);
	}

	inline double dotProduct(const Vec2 &v1, const Vec2 &v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	Vec2 getNormalized(const Vec2 &);
	Vec2 point2Vec(const Point &, const Point &);
}

#endif