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

	bool moveable;
	bool collidable;
	
	GameObject();
	~GameObject();
	


};







#endif