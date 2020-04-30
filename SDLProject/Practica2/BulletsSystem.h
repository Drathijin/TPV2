#pragma once
#include  "System.h"
#include "Vector2D.h"
#include "Entity.h"
#include "BulletsPool.h"
#include "Manager.h"


class BulletsSystem : public System {
public:

	// - añadir una bala al juego, como en la práctica 1 pero usando entidades.
	// - no olvidar añadir la bala al grupo _grp_Bullet
	void shoot(Vector2D pos, double width, double height, double rot)
	{
		int x = pos.getX();
		int y = pos.getY();
		int w = width;
		int h = height;
		int r = rot;

		Entity* e = mngr_->addEntity<BulletsPool>(x, y, w, h, r);
		if (e != nullptr)
			e->addToGroup(ecs::_grp_Bullet);
	};
	// - desactivar la bala “b”
	void onCollisionWithAsteroid(Entity* b, Entity* a)
	{

	};
	// - si el juego está parado no hacer nada.
	// - mover las balas y desactivar las que se salen de la ventana
	void update() override;

	BulletsSystem() : System(ecs::_sys_Bullets) {};
};
