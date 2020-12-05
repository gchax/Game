#pragma once
#include "stdfn.h"

class damageDisplay
{
public:
	Text text;
	string damage;
	int counter = 0;
	int lifetime = 50;
	float speed = 300;
	bool destroy = false;

	damageDisplay();

	void update(float deltaTime);

private:
};

