#include"player.h"



extern SDL_Window *window;

Player::Player()
{
	initPlayer();
}

Player::~Player()
{

}

void Player::initPlayer()
{
	box.x = 200;
	box.y = 200;
	box.w = box.h = 28;
	movespeed = 3;
	deltaX = 0;
	deltaY = 0;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	
	//falling = true;
}

void Player::updatePlayer(Camera *camera)
{
	// update camera position
	updateCamera(camera);
}

void Player::updateCamera(Camera *camera)
{
	camera->setX(box.x - camera->box.w / 2);
	camera->setY(box.y - camera->box.h / 2);
	
	if(camera->box.x < 0)
		camera->box.x = 0;
	if(camera->box.y < 0)
		camera->box.y = 0;
	if(camera->box.x + camera->box.w > camera->numLevelTiles * camera->tileSize)
		camera->box.x = (camera->numLevelTiles * camera->tileSize) - camera->box.w;
	if(camera->box.y + camera->box.h > camera->numLevelTiles * camera->tileSize)
		camera->box.y = (camera->numLevelTiles * camera->tileSize) - camera->box.h;
}



void Player::renderPlayer(SDL_Renderer *renderer, Camera *camera)
{

	SDL_Rect offset;
	offset.x = box.x - camera->box.x;
	offset.y = box.y - camera->box.y;
	offset.w = box.w;
	offset.h = box.h;
	
	
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &offset);
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

