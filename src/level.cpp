#include"core.h"

using namespace std;

extern Level level;
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
		int i, j;
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
		for(i = 0; i < level.width; i++)
		{
			for(j = 0; j < level.height; j++)
			{
				//level.blocks[i][j] = (Block*) malloc(sizeof(Block));
				Block block;
				level.blocks[i][j] = block;
			}
		}
		
		
		
		// these keep track of which tile we are on
		// in the level when assigning block types to it
		int counterX = 0;   
		int counterY = 0;
		
		//while the file has lines, read them 
		while(getline(file, line))
		{
			SDL_Log("Line: %d being read", counterY);
			stringstream lineStream(line);  //parse the string to separate the blocks for IDing
			counterX = 0;  // reset the x counter for each level
			while(getline(lineStream, cblock, ' '))
			{
				// ID the blocks and load them into the level struct
				const char *cstr = cblock.c_str();  //convert the string into a char array
				char chartoken = *cstr;  // put that value into a standard char primitive
				int token = ((int) chartoken) - 48 ;  // type cast to int  (the - 48 is for the integer value shift from the conversion from a char to an int.) 
				SDL_Log("Current Block: %d", token);
				SDL_Log("Col: %d being read", counterX);
				switch(token)  
				{
					case BLOCK_AIR:
						// Configure the block
						level.blocks[counterY][counterX].size = 64;
						level.blocks[counterY][counterX].solid = false;
						level.blocks[counterY][counterX].collidable = false;
						level.blocks[counterY][counterX].rect.x = counterX * level.blocks[counterY][counterX].size;
						level.blocks[counterY][counterX].rect.y = counterY * level.blocks[counterY][counterX].size;
						level.blocks[counterY][counterX].color.r = 255;
						level.blocks[counterY][counterX].color.g = 255;
						level.blocks[counterY][counterX].color.b = 255;
						level.blocks[counterY][counterX].color.a = 255;
						break;
					case BLOCK_DIRT:
						level.blocks[counterY][counterX].size = 64;
						level.blocks[counterY][counterX].solid = true;
						level.blocks[counterY][counterX].collidable = true;
						level.blocks[counterY][counterX].rect.x = counterX * level.blocks[counterY][counterX].size;
						level.blocks[counterY][counterX].rect.y = counterY * level.blocks[counterY][counterX].size;
						level.blocks[counterY][counterX].color.r = 0;
						level.blocks[counterY][counterX].color.g = 255;
						level.blocks[counterY][counterX].color.b = 0;
						level.blocks[counterY][counterX].color.a = 255;
						break;
				}
				counterX++;
			}
			counterY++;
		}
		SDL_Log("Import Completed");
		if(counterX == level.width - 1 && counterY == level.height - 1)
		{
			SDL_Log("Blocks completed all the way through for level import");
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

void renderLevel(SDL_Renderer *renderer)
{

	// loop through the blocks and render them
	int i,j;
	
	for(i = 0; i < level.width; i++)
	{
		for(j = 0; j < level.width; j++)
		{
			SDL_SetRenderDrawColor(renderer,
								   level.blocks[i][j].color.r, 
								   level.blocks[i][j].color.g, 
								   level.blocks[i][j].color.b, 
								   level.blocks[i][j].color.a
								   );
			SDL_RenderFillRect(renderer, &(level.blocks[i][j].rect));
		}
	}
}
























