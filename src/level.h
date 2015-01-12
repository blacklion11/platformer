#ifndef LEVEL_H
#define LEVEL_H

#define BLOCK_AIR 0
#define BLOCK_DIRT 1

typedef struct Block 
{
	int size;
	bool solid;
	bool collidable;
	
}Block;

typedef struct Level
{
	int width;
	int height;
	Block **blocks;
}Level;


void loadLevel();
void updateLevel();

#endif