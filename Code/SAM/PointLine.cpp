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
	pl.start = start;
	pl.end = end;
	//pl.start = aLine.project(start);
	//pl.end = aLine.project(end);
	return pl;
}

double PointLine::angle(PointLine other)
{
	Line l1 = toLine();
	Line l2 = other.toLine();
	return l1.angle(l2);
}

constexpr double pi() { return atan(1) * 4; }
double PointLine::collDistThresh = 30;
double PointLine::collAngleThresh = pi()*0.02222222;


bool PointLine::mergeIfColl(PointLine other, PointLine* ret)
{
	double temp = angle(other);
	if (temp < 0 ? -temp : temp > collAngleThresh)
	{	
		return false;
	}

	vector<double> dists;
	dists.push_back(start.distance(other.start));
	dists.push_back(start.distance(other.end));
	dists.push_back(end.distance(other.start));
	dists.push_back(end.distance(other.end));

	int min = 0;
	int max = 0;
	for (int i = 0; i < dists.size(); i++)
	{
		min = dists[i] < dists[min] ? i : min;
		max = dists[i] > dists[max] ? i : max;
	}

	if (dists[min] > collDistThresh)
		return false;
	
	Point newStart;
	Point newEnd;

	if (max == 0)
	{
		newStart = start;
		newEnd = other.start;
	}
	else if (max == 1)
	{
		newStart = start;
		newEnd = other.end;
	}
	else if (max == 2)
	{
		newStart = end;
		newEnd = other.start;
	}
	else if (max == 3)
	{
		newStart = end;
		newEnd = other.end;
	}

	ret->start = newStart;
	ret->end = newEnd;
	return true;
}

bool PointLine::operator==(PointLine other)
{
	return (start == other.start && end == other.end) || (start == other.end && end == other.start);
}

Line PointLine::toLine()
{
	Line l;
	l.m = (start.y - end.y) / (start.x - end.x);
	//b = y-mx
	l.b = start.y - l.m*start.x;
	return l;
}

string PointLine::toString()
{
	stringstream ss;
	//ss << "start: " << start.toString() << " end: " << end.toString();
	ss << start.toString() << "\n" << end.toString();
	return ss.str();
}