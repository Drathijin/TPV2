#pragma once

#include "ecs.h"
#include "BulletsSystem.h"
#include "AsteroidsSystem.h"
#include "System.h"
#include "Score.h"
#include "GameState.h"
#include "FighterSystem.h"


class GameCtrlSystem: public System {
public:

	GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	}

	// - crear una entidad, añade sus componentes (Score y GameState) y asociarla
// con el handler _hndlr_GameState.
	void init() override {
		Entity *e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		sc->points_ = 0;

		e->addComponent<GameState>();
		mngr_->setHandler(ecs::_hdlr_GameState,e);
	}



	// - si el juego está parado y el jugador pulsa ENTER empieza una nueva ronda:
// 1) añadir 10 asteroides llamando a addAsteroids del AsteroidsSystem.
// 2) actualizar el estado del juego y el número de vidas (si es necesario)
// en los componentes correspondientes (Score, Heath, GameState, …).
	void update() override {
		auto ih = game_->getInputHandler();

		if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN) && !playing_) {
			//mngr_->getSystem<StarsSystem>(ecs::_sys_Stars)->addStars(10);
			mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->addAsteroids(10);
			playing_ = true;
		}
	}

// - a este método se le va a llamar cuando muere el caza.
// - desactivar todos los asteroides y las balas.
// - actualizar los componentes correspondientes (Score, Heath, GameState, …).
	void onFighterDeath()
	{
		//desactivamos las balas y los asteroides para que desaparezcan

		for (auto ast : mngr_->getGroupEntities(ecs::_grp_Asteroid))
			ast->setActive(false);
		for (auto bullet : mngr_->getGroupEntities(ecs::_grp_Bullet))
			bullet->setActive(false);

		//pausamos la musica y quitamos una vida al caza
		playing_ = false;;
		game_->getAudioMngr()->pauseMusic();
		//health->LoseLife();

		//si el caza se queda sin vidas, el juego termina
		//if (fighter->getComponent<Health>(ecs::Health)->kill() == 0)
		if (false)
		{
			finished_ = true;

			//scoreManager_->setWinner(false);
			//health_->reset();
		}

		//ponemos al caza en el centro
		mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->resetFighter();
	}

	// - a este método se le va a llamar cuando no haya más asteroides.
	// - desactivar todas las balas.
	// - actualizar los componentes correspondientes (Score, GameState, …).
	void onAsteroidsExtenction()
	{
		//scoreManager_->setWinner(true);
		finished_ = true;
		playing_ = false;
		//health_->reset();
		mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->resetFighter();
	}

	inline bool playing() { return playing_; }
	inline bool finished() { return finished_; }
protected:
	bool playing_ = false;
	bool finished_ = false;
};

