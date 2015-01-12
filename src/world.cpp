#include"core.h"


Level level;

void loadWorld()
{
	//load the level
	loadLevel();
}

void renderWorld(SDL_Renderer *renderer)
{
	
	//render the level
	renderLevel(renderer);
}