#pragma once
#include "Vector2D.h"
class Bullet
{
public:
	Bullet(): vel_(0,0),pos_(0,0),rot_(0),w_(0),h_(0),enabled_(0){};
	~Bullet() {};


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

	inline bool isActive() { return enabled_; };
	void setActive(bool t) { enabled_ = t; };

private:
	bool enabled_;
	Vector2D vel_;
	Vector2D pos_;
	double rot_;
	double w_;
	double h_;
};

