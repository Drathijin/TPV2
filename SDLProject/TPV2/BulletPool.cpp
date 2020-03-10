#include "BulletPool.h"

void BulletPool::shoot(Vector2D pos, double r, double w, double h)
{
	Uint32 time = game_->getTime();
	if ( time - lastShot >= 250)
	{
		Bullet* b = bullets.getObj();
		if (b != nullptr)
		{
			game_->getAudioMngr()->playChannel(Resources::GunShot, 0);
			b->setPos(pos);
			b->setRot(r);
			b->setWH(w,h);
			b->setVel(Vector2D(0, -1).rotate(r) * 2);
			b->setActive(true);

			lastShot = time;
		}

	}
}
