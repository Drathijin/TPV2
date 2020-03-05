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
	
	/*Devuelve los asteroides restantes
	* <param> chachi </param>
	*/
	int getRemainingAsteroids(int a) { return asteroidPool_->getNumOfAsteroid(); } 


private:
	// #Chachi Wachi#
	// Pool de asteroides
	AsteroidPool* asteroidPool_; 


	Health* health_;
};

