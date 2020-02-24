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
		
		bullet->pos = bullet->pos + bullet->vel;
		
		if (bullet->pos.getX() > game_->getWindowWidth() || bullet->pos.getX() < 0 ||
			bullet->pos.getY() > game_->getWindowHeight() || bullet->pos.getY() < 0)
		{
			bullet->setInUse(false);
		}
	}
}
