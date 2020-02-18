#pragma once
#include "Component.h"
#include "Transform.h"
class BulletViewer :
	public Component
{
public:
	BulletViewer();
	~BulletViewer();

	void init() override;
	void draw() override;

	BulletPool* bp_;
};

