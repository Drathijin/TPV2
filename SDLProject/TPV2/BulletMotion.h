#pragma once
#include "Component.h"
#include "BulletPool.h"
#include "Transform.h"

class BulletMotion :
	public Component
{
public:
	BulletMotion() :Component(ecs::BulletMotion), tr_(nullptr) {};
	~BulletMotion() {};

	void init()override;
	void update()override;

private:
	Transform* tr_;
	BulletPool* bp_;
};

