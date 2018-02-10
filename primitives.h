//primitives.h
#ifndef PRIMITIVES__H_
#define PRIMITIVES__H_

typedef struct 
{
	int x;
	int y;
} Point;

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

#endif