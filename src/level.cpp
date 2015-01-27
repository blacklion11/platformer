#include"core.h"

using namespace std;

extern SDL_Surface *screen;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
SDL_Texture *mapText;

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
	// Read in the first two lines of the level to 
	// set the width and height of the level
	string line, cblock;  // string for reading in and storing the block ids
	ifstream file;  // the stream used to read in the file
	try
	{
		file.open("level.txt");
		
		for(int i = 0; i < 2; i++)
		{
			getline(file, line);
			stringstream lineStream(line);
			getline(lineStream, cblock, ' ');
			int token;
			sscanf(cblock.c_str(), "%d", &token);
			
			if(i == 0) width = token;
			else height = token;
		}
		
		file.close();
		
		//SDL_Log("Width: %d   Height: %d", width, height);
	}
	catch(ifstream::failure e)
	{
		SDL_Log("Error reading level file");
	}
	
	tileSize = 32;
	gravity = 1;
	
	blocks = (struct Block **) malloc(height * sizeof(struct Block *));
	for(int i = 0; i < height; i++)
	{
		blocks[i] = (struct Block *) malloc(width * sizeof(struct Block));
	}
	
	SDL_Log("\nLevel Initialized");
}

/**
*	Load the blocks used in the level
*/
void Level::loadBlocks()
{	
	SDL_Log("Loading Blocks...");
	//phys.gravity = 5.0f;
	string line, cblock;  // string for reading in and storing the block ids
	ifstream file("level.txt");  // the stream used to read in the file
	
	try
	{
		file.is_open();  // open the file
		getline(file, line); // skip the first two lines (those are the width and height of the map)
		getline(file, line); 
		
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
				//SDL_Log("Line Read: %d", counterX);
				
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
						blocks[counterY][counterX].txtr = SDL_CreateTextureFromSurface(renderer, IMG_Load("air.png"));
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
						blocks[counterY][counterX].txtr = SDL_CreateTextureFromSurface(renderer, IMG_Load("grass.png"));
						break;
				}
				//SDL_Log("Block Loaded: %d, %d", counterX, counterY);
				
				//Blit if blitting <----- for later use (not sure if going to implement or not
				
				counterX++;
			}
			counterY++;
		}		
	}
	catch(ifstream::failure e)
	{
		SDL_Log("Error loading  file");
	}


	// Create texture for optimized rendering
	//mapText = SDL_CreateTextureFromSurface(renderer, screen);
	
	
	SDL_Log("Level Loaded");

}


/**
*	Check for collisions
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
void Level::renderLevel(SDL_Renderer *rend, Camera *camera)
{
	//SDL_Renderer *tileRend = SDL_CreateSoftwareRenderer(screen);
	//SDL_Surface *crop = SDL_CreateRGBSurface(0, camera->box.w, camera->box.h, 32, 0, 0, 0, 0);
	
	// Render the level to "camera screen"
	
	
	
	int startTileX = camera->box.x / tileSize;
	int startTileY = camera->box.y / tileSize;
	int endTileX = startTileX + (camera->box.w / tileSize) + 1;
	int endTileY = startTileY + (camera->box.h / tileSize) + 1;
	if(startTileX < 0) startTileX = 0;
	if(startTileY < 0) startTileY = 0;
	if(endTileX > width) endTileX = width;
	if(endTileY > height) endTileY = height;
	
	/*
	SDL_Surface *test = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	SDL_Texture *text = SDL_CreateTextureFromSurface(rend, test);
	SDL_RenderCopy(rend, text, NULL, NULL); 
	
	SDL_FreeSurface(test);
	SDL_DestroyTexture(text);
	*/
	
	for(int i = startTileY; i < endTileY; i++)
	{
		for(int j = startTileX; j < endTileX; j++)
		{
			SDL_Rect offset;
			offset.x = blocks[i][j].box.x - camera->box.x;
			offset.y = blocks[i][j].box.y - camera->box.y;
			offset.w = camera->box.w;
			offset.h = camera->box.h;
			SDL_RenderCopy(renderer, blocks[i][j].txtr, NULL, &offset);
			//SDL_RenderFillRect(renderer, &offset);
		}
	}
	
	/*
	for(int i = startTileY; i < endTileY; i++)
	{
		for(int j = startTileX; j < endTileX; j++)
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
		}
	}
	*/
	
}





















