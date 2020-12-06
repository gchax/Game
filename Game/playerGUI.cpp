#include "playerGUI.h"

playerGUI::playerGUI(Font* font, float playerHP, float playerMP, int playerMoney, int score, int playerWandLevel)
{
	this->font = font;
	this->hp = playerHP;
	this->mp = playerMP;
	this->money = playerMoney;
	this->score = score;
	this->wand = playerWandLevel;

	this->hpBarBase.setSize(Vector2f(barMaxWidth, 40.f));
	this->hpBarBase.setFillColor(Color(50, 50, 50));
	this->hpBarBase.setOutlineColor(Color::Black);
	this->hpBarBase.setOutlineThickness(3);

	this->hpAmount.setSize(Vector2f(barMaxWidth, 40.f));
	this->hpAmount.setFillColor(Color::Green);
	this->hpAmount.setOutlineColor(Color::Black);
	this->hpAmount.setOutlineThickness(3);

	this->mpBarBase.setSize(Vector2f(barMaxWidth, 15.f));
	this->mpBarBase.setFillColor(Color(50, 50, 50));
	this->mpBarBase.setOutlineColor(Color::Black);
	this->mpBarBase.setOutlineThickness(3);

	this->mpAmount.setSize(Vector2f(barMaxWidth, 15.f));
	this->mpAmount.setFillColor(Color::Magenta);
	this->mpAmount.setOutlineColor(Color::Black);
	this->mpAmount.setOutlineThickness(3);

	this->Score.setCharacterSize(30);
	this->Score.setFont(*this->font);
	this->Score.setString("SCORE: " + to_string(this->score));
	this->Score.setFillColor(Color::White);
	this->Score.setOutlineThickness(2);

	this->wandLevel.setCharacterSize(20);
	this->wandLevel.setFont(*this->font);
	this->wandLevel.setFillColor(Color::White);
	this->wandLevel.setOutlineThickness(2);

	this->Money.setCharacterSize(30);
	this->Money.setFont(*this->font);
	this->Money.setString("COINS: " + to_string(this->money));
	this->Money.setFillColor(Color::White);
	this->Money.setOutlineThickness(2);
}

void playerGUI::updateStatus(float deltaTime, Vector2f windowSize, Vector2f playerPosition)
{
	this->hpBarBase.setPosition(playerPosition.x - windowSize.x / 2.f + 20.f, playerPosition.y - windowSize.y / 2.f + 20.f);
	this->hpAmount.setPosition(this->hpBarBase.getPosition());
	this->mpBarBase.setPosition(playerPosition.x - windowSize.x / 2.f + 20.f, playerPosition.y - windowSize.y / 2.f + 80.f);
	this->mpAmount.setPosition(this->mpBarBase.getPosition());
	this->Score.setOrigin(this->Score.getLocalBounds().width / 2.f, 0.f);
	this->Score.setPosition(playerPosition.x, playerPosition.y - windowSize.y / 2.f + 20.f);

	float hpPercentage = hp / maxHP;
	float hpDisplay = static_cast<float>(std::floor(this->barMaxWidth * hpPercentage));
	if (hpDisplay < 0) hpDisplay = 0;
	this->hpAmount.setSize((Vector2f(hpDisplay, this->hpAmount.getSize().y)));
	float mpPercentage = mp / maxMP;
	float mpDisplay = static_cast<float>(std::floor(this->barMaxWidth * mpPercentage));
	if (mpDisplay < 0) mpDisplay = 0;
	this->mpAmount.setSize((Vector2f(mpDisplay, this->mpAmount.getSize().y)));
}

void playerGUI::updateWandState(float deltaTime, Vector2f windowSize, Vector2f playerPosition)
{
	string state;
	if (wand == 0) state = "";
	else if (wand > 0 && wand < 60) state = "WAND LEVEL: " + to_string(this->wand);
	else if (wand == 60) state = "WAND LEVEL: MAX";

	this->wandLevel.setString(state);
	this->wandLevel.setOrigin(this->wandLevel.getLocalBounds().width, 0.f);
	this->wandLevel.setPosition(playerPosition.x + windowSize.x / 2.f - 20.f, playerPosition.y - windowSize.y / 2.f + 70.f);
}

void playerGUI::updateCoin(float deltaTime, Vector2f windowSize, Vector2f playerPosition)
{
	this->Money.setOrigin(this->Money.getLocalBounds().width, 0.f);
	this->Money.setPosition(playerPosition.x + windowSize.x / 2.f - 20.f, playerPosition.y - windowSize.y / 2.f + 20.f);
}

void playerGUI::updateCastle(float deltaTime, Vector2f windowSize)
{
	float hpPercentage = hp / maxHP;
	float hpDisplay = static_cast<float>(std::floor(this->barMaxWidth * hpPercentage));
	if (hpDisplay < 0) hpDisplay = 0;
	this->hpAmount.setSize((Vector2f(hpDisplay, this->hpAmount.getSize().y)));
	float mpPercentage = mp / maxMP;
	float mpDisplay = static_cast<float>(std::floor(this->barMaxWidth * mpPercentage));
	if (mpDisplay < 0) mpDisplay = 0;
	this->mpAmount.setSize((Vector2f(mpDisplay, this->mpAmount.getSize().y)));

	string state;
	if (wand == 0) state = "";
	else if (wand > 0 && wand < 60) state = "WAND LEVEL: " + to_string(this->wand);
	else if (wand == 60) state = "WAND LEVEL: MAX";

	this->hpBarBase.setPosition(20.f - windowSize.x / 2.f, 20.f - windowSize.y / 2.f);
	this->hpAmount.setPosition(this->hpBarBase.getPosition());
	this->mpBarBase.setPosition(20.f - windowSize.x / 2.f, 80.f - windowSize.y / 2.f);
	this->mpAmount.setPosition(this->mpBarBase.getPosition());
	this->Score.setOrigin(this->Score.getLocalBounds().width / 2.f, 0.f);
	this->Score.setPosition(0.f, 20.f - windowSize.y / 2.f);
	this->wandLevel.setString(state);
	this->wandLevel.setOrigin(this->wandLevel.getLocalBounds().width, 0.f);
	this->wandLevel.setPosition(windowSize.x / 2.f - 20.f, 70.f - windowSize.y / 2.f);
	this->Money.setOrigin(this->Money.getLocalBounds().width, 0.f);
	this->Money.setPosition(windowSize.x / 2.f - 20.f, 20.f - windowSize.y / 2.f);
}

void playerGUI::drawStatus(RenderWindow& window)
{
	window.draw(this->hpBarBase);
	window.draw(this->hpAmount);
	window.draw(this->mpBarBase);
	window.draw(this->mpAmount);
	window.draw(this->Score);
}

void playerGUI::drawWandState(RenderWindow& window)
{
	window.draw(this->wandLevel);
}

void playerGUI::drawCoin(RenderWindow& window)
{
	window.draw(this->Money);
}