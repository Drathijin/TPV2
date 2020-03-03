#pragma once
#include "Asteroid.h"
#include "ObjectPool.h"
#include "Component.h"
#include "Bullet.h"

class AsteroidPool : public Component
{
public:
	AsteroidPool() :Component(ecs::AsteroidPool), pool_([](Asteroid* a) {return a->inUse(); }) {};
	void generateAsteroids(int n);
	void disableAll();
	void onCollision(Asteroid* a, Bullet* b);
	inline int getNumOfAsteroid() { return numAsteroids; };
	vector<Asteroid*> getPool() { return  pool_.getPool(); };
private:
	ObjectPool<Asteroid, 30> pool_;
	int numAsteroids = 0;
};

