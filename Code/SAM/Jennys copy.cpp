#include "Tester.h"


Tester::Tester()
{

}


Tester::~Tester()
{
	 
}



bool Tester::testProjectionTrvial()
{
    
//Test 1
    
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
    
 //Test 2
    /*
    
    Line l2;
    l2.r = 1;
    l2.theta = M_PI/4;
    Point input2;
    input2.x = 1/2;
    input2.y = 1;
    Point expected2;
    expected2.x = 1/4;
    expected2.y = 1/4;
    Point answer2 = l2.project(input2);
    	if (answer2 == expected2)
		return true;
	cout << "FAILED - testProjectionTrvial:\t" << "expected: " << expected2.toString() 
		<< " answer: " << answer2.toString() << endl;
	return false;
//Test 3
    
    Line l3;
    l3.r = 2;
    l3.theta = 2*M_PI/3;
    Point input3;
    input3.x = -3;
    input3.y = 1.5;
    Point expected3;
    expected3.x = -((9+1.5*sqrt(3.0)) / 4.0);
    expected3.y = (9+1.5*sqrt(3.0)) / (4.0*sqrt(3.0));
    Point answer3 = l3.project(input3);
    	if (answer3 == expected3)
		return true;
	cout << "FAILED - testProjectionTrvial:\t" << "expected: " << expected3.toString() 
		<< " answer: " << answer3.toString() << endl;
	return false;
 //Test 4
    
    Line l4;
    l4.r = 1;
    l4.theta = 11*M_PI/6;
    Point input4;
    input4.x = sqrt(3);
    input4.y = -1;
    Point expected4;
    expected4.x = sqrt(3.0) / 2.0;
    expected4.y = -1/ 2.0;
    Point answer4 = l4.project(input4);
    	if (answer4 == expected4)
		return true;
	cout << "FAILED - testProjectionTrvial:\t" << "expected: " << expected4.toString() 
		<< " answer: " << answer4.toString() << endl;
	return false;
	*/


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