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
	body.setFillColor(Color(255, 255, 255, 255));
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void enemy::updateFly(float deltaTime, Vector2f playerPosition)
{
	body.setFillColor(Color(255, 255, 255, 255));
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.setPosition(position.x, playerPosition.y);
}

void enemy::updateWalk(float deltaTime)
{
	body.setFillColor(Color(255, 255, 255, 255));

	if (direction == IDLE)
	if (direction == UP)
	{
		body.move(0, -(speed * deltaTime));
	}
	if (direction == DOWN)
	{
		body.move(0, speed * deltaTime);
	}
	if (direction == LEFT)
	{
		body.move(-(speed * deltaTime), 0);
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

void enemy::updateSemiBoss(float deltaTime)
{
	body.setFillColor(Color(255, 255, 255, 255));
}

void enemy::updateBoss(float deltaTime)
{
	body.setFillColor(Color(255, 255, 255, 255));
}

void enemy::hurt()
{
	body.setFillColor(Color(255, 0, 0, 255));
}

void enemy::draw(RenderWindow& window)
{
	window.draw(body);
}