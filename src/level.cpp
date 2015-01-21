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
	width = height = 32;
	
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
						blocks[counterY][counterX].size = 32;
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
						blocks[counterY][counterX].size = 32;
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


/**
*	Check for collisions
*/


bool checkHorCollisions(SDL_Rect *testPos)
{

}

bool checkVerCollisions(SDL_Rect *testPos)
{

}

void Level::checkCollisions(Player *player)
{
	for(unsigned int i = 0; i < collidables.size(); i++)
	{	
	
		//check if the player collides with any blocks
		SDL_Rect testPos;
		testPos.x = player->box.x + player->deltaX;
		testPos.y = player->box.y + player->deltaY;
		testPos.w = player->box.w;
		testPos.h = player->box.h;
		if(SDL_HasIntersection(&testPos, &(collidables[i]->box)) == SDL_TRUE)
		{
			//test the four edges to see where the collision is
			bool left, right, top, bottom;
			left = right = top = bottom = false;
			if(collidables[i]->box.x + collidables[i]->box.w > testPos.x
			&& collidables[i]->box.x + collidables[i]->box.w < testPos.x + testPos.w)
			{
				//collision on left side of player
				left = true;
				//player->deltaX = 0;
				//break;
			}
			if(collidables[i]->box.x < testPos.x + testPos.w 
			&& collidables[i]->box.x > testPos.x)
			{
				//collision on right side of player
				right = true;
				//player->deltaX = 0;
				//break;
			}
			if(collidables[i]->box.y + collidables[i]->box.h > testPos.y
			&& collidables[i]->box.y + collidables[i]->box.h < testPos.y + testPos.h)
			{
				//collision on top side of player
				top = true;
				//player->deltaY = 0;
				//break;
			}
			if(collidables[i]->box.y < testPos.y + testPos.h
			&& collidables[i]->box.y > testPos.y)
			{
				//collision on bottom side of player
				bottom = true;
				//player->deltaY = 0;
				//break;
			}
			
			if(player->deltaX < 0)
			{
				if(left)
				{
					player->deltaX = 0;
				}
			}else
			{
				if(right)
				{
					player->deltaX = 0;
				}
			}
			if(player->deltaY < 0)
			{
				if(top)
				{
					player->deltaY = 0;
				}
			}else
			{
				if(bottom)
				{
					player->deltaY = 0;
				}
			}
			
			break;
		}
		else
		{
			player->setColor(255, 0, 0, 255);
		}
		
	}
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





















