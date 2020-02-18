#pragma once
#include "Component.h"
class FighterMotion :
	public Component
{
public:
	FighterMotion() :Component(ecs::FighterMotion) {};
	~FighterMotion() {};
	void draw() override;




};

