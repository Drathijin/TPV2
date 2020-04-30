#pragma once
#include "Component.h"
#include "Transform.h"
class Gun :
	public Component
{
public:
	Gun(SDL_Keycode key=SDLK_SPACE) :Component(ecs::Gun),tr_(nullptr), fireKey_(key){} ;
	~Gun() {};

	void update()override;
	void init()override;
private:
	Transform* tr_;
	SDL_Keycode fireKey_;
};

