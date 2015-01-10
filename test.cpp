#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>


// SDL Variables
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *screen;

int main(int argc, char** argv)
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Game Window",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  640,
							  480,
							  0
							 );
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);  //<--Check on different graphics cards if should be SDL_RENDERER_ACCELERATED
	screen = SDL_GetWindowSurface(window);
	
	SDL_Delay(5000);
	
	SDL_Quit();
	
}