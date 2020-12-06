#include "item.h"

item::item(Texture* texture, Vector2u imageCount, Vector2f size) :
	animation(texture, imageCount, 0.05f)
{
	this->size = size;

	body.setSize(size);
	body.setOrigin(body.getSize() / 2.f);
	body.setTexture(texture);
}

void item::update(float deltaTime)
{
	animation.update(0, deltaTime);
	body.setTextureRect(animation.uvRect);
}

void item::draw(RenderWindow& window)
{
	window.draw(body);
}
