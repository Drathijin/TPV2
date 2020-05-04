#include "AsteroidsSystem.h"
#include "GameCtrlSystem.h"

void AsteroidsSystem::update()
{
	if (!mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->playing) return;

	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
		if (!e->isActive())
			return;
		auto a = e->getComponent<Transform>(ecs::Transform);
		a->rotation_ = (a->rotation_ + 1);
		a->position_ = a->position_ + a->velocity_;
		if (a->position_.getX() < 0)
			//comprobamos si se sale por algun extremo para que entre por el opuesto
		{
			a->position_ = { (double)game_->getWindowWidth(), a->position_.getY() };
		}
		else if (a->position_.getX() > game_->getWindowWidth())
		{
			a->position_ = { 0, a->position_.getY() };
		}
		if (a->position_.getY() < 0)
		{
			a->position_ = { a->position_.getX(), (double)game_->getWindowHeight() };

		}
		else if (a->position_.getY() > game_->getWindowHeight())
		{
			a->position_ = { a->position_.getX(),0 };
		}
	}
}

