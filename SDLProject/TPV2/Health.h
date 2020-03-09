#pragma once
#include "Component.h"
class Health :
	public Component
{
public:
	Health();
	~Health();


	inline int kill() { lives_--; return lives_; };
	inline void reset() { lives_ = 3; };
	void draw();
	inline int getLives() { return lives_; }
private:
	int lives_;
};

