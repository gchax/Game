#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include "random.h"

using namespace std;
using namespace sf;

enum directions { IDLE = 0, UP, DOWN, RIGHT, LEFT };
enum states { MENU = 0, HOME, OUTDOOR, SKY, CASTLE, STORE, PAUSE, GAME_OVER, SCORE, TUTORIAL, CREDIT };
enum click { UNSELECTED = 0, BOUGHT, BYE };

//define global variables;
static float viewWidght = 1500.f;
static float viewHeight = 900.f;
static unsigned int framerateLimit = 60;
static float maxHP = 3000.f;
static float maxMP = 800.f;
static float gravity = 3000.f;