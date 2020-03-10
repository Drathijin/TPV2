#include "AsteroidPool.h"
#include "Asteroid.h"
#include "Collisions.h"


void AsteroidPool::generateAsteroids(int n)
{
	Asteroid* a;
	for (int i = 0; i < n; i++)
	{
		a = pool_.getObj();
		if (a != nullptr)
		{

			/*
				generamos dos booleanos aleatorios:
				horizontal: determina si el asteroide saldra por las paredes horizontales o por las verticales
				which: determina si el asteroide saldra por la primera (arriba o izquierda) o por la segunda (derecha o abajo) de las opciones
			*/
			RandomNumberGenerator* ran = game_->getRandGen();
			bool horizontal = ran->nextInt(0, 2);
			bool which = ran->nextInt(0, 2);
			Vector2D pos;
			double value = 0;

			//generamos un valor aleatorio para calcular desde donde saldra el asteroide.
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

			//calculamos la velocidad del asteroide
			Vector2D c((game_->getWindowWidth() / 2 - ran->nextInt(-100, 100)), game_->getWindowHeight() / 2 - (ran->nextInt(-100, 100)));
			int m = ran->nextInt(1, 2);
			a->setVel((c - pos).normalize() * (m));
			a->setPos(pos);
			a->setGens(ran->nextInt(1, Asteroid::MAX_GENERATIONS));
			a->setSize();
			a->setRot(ran->nextInt(0, 359));
			a->setActive(true);
		}
	}
	numAsteroids += n;
}

void AsteroidPool::disableAll()
{
	vector<Asteroid*> p = pool_.getPool();
	for (Asteroid* a : p)
	{
		a->setActive(false);
	}
	numAsteroids = 0;
}

void AsteroidPool::onCollision(Asteroid* a, Bullet* b)
{
	//se destruyen y se escucha una explosion

	a->setActive(false);
	b->setActive(false);
	game_->getAudioMngr()->playChannel(Resources::Explosion, 0);

	if (a->getGens() >= 0)
	//si el asteroide puede generar sub-asteroides, busca dos asteroides en la pool y les asigna los valores necesarios
	{
		for (int i = 0; i < 2; i++)
		{
			Asteroid* newAsteroid = pool_.getObj();

			Vector2D v = a->getVel().rotate(i * 45.0);
			Vector2D p = a->getPos() + v.normalize();

			newAsteroid->setPos(p);
			newAsteroid->setVel(v);
			newAsteroid->setRot(a->getRot() + i * 45.0) ;
			newAsteroid->setGens(a->getGens() - 1);
			newAsteroid->setActive(true); 
			newAsteroid->setSize();
		}

		//-1 asteroide que se destruye +2 que se crean
		numAsteroids++;
	}
	
	//-1 asteroide que se destruye
	else numAsteroids--;
}
