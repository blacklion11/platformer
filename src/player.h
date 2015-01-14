#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL.h>

class Player
{
	
	public:
	
	int x;
	int y;
	SDL_Rect box;
	int movespeed;
	bool falling;
	
	Player();
	
	void initPlayer();
	void updatePlayer();
	void renderPlayer(SDL_Renderer *);


};


#endif