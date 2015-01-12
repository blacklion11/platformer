#ifndef LEVEL_H
#define LEVEL_H

#define BLOCK_AIR 0
#define BLOCK_DIRT 1

#include<SDL2/SDL.h>

typedef struct Block 
{
	int size;
	bool solid;
	bool collidable;
	SDL_Rect rect;
	SDL_Color color;
}Block;

typedef struct Level
{
	int width;
	int height;
	Block **blocks;
}Level;


void loadLevel();
void updateLevel();

#endif