#include "player.h"

player::player(Texture* texture, Vector2u imageCount, float switchTime, float speed) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 4;

	body.setSize(Vector2f(71.11f, 120.0f));
	body.setOrigin(body.getSize() / 2.f);
	body.setTexture(texture);
}

player::~player()
{
}

void player::update(float deltaTime)
{
	Vector2f movement(0.0f, 0.0f);

	//walk
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		movement.y -= speed * deltaTime;
		direction = UP;
		row = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		movement.y += speed * deltaTime;
		direction = DOWN;
		row = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::A))
	{
		movement.x -= speed * deltaTime;
		direction = LEFT;
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		movement.x += speed * deltaTime;
		direction = RIGHT;
		row = 7;
	}

	if (row == 1 && movement.y == 0) row = 0;
	if (row == 3 && movement.y == 0) row = 2;
	if (row == 5 && movement.x == 0) row = 4;
	if (row == 7 && movement.x == 0) row = 6;

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void player::updateBossFight(float deltaTime)
{
	velocity.x *= 0.f;
		
	if (Keyboard::isKeyPressed(Keyboard::W) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.f * gravity * jumpHeight);
		//row = 1;
	}

	velocity.y += gravity * deltaTime;

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		velocity.x -= speed;
		direction = 'l';
		row = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity.x += speed;
		direction = 'r';
		row = 7;
	}

	if (row == 5 && velocity.x == 0) row = 4;
	if (row == 7 && velocity.x == 0) row = 6;

	animation.update(row, deltaTime);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void player::draw(RenderWindow& window)
{
	window.draw(body);
}

void player::onCollision(Vector2f direction)
{
	if (direction.x < 0.f)
	{
		velocity.x = 0.f;
	}
	else if (direction.x > 0.f)
	{
		velocity.x = 0.f;
	}
	if (direction.y < 0.f)
	{
		velocity.y = 0.f;
		canJump = true;
	}
	else if (direction.y > 0.f)
	{
		velocity.y = 0.f;
	}
}
