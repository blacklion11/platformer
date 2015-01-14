#ifndef WORLD_H
#define WORLD_H

#include<SDL2/SDL.h>
#include"level.h"


class World
{
	public:
	
	Level *level;
	
	// ctor
	World();
	
	void initWorld();
	void loadWorld();
	void renderWorld(SDL_Renderer *);
};

#endif