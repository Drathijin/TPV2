#include "AsteroidPool.h"

void AsteroidPool::generateAsteroids(int n)
{
	Asteroid* a;
	for (int i = 0; i < n; i++)
	{
		a = pool_.getObj();

		RandomNumberGenerator *ran = game_->getRandGen();
		bool horizontal = ran->nextInt(0, 1);
		bool which = ran->nextInt(0, 1);
		Vector2D pos;
		double value=0;
		if (horizontal)
		{
			value = ran->nextInt(0, game_->getWindowWidth());
			pos = Vector2D(value, game_->getWindowHeight() * (int)which);
		}
		else
		{
			value = ran->nextInt(0, game_->getWindowHeight());
			pos = Vector2D(game_->getWindowWidth() * (int)which, value);
		}

		a = new Asteroid();
	}
}

void AsteroidPool::disableAll()
{
	vector<Asteroid*> p = pool_.getPool();
	for (Asteroid* a : p)
	{

	}
}

void AsteroidPool::onCollision(Asteroid* a, Bullet* b)
{

}
