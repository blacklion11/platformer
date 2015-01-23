#include"core.h"

using namespace std;

extern SDL_Surface *screen;
extern SDL_Window *window;

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
	tileSize = 32;
	gravity = 2;
	
	blocks = (struct Block **) malloc(width * sizeof(struct Block *));
	for(int i = 0; i < width; i++)
	{
		blocks[i] = (struct Block *) malloc(height * sizeof(struct Block));
	}
	
	SDL_Log("Level Initialized");
}

/**
*	Load the blocks used in the level
*/
void Level::loadBlocks()
{	
	//phys.gravity = 5.0f;
	string line, cblock;  // string for reading in and storing the block ids
	ifstream file("level_small.txt");  // the stream used to read in the file
	
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
			//SDL_Log("Line: %d being read", counterY);
			stringstream lineStream(line);  //parse the string to separate the blocks for IDing
			counterX = 0;  // reset the x counter for each level
			while(getline(lineStream, cblock, ' '))
			{
				// ID the blocks and load them into the level struct
				const char *cstr = cblock.c_str();  //convert the string into a char array
				char chartoken = *cstr;  // put that value into a standard char primitive
				int token = ((int) chartoken) - 48 ;  // type cast to int  (the - 48 is for the integer value shift from the conversion from a char to an int.) 
				//SDL_Log("Col: %d being read. Current Block: %d", counterX, token);
				switch(token)  
				{
					case BLOCK_AIR:
						// Configure the block
						blocks[counterY][counterX].id = 0;
						blocks[counterY][counterX].size = tileSize;
						blocks[counterY][counterX].solid = false;
						blocks[counterY][counterX].collidable = false;
						blocks[counterY][counterX].box.x = counterX * blocks[counterY][counterX].size;
						blocks[counterY][counterX].box.y = counterY * blocks[counterY][counterX].size;
						blocks[counterY][counterX].box.w = blocks[counterY][counterX].size;
						blocks[counterY][counterX].box.h = blocks[counterY][counterX].size;
						blocks[counterY][counterX].color.r = 255;
						blocks[counterY][counterX].color.g = 255;
						blocks[counterY][counterX].color.b = 255;
						blocks[counterY][counterX].color.a = 255;
						break;
					case BLOCK_DIRT:
						blocks[counterY][counterX].id = 1;
						blocks[counterY][counterX].size = tileSize;
						blocks[counterY][counterX].solid = true;
						blocks[counterY][counterX].collidable = true;
						blocks[counterY][counterX].box.x = counterX * blocks[counterY][counterX].size;
						blocks[counterY][counterX].box.y = counterY * blocks[counterY][counterX].size;
						blocks[counterY][counterX].box.w = blocks[counterY][counterX].size;
						blocks[counterY][counterX].box.h = blocks[counterY][counterX].size;
						blocks[counterY][counterX].color.r = 0;
						blocks[counterY][counterX].color.g = 255;
						blocks[counterY][counterX].color.b = 0;
						blocks[counterY][counterX].color.a = 255;
						break;
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


/**
*	Check for collisions
*/

/*
void Level::checkHorCollisions(Player *player)
{
	// Create the test position that takes 
	// the delta positions in to account
	SDL_Rect testPos;
	testPos.x = player->getX();
	testPos.y = player->getY();
	testPos.w = player->getW();
	testPos.h = player->getH();
	
	
	struct Block testBlocks[4];
	testBlocks[0] = blocks[testPos.x / tileSize][testPos.y / tileSize];  // Left Tile
	testBlocks[1] = blocks[(testPos.x + testPos.w - 1) / tileSize][testPos.y / tileSize]; // Right Tile
	testBlocks[2] = blocks[testPos.x / tileSize][(testPos.y + testPos.h - 1) / tileSize];  //Bottom Left
	testBlocks[3] = blocks[(testPos.x + testPos.w - 1) / tileSize][(testPos.y + testPos.h - 1) / tileSize]; // Bottom Right
	
	bool topLeft = testBlocks[0].solid;
	bool topRight = testBlocks[1].solid;
	bool bottomLeft = testBlocks[2].solid;
	bool bottomRight = testBlocks[3].solid;
	
	if(player->dx < 0)
	{
		if(topLeft || bottomLeft)
		{
			SDL_Log("Hit Left");
		}
	}
	if(player->dx > 0)
	{
		if(topRight || bottomRight)
		{
			SDL_Log("Hit Right");
		}
	}
}
*/

void Level::checkLeftCollisions(Player *player)
{
	// Create the test position that takes 
	// the delta positions in to account
	SDL_Rect testPos;
	testPos.x = player->getX() + player->dx;
	testPos.y = player->getY();
	testPos.w = player->getW();
	testPos.h = player->getH();
	
	int rowTop = testPos.y / tileSize;
	int rowBot = (testPos.y + testPos.h) / tileSize;
	int colLeft = testPos.x / tileSize;
	int colRight = (testPos.x + testPos.w) / tileSize;
	
	bool collision = blocks[rowTop][colLeft].solid || blocks[rowBot][colLeft].solid;
	
	if(collision)
	{
		player->dx = 0;
		player->tempX = blocks[testPos.y / tileSize][testPos.x / tileSize].box.x + blocks[testPos.y / tileSize][testPos.x / tileSize].box.w + 1; 
	}
}

void Level::checkRightCollisions(Player *player)
{
	// Create the test position that takes 
	// the delta positions in to account
	SDL_Rect testPos;
	testPos.x = player->getX() + player->dx;
	testPos.y = player->getY();
	testPos.w = player->getW();
	testPos.h = player->getH();
	
	int rowTop = testPos.y / tileSize;
	int rowBot = (testPos.y + testPos.h) / tileSize;
	int colLeft = testPos.x / tileSize;
	int colRight = (testPos.x + testPos.w) / tileSize;
	
	bool collision = blocks[rowTop][colRight].solid || blocks[rowBot][colRight].solid;
	
	if(collision)
	{
		player->dx = 0;
		player->tempX = blocks[testPos.y / tileSize][(testPos.x / tileSize) + 1].box.x - player->getW() - 1; 
	}
}

void Level::checkTopCollisions(Player *player)
{
	// Create the test position that takes 
	// the delta positions in to account
	SDL_Rect testPos;
	testPos.x = player->getX();
	testPos.y = player->getY() + player->dy;
	testPos.w = player->getW();
	testPos.h = player->getH();
	
	bool collision = blocks[testPos.y / tileSize][testPos.x / tileSize].solid || blocks[testPos.y / tileSize][(testPos.x + testPos.w)/ tileSize].solid;

	if(collision)
	{
		player->dy = 0;
		player->tempY = blocks[testPos.y / tileSize][testPos.x / tileSize].box.y + blocks[testPos.y / tileSize][testPos.x / tileSize].box.h + 1; 
	}
}

void Level::checkBottomCollisions(Player *player)
{
	// Create the test position that takes 
	// the delta positions in to account
	SDL_Rect testPos;
	testPos.x = player->getX();
	testPos.y = player->getY() + player->dy;
	testPos.w = player->getW();
	testPos.h = player->getH();
	
	bool collision = blocks[(testPos.y + testPos.h) / tileSize][testPos.x / tileSize].solid || blocks[(testPos.y + testPos.h) / tileSize][(testPos.x + testPos.w)/ tileSize].solid;

	
	if(collision)
	{
		player->dy = 0;
		player->tempY = blocks[(testPos.y / tileSize) + 1][testPos.x / tileSize].box.y - player->getH() - 1;
		player->grounded = true;
	}
}

Block* Level::getBlock(int row, int col)
{
	
	return (struct Block*) &(blocks[col, row]);
}

void Level::checkCollisions(Player *player)
{	
	player->tempX = player->getX();
	player->tempY = player->getY();
	
	// Apply Level Gravity
	player->dy += gravity;

	if(player->dx < 0)
	{
		checkLeftCollisions(player);
	}
	if(player->dx > 0)
	{
		checkRightCollisions(player);
	}
	if(player->dy < 0)
	{
		checkTopCollisions(player);
	}
	if(player->dy > 0)
	{
		checkBottomCollisions(player);
		if(player->dy > player->maxFallSpeed)
			player->dy = player->maxFallSpeed;
	}
	
	player->tempX += player->dx;
	player->tempY += player->dy;
}

/**
*	Update the level
*/
void Level::updateLevel(Player *player)
{
	// Check the player for potential collisions
	checkCollisions(player);
	
	// Apply movement to the player
	player->applyMovement();
}

/**
*	Render the level
*/
void Level::renderLevel(SDL_Renderer *renderer, Camera *camera)
{
	//SDL_Renderer *tileRend = SDL_CreateSoftwareRenderer(screen);
	//SDL_Surface *crop = SDL_CreateRGBSurface(0, camera->box.w, camera->box.h, 32, 0, 0, 0, 0);
	
	// Render the level to "camera screen"
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
			SDL_Rect offset;
			offset.x = blocks[i][j].box.x - camera->box.x;
			offset.y = blocks[i][j].box.y - camera->box.y;
			offset.w = camera->box.w;
			offset.h = camera->box.h;
			SDL_RenderFillRect(renderer, &offset);
			//SDL_RenderFillRect(renderer, &(blocks[i][j].box));
			
		}
	}
	
	
	//SDL_BlitSurface(screen, &(camera->box), crop, NULL);
	//SDL_Texture *map = SDL_CreateTextureFromSurface(renderer, crop);

	//SDL_Log("camera position:  %d, %d", camera->box.x, camera->box.y);
	//SDL_Log("player position:  %d, %d", player->box.x, player->box.y);

	//SDL_RenderCopy(renderer, map, NULL, NULL); 
	
	//SDL_FreeSurface(crop);
	//SDL_DestroyTexture(map);
	//SDL_DestroyRenderer(tileRend);
}





















