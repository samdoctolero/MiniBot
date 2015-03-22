#include "LineExtractor.h"


LineExtractor::LineExtractor()
{
}


LineExtractor::~LineExtractor()
{
}

double LineExtractor::threshold = 100; //100 mm 

vector<PointLine> LineExtractor::splitMerge(vector<Point> points, int startIndex, int endIndex)
{
	bool found = false;
	Line current = Line::pointsToLine(points, startIndex, endIndex);
	int max = -1;
	double maxVal = 0;
	for (int i = startIndex; i < endIndex; i++)
	{
		double currentDist = current.distance(points[i]);
		if (currentDist > maxVal)
		{
			max = i;
			maxVal = currentDist;
		}
	}
	if (maxVal <= threshold)
	{
		vector<PointLine> ret;
		ret.push_back(PointLine::fromLine(current, points[startIndex], points[endIndex]));
		return ret;
	}
	vector<PointLine> left = splitMerge(points, startIndex, startIndex + max);
	vector<PointLine> right = splitMerge(points, startIndex + max + 1, endIndex);
	left.insert(left.end(), right.begin(), right.end());
	return left;
}