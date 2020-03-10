#include "BulletMotion.h"
#include "entity.h"
#include "Bullet.h"
void BulletMotion::init()
{
	tr_ = GETCMP1_(Transform);
	bp_ = GETCMP1_(BulletPool);
}

void BulletMotion::update()
{
	std::vector<Bullet*> v = static_cast<BulletPool*>(bp_)->getPool();
	for (Bullet* bullet : v)
	{
		Vector2D pos= bullet->getPos();
		Vector2D vel= bullet->getVel();
		bullet->setPos(pos+vel);
		pos = bullet->getPos();
		if (pos.getX() > game_->getWindowWidth() ||pos.getX() < 0 ||
			pos.getY() > game_->getWindowHeight() || pos.getY() < 0)
		//las balas se destruyen al salir de la pantalla
		{
			bullet->setActive(false);
		}
	}
}
