#include "FighterSystem.h"
#include "Manager.h"
#include "Transform.h"
#include "ImageComponent.h"
#include "GameCtrlSystem.h"
void FighterSystem::init()
{
	Entity* fighter = (mngr_->addEntity());
	auto fighterTr = fighter->addComponent<Transform>();
	fighterTr->height_ = 80;
	fighterTr->width_ = 80;
	fighterTr->position_ = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight()/2);
	auto image = fighter->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::TextureId::Airplanes));
	image->clip_ = { 47, 90, 207, 250 };
	mngr_->setHandler(ecs::_hdlr_Fighter, fighter);
}

void FighterSystem::update()
{
	
	if (mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->playing())
	{
		InputHandler* ih = InputHandler::instance();
		Entity* fighter = mngr_->getHandler(ecs::_hdlr_Fighter);
		Transform* tr_ = GETCMP2(fighter, Transform);
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(up_)) {
				Vector2D vel = tr_->velocity_;
				Vector2D newVel = vel + Vector2D(0, -1).rotate(tr_->rotation_) * 0.5;
				tr_->velocity_ =newVel;
				cout << "up";

			}
			else if (ih->isKeyDown(left_)) {
				tr_->rotation_ =tr_->rotation_ - 5;
				cout << "left";

			}
			else if (ih->isKeyDown(right_)) {
				tr_->rotation_ =tr_->rotation_ + 5;
				cout << "right";
			}
			cout << endl;
		}
		Vector2D newPos = tr_->position_ + tr_->velocity_;
		if (!((newPos.getX() + tr_->width_) > game_->getWindowWidth() || newPos.getX() < 0 
			|| newPos.getY() + tr_->height_ > game_->getWindowHeight() || newPos.getY() < 0))
		{
			if (tr_->velocity_.getX() != 0 || tr_->velocity_.getY() != 0)
			{
				tr_->position_ = tr_->position_ + tr_->velocity_;
				Vector2D newVel = tr_->velocity_ * 0.995;
				if (abs(newVel.getX()) < 0.1 && abs(newVel.getY()) < 0.1)
				{
					newVel = Vector2D(0, 0);
				}
				tr_->velocity_ =newVel;
			}
		}
		else
			tr_->velocity_ =tr_->velocity_ * -1;
	}
	
}