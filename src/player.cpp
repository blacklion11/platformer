#include"player.h"

Player player;


void initPlayer()
{
	player.x = 50;
	player.y = 50;
	player.box.x = player.x;
	player.box.y = player.y;
	player.box.w = player.box.h = 50;

}

void drawPlayer(SDL_Renderer *renderer)
{
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &(player.box));
}


