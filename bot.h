
#include "Wall.h"
#include "Snake.h"
#include "Line.h"
#include "Game.h"

bool chooseMove(Snake* bot, std::string level, Snake enemy, Apple apple);
bool hardMode(Snake* bot, Snake enemy, Apple apple); 
bool normalMode(Snake* bot, Snake enemy, Apple apple); 
bool goToApple(Snake* bot, Snake enemy, Apple apple);

