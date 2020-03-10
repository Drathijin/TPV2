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
		a->setRot(a->getRot()+1);
		a->setPos(a->getPos() + a->getVel());
		if (a->getPos().getX() < 0)
		{
			a->setPos({ (double)game_->getWindowWidth(), a->getPos().getY() });

		}
		else if (a->getPos().getX() > game_->getWindowWidth())
		{
			a->setPos({0, a->getPos().getY()});
		}
		if (a->getPos().getY() < 0)
		{
			a->setPos({ a->getPos().getX(), (double)game_->getWindowHeight() });

		}
		else if (a->getPos().getY() > game_->getWindowHeight())
		{
			a->setPos({ a->getPos().getX(),0 });
		}
	}
}
