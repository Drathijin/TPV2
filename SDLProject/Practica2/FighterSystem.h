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
	void onCollisionWithAsteroid(Entity* a)
	{

	}
	void init() override;
	void update() override;
	void resetFighter()
	{
		Transform* fighterTr_ = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
		fighterTr_->position_ = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
		fighterTr_->velocity_ = Vector2D(0, 0);
		fighterTr_->rotation_ = 0;
	}

	SDL_Keycode up_=SDLK_UP;
	SDL_Keycode right_=SDLK_RIGHT;
	SDL_Keycode left_=SDLK_LEFT;

};