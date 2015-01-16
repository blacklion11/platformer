#include"object.h"



GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}


void GameObject::applyMovement()
{
	box.x += deltaX;
	box.y += deltaY;
}