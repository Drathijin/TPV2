#pragma once
#include "ecs.h"
#include "Manager.h"
#include "ImageComponent.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "Manager.h"
#include "Score.h"
#include "SDLGame.h"
#include "Texture.h"
#include "Gamestate.h"

class RenderSystem: public System {
public:
	RenderSystem() :
			System(ecs::_sys_Render) {
	}

	void draw(Entity *e) {
		Transform *tr = e->getComponent<Transform>(ecs::Transform);
		ImageComponent *img = e->getComponent<ImageComponent>(ecs::ImageComponent);
		SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
				tr->height_);
		img->tex_->render(dest, tr->rotation_, img->clip_);
	}

	void drawScore() {
		auto sc = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
		Texture scoreMsg(game_->getRenderer(), std::to_string(sc->points_),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x0000ffff) });
		scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2,
				10);
	}

	void update() override {

		// draw asteroids and bullets
		for (auto &e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			draw(e);
		}

		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			draw(e);
		}
		// draw fighter
		draw(mngr_->getHandler(ecs::_hdlr_Fighter));

		// draw score
		drawScore();
		GameState* gamesTate = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState);

		// info message
		if (!gamesTate->playing)
		{
			Texture msg(game_->getRenderer(),"Press ENTER to start", game_->getFontMngr()->getFont(Resources::ARIAL24),{COLOR(0xff0000ff)});
			msg.render(game_->getWindowWidth()/2-msg.getWidth()/2,game_->getWindowHeight()-msg.getHeight()-10);

			//if game is over, we show the player wether they've won or not
			if (gamesTate->finished)
			{
				string line = (gamesTate->fighterWinner) ? "You win" : "You lose";
				SDL_Color c = (gamesTate->fighterWinner) ? SDL_Color{COLOR(0x00ff00ff)} : SDL_Color{COLOR(0xff0000ff)};
				Texture msg(game_->getRenderer(), line, 
					game_->getFontMngr()->getFont(Resources::ARIAL24), c);
				msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - 2*msg.getHeight()-5);
			}
		}
	}
};

