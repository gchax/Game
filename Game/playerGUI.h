#pragma once
#include "stdfn.h"
#include "player.h"

class playerGUI
{
public:
	playerGUI(Font* font, float playerHP, float playerMP, int playerMoney, int score, int playerWandLevel);

	void updateStatus(float deltaTime, Vector2f windowSize, Vector2f playerPosition);
	void updateWandState(float deltaTime, Vector2f windowSize, Vector2f playerPosition);
	void updateCoin(float deltaTime, Vector2f windowSize, Vector2f playerPosition);
	void updateCastle(float deltaTime, Vector2f windowSize);
	void drawStatus(RenderWindow& window);
	void drawWandState(RenderWindow& window);
	void drawCoin(RenderWindow& window);

private:
	RectangleShape hpBarBase;
	RectangleShape hpAmount;
	RectangleShape mpBarBase;
	RectangleShape mpAmount;
	Text wandLevel;
	Text Money;
	Text Score;
	Font* font;
	float barMaxWidth = 400.f;
	float hp;
	float mp;
	int wand;
	int money;
	int score;
};

