#pragma once	

#include <ctime>

class Time
{
public:
	Time() {};
	~Time() {};

	void StartTimer();
	void EndTimer();

	float deltaTime = 0;
private:
	clock_t startTime;
	clock_t endTime;
};