#include "Gun.h"
#include "InputHandler.h"
#include "BulletPool.h"
#include "Entity.h"
#include "SDL_macros.h"

void Gun::update()
{
	InputHandler* EH = InputHandler::instance();

	if (EH->keyDownEvent())
	{
		if (EH->isKeyDown(SDLK_SPACE))
		{
			Vector2D pos = tr_->getPos();
			pos.setX(cos((tr_->getRot()*M_PI)/180.0) + pos.getX() + tr_->getW()/2);
			pos.setY(sin((tr_->getRot()*M_PI)/180.0) + pos.getY() + tr_->getH() / 2);
			pos = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2) + Vector2D(0, -(tr_->getH() / 2 + 5.0)).rotate(tr_->getRot());
			GETCMP1_(BulletPool)->shoot(pos,tr_->getRot(),2,6);
		}
	}
}
void Gun::init()
{
	tr_ = GETCMP1_(Transform);
}