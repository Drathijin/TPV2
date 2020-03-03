#pragma once
#include "Component.h"
#include "AsteroidPool.h"

class AsteroidsViewer :
	public Component
{
public:
	AsteroidsViewer();
	~AsteroidsViewer();

	void init() override;
	void draw() override;

	AsteroidPool* ap_;
};

