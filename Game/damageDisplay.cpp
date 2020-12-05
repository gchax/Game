#include "damageDisplay.h"

damageDisplay::damageDisplay()
{
	text.setFillColor(Color::Red);
	text.setCharacterSize(25);
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
}

void damageDisplay::update(float deltaTime)
{
	text.move(0.f, -speed * deltaTime);
	counter++;
	if (counter >= lifetime) destroy = true;
}
