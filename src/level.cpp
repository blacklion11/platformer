#include"core.h"

using namespace std;

Level level;
LevelPhysics phys;
extern Player player;

void loadLevel()
{
	phys.gravity = 5.0f;
	
	string line, cblock;  // string for reading in and storing the block ids
	ifstream file("level.txt");  // the stream used to read in the file
	
	//try opening the level file; else print out an error log
	try
	{
		file.is_open();  // open the file
		
		/*
		*	Read in the first two lines to set the width and height of the level
		*/
		int i;
		for(i = 0; i < 2; i++)
		{
			getline(file, line);
			stringstream lineStream(line);
			getline(lineStream, cblock, ' ');
			const char *cstr = cblock.c_str();
			char chartoken = *cstr;
			int token = ((int) chartoken) - 48;
			if(i == 0)
				level.width = token;
			else
				level.height = token;
		}
		
		
		/*
		*	Allocate memory to the block array in the level
		*/
		
		level.blocks = (Block**) malloc( level.width * sizeof(Block*));
		for(i = 0; i < level.width; i++)
		{
			level.blocks[i] = (Block*) malloc( level.height * sizeof(Block));
		}
		
		// these keep track of which tile we are on
		// in the level when assigning block types to it
		int counterX = 0;   
		int counterY = 0;
		
		//while the file has lines, read them 
		while(getline(file, line))
		{

			stringstream lineStream(line);  //parse the string to separate the blocks for IDing
			while(getline(lineStream, cblock, ' '))
			{
				// ID the blocks and load them into the level struct
				*cstr = cblock.c_str();  //convert the string into a char array
				chartoken = *cstr;  // put that value into a standard char primitive
				token = ((int) chartoken) - 48 ;  // type cast to int  (the - 48 is for the integer value shift from the conversion from a char to an int.) 
				
				
				switch(token)  
				{
					//instantiate a block for assigning
					Block block;
					case BLOCK_AIR:
						block.size = 64;
						block.solid = false;
						block.collidable = false;
						block.rect.x = counterX * block.size;
						block.rect.y = counterY *block.size;
						block.color.r = 255;
						block.color.g = 255;
						block.color.b = 255;
						block.color.a = 255;
						level.blocks[counterY][counterX] = block;	
						break;
					case BLOCK_DIRT:
					block.size = 64;
						block.solid = true;
						block.collidable = true;
						block.rect.x = counterX * block.size;
						block.rect.y = counterY *block.size;
						block.color.r = 0;
						block.color.g = 255;
						block.color.b = 0;
						block.color.a = 255;
						level.blocks[counterY][counterX] = block;	
						break;
				}
				counterX++;
			}
			counterY++;
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