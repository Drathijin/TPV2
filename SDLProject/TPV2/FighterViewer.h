#pragma once
#include "Component.h"
#include "Transform.h"
#include "Texture.h"

class FighterViewer :
	public Component
{
public:
	FighterViewer();
	~FighterViewer();

	void init() override;
	void draw() override;

	Transform* tr_;
};

