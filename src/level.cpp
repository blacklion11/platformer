#include"core.h"

using namespace std;


//Constructor
Level::Level()
{
	initLevel();
	loadLevel();
}

void Level::initLevel()
{
	width = height = 16;
	
	blocks = (struct Block **) malloc(width * sizeof(struct Block *));
	for(int i = 0; i < width; i++)
	{
		blocks[i] = (struct Block *) malloc(height * sizeof(struct Block));
	}
}

void Level::loadLevel()
{	
	//phys.gravity = 5.0f;
	string line, cblock;  // string for reading in and storing the block ids
	ifstream file("level.txt");  // the stream used to read in the file
	
	try
	{
		
	}
	catch(ifstream::failure e)
	{
		SDL_Log("Error loading  file");
	}
}
