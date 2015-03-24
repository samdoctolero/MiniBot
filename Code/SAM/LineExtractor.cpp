#include "LineExtractor.h"


LineExtractor::LineExtractor()
{
}


LineExtractor::~LineExtractor()
{
}

vector<PointLine> LineExtractor::merge(vector<PointLine> lines)
{
	vector<PointLine> copy(lines);

	for (int i = 0; i < copy.size(); i++)
	{
		for (int j = 0; j < copy.size(); j++)
		{
			if (i < 0)
				i = 0;
			if (i == j)
				continue;
			PointLine merged;
			if (copy[i].mergeIfColl(copy[j], &merged))
			{
				//cout << "size: " << copy.size() << " i: " << i << " j: " << j << endl;
				//cout << "merging " << copy[i].toString() << " with " << copy[j].toString() << endl << endl << endl;
				copy.erase(copy.begin() + i);
				//adjust indicies accordingly
				if (j >= i)
					j--;
				//i--;
				copy.erase(copy.begin() + j);
				if (i >= j)
					i--;
				j--;

				//cout << " i: " << i << " j: " << j << endl;

				copy.push_back(merged);
			}
		}
	}
	return copy;
}

double LineExtractor::minDistThreshold = 30; //110 mm 
double LineExtractor::clusterThreshold = 25;

vector<PointLine> LineExtractor::splitMerge(vector<Point> points, int startIndex, int endIndex)
{
	//initialize L
	vector<PointLine> L;
	stack<vector<Point> > st;
	int last = 0;

	for (int i = 0; i < points.size()-1; i++)
	{
		if (points[i].distance(points[i + 1]) > clusterThreshold || i == points.size()-2)
		{
			//cout << "found one " << points[i].distance(points[i + 1]) << " at " << i << " from " << last << endl;
			//cout << points[last].toString() << " : " << points[i].toString() << endl;
			vector<Point> temp;
			for (int j = last; j<=i; j++)
			{
				temp.push_back(points[j]);
			}
			last = i+1;
			if (temp.size()>1)
				st.push(temp);
		}
	}
	//cout << "stack size " << st.size() << endl;
	if (st.empty())
		st.push(points);

	while (!st.empty())
	{
		vector<Point> currentPoints = st.top();
		st.pop();
		//fit a line for the next si in L
		Line fit = Line::pointsToLine(currentPoints, 0, currentPoints.size());
		
		int max = -1;
		double maxVal = 0;
		//find the point with the max distance to L
		for (int i = 0; i < currentPoints.size(); i++)
		{
			double currentDist = fit.distance(currentPoints[i]);
			if (currentDist > maxVal && currentDist > minDistThreshold && i > 2 && i < currentPoints.size() - 3)
			{
				bool hasLeftOver =	i > 0 && 
									fit.distance(currentPoints[i - 1]) > minDistThreshold &&
									fit.sameSide(currentPoints[i],currentPoints[i-1]);

				bool hasRightOver = i < currentPoints.size() && 
									fit.distance(currentPoints[i + 1]) > minDistThreshold && 
									fit.sameSide(currentPoints[i], currentPoints[i + 1]);
				if (hasRightOver || hasLeftOver)
				{
					max = i;
					maxVal = currentDist;
				}
				else
				{
					currentPoints.erase(currentPoints.begin() + i);
					i--;
				}
			}
		}
		//cout << "max: " << max << endl;
		if (max == -1)
		{
			//cout << "adding set to final! size: " << currentPoints.size() << endl;
			//if all points fit criteria considder this a full line and add it to the set
			PointLine pl = PointLine::fromLine(fit, currentPoints[0], currentPoints.back());
			L.push_back(pl);
			continue;
		}
		//cout << "max point: " << currentPoints[max].toString() << endl;

		//construct left set
		vector<Point>::iterator leftFirst = currentPoints.begin();
		vector<Point>::iterator leftLast = currentPoints.begin() + max;
		//cout << "left first: " << 0 << " left last " << max << endl;
		vector<Point> left(leftFirst, leftLast);

		//construct right set
		vector<Point>::iterator rightFirst = currentPoints.begin() + max + 1;
		vector<Point>::iterator rightLast = currentPoints.end();
		//cout << "right first: " << max + 1 << " right last " << currentPoints.size() << endl;
		vector<Point> right(rightFirst, rightLast);

		//add them to the stack
		if (left.size() > 2)
			st.push(left);
		if (right.size() > 2)
			st.push(right);
	}

	cout << L.size() << endl;
	for (int i = 0; i < L.size(); i++)
	{
		cout << L[i].toString() << endl;
	}
	return merge(L);
}

/*vector<PointLine> LineExtractor::splitMerge(vector<Point> points, int startIndex, int endIndex)
{
	if (endIndex == startIndex)
	{
		vector<PointLine> pl;
		return pl;
	}
	cout << "getting points based on start: " << startIndex << " and end: " << endIndex << endl;
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
	if (max == startIndex || endIndex == max)
	{
		vector<PointLine> pl;
		return pl;
	}
	if (maxVal <= minDistThreshold)
	{
		vector<PointLine> ret;
		ret.push_back(PointLine::fromLine(current, points[startIndex], points[endIndex]));
		return ret;
	}
	vector<PointLine> left = splitMerge(points, startIndex, startIndex + max);
	vector<PointLine> right = splitMerge(points, startIndex + max + 1, endIndex);
	left.insert(left.end(), right.begin(), right.end());
	return left;
}*/