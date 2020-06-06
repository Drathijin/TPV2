#pragma once

#include "ecs.h"
#include "BulletsSystem.h"
#include "AsteroidsSystem.h"
#include "System.h"
#include "Score.h"
#include "Health.h"
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
		GameState* game = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
		auto ih = game_->getInputHandler();
		bool& finished_ = game->finished;
		bool& playing_ = game->playing;
		bool& playerWins_  = game->fighterWinner;

		if (!playing_)
		{
			//si el juego está pausado, se pueden añadir asteroides
			if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN) && !playing_) {
				mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->addAsteroids(10);
				playing_ = true;
				finished_ = false;
				playerWins_ = false;
			}
		}
	}

// - a este método se le va a llamar cuando muere el caza.
// - desactivar todos los asteroides y las balas.
// - actualizar los componentes correspondientes (Score, Heath, GameState, …).
	void onFighterDeath()
	{

		GameState* game = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
		auto ih = game_->getInputHandler();
		bool& finished_ = game->finished;
		bool& playing_ = game->playing;
		bool& playerWins_ = game->fighterWinner;

		Entity* fighter = mngr_->getHandler(ecs::_hdlr_Fighter);

		//desactivamos las balas y los asteroides para que desaparezcan

		for (auto ast : mngr_->getGroupEntities(ecs::_grp_Asteroid))
			ast->setActive(false);
		for (auto bullet : mngr_->getGroupEntities(ecs::_grp_Bullet))
			bullet->setActive(false);

		//pausamos la musica y quitamos una vida al caza
		playing_ = false;

		game_->getAudioMngr()->pauseMusic();

		Health* h = fighter->getComponent<Health>(ecs::Health);
		h->lifes_--;

		//si el caza se queda sin vidas, el juego termina
		if (h->lifes_ == 0)
		{
			finished_ = true;
			h->lifes_ = 3;
			mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score)->points_ = 0;
		}

		//ponemos al caza en el centro
		resetFighter();
	}

	// - a este método se le va a llamar cuando no haya más asteroides.
	// - desactivar todas las balas.
	// - actualizar los componentes correspondientes (Score, GameState, …).
	void onAsteroidsExtenction()
	{
		GameState* game = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);
		game->finished=true;
		game->playing=false;
		game->fighterWinner=true;

		resetFighter();
	}
	void resetFighter()
	{
		//reseteamos su posición, rotación y velocidad
		Transform* fighterTr_ = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
		fighterTr_->position_ = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
		fighterTr_->velocity_ = Vector2D(0, 0);
		fighterTr_->rotation_ = 0;
	}
};

