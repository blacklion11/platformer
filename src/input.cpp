#include "gamemanager.h"

// SDL Event variable
SDL_Event e;

// Game manager object
extern GameManager *gm;

extern float deltaTime;

bool left = false;
bool right = false;
bool up = false;
bool down = false;
bool space = false;



void checkKeys()
{
	if(left)
	{
		gm->player->box.x -= gm->player->movespeed;
	}
	if(right)
	{
		gm->player->box.x += gm->player->movespeed;
	}
	if(up)
	{
		gm->player->box.y -= gm->player->movespeed;
	}
	if(down)
	{
		gm->player->box.y += gm->player->movespeed;	
	}
}


int getInput()
{
	if(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
				return -1;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return -1;
					case SDLK_LEFT:
						left = true;
						break;
					case SDLK_RIGHT:
						right = true;
						break;
					case SDLK_UP:
						up = true;
						break;
					case SDLK_DOWN:
						down = true;
						break;
				}
				break;
			case SDL_KEYUP:
				
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return -1;
					case SDLK_LEFT:
						left = false;
						break;
					case SDLK_RIGHT:
						right = false;
						break;
					case SDLK_UP:
						up = false;
						break;
					case SDLK_DOWN:
						down = false;
						break;
				}
				
				break;
			case SDL_MOUSEBUTTONDOWN:
				if(e.button.button == SDL_BUTTON_LEFT)
				{
					//movePlayerXY(e.button.x, e.button.y);
					//player->x = e.button.x - (player->w >> 1);
					//player->y = e.button.y - (player->h >> 1);
				}
				if(e.button.button == SDL_BUTTON_RIGHT)
				{
					
				}
				break;
		}
	}
	
	checkKeys();
	return 0;
}

