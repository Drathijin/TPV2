#include "FighterGunSystem.h"
#include "GameCtrlSystem.h"
#include "BulletsSystem.h"

void FighterGunSystem::update()
{
	if (mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->playing())
	{
		auto ih = InputHandler::instance();
		if (ih->isKeyDown(shootK_)&& SDLGame::instance()->getTime() > lastShoot + 250)
		{
			auto tr_ = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
			Vector2D pos = tr_->position_;
			pos.setX(cos((tr_->rotation_ * M_PI) / 180.0) + pos.getX() + tr_->width_ / 2);
			pos.setY(sin((tr_->rotation_ * M_PI) / 180.0) + pos.getY() + tr_->height_ / 2);
			mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->shoot(pos, 5.0,30.0,tr_->rotation_);
			//game_->getAudioMngr()->playChannel(Resources::AudioId::Paddle_Hit, 0);
		}
	}
}