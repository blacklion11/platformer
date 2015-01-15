#ifndef ENTITY_H
#define ENTITY_H

#include"object.h"

class Entity: public GameObject
{

	public:
	
	
	Entity();
	~Entity();
	
	
	
};

class LivingEntity: public Entity
{

	public:
	
	float movespeed;
	
	LivingEntity();
	~LivingEntity();

};

class Character: public LivingEntity
{

	public:
	
	
	Character();
	~Character();

};

#endif