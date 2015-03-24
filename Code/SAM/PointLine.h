#pragma once
#include "Line.h"
#include "Point.h"


class PointLine
{
public:
	Point start;
	Point end;
	PointLine();
	~PointLine();
	static PointLine fromLine(Line aLine, Point start, Point end);
	Line toLine();
	string toString();
	bool mergeIfColl(PointLine other, PointLine* ret);
	double angle(PointLine other);
	bool operator==(PointLine other);
	static double collDistThresh;
	static double collAngleThresh;
};

