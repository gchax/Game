#pragma once
#include "stdfn.h"
#include "collider.h"

class projectile
{
public:
	projectile(Texture* texture, float speed, float attackDamage);

	int direction = UP;
	bool isCollided = false;
	RectangleShape body;

	void update(float deltaTime);
	void draw(RenderWindow& window);

	collider getCollider() { return collider(body); }

private:
	float speed;
	float atkdmg;
};