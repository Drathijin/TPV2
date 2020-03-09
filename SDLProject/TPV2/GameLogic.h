#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"
#include "AsteroidPool.h"
#include "BulletPool.h"
#include "Health.h"

class GameLogic: public Component {
public:
	GameLogic(Transform* fighterTr, Health* health, AsteroidPool* asteroidPool, BulletPool* bulletPool)
	: Component(ecs::GameLogic),
		fighterTr_(fighterTr), health_(health), asteroidPool_(asteroidPool), bulletsPool_(bulletPool)
	{

	}
	virtual ~GameLogic();
	
	void init() override;
	void update() override;
	
	void resetFighter();
	void createAsteroids();
private:

	AsteroidPool* asteroidPool_;
	BulletPool* bulletsPool_;
	
	Health* health_;
	Transform* fighterTr_;
	ScoreManager *scoreManager_;
};

