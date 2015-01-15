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
	Character::box.x = 50;
	Character::box.y = 50;
	Character::box.w = Character::box.h = 28;
	movespeed = 5;
	//falling = true;
}

void Player::updatePlayer()
{

}

bool Collidable::collidesWith(GameObject *thing)
{
	return false;
}


void Player::renderPlayer(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &(Character::box));
}




////////////////////////// Getters and Setters

void Player::setX(int x){Character::box.x = x;}
void Player::setY(int y){Character::box.y = y;}
void Player::setW(int w){Character::box.w = w;}
void Player::setH(int h){Character::box.h = h;}

int Player::getX(){return Character::box.x;}
int Player::getY(){return Character::box.y;}
int Player::getW(){return Character::box.w;}
int Player::getH(){return Character::box.h;}

