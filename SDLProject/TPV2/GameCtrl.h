#pragma once

#include "Component.h"
#include "Health.h"
#include "AsteroidPool.h"

class GameCtrl: public Component {

public:
	GameCtrl(AsteroidPool* pool, Health* health) : Component(ecs::GameCtrl), asteroidPool_(pool), health_(health) {};
	virtual ~GameCtrl();

	void init() override;
	void update() override;
	void draw() override;
	
	int getRemainingAsteroids() { return asteroidPool_->getNumOfAsteroid(); } 


private:

	AsteroidPool* asteroidPool_; 


	Health* health_;
};

