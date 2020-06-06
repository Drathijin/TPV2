#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"
#include "Transform.h"
#include "GameCtrlSystem.h"

class CollisionSystem: public System {
public:
	CollisionSystem() :
		System(ecs::_sys_Collisions) {
	}

	void update() {

		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid))
		{
			
			//comprobamos todas las posibles colisiones del asteroide con:
			if (e->isActive())
			{
				auto tr = e->getComponent<Transform>(ecs::Transform);
				auto fighter = mngr_->getHandler(ecs::_hdlr_Fighter);
				auto fighterTr = fighter->getComponent<Transform>(ecs::Transform);
				auto ctrlSystem = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);
				//con el caza
				if (Collisions::collidesWithRotation(tr->position_, tr->width_, tr->height_, tr->rotation_,
													 fighterTr->position_, fighterTr->width_, fighterTr->height_, fighterTr->rotation_))
					ctrlSystem->onFighterDeath();
				else
				{

					//con las balas
					for (auto b: mngr_->getGroupEntities(ecs::_grp_Bullet))
					{
						Transform* bTr = b->getComponent<Transform>(ecs::Transform);
						if (b->isActive() && Collisions::collidesWithRotation(tr->position_, tr->width_, tr->height_, tr->rotation_, bTr->position_, bTr->width_, bTr->height_, bTr->rotation_))
						{
							mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->onCollisionWithBullet(e, b);

							//si ya no quedan asteroides, se termina el juego
							if(mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->getNumOfAsteroids() == 0)
							{
								ctrlSystem->onAsteroidsExtenction();
							}
						}
					}
				}
			}
		
		}
	}
};

