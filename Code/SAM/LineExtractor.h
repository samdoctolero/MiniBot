#pragma once
#include <vector>
#include "PointLine.h"
#include "Line.h"
#include <iostream>
#include <stack>

using namespace std;

class LineExtractor
{
public:
	static double minDistThreshold;
	static double clusterThreshold;
	LineExtractor();
	~LineExtractor();
	static vector<PointLine> splitMerge(vector<Point> points, int startIndex, int endIndex);
	static vector<PointLine> merge(vector<PointLine> lines);
};

