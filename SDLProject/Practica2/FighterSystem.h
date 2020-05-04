#pragma once
#include "System.h"
#include "Entity.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Manager.h"
class FighterSystem : public System
{
public:
	FighterSystem() :System(ecs::_sys_Fighter)
	{

	};
	~FighterSystem(){};

	void init() override;
	void update() override;


	SDL_Keycode up_=SDLK_UP;
	SDL_Keycode right_=SDLK_RIGHT;
	SDL_Keycode left_=SDLK_LEFT;

};