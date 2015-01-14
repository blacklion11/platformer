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

class Level
{
	//struct Physics phys;
	
	public: 
		int width, height;
		struct Block **blocks;
	
		Level();
		~Level();
		
	private:
	
	void initLevel();
	void loadLevel();
	void destroyLevel();
	
	public:

	void renderLevel(SDL_Renderer *);
};


void updateLevel();

#endif























































