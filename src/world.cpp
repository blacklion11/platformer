#include"world.h"




World::World()
{
	initWorld();
	loadWorld();
}

void World::initWorld()
{
}

void World::loadWorld()
{
	//load the level
	level = new Level();
}

void World::renderWorld(SDL_Renderer *renderer)
{
	
	//render the level
	level->renderLevel(renderer);
}