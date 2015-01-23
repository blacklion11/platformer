#include"core.h"

using namespace std;

//SDL variables
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Surface *screen;

// Running variables
bool running = false;
float fps = 10.0;
unsigned int prevTime;
unsigned int currTime;
float deltaTime;
float frameTime;


GameManager *gm;


void initCore()
{
	running = true;
	gm = new GameManager();
}

void runCore()
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
			gm->updateGame();
			
		}
		
		/**
		* Render the game
		*/
		gm->renderGame(renderer);
	}
	
}

void quitCore()
{

}