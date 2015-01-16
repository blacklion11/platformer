#include"player.h"



Player::Player()
{
	initPlayer();
}

Player::~Player()
{

}

void Player::initPlayer()
{
	box.x = 50;
	box.y = 50;
	box.w = box.h = 28;
	movespeed = 5;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	//falling = true;
}

void Player::updatePlayer()
{

}



void Player::renderPlayer(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &box);
}




////////////////////////// Getters and Setters
void Player::setXY(int x, int y)
{
	box.x = x;
	box.y = y;
}
void Player::setX(int x){box.x = x;}
void Player::setY(int y){box.y = y;}
void Player::setW(int w){box.w = w;}
void Player::setH(int h){box.h = h;}

int Player::getX(){return box.x;}
int Player::getY(){return box.y;}
int Player::getW(){return box.w;}
int Player::getH(){return box.h;}

