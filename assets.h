//assets.h
#pragma once

#ifndef ASSETS__H_
#define ASSETS__H_

#include "primitives.h"

namespace primitives
{
	typedef struct
	{
		Point center;
		Line uString;
		Line lString;
	} Bow;

	Humanoid genHumanoid(const Point &); //centre of the circle constituting the head is passed as argument
	Bow genBow(const Point &);
}

#endif
