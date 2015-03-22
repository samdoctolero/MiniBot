#pragma once
#include <vector>
#include "PointLine.h"
#include "Line.h"

using namespace std;

class LineExtractor
{
public:
	static double threshold;
	LineExtractor();
	~LineExtractor();
	static vector<PointLine> splitMerge(vector<Point> points, int startIndex, int endIndex);
};

