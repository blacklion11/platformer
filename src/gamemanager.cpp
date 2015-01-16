#include"gamemanager.h"

extern SDL_Window *window;


//ctor
GameManager::GameManager()
{
	initGame();
}

//dtor
GameManager::~GameManager()
{
	destroyGame();
}

//Initializes the game
void GameManager::initGame()
{
	player = new Player();  //intializes the player
	camera = new Camera();
	//loadAssets(); // loads all the assets the game needs to run (i.e level maps, character sprites, backgrounds, etc)
	world = new World(); // create the world
}

//Destroys the game 
void GameManager::destroyGame()
{
	
}

void GameManager::updateGame()
{
	player->updatePlayer(camera);
	
	world->updateWorld(player);
}

void GameManager::renderGame(SDL_Renderer *renderer)
{
	/**
	* Render To Buffer
	*/
	
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	// Draw background
	
	
	// Draw the world
	world->renderWorld(renderer, camera);
	
	
	
	
	// Draw the player
	player->renderPlayer(renderer);
	
	
	/**
	* Render To Screen
	*/ 
	SDL_RenderPresent(renderer);
}




























