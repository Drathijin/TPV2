#include "BulletsSystem.h"

void BulletsSystem::update()
{
	for (auto& entity : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
		if (!entity->isActive())
			return;
		auto bulletTr = entity->getComponent<Transform>(ecs::Transform);
		bulletTr->rotation_ = (bulletTr->rotation_ + 1);
		bulletTr->position_ = bulletTr->position_ + bulletTr->velocity_;
		int x = bulletTr->position_.getX();
		int y = bulletTr->position_.getY();

		if (x < -bulletTr->width_ / 2 || x>game_->getWindowWidth() + bulletTr->width_ / 2 ||
			y < -bulletTr->height_ / 2 || y>game_->getWindowHeight() + bulletTr->height_ / 2)
			entity->setActive(false);
	}
}
