#pragma once
#include "System.h"
#include "Entity.h"
#include "ObjectFactory.h"
class FighterSystem : public System
{
public:
	FighterSystem() :System(ecs::_sys_Fighter)
	{

	};
	~FighterSystem(){};
	void onCollisionWithAsteroid(Entity* a)
	{

	}
	void init() override;
	void update() override
	{

	}

};