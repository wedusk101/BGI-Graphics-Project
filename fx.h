//fx.h
#pragma once

#include "graphics.h"
#include "primitives.h"

#ifndef FX__H_
#define FX__H_

namespace primitives
{
	void shockWave(const Point &, const int &, const int &);
}

void boxBlur(const int &, const int &, const int &, const int &, const int &); // WIP

#endif