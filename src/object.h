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
	int maxFallSpeed; // The maximum speed the object can fall
	int jumpSpeed;  // the object's jump speed
	bool jumping;  // boolean to test if the player is jumping
	bool grounded;  // boolean to test if the object is on the ground
	
	GameObject();
	~GameObject();
	
	void applyMovement();

};







#endif