#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL.h>
#include"entity.h"

class Player: public Character
{
	
	public:
	
	Player();
	~Player();
	
	void initPlayer();
	void updatePlayer();
	void renderPlayer(SDL_Renderer *);
	
	void setXY(int , int);
	void setX(int);
	void setY(int);
	void setW(int);
	void setH(int);
	
	int getX();
	int getY();
	int getW();
	int getH();

};


#endif