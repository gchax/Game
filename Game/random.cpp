#include "random.h"

int generateRandom(int max, float start)
{
	int randomNumber = rand();
	float random = (randomNumber % max) + start;
	int myRandom = random;

	return myRandom;
}

int generateIntRandom(int max, int start)
{
	int randomNumber = rand();
	float random = (randomNumber % max) + start;
	int myRandom = random;

	return myRandom;
}

bool generateRandomBoolean()
{
	int randomNumber = rand();
	float random = (randomNumber % 2) + 1;
	int myRandom = random;
	if (myRandom == 1) return true;
	else return false;
}
