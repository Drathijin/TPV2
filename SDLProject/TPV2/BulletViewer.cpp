#include "BulletViewer.h"
#include "BulletPool.h"
#include "Entity.h"

BulletViewer::BulletViewer() :Component(ecs::FighterViewer)
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
	SDL_Rect dest = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(),tr_->getH() };
	game_->getTextureMngr()->getTexture(Resources::TennisBall)->render(dest, tr_->getRot());

}