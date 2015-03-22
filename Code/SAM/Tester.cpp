#include "Tester.h"


Tester::Tester()
{

}


Tester::~Tester()
{
	 
}



bool Tester::testProjectionTrvial()
{
	Line l;
	l.r = 1;
	l.theta = M_PI/4;

	Point input;
	input.x = 1;
	input.y = 1;

	Point expected;
	expected.x = sqrt(2.0) / 2.0;
	expected.y = sqrt(2.0) / 2.0;
	
	Point answer = l.project(input);

	if (answer == expected)
		return true;
	cout << "FAILED - testProjectionTrvial:\t" << "expected: " << expected.toString() 
		<< " answer: " << answer.toString() << endl;
	return false;
}

bool Tester::testPointsToLineTrivial()
{
	vector<Point> points;
	points.push_back(Point(0, 2));
	points.push_back(Point(1, 1));
	points.push_back(Point(2, 0));

	Line expected;
	expected.r = sqrt(2.0) / 2.0;
	expected.theta = M_PI / 4;

	Line answer = Line::pointsToLine(points, 0, points.size());
	if (expected == answer)
		return true;
	cout << "FAILED - testPointsToLineTrivial:\t" << "expected: " << expected.toString()
		<< " answer: " << answer.toString() << endl;
	return false;
}

void Tester::testAll()
{
	int sum = 0;
	int passed = 0;
	auto clock = chrono::high_resolution_clock();
	auto start = clock.now();

	cout << "starting: testProjectionTrvial" << endl;
	passed += testProjectionTrvial();
	sum++;
	cout << "starting: testPointsToLineTrivial" << endl;
	passed += testPointsToLineTrivial();
	sum++;
	
	auto end = clock.now();

	cout << (float)passed / (float)sum << "% passed in " << (end-start).count() << " ms " << endl;
}