#ifndef LEVEL_H
#define LEVEL_H

#define BLOCK_AIR 0
#define BLOCK_DIRT 1

#include<SDL2/SDL.h>

struct Block 
{
	int size;
	bool solid;
	bool collidable;
	SDL_Rect rect;
	SDL_Color color;
};

/*
typedef struct Level
{
	int width;
	int height;
	Block **blocks;
}Level;
*/

class Level
{
	//struct Physics phys;
	
	public: 
		int width, height;
		struct Block **blocks;
	
		Level();
	private:
	
	void initLevel();
	void loadLevel();
};
void updateLevel();
void renderLevel(SDL_Renderer *);

#endif























































