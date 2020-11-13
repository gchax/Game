#include "random.h"

int generateRandom(int max)
{
	int randomNumber = rand();
	float random = (randomNumber % max) + 1;
	int myRandom = random;

	return myRandom;
}

int generateRandom0(int max)
{
	int randomNumber = rand();
	float random = (randomNumber % max) + 1;
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
