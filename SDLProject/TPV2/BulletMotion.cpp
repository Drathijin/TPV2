#include "BulletMotion.h"
#include "entity.h"
void BulletMotion::init()
{
	tr_ = GETCMP1_(Transform);
}

void BulletMotion::update()
{
	tr_->setPos(tr_->getPos() + tr_->getVel());
}
