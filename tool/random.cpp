#include "random.h"
#include<iostream>
void initRandom()
{
	srand(static_cast<unsigned int>(time(nullptr)));
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
