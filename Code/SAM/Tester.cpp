#include "Tester.h"


Tester::Tester()
{

}


Tester::~Tester()
{
	 
}

bool Tester::testLineAngleTrivial()
{
	Line l1;
	l1.m = 1;
	l1.b = 0;

	Line l2;
	l2.m = -1;
	l2.b = 0;

	double expected = M_PI/2;

	double answer = l1.angle(l2);
	if (answer == expected)
		return true;
	cout << "FAILED - testLineAngleTrivial:" << endl << "\texpected: " << expected
		<< " answer: " << answer << endl;
	return false;
}

bool Tester::testProjectionTrvial()
{
	Line l;
	l.b = 2;
	l.m = -1;

	Point input;
	input.x = 1;
	input.y = 1;

	Point expected;
	expected.x = 1;
	expected.y = 1;
	
	Point answer = l.project(input);

	if (answer == expected)
		return true;
	cout << "FAILED - testProjectionTrvial:" << endl << "\texpected: " << expected.toString() 
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
	expected.m = -1;
	expected.b = 2;

	Line answer = Line::pointsToLine(points, 0, points.size());
	if (expected == answer)
		return true;
	cout << "FAILED - testPointsToLineTrivial:" << endl << "\texpected: " << expected.toString()
		<< " answer: " << answer.toString() << endl;
	return false;
}

bool Tester::testPointLineAngleTirvial()
{
	PointLine l1;
	l1.start = Point(0, 1);
	l1.end = Point(1, 0);

	PointLine l2;
	l2.start = Point(0, 1);
	l2.end = Point(1, 0);

	double expected = 0;
	double answer = l1.angle(l2);
	answer = answer < 0.0 ? -answer : answer;
	if (expected == answer)
		return true;
	cout << "FAILED - testPointLineAngleTirvial:" << endl << "\texpected: " << expected
		<< " answer: " << answer << endl;
	return false;
}

bool Tester::testPointLineAngle90()
{
	PointLine l1;
	l1.start = Point(0, 1);
	l1.end = Point(1, 0);

	PointLine l2;
	l2.start = Point(0, 0);
	l2.end = Point(1, 1);

	double expected = M_PI/2;
	double answer = l1.angle(l2);
	answer = answer < 0.0 ? -answer : answer;
	if (expected == answer)
		return true;
	cout << "FAILED - testPointLineAngle90:" << endl << "\texpected: " << expected
		<< " answer: " << answer << endl;
	return false;
}

bool Tester::testPointLineAngle45()
{
	PointLine l1;
	l1.start = Point(0, 0);
	l1.end = Point(1, 1);

	PointLine l2;
	l2.start = Point(0, 0);
	l2.end = Point(1, 0);

	double expected = M_PI/4;
	double answer = l1.angle(l2);
	answer = answer < 0.0 ? -answer : answer;
	if (expected == answer)
		return true;
	cout << "FAILED - testPointLineAngle45:" << endl << "\texpected: " << expected
		<< " answer: " << answer << endl;
	return false;
}

bool Tester::testPointDistance()
{
	Point p1(0, 0);
	Point p2(sqrt(2)/2, sqrt(2)/2);

	double answer = p1.distance(p2);
	
	double expected = 1;

	if (expected == answer)
		return true;
	cout << "FAILED - testPointDistance:" << endl << "\texpected: " << expected
		<< " answer: " << answer << endl;
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
	cout << "starting: testLineAngleTrivial" << endl;
	passed += testLineAngleTrivial();
	sum++;
	cout << "starting: testPointLineAngle90" << endl;
	passed += testPointLineAngle90();
	sum++;
	cout << "starting: testPointLineAngle45" << endl;
	passed += testPointLineAngle45();
	sum++;
	cout << "starting: testPointDistance" << endl;
	passed += testPointDistance();
	sum++;
	
	auto end = clock.now();

	cout << 100.0*(float)passed / (float)sum << "% passed in " << (end-start).count() << " ms " << endl;
}