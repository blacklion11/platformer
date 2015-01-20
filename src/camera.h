#ifndef CAMERA_H
#define CAMERA_H


#include"object.h"

class Camera: public Object
{

	public:

	int numLevelTiles;
	int tileSize;
	
	Camera();
	~Camera();
	
	/*
	void setXY(int , int);
	void setX(int);
	void setY(int);
	void setW(int);
	void setH(int);
	
	int getX();
	int getY();
	int getW();
	int getH();
	*/
};


#endif