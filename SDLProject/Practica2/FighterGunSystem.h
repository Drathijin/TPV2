#pragma once
#include "System.h"
#include "Entity.h"
#include "ObjectFactory.h"
class FighterGunSystem : public System
{
public:
	FighterGunSystem() : System(ecs::_sys_FighterGun)
	{}
	virtual ~FighterGunSystem(){}
	void update()override;
private:

	size_t lastShoot = 0;
	SDL_Keycode shootK_ = SDLK_SPACE;
};