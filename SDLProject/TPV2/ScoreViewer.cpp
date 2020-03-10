#include "ScoreViewer.h"

#include "Texture.h"
#include "Entity.h"
#include "SDL_macros.h"

ScoreViewer::ScoreViewer() :
		Component(ecs::ScoreViewer), //
		scoreManager_(nullptr) {
}

ScoreViewer::~ScoreViewer() {
}

void ScoreViewer::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

void ScoreViewer::draw() {
	string message;
	SDL_Color mColor;
	if (scoreManager_->isFinished())
	{
		//cuando el juego termina, le mostramos al jugador si gana o pierde
		if (scoreManager_->fighterWon())
		{
			message = "You win!";
			mColor = { 125,200,125,255 };
		}
		else {
			message = "You Lose!";
			mColor = { 200,125,125,255 };
		}
		Texture text = Texture(game_->getRenderer(), message, *game_->getFontMngr()->getFont(Resources::ARIAL24),mColor);
		text.render(game_->getWindowWidth()/2 - (text.getWidth()/2), 5 * game_->getWindowHeight() / 8 - (text.getHeight()));
	}

	//si el juego esta en pausa, le enseñamos que hacer y su puntuacion
	if(!scoreManager_->isPlaying())
	{
		message = "Press any key to start.";
		Texture text = Texture(game_->getRenderer(), message, *game_->getFontMngr()->getFont(Resources::ARIAL24), { 255,255,255,255 });
		text.render(game_->getWindowWidth() / 2 - (text.getWidth() / 2), 6 * game_->getWindowHeight() / 8 - (text.getHeight()));
	}
	message = "score: " + to_string(scoreManager_->getScore());
	Texture t = Texture(game_->getRenderer(), message, *game_->getFontMngr()->getFont(Resources::ARIAL24), { 255,0,255,255 });
	t.render(game_->getWindowWidth() / 2 - (t.getWidth() / 2),  game_->getWindowHeight() / 8 - (t.getHeight()));
}
