#pragma once
#include "stdfn.h"
#include "animation.h"
#include "collider.h"

class enemy
{
public:
	int direction = LEFT;
	int counter = 0;
	bool isCollided = false;
	bool isDead = false;
	bool isRespawned = false;
	bool isAggroed = false;
	int action = 0;
	int effectLifetime = 0;
	float hp;
	float damage;
	float speed;
	RectangleShape body;
	enemy(Texture* texture, Vector2u imageCount, Vector2f size, Vector2f position, float switchTime, float speed, float hp, int damage);
	~enemy();

	void updateStill(float deltaTime);
	void updateAggroedFly(float deltaTime, Vector2f playerPosition);
	void updateWalk(float deltaTime, Vector2f playerPosition);
	void updateAggrovated(float deltaTime, Vector2f playerPosition);
	void updateBoss(float deltaTime);
	void hurt();
	void draw(RenderWindow& window);

	collider getCollider() { return collider(body); }

private:
	animation animation;
	Vector2f size;
	Vector2f position;
	unsigned int row = 0;
};