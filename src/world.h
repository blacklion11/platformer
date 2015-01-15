#ifndef WORLD_H
#define WORLD_H

#include<SDL2/SDL.h>
#include"level.h"
#include"player.h"

class World
{
	public:
	
	Level *level;
	
	// ctor
	World();
	
	void initWorld();
	void loadWorld();
	void updateWorld(Player *);
	void renderWorld(SDL_Renderer *);
};

#endif