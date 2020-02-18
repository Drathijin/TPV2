#pragma once
#include "Component.h"
#include "Transform.h"
class Gun :
	public Component
{
public:
	Gun() :Component(ecs::Gun) {} ;
	~Gun() {};

	void update()override;
	void init()override;
private:
	Transform* tr_;

};

