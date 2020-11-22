#pragma once
#include "stdfn.h"
#include "animation.h"
#include "collider.h"
#include "projectile.h"
#include "hitbox.h"

class player
{
public:
	int direction = UP;
	float speed;
	float hp;
	float mp;
	int money;
	float gravity;

	player(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	~player();

	void update(float deltaTime);
	void updateBossFight(float deltaTime);
	void draw(RenderWindow& window);
	void onCollision(Vector2f direction);
	void setPosition(Vector2f(xy)) { body.setPosition(xy); };
	void setSize(Vector2f(wh)) { body.setSize(wh); };
	void setAnimationRow(unsigned int r) { row = r; }
	void move(Vector2f(ab)) { body.move(ab); }

	Vector2f getPosition() { return body.getPosition(); }
	FloatRect getGlobalBounds() { return body.getGlobalBounds(); }
	collider getCollider() { return collider(body); }

private:
	RectangleShape body;
	animation animation;
	unsigned int row;

	Vector2f velocity;
	bool canJump = false;
	float jumpHeight = 150.f;
};