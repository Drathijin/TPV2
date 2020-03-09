#include "AsteroidsViewer.h"
#include "ecs.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Resources.h"

AsteroidsViewer::AsteroidsViewer() : Component(ecs::AsteroidsViewer), ap_(nullptr)
{
}
AsteroidsViewer::~AsteroidsViewer()
{
	ap_ = nullptr;
}

void AsteroidsViewer::init()
{
	ap_ = GETCMP1_(AsteroidPool);
}

void AsteroidsViewer::draw()
{
	std::vector<Asteroid*> v = (ap_)->getPool();
	for (Asteroid* bullet : v)
	{
		if (bullet->inUse())
		{
			SDL_Rect dest = { bullet->pos_.getX(), bullet->pos_.getY(), bullet->w_,bullet->h_ };
			game_->getTextureMngr()->getTexture(Resources::Asteroid)->render(dest, bullet->rot_);
		}
	}

}