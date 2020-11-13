#include "projectile.h"

projectile::projectile(Texture* texture, float speed, float attackDamage)
{
	this->speed = speed;
	this->atkdmg = attackDamage;
	body.setSize(Vector2f(15.f, 15.f));
	body.setPosition(Vector2f(0.f, 0.f));
	body.setOrigin(body.getSize() / 2.f);
	body.setTexture(texture);
}

void projectile::update(float deltaTime)
{
	Vector2f movement(0.0f, 0.0f);

	if (direction == 'u')
	{
		body.move(0, -(speed));
	}
	if (direction == 'd')
	{
		body.move(0, speed);
	}
	if (direction == 'l')
	{
		body.move(-(speed), 0);
	}
	if (direction == 'r')
	{
		body.move(speed, 0);
	}
}