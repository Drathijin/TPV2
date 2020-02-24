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
			//pos.setX(-cos(tr_->getRot() + 90) * tr_->getW() + (pos.getX()));
			//pos.setY(sin(tr_->getRot() ) * tr_->getH() + (pos.getY()));
			GETCMP1_(BulletPool)->shoot(pos,tr_->getRot(),10,10);
		}
	}
}
void Gun::init()
{
	tr_ = GETCMP1_(Transform);
}