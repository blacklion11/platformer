#ifndef CORE_H
#define CORE_H

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"input.h"
#include"player.h"
#include"physics.h"
#include"world.h"
//#include"level.h"


void initGame();
void runGame();
void quitGame();

void loadAssets();
#endif