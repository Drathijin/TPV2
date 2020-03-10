#pragma once

#include "ecs.h"
#include "BulletsSystem.h"
#include "AsteroidsSystem.h"
#include "System.h"
#include "Score.h"
#include "GameState.h"


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

		if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			//mngr_->getSystem<StarsSystem>(ecs::_sys_Stars)->addStars(10);
		}
	}

// - a este método se le va a llamar cuando muere el caza.
// - desactivar todos los asteroides y las balas.
// - actualizar los componentes correspondientes (Score, Heath, GameState, …).
	void onFighterDeath()
	{

	}

// - a este método se le va a llamar cuando muere el caza.
// - desactivar todos los asteroides y las balas.
// - actualizar los componentes correspondientes (Score, GameState, …).
	void onAsteroidsExtenction()
	{

	}

};

