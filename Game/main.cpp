#include <SFML\Graphics.hpp>
#include <iostream>
#include "player.h"
#include "platform.h"

static float viewheight = 1000.0f;

void resizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(viewheight * aspectRatio, viewheight);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 800), "Jack!", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(viewheight + 600, viewheight));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("test.png");
	sf::Texture obj1Texture;
	obj1Texture.loadFromFile("test_obj1.png");
	sf::Texture obj2Texture;
	obj2Texture.loadFromFile("test_obj2.png");

	player player(&playerTexture, sf::Vector2u(8, 8), 0.12f, 200.0f);

	platform platform1(&obj1Texture, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(100.0f, 15.0f));
	platform platform2(&obj2Texture, sf::Vector2f(80.0f, 80.0f), sf::Vector2f(200.0f, 0.0f));
		
	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event evt;
		while (window.pollEvent(evt)) 
		{
			switch (evt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				resizeView(window, view);
				break;
			}
		}

		player.Update(deltaTime);
		
		collider playerCollision = player.getCollider();
		collider platform1Collision = platform1.getCollider();
		platform1.getCollider().checkCollider(playerCollision, 0.0f);
		platform2.getCollider().checkCollider(playerCollision, 1.0f);
		platform2.getCollider().checkCollider(platform1Collision, 0.0f);
		
		view.setCenter(player.getPosition());
		
		window.clear(sf::Color(255, 170, 77));
		window.setView(view);
		player.Draw(window);
		platform1.draw(window);
		platform2.draw(window);
		window.display();
	}

	return 0;
}