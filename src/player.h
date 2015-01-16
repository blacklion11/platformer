#ifndef PLAYER_H
#define PLAYER_H

#include<SDL2/SDL.h>
#include"entity.h"
#include"camera.h"

class Player: public Character
{
	
	public:
	
	Player();
	~Player();
	
	void initPlayer();
	void updatePlayer(Camera *);
	void renderPlayer(SDL_Renderer *);
	void updateCamera(Camera *);
	
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