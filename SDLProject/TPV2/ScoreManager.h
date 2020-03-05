#pragma once

#include "Component.h"

class ScoreManager: public Component {
public:
	enum GameState
	{
		Paused,
		Playing,
		Finished,
		Unfinished
	};

	ScoreManager();
	virtual ~ScoreManager();



	int getScore() { return score_; }
	void setScore(int s) { score_ = s; };

	GameState getGameState() { return gameState_; };
	void setGameState(GameState gs) { gameState_ = gs; };
	
	void virtual draw() override;

private:
	int score_;
	GameState gameState_;

};
