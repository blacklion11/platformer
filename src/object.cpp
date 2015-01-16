#include"object.h"

////////////////Object////////////////////////////

//ctor
Object::Object()
{

}
//dtor
Object::~Object()
{

}

void Object::setXY(int x, int y)
{
	box.x = x;
	box.y = y;
}
void Object::setX(int x){box.x = x;}
void Object::setY(int y){box.y = y;}
void Object::setW(int w){box.w = w;}
void Object::setH(int h){box.h = h;}
void Object::setColor(int r, int g, int b, int a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

int Object::getX(){return box.x;}
int Object::getY(){return box.y;}
int Object::getW(){return box.w;}
int Object::getH(){return box.h;}