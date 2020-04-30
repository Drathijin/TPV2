#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"


GameLogic::~GameLogic() {
}

void GameLogic::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}
void GameLogic::createAsteroids()
{
	asteroidPool_->generateAsteroids(10);
}
void GameLogic::update() {

	
	if (scoreManager_->isPlaying())
	{

		//comprobamos las colisiones de cada asteroide:
		auto aP = asteroidPool_->getPool();
		for (auto a : aP)
		{
			if (a->isActive())
			{
	//con el caza
				if (Collisions::collidesWithRotation(a->getPos(), a->getW(), a->getH(), a->getRot(), fighterTr_->getPos(),
					fighterTr_->getW(), fighterTr_->getH(), fighterTr_->getRot()))
				{
					//desactivamos las balas y los asteroides para que desaparezcan
					//pausamos la musica y quitamos una vida al caza

					asteroidPool_->disableAll();
					bulletsPool_->disableAll();
					scoreManager_->setPlaying(false);
					game_->getAudioMngr()->pauseMusic();

					//si el caza se queda sin vidas, el juego termina
					if (health_->kill() == 0)
					{
						scoreManager_->setFinished(true);
						scoreManager_->setPlaying(false);
						scoreManager_->setWinner(false);
						health_->reset();
					}

					//ponemos al caza en el centro
					resetFighter();
				}			
				else
				{

					//con las balas
					auto bP = bulletsPool_->getPool();
					for (auto b : bP)
					{
						if (b->isActive() && Collisions::collidesWithRotation(a->getPos(), a->getW(), a->getH(), a->getRot(), b->getPos(), b->getW(), b->getH(), b->getRot()))
						{

							//añadimos un punto y comprobamos si quedan asteroides
							//si no quedan, se acaba el juego
							asteroidPool_->onCollision(a, b);
							scoreManager_->addScore();
							if (asteroidPool_->getNumOfAsteroid() == 0)
							{
								scoreManager_->setWinner(true);
								scoreManager_->setFinished(true);
								scoreManager_->setPlaying(false);
								health_->reset();
								resetFighter();
							}
						}
					}
				}
			}
		}
	}
	

	
}

void GameLogic::resetFighter()
{
	fighterTr_->setPos(game_->getWindowWidth() / 2 - fighterTr_->getW() / 2,
		game_->getWindowHeight() / 2 - fighterTr_->getH() / 2);
	fighterTr_->setVel(0, 0);
	fighterTr_->setRot(0);
}

