#pragma once
#include "Point.h"
#include "Line.h"

class PointLine
{
public:
	Point start;
	Point end;
	PointLine();
	~PointLine();
	static PointLine fromLine(Line aLine, Point start, Point end);
};

