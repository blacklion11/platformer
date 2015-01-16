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


#include"gamemanager.h"




void initCore();
void runCore();
void quitCore();

void loadAssets();
#endif