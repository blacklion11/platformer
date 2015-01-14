#include"player.h"



Player::Player()
{
	initPlayer();
}

void Player::initPlayer()
{
	x = 50;
	y = 50;
	box.x = x;
	box.y = y;
	box.w = box.h = 28;
	movespeed = 5;
	falling = true;
}

void Player::updatePlayer()
{

}

void Player::renderPlayer(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &box);
}


