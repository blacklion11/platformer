#ifndef PLAYER_H
#define PLAYER_H

#include"core.h"

typedef struct Player
{
	int x;
	int y;
	SDL_Rect box;
}Player;

void initPlayer();
void drawPlayer(SDL_Renderer *);

#endif