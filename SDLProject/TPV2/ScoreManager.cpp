#include "ScoreManager.h"
#include "Entity.h"
#include "GameCtrl.h"
ScoreManager::ScoreManager() :
		Component(ecs::ScoreManager), //
		score_(0), //
		gameState_(GameState::Paused) //
{
}

ScoreManager::~ScoreManager() {
}

void ScoreManager::draw()
{
	if (gameState_ == Finished)
	{
		std::string finishedMessage = (GETCMP1_(GameCtrl)->getRemainingAsteroids() == 0) ? "Game Over! You won!" : "Game Over!You lost";
		const SDL_Color grey = SDL_Color{ 125,125,125,255 };

		Texture text = Texture(game_->getRenderer(), finishedMessage, *game_->getFontMngr()->getFont(Resources::ARIAL24), grey);
		text.render(SDL_Rect{(game_->getWindowWidth()/2)-(text.getWidth()/2), (game_->getWindowHeight() / 2) - (text.getHeight() / 2),text.getWidth(), text.getHeight()});
	}
}

