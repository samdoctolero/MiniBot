#include "Robot.h"

Robot::Robot()
{
}


Robot::~Robot()
{
}

void Robot::run()
{
	vector<PointLine> lines = nav.getLines(&laser);
	cout << lines.size() << endl;
	for (int i = 0; i < lines.size(); i++)
	{
		cout << lines[i].toString() << endl;
	}
}