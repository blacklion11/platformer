#ifndef LEVEL_H
#define LEVEL_H

#define BLOCK_AIR 0
#define BLOCK_DIRT 1

#include<SDL2/SDL.h>
#include<vector>
#include"object.h"
#include"player.h"

struct Block: public GameObject
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
	std::vector<GameObject *> collidables;
	

	Level();
	~Level();
	
	private:
	
	void initLevel();
	void loadBlocks();
	void destroyLevel();
	
	public:
	
	
	void checkCollisions(Player *);
	void updateLevel(Player *);
	void renderLevel(SDL_Renderer *);
};


void updateLevel();

#endif























































