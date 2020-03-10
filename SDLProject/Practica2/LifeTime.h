#pragma once

#include <SDL_stdinc.h> // for Uint32
#include "Component.h"

struct AsteroidLifeTime: Component {
	AsteroidLifeTime() :
			Component(ecs::AsteroidLifeTime), //
			generations_(0) //
	{
	}

	Uint32 generations_;
};

