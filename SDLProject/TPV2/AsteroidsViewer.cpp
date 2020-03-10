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
	for (Asteroid* a : v)
	{
		if (a->isActive())
		{
			SDL_Rect dest = { a->getPos().getX(), a->getPos().getY(), a->getW(),a->getH() };
			game_->getTextureMngr()->getTexture(Resources::Asteroid)->render(dest, a->getRot());
		}
	}

}