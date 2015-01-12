#include"core.h"

using namespace std;

Level level;
LevelPhysics phys;
extern Player player;

void loadLevel()
{
	phys.gravity = 5.0f;
	
	string line, block;  // string for reading in and storing the block ids
	ifstream file("level.txt");  // the stream used to read in the file
	
	//try opening the level file; else print out an error log
	try
	{
		file.is_open();  // open the file
		
		/*
		*	Read in the first two lines to set the width and height of the level
		*/
		getline(file, line);
		stringstream lineStream(line);
		getline(lineStream, block, ' ');
		const char *cstr = block.c_str();
		char chartoken = *cstr;
		int token = ((int) chartoken) - 48;
		
		
		//while the file has lines, read them 
		while(getline(file, line))
		{

			stringstream lineStream(line);  //parse the string to separate the blocks for IDing
			while(getline(lineStream, block, ' '))
			{
				// ID the blocks and load them into the level struct
				*cstr = block.c_str();  //convert the string into a char array
				chartoken = *cstr;  // put that value into a standard char primitive
				token = ((int) chartoken) - 48 ;  // type cast to int  (the - 48 is for the integer value shift from the conversion from a char to an int.) 
				
				
				switch(token)  
				{
					case BLOCK_AIR:
						break;
					case BLOCK_DIRT:
						break;
				}
			}
		}
	}
	catch(ifstream::failure e)
	{
		SDL_Log("Error loading level file");
	}
}


void updateLevel()
{
	//update the physics in the level
	
	
	//update player
	if(player.falling)
	{
		player.box.y += phys.gravity;
	}
	
}

void renderLevel()
{

}