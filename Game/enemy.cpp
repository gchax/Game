#include "enemy.h"
#include "random.h"

enemy::enemy(Texture* texture, Vector2u imageCount, Vector2f size, Vector2f position, float switchTime, float speed, float hp, int damage) :
	animation(texture, imageCount, switchTime)
{
	this->size = size;
	this->position = position;
	this->speed = speed;
	this->hp = hp;
	this->damage = damage;

	body.setSize(size);
	body.setPosition(position);
	body.setTexture(texture);
	body.setOrigin(body.getSize() / 2.f);
}

enemy::~enemy()
{
}

void enemy::updateStill(float deltaTime)
{
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateAggroedFly(float deltaTime, Vector2f playerPosition)
{
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.setPosition(position.x, playerPosition.y);
}

void enemy::updateWalk(float deltaTime, Vector2f playerPosition)
{
	if (direction == IDLE);
	if (direction == UP) body.move(0, -speed * deltaTime);
	if (direction == DOWN) body.move(0, speed * deltaTime);
	if (direction == LEFT)
	{
		body.move(-speed * deltaTime, 0);
		row = 0;
	}
	if (direction == RIGHT)
	{
		body.move(speed * deltaTime, 0);
		row = 2;
	}

	counter++;
	if (counter >= 300)
	{
		direction = generateIntRandom(10, 0);
		counter = 0;
	}

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateAggrovated(float deltaTime, Vector2f playerPosition)
{
	if (action == 1)
	{
		if (body.getPosition().x > playerPosition.x)
		{
			body.move(-speed * deltaTime, 0);
			row = 0;
		}
		else
		{
			body.move(speed * deltaTime, 0);
			row = 2;
		}
		if (body.getPosition().y > playerPosition.y) body.move(0, -speed * deltaTime);
		else body.move(0, speed * deltaTime);
	}

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateBoss(float deltaTime)
{
}

void enemy::draw(RenderWindow& window)
{
	window.draw(body);
}