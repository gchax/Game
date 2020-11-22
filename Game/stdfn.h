#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;

enum directions { UP = 0, DOWN, RIGHT, LEFT };
enum states { MENU = 0, HOME, OUTDOOR, SKY, CASTLE, STORE, PAUSE, GAME_OVER, SCORE, CREDIT };
enum wandStates { UNOBTAINED = 0, REGULAR, KINDA_GOOD, OP };
enum click { IDLE = 0, BOUGHT, BYE };