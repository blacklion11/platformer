#include"core.h"

using namespace std;


//ctor
Level::Level()
{
	initLevel();
	loadBlocks();
}

//dtor
Level::~Level()
{
	destroyLevel();
}

// Destroys the level and frees memory used my blocks
void Level::destroyLevel()
{
	for(int i = 0; i < width; i++)
	{
		free(blocks[i]);
	}
	free(blocks);
}

void Level::initLevel()
{
	width = height = 16;
	
	blocks = (struct Block **) malloc(width * sizeof(struct Block *));
	for(int i = 0; i < width; i++)
	{
		blocks[i] = (struct Block *) malloc(height * sizeof(struct Block));
	}
	
	SDL_Log("Level Initialized");
}

void Level::loadBlocks()
{	
	//phys.gravity = 5.0f;
	string line, cblock;  // string for reading in and storing the block ids
	ifstream file("level.txt");  // the stream used to read in the file
	
	try
	{
		file.is_open();  // open the file
		
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
				SDL_Log("Col: %d being read. Current Block: %d", counterX, token);
				switch(token)  
				{
					case BLOCK_AIR:
						// Configure the block
						blocks[counterY][counterX].size = 32;
						blocks[counterY][counterX].solid = false;
						blocks[counterY][counterX].collidable = true;
						blocks[counterY][counterX].rect.x = counterX * blocks[counterY][counterX].size;
						blocks[counterY][counterX].rect.y = counterY * blocks[counterY][counterX].size;
						blocks[counterY][counterX].rect.w = blocks[counterY][counterX].size;
						blocks[counterY][counterX].rect.h = blocks[counterY][counterX].size;
						blocks[counterY][counterX].color.r = 255;
						blocks[counterY][counterX].color.g = 255;
						blocks[counterY][counterX].color.b = 255;
						blocks[counterY][counterX].color.a = 255;
						break;
					case BLOCK_DIRT:
						blocks[counterY][counterX].size = 32;
						blocks[counterY][counterX].solid = true;
						blocks[counterY][counterX].collidable = true;
						blocks[counterY][counterX].rect.x = counterX * blocks[counterY][counterX].size;
						blocks[counterY][counterX].rect.y = counterY * blocks[counterY][counterX].size;
						blocks[counterY][counterX].rect.w = blocks[counterY][counterX].size;
						blocks[counterY][counterX].rect.h = blocks[counterY][counterX].size;
						blocks[counterY][counterX].color.r = 0;
						blocks[counterY][counterX].color.g = 255;
						blocks[counterY][counterX].color.b = 0;
						blocks[counterY][counterX].color.a = 255;
						break;
				}
				
				// if the block is collidable add to collidables vector
				if(blocks[counterY][counterX].collidable)
				{	
					collidables.push_back(&(blocks[counterY][counterX]));
				}
				counterX++;
			}
			counterY++;
		}
	}
	catch(ifstream::failure e)
	{
		SDL_Log("Error loading  file");
	}
	
	SDL_Log("Level Loaded");

}



void Level::checkCollisions(Player *player)
{
	for(unsigned int i = 0; i < collidables.size(); i++)
	{	
	
		//SDL_Log("Player Position: %d, %d              Block 1 Position: %d, %d", player->getX(), player->getY(), collidables[1]->box.x, collidables[1]->box.y);
		//check if the player collides with any blocks
		if(SDL_IntersectRect(&(player->box), &(collidables[i]->box), NULL) == SDL_TRUE)
		{
			SDL_Log("Collision");
		}
		else
		{
			//SDL_Log("No Collision");
		}
		
	}
}


void Level::updateLevel(Player *player)
{
	checkCollisions(player);
}

void Level::renderLevel(SDL_Renderer *renderer)
{
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			SDL_SetRenderDrawColor(renderer, 
								   blocks[i][j].color.r,
								   blocks[i][j].color.g,
								   blocks[i][j].color.b,
								   blocks[i][j].color.a
								  );
			SDL_RenderFillRect(renderer, &(blocks[i][j].rect));
		}
	}
}





















