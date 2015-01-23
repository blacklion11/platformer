#include"core.h"


#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

using namespace std;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *screen;

void initSDL()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Game Window", 
															SDL_WINDOWPOS_UNDEFINED,
															SDL_WINDOWPOS_UNDEFINED,
															DEFAULT_WINDOW_WIDTH,
															DEFAULT_WINDOW_HEIGHT,
															0
														);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	screen = SDL_GetWindowSurface(window);

	
	
	// Redirect output to log files
	FILE * my_stdout = freopen ("logs/log.txt", "wt" /*or "wt"*/, stdout);
	//FILE * my_stderr = freopen ("log.txt", "wb" /*or "wt"*/, stderr);
	
	cout << "SDL Initialized..." << endl;
}

void closeSDL()
{
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char** argv)
{
	
	initSDL();
	
	initCore();
	runCore();
	quitCore();
	
	closeSDL();
	
}