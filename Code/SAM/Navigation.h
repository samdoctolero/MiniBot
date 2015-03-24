#pragma once
#include "State.h"
#include "StateFactory.h"
#include <iostream>
#include "LineExtractor.h"
#include "PointLine.h"
#include "Laser.h"

using namespace std;

class Navigation
{

public:
	int currentState;
	Navigation();
	~Navigation();
	vector<State> allStates;
	vector<PointLine> getLines(Laser* laser);
};