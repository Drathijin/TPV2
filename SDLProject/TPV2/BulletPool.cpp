#include "BulletPool.h"

void BulletPool::shoot(Vector2D pos, double r, double w, double h)
{
	Uint32 time = game_->getTime();
	if ( time- lastShot > 0.24)
	{
		Bullet* b = bullets.getObj();
		if (b != nullptr)
		{
			b->pos = pos;
			b->rot = r;
			b->w = w;
			b->h = h;
			b->vel = Vector2D(0, -1).rotate(r) * 10;
			lastShot = time;
			b->setInUse(true);
		}

	}
}
