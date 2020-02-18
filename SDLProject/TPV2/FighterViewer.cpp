#include "FighterViewer.h"
#include "ecs.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Resources.h"

FighterViewer::FighterViewer():Component(ecs::FighterViewer)
{
} 
FighterViewer::~FighterViewer()
{
	tr_ = nullptr;
}

void FighterViewer::init()
{
	tr_ = GETCMP1_(Transform);
}

void FighterViewer::draw()
{
	SDL_Rect dest = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(),tr_->getH() };
	SDL_Rect clip = { 47, 90, 207, 250 };
	game_->getTextureMngr()->getTexture(Resources::Airplanes)->render(dest, tr_->getRot(), &clip );

}