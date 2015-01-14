#include"core.h"

using namespace std;

bool running = false;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Surface *screen;

float fps = 10.0;
unsigned int prevTime;
unsigned int currTime;
float deltaTime;
float frameTime;

void initGame()
{
	running = true; //sets the running boolean to true for the game loop
	initPlayer();  //intializes the player
	loadAssets(); // loads all the assets the game needs to run (i.e level maps, character sprites, backgrounds, etc)
	loadWorld();
}

void runGame()
{
	
	
	while(running)
	{
		//fps clock
		prevTime = currTime;  // set the current time (the start time for the old frame) to the old time
		currTime = SDL_GetTicks(); // pull the new time from SDL
		deltaTime = (currTime - prevTime) / 1000.0f;  // find the difference and divide by 1000 to get in seconds (this is the time the previous frame took to execute)
		frameTime += deltaTime;  // this is the check for if the frame executed too fast. the delta time is added to the frame time until enough ticks have gone by to allow another update
		
		//SDL_Log("delta time is: %f", deltaTime);
		//cout << "delta time is: " << deltaTime << endl;
		
		//get input and test for game close
		running = getInput() != -1;
		
		if(frameTime > 0.0166666f)  // if the execution time of the last frame is greater than the target fps time then execute this frame (this allows all computers to run the game at a constant speed regardless of processor speed)
		{
			frameTime = 0; // reset the frame time
			
			/**
			* Update Game Logic
			*/
			//updateLevel();
			
		}
		/**
		* Render To Buffer
		*/
		
		// Clear the screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		// Draw background
		
		
		// Draw the world
		renderWorld(renderer);
		
		
		// Draw the player
		drawPlayer(renderer);
		
		/**
		* Render To Screen
		*/
		SDL_RenderPresent(renderer);
	}
	
}

void quitGame()
{

}