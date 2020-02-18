#pragma once
#include "Component.h"
#include "Transform.h"
class BulletMotion :
	public Component
{
public:
	BulletMotion() :Component(ecs::BulletMotion) {};
	~BulletMotion() {};

	void init()override;
	void update()override;

private:
	Transform* tr_;
};

