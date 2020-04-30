#include "FighterSystem.h"
#include "Manager.h"
#include "Transform.h"
#include "ImageComponent.h"

void FighterSystem::init()
{
	Entity* fighter = (mngr_->addEntity());
	auto fighterTr = fighter->addComponent<Transform>();
	fighterTr->position_ = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight());
	auto image = fighter->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::TextureId::SpaceShips));
	image->clip_ = { 47, 90, 207, 250 };
	mngr_->setHandler(ecs::_hdlr_Fighter, fighter);
}