#pragma once
#include "Component.h"
struct GameState : Component
{
	GameState() : Component(ecs::GameState)
	{}
	bool finished = false;
	bool playing = false;
	bool fighterWinner = false;
};