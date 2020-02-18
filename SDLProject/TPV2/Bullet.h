#pragma once
#include "Vector2D.h"
class Bullet
{
public:
	Bullet(): vel(0,0),pos(0,0),rot(0),w(0),h(0),enabled(0){};
	~Bullet() {};

	Vector2D vel;
	Vector2D pos;
	double rot;
	double w;
	double h;
	bool inUse() { return enabled; };
	void setInUse(bool t) { enabled = t; };
private:
	bool enabled;
};

