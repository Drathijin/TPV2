#pragma once
#include "Vector2D.h"
class Asteroid
{
public:

	static const int MAX_GENERATIONS = 3;
	Asteroid() : vel_(), pos_(), rot_(0), w_(40), h_(40), gens_(0), enabled_(false) {};
	Asteroid(Vector2D vel, Vector2D pos, double rot = 0.0, double w = 40.0, double h = 40.0, int gens = 0) 
	{ vel_ = vel; pos_ = pos; rot_ = rot; w_ = w; h_ = h; gens_ = gens;}
	~Asteroid() {};

	void setVel(Vector2D vel) { vel_ = vel; }
	Vector2D getVel() { return vel_; }

	void setPos(Vector2D pos) { pos_ = pos; }
	Vector2D getPos() { return pos_; }

	inline double getW() { return w_; }
	inline double getH() { return h_; }
	void setW(double w) { w_ = w; }
	void setH(double w) { w_ = w; }
	inline void setWH(double w, double h) { w_ = w; h_ = h; }

	inline double getRot() { return rot_; }
	void setRot(double rot) { rot_ = rot; }

	inline int getGens() { return gens_; }
	void setGens(int gens) { gens_ = gens; }

	void setSize() { w_ = 10.0 + 3.0 * gens_; h_ = w_; };


	bool isActive() { return enabled_; };
	void setActive(bool t) { enabled_ = t; };
private:
	bool enabled_=false;

	Vector2D vel_;
	Vector2D pos_;
	double w_;
	double h_;
	double rot_;
	int gens_;
};

