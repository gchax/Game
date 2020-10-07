#pragma once
#include <SFML\Graphics.hpp>

class collider
{
public:
	collider(sf::RectangleShape& body);
	~collider();

	void move(float dx, float dy) { body.move(dx, dy); }

	bool checkCollider(collider other, float push);
	sf::Vector2f getPosition() { return body.getPosition(); }
	sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; }

private:
	sf::RectangleShape& body;
};