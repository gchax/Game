#include <SFML\Graphics.hpp>
#include <iostream>
#include "player.h"
#include "platform.h"
#include "map.h"

static float viewheight = 900.0f;

void resizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(viewheight * aspectRatio, viewheight);
}

int main()
{
	RenderWindow window(VideoMode(825, 900), "Jack!", Style::Close | Style::Resize);
	View view(Vector2f(0.0f, 0.0f), Vector2f(viewheight - 75, viewheight));
	Texture playerTexture;
	playerTexture.loadFromFile("test_jack.png");
	Texture obj1Texture;
	obj1Texture.loadFromFile("test_obj1.png");
	Texture obj2Texture;
	obj2Texture.loadFromFile("test_obj2.png");

	player player(&playerTexture, Vector2u(8, 8), 0.12f, 300.0f);

	platform platform1(nullptr, Vector2f(1725.0f, 75.0f), Vector2f(0.0f, -825.0f));
	platform platform2(nullptr, Vector2f(75.0f, 1650.0f), Vector2f(-825.0f, 37.5f));
	platform platform3(nullptr, Vector2f(75.0f, 1650.0f), Vector2f(825.0f, 37.5f));
	platform platform4(nullptr, Vector2f(1725.0f, 75.0f), Vector2f(0.0f, 900.0f));
		
	float deltaTime = 0.0f;
	Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		Event evt;
		while (window.pollEvent(evt)) 
		{
			switch (evt.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				resizeView(window, view);
				break;
			}
		}

		player.update(deltaTime);
		
		collider playerCollision = player.getCollider(); 
		platform1.getCollider().checkCollider(playerCollision, 1.0f);
		platform2.getCollider().checkCollider(playerCollision, 1.0f);
		platform3.getCollider().checkCollider(playerCollision, 1.0f);
		platform4.getCollider().checkCollider(playerCollision, 1.0f);
		
		view.setCenter(player.getPosition());
		
		window.clear(/*Color(255, 170, 77)*/);
		window.setView(view);
		
		const int level[] =
		{
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
		};

		tilemap map;
		if (!map.load("map.png", Vector2u(75, 75), level, 23, 24)) return -1;

		map.setOrigin(862.5f, 862.5f);
		map.setPosition(0.0f, 0.0f);

		window.draw(map);

		player.draw(window);
		window.display();
	}

	return 0;
}