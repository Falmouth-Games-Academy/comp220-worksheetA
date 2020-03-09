#include "Time.h"

void Time::StartTimer()
{
	startTime = clock();
}

void Time::EndTimer()
{
	endTime = clock();

	deltaTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
}
