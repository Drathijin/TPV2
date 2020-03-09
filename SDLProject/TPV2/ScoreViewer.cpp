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
	if (scoreManager_->isFinished())
	{
		message = (scoreManager_->fighterWon()) ? "Has ganado!" : "Has perdido!";
		Texture text = Texture(game_->getRenderer(), message, *game_->getFontMngr()->getFont(Resources::ARIAL24), { 255,255,255,255 });
		text.render(game_->getWindowWidth()/2 - (text.getWidth()/2), game_->getWindowHeight() / 2 - (text.getHeight() / 2));
	}
	else if(!scoreManager_->isPlaying())
	{
		message = "Presione cualquier tecla para empezar";
		Texture text = Texture(game_->getRenderer(), message, *game_->getFontMngr()->getFont(Resources::ARIAL24), { 255,255,255,255 });
		text.render(game_->getWindowWidth() / 2 - (text.getWidth() / 2), game_->getWindowHeight() / 2 - (text.getHeight() / 2));
	}
}
