#pragma once
#include  "System.h"
#include "Vector2D.h"
#include "Entity.h"
class BulletsSystem : public System {
public:

	// - añadir una bala al juego, como en la práctica 1 pero usando entidades.
	// - no olvidar añadir la bala al grupo _grp_Bullet
	void shoot(Vector2D pos, Vector2D vel, double width, double height)
	{

	};
	// - desactivar la bala “b”
	void onCollisionWithAsteroid(Entity* b, Entity* a)
	{

	};
	// - si el juego está parado no hacer nada.
	// - mover las balas y desactivar las que se salen de la ventana
	void update() override
	{

	};

	BulletsSystem() : System(ecs::_sys_Bullets) {};
};
