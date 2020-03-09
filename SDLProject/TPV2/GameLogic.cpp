#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"


GameLogic::~GameLogic() {
}

void GameLogic::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
	createAsteroids();
}
void GameLogic::createAsteroids()
{
	asteroidPool_->generateAsteroids(10);
}
void GameLogic::update() {
	if (scoreManager_->isPlaying())
	{
		auto aP = asteroidPool_->getPool();
		for (auto a : aP)
		{
			if (a->inUse())
			{
				if (Collisions::collidesWithRotation(a->pos_, a->w_, a->h_, a->rot_, fighterTr_->getPos(),
					fighterTr_->getW(), fighterTr_->getH(), fighterTr_->getRot()))
				{
					asteroidPool_->disableAll();
					bulletsPool_->disableAll();
					scoreManager_->setPlaying(false);
					game_->getAudioMngr()->pauseMusic();
					if (health_->kill() == 0)
					{
						scoreManager_->setFinished(true);
						health_->reset();
						//fighterWinner = false;
					}
					else
					{
						resetFighter();
					}
				}
				else
				{
					auto bP = bulletsPool_->getPool();
					for (auto b : bP)
					{
						if (Collisions::collidesWithRotation(a->pos_, a->w_, a->h_, a->rot_, b->pos, b->w, b->h, b->rot))
						{
							asteroidPool_->onCollision(a, b);
						}
					}
				}
			}
		}
	}
	else
	{
		asteroidPool_->disableAll();
	}
}

void GameLogic::resetFighter()
{
	fighterTr_->setPos(game_->getWindowWidth() / 2 - fighterTr_->getW() / 2,
		game_->getWindowHeight() / 2 - fighterTr_->getH() / 2);
	fighterTr_->setVel(0, 0);
	fighterTr_->setRot(0);
}

