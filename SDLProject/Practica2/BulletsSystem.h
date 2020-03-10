#pragma once
#include  "System.h"
#include "Vector2D.h"
#include "Entity.h"
class BulletsSystem : public System {
public:

	// - a�adir una bala al juego, como en la pr�ctica 1 pero usando entidades.
	// - no olvidar a�adir la bala al grupo _grp_Bullet
	void shoot(Vector2D pos, Vector2D vel, double width, double height)
	{

	};
	// - desactivar la bala �b�
	void onCollisionWithAsteroid(Entity* b, Entity* a)
	{

	};
	// - si el juego est� parado no hacer nada.
	// - mover las balas y desactivar las que se salen de la ventana
	void update() override
	{

	};

	BulletsSystem() : System(ecs::_sys_Bullets) {};
};
