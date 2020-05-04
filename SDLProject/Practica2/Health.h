#pragma once
#include "Component.h"
struct Health : Component
{
	Health() :Component(ecs::Health), lifes_(3){};
	int lifes_;
};