#include "AsteroidsMotion.h"
#include "Entity.h"
void AsteroidsMotion::init()
{

	ap_ = GETCMP1_(AsteroidPool);
}
void AsteroidsMotion::update()
{
	vector<Asteroid*> asteroids = ap_->getPool();

	for (Asteroid* a : asteroids)
	{
		a->rot_++;
		a->pos_ = a->pos_ + a->vel_;
		if (a->pos_.getX() < 0)
		{
			a->pos_.setX(game_->getWindowWidth());
		}
		else if (a->pos_.getX() > game_->getWindowWidth())
		{
			a->pos_.setX(0);
		}
		if (a->pos_.getY() < 0)
		{
			a->pos_.setY(game_->getWindowHeight());
		}
		else if (a->pos_.getY() > game_->getWindowHeight())
		{
			a->pos_.setY(0);
		}
	}
}
