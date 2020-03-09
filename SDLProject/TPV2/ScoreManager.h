#pragma once

#include "Component.h"

class ScoreManager: public Component {
public:

	ScoreManager();
	virtual ~ScoreManager();
	
	int getScore() { return score_; }
	void addScore(int points=1) { score_+=points; }
	void setScore(int s) { score_ = s; };

	bool isPlaying() { return playing_; };
	bool isFinished() { return finished_; };
	
	void setPlaying(bool b) { playing_ = b; };
	void setFinished(bool b) { finished_ = b; };

	bool fighterWon() { return fighterWinner; };
	void setWinner(bool b) { fighterWinner = b; }
	virtual void update();
private:
	int score_;
	bool playing_ = true;
	bool finished_ = false;
	bool fighterWinner = false;

};
