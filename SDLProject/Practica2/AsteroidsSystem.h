#pragma once

#include <cmath>
#include "SDL_macros.h"
#include "LifeTime.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "AsteroidsPool.h"
#include "Manager.h"
#include "Score.h"
#include "SDLGame.h"

class AsteroidsSystem : public System {
public:
	AsteroidsSystem() :
		System(ecs::_sys_Asteroids) {
	}

	void onCollisionWithBullet(Entity* a, Entity* b) {

		auto sc = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
		sc->points_++;

		//se destruyen y se escucha una explosion
		AsteroidsPool::destroy(a);
		a->removeFromGroup(ecs::_grp_Asteroid);
		b->setActive(false);
		game_->getAudioMngr()->playChannel(Resources::Explosion, 0);

		//generamos los asteroides necesarios si las generaciones son mayores que 0
		int lifes = a->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime)->generations_;
		if ( lifes> 0)
		{
			for (int i = 0; i < 2; i++)
			{
				Transform* tr = a->getComponent<Transform>(ecs::Transform);
				Vector2D v = tr->velocity_.rotate(i * 45.0);
				Vector2D p = tr->position_ + v.normalize();
				double rot = a->getComponent<Transform>(ecs::Transform)->rotation_ + i * 45.0;
				int gens = lifes - 1;


				Entity* e = mngr_->addEntity<AsteroidsPool>(tr->position_.getX(), tr->position_.getY(), 30, 30, rot, v, gens);
				if (e != nullptr)
					e->addToGroup(ecs::_grp_Asteroid);
			}
			a->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime)->generations_--;

			//-1 asteroide que se destruye +2 que se crean
			numOfAsteroids_++;
		}

		//-1 asteroide que se destruye
		else numOfAsteroids_--;
	}

	void addAsteroids(std::size_t n) {
		for (auto i(0u); i < n; i++) {
			RandomNumberGenerator* ran = game_->getRandGen();
			bool horizontal = ran->nextInt(0, 2);
			bool which = ran->nextInt(0, 2);
			Vector2D pos;
			double value = 0;

			//generamos un valor aleatorio para calcular desde donde saldra el asteroide.
			if (horizontal)
			{
				value = ran->nextInt(0, game_->getWindowWidth());
				pos = Vector2D(value, game_->getWindowHeight() * (int)which);
			}
			else
			{
				value = ran->nextInt(0, game_->getWindowHeight());
				pos = Vector2D(game_->getWindowWidth() * (int)which, value);
			}
			Vector2D c((game_->getWindowWidth() / 2 - ran->nextInt(-100, 100)), game_->getWindowHeight() / 2 - (ran->nextInt(-100, 100)));

			int x = pos.getX();
			int y = pos.getY();
			int w = game_->getRandGen()->nextInt(25, 50);
			int h = w;
			int r = game_->getRandGen()->nextInt(1, 180);
			Uint32 lt = game_->getRandGen()->nextInt(1, 3);
			int m = ran->nextInt(1, 2);


			Entity* e = mngr_->addEntity<AsteroidsPool>(x, y, w, h, r, (c - pos).normalize() * (m), lt);
			if (e != nullptr)
				e->addToGroup(ecs::_grp_Asteroid);
			numOfAsteroids_++;
		}
	}

	void update() override;
	int getNumOfAsteroids() { return numOfAsteroids_; }
private:
	int numOfAsteroids_ = 0;
};

