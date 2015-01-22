#include"object.h"



GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}


void GameObject::applyMovement()
{
	box.x = tempX;
	box.y = tempY;
}