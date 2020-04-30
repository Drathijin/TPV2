#include "FighterCtrl.h"
#include "SDL_macros.h"
#include "InputHandler.h"
#include "Entity.h"


FighterCtrl::~FighterCtrl()
{
}


void FighterCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterCtrl::update() {

	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(up_)) {
			Vector2D vel = tr_->getVel();
			Vector2D newVel = vel+ Vector2D(0,-1).rotate(tr_->getRot())*0.5;
			tr_->setVel(newVel);

		}
		else if (ih->isKeyDown(left_)) {
			tr_->setRot(tr_->getRot()-5);
		}
		else if (ih->isKeyDown(right_)) {
			tr_->setRot(tr_->getRot()+5);
		}

	}
}
