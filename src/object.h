#ifndef OBJECT_H
#define OBJECT_H

#include<SDL2/SDL.h>

class Object
{
	
	
	
	public:
	
	SDL_Rect box;
	
	
	Object();
	~Object();
	
	virtual void setXY(int , int);
	virtual void setX(int);
	virtual void setY(int);
	virtual void setW(int);
	virtual void setH(int);
	
	virtual int getX();
	virtual int getY();
	virtual int getW();
	virtual int getH();
};



class GameObject: public Object
{

	public:
	
	bool moveable;
	bool collidable;
	
	GameObject();
	~GameObject();
	


};

class Collidable
{
	
	public:
	
	~Collidable();
	
	
	virtual bool collidesWith(GameObject *)=0;
	
};



#endif