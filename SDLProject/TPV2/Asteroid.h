#pragma once
#include "Vector2D.h"
class Asteroid
{
	const int MAX_GENERATIONS = 3;
public:
	Asteroid() : vel_(), pos_(), rot_(0), w_(0), h_(0), gens_(0), enabled_(false) {};
	Asteroid(Vector2D vel, Vector2D pos, double rot = 0.0, double w = 40.0, double h = 40.0, int gens = 0) 
	{ vel_ = vel; pos_ = pos; rot_ = rot; w_ = w; h_ = h; gens_ = gens;}
	~Asteroid() {};

	Vector2D vel_;
	Vector2D pos_;
	double w_;
	double h_;
	double rot_;
	int gens_;
	bool inUse() { return enabled_; };
	void setInUse(bool t) { enabled_ = t; };

private:
	bool enabled_;
};

