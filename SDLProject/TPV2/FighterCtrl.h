#pragma once
#include "Component.h"
#include "Transform.h"

class FighterCtrl :
	public Component
{
public:
	FighterCtrl(SDL_Keycode up = SDLK_UP, SDL_Keycode right = SDLK_RIGHT, SDL_Keycode left = SDLK_LEFT) :
		up_(up), right_(right), left_(left), Component(ecs::FighterCtrl)
	{
	}
	~FighterCtrl();
	void init() override;
	void update() override;
private:
	SDL_Keycode up_;
	SDL_Keycode right_;
	SDL_Keycode left_;
	Transform* tr_;
};

