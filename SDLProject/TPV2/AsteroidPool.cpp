#include "AsteroidPool.h"
#include "Asteroid.h"
#include "Collisions.h"
void AsteroidPool::generateAsteroids(int n)
{
	Asteroid* a;
	for (int i = 0; i < n; i++)
	{
		a = pool_.getObj();

		RandomNumberGenerator *ran = game_->getRandGen();
		bool horizontal = ran->nextInt(0, 2);
		bool which = ran->nextInt(0, 2);
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
		Vector2D c((game_->getWindowWidth()/2- ran->nextInt(-100,100)), game_->getWindowHeight() / 2 - ( ran->nextInt(-100,100)));
		int m = ran->nextInt(1, 2);
		a->vel_ = (c - pos).normalize();a->vel_=a->vel_*(20);
		cout << a->vel_;
		a->pos_ = pos;
		a->gens_ = ran->nextInt(1, Asteroid::MAX_GENERATIONS);
		a->setSize();
		a->rot_ = ran->nextInt(0, 359);
		a->setInUse(true);

	}
	numAsteroids += n;
}

void AsteroidPool::disableAll()
{
	vector<Asteroid*> p = pool_.getPool();
	for (Asteroid* a : p)
	{
		a->setInUse(false);
	}
}

void AsteroidPool::onCollision(Asteroid* a, Bullet* b)
{
	if (Collisions::collides(a->pos_, a->w_, a->h_, b->pos, b->w, b->h))
	{
		a->setInUse(0);

		if (a->gens_ >= 0)
		{
			for (int i = 0; i < 2; i++)
			{
				Asteroid* newAsteroid = pool_.getObj();

				Vector2D v = a->vel_.rotate(i * 45.0);
				Vector2D p = a->pos_ + v.normalize();
				RandomNumberGenerator* ran = game_->getRandGen();

				newAsteroid->setSize();
				newAsteroid->rot_ = a->rot_ + i * 45.0;
				newAsteroid->setInUse(true);
				newAsteroid->gens_ = a->gens_ - 1;
			}
		numAsteroids++;
		}
		else numAsteroids--;

	}
}