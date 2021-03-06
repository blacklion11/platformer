#ifndef LEVEL_H
#define LEVEL_H

#define BLOCK_AIR 0
#define BLOCK_DIRT 1

#include<SDL2/SDL.h>
#include<vector>
#include<string>
#include"object.h"
#include"player.h"
#include"camera.h"


struct Block: public GameObject
{
	int id;
	int size;
	bool solid;
	bool collidable;
	SDL_Color color;
	SDL_Texture *txtr;
};

class Level
{
	//struct Physics phys;
	
	public: 
	
	int width, height;
	int tileSize;
	struct Block **blocks; 
	int gravity;
	

	Level();
	~Level();
	
	private:
	
	void initLevel();
	void loadBlocks();
	void destroyLevel();
	
	public:
	
	Block* getBlock(int, int);
	void checkCollisions(Player *);
	void checkLeftCollisions(Player *);
	void checkRightCollisions(Player*);
	void checkTopCollisions(Player *);
	void checkBottomCollisions(Player *);
	void updateLevel(Player *);
	void renderLevel(SDL_Renderer *, Camera *);
	
};


void updateLevel();

#endif























































