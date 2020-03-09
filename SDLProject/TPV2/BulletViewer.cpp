#include "BulletViewer.h"
#include "BulletPool.h"
#include "Entity.h"

BulletViewer::BulletViewer() :Component(ecs::BulletViewer), bp_(nullptr)
{
}
BulletViewer::~BulletViewer()
{
	bp_ = nullptr;
}

void BulletViewer::init()
{
	bp_ = GETCMP1_(BulletPool);
}

void BulletViewer::draw()
{
	std::vector<Bullet *> v = static_cast<BulletPool*>(bp_)->getPool();
	for (Bullet* bullet : v)
	{
		if (bullet->inUse())
		{
			SDL_Rect dest = { bullet->pos.getX(), bullet->pos.getY(), bullet->w,bullet->h };
			game_->getTextureMngr()->getTexture(Resources::TennisBall)->render(dest, bullet->rot);
		}
	}

}