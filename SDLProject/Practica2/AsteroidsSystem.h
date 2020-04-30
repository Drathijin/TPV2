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

	void onCollision(Entity* s) {
		s->setActive(false);
		auto sc = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
		sc->points_++;
	}

	void addAsteroids(std::size_t n) {
		for (auto i(0u); i < n; i++) {
			int x = game_->getRandGen()->nextInt(0, game_->getWindowWidth());
			int y = game_->getRandGen()->nextInt(0, game_->getWindowHeight());
			int w = game_->getRandGen()->nextInt(25, 50);
			int h = w;
			int r = game_->getRandGen()->nextInt(1, 2);
			Uint32 lt = game_->getRandGen()->nextInt(5, 10);

			Entity* e = mngr_->addEntity<AsteroidsPool>(x, y, w, h, r, lt);
			if (e != nullptr)
				e->addToGroup(ecs::_grp_Asteroid);
		}
	}

	void update() override {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			if (!e->isActive())
				return;
		}

	}
};

