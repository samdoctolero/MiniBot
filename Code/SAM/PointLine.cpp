#include "PointLine.h"


PointLine::PointLine()
{
}


PointLine::~PointLine()
{
}

PointLine PointLine::fromLine(Line aLine, Point start, Point end)
{
	PointLine pl;
	pl.start = aLine.project(start);
	pl.end = aLine.project(end);
	return pl;
}