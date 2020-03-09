#pragma once

#include "Component.h"

class ScoreManager: public Component {
public:

	ScoreManager();
	virtual ~ScoreManager();
	
	int getScore() { return score_; }
	void setScore(int s) { score_ = s; };

	bool isPlaying() { return playing_; };
	bool isFinished() { return finished_; };
	
	void setPlaying(bool b) { playing_ = b; };
	void setFinished(bool b) { finished_ = b; };


private:
	int score_;
	bool playing_ = true;
	bool finished_ = false;

};
