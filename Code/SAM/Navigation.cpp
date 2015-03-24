#include "Navigation.h"


Navigation::Navigation()
{
	allStates.push_back(StateFactory::getGoalSeakingState());
	allStates.push_back(StateFactory::getObjectOrientState());
	allStates.push_back(StateFactory::getReverseState());
	allStates.push_back(StateFactory::getReverseTurnState());
	allStates.push_back(StateFactory::getAdjustState());
	currentState = 0;
}


Navigation::~Navigation()
{

}

vector<PointLine> Navigation::getLines(Laser* laser)
{
	laser->requestData();
	vector<Point> points = laser->getDataCart(true, 500.0,false);
	cout << points.size() << endl;
	for (auto it = points.begin(); it < points.end(); it++)
	{
		cout << (*it).toString() << endl;
	}
	
	return LineExtractor::splitMerge(points, 0, points.size());
}
