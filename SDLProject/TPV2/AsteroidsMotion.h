#pragma once
#include "Component.h"+
#include "AsteroidPool.h"

class AsteroidsMotion :
	public Component
{
public:
	AsteroidsMotion() : Component(ecs::AsteroidsMotion), ap_(nullptr) {};

	void init() override;

	void update() override;
	AsteroidPool* ap_;
private:
	

};

