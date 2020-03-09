#include "ScoreManager.h"
#include "Entity.h"
#include "GameCtrl.h"
#include "GameLogic.h"
#include "InputHandler.h"
ScoreManager::ScoreManager() :
		Component(ecs::ScoreManager), //
		score_(0) //
{
}

ScoreManager::~ScoreManager() {
}

void ScoreManager::update()
{
	InputHandler* ih = InputHandler::instance();
	if (!playing_ && ih->keyDownEvent())
	{
		if (finished_)
		{
			finished_ = false;
			score_ = 0;
			fighterWinner = false;
		}
		playing_ = true;
		GETCMP1_(GameLogic)->resetFighter();
		GETCMP1_(GameLogic)->createAsteroids();
		game_->getAudioMngr()->resumeMusic();
	}
}


