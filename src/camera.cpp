#include "camera.h"


extern SDL_Window *window;

Camera::Camera()
{
	box.x = 0;
	box.y = 0;
	SDL_GetWindowSize(window, &(box.w), &(box.h));
}

Camera::~Camera()
{

}
/*
void Camera::setXY(int x, int y)
{
	box.x = x;
	box.y = y;
}

void Camera::setX(int x)
{
	box.x = x;
}

void Camera::setY(int y)
{
	box.y = y;
}

void Camera::setW(int w)
{
	box.w = w;
}

void Camera::setH(int h)
{
	box.h = h;
}

int Camera::getX()
{
	return box.x;
}

int Camera::getY()
{
	return box.y;
}
int Camera::getW()
{
	return box.w;
}
int Camera::getH()
{
	return box.h;
}
*/







































