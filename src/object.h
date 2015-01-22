#ifndef OBJECT_H
#define OBJECT_H

#include<SDL2/SDL.h>

class Object
{
	
	
	
	public:
	
	SDL_Rect box;
	SDL_Color color;
	
	Object();
	~Object();
	
	virtual void setXY(int , int);
	virtual void setX(int);
	virtual void setY(int);
	virtual void setW(int);
	virtual void setH(int);
	virtual void setColor(int, int, int, int);
	
	virtual int getX();
	virtual int getY();
	virtual int getW();
	virtual int getH();
};



class GameObject: public Object
{

	public:

	bool moveable;  // boolean to set if the object is able to move
	bool collidable; // boolean if things will collide with it
	int dx, dy; // the direction and movement speed variables
	int tempX, tempY;  // the temp location for movement to check for collisions
	
	GameObject();
	~GameObject();
	
	void applyMovement();

};







#endif