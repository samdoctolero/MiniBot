#pragma once

using namespace std;

class Wheels
{
private: 
	int leftSpeed;
	int rightSpeed;
	int MoveFlag;

public:
	
	Wheels();
	~Wheels();

	void Move();
	void GetSpeeds(int &left, int &right);
	void UpdateSpeeds(int left, int right);
	void UpdateFlag(int flag);
	int GetFlag();

};