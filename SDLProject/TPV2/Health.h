#pragma once
#include "Component.h"
class Health :
	public Component
{
public:
	Health();
	~Health();


	inline void kill() { lives_--; if (lives_ < 1) { /*game_->hemuerto()*/ }; };
	inline void reset() { lives_ = 3; };
	void draw();
private:
	int lives_;
};

