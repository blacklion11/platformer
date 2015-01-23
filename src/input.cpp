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
bool jumping = false;



void checkKeys()
{
	/**
	*	This sets the delta movement to test for possible collisions
	*/
	if(left)
	{
		gm->player->dx = -(gm->player->movespeed);
	}
	if(right)
	{
		gm->player->dx = gm->player->movespeed;
	}
	if(up)
	{
		gm->player->dy = -(gm->player->movespeed);
	}
	if(down)
	{
		gm->player->dy = gm->player->movespeed;
	}
	if(jumping)
	{
		gm->player->setJumping(true);
	}
	
	if(!(left || right))
	{
		gm->player->dx = 0;
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
					case SDLK_a:
						left = true;
						break;
					case SDLK_d:
						right = true;
						break;
					case SDLK_w:
						up = true;
						break;
					case SDLK_s:
						down = true;
						break;
					case SDLK_SPACE:
						jumping = true;
						break;
				}
				break;
			case SDL_KEYUP:
				
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return -1;
					case SDLK_a:
						left = false;
						break;
					case SDLK_d:
						right = false;
						break;
					case SDLK_w:
						up = false;
						break;
					case SDLK_s:
						down = false;
						break;
					case SDLK_SPACE:
						jumping = false;
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

