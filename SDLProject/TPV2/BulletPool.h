#pragma once

#include <memory>
#include "vector2D.h"
#include "Component.h"
#include <SDL_stdinc.h>
#include "ObjectPool.h"
#include "Bullet.h"


class BulletPool : public Component
{
public:
	BulletPool() :Component(ecs::BulletPool), bullets([](Bullet* b) {return b->isActive(); }) {};
	~BulletPool() {};

	void shoot(Vector2D pos, double r, double w, double h);
	void disableAll() { vector <Bullet*> v = getPool(); for (Bullet* bullet : v) { bullet->setActive(false); } };
	//void onCollision(Bullet* b, Asteroid* a);
	vector<Bullet* > getPool() { return bullets.getPool(); }
	
private:
	Uint32 lastShot=0;
	ObjectPool<Bullet, 10> bullets;

};

