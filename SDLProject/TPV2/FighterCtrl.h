#pragma once
#include "Component.h"
#include "Transform.h"

class FighterCtrl :
	public Component
{
public:
	FighterCtrl();
	~FighterCtrl();
	void init() override;
	void update() override;
private:
	SDL_Keycode up_;
	SDL_Keycode down_;
	SDL_Keycode right_;
	SDL_Keycode left_;
	SDL_Keycode fire_;
	Transform* tr_;
};

