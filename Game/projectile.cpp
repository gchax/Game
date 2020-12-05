#include "projectile.h"

projectile::projectile(Texture* texture, float speed, int attackDamage)
{
	this->speed = speed;
	this->damage = attackDamage;
	body.setSize(Vector2f(15.f, 15.f));
	body.setPosition(Vector2f(0.f, 0.f));
	body.setOrigin(body.getSize() / 2.f);
	body.setTexture(texture);
}

void projectile::update(float deltaTime)
{
	if (direction == UP) body.move(0, -(speed * deltaTime));
	if (direction == DOWN) body.move(0, speed * deltaTime);
	if (direction == LEFT) body.move(-(speed * deltaTime), 0);
	if (direction == RIGHT) body.move(speed * deltaTime, 0);
}

void projectile::draw(RenderWindow& window)
{
	window.draw(body);
}
