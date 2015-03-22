#pragma once

using namespace std;

class Wheels
{
private: 

public:
	int leftSpeed;
	int rightSpeed;
	int MoveFlag;

	Wheels();
	~Wheels();

	static void Move(int* right, int* left, int* flag);
	void UpdateSpeeds(int left, int right);
	void UpdateFlag(int flag);

};