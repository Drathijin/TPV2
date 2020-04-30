#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"
#include "Transform.h"
#include "Health.h"

class CollisionSystem: public System {
public:
	CollisionSystem() :
		System(ecs::_sys_Collisions) {
	}

	void update() {
		/*
		auto ptr = mngr_->getHandler(ecs::_hdlr_PacMan)->getComponent<Transform>(ecs::Transform);
		for( auto& e : mngr_->getGroupEntities(ecs::_grp_Star)) {
			auto etr = e->getComponent<Transform>(ecs::Transform);
			if ( Collisions::collides(ptr->position_, ptr->width_, ptr->height_, etr->position_, etr->width_, etr->height_)) {
				mngr_->getSystem<StarsSystem>(ecs::_sys_Stars)->onCollision(e);
			}
		}
		*/
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid))
		{

			if (e->isActive())
			{
				auto tr = e->getComponent<Transform>(ecs::Transform);
				auto fighter = mngr_->getHandler(ecs::_hdlr_Fighter);
				auto fighterTr = fighter->getComponent<Transform>(ecs::Transform);
				auto ctrlSystem = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);
				//con el caza
				if (Collisions::collidesWithRotation(tr->position_, tr->width_, tr->height_, tr->rotation_, fighterTr->position_,
					fighterTr->width_, fighterTr->height_, fighterTr->rotation_))
				{
					//desactivamos las balas y los asteroides para que desaparezcan
					//pausamos la musica y quitamos una vida al caza

					for (auto ast : mngr_->getGroupEntities(ecs::_grp_Asteroid))
						ast->setActive(false);
					for (auto bullet : mngr_->getGroupEntities(ecs::_grp_Bullet))
						bullet->setActive(false);
					
					ctrlSystem->setPlaying(false);
					game_->getAudioMngr()->pauseMusic();

					//si el caza se queda sin vidas, el juego termina
					//if (fighter->getComponent<Health>(ecs::Health)->kill() == 0)
					if(false)
					{
						ctrlSystem->setFinished(true);
						ctrlSystem->setPlaying(false);
						
						//scoreManager_->setWinner(false);
						//health_->reset();
					}

					//ponemos al caza en el centro
					mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->resetFighter();
				}
				else
				{

					//con las balas
					for (auto b: mngr_->getGroupEntities(ecs::_grp_Bullet))
					{
						Transform* bTr = b->getComponent<Transform>(ecs::Transform);
						if (b->isActive() && Collisions::collidesWithRotation(tr->position_, tr->width_, tr->height_, tr->rotation_, bTr->position_, bTr->width_, bTr->height_, bTr->rotation_))
						{
							mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->onCollisionWithBullet(e, b);

							if (asteroidPool_->getNumOfAsteroid() == 0)
							{
								//scoreManager_->setWinner(true);
								ctrlSystem->setFinished(true);
								ctrlSystem->setPlaying(false);
								//health_->reset();
								mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->resetFighter();
							}
						}
					}
				}
			}
		
		}
	}
};

