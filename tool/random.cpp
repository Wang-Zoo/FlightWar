#include "random.h"
#include<iostream>
void initRandom()
{
	srand(time(0));
}

int getIntRange(int max, int min)
{
	if (max < min) {
		max = max ^ min;
		min = max ^ min;
		max = max ^ min;
	}
	return rand()%(max - min + 1)+min;
}
