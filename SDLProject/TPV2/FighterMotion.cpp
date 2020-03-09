#include "FighterMotion.h"
#include "Transform.h"
#include "SDL_macros.h"
#include "Entity.h"


void FighterMotion::draw()
{
	Transform *tc = GETCMP2_(ecs::Transform,Transform);
	Vector2D newPos = tc->getPos() + tc->getVel();
	if (! ((newPos.getX() + tc->getW()) > game_->getWindowWidth() || newPos.getX() < 0 || newPos.getY() + tc->getH() > game_->getWindowHeight() || newPos.getY() < 0))
	{
		if (tc->getVel().getX() != 0 || tc->getVel().getY() != 0)
		{
			tc->setPos(tc->getPos() + tc->getVel());
			Vector2D newVel = tc->getVel() * 0.995;
			if (abs(newVel.getX()) < 0.1 && abs(newVel.getY()) < 0.1)
			{
				newVel = Vector2D(0, 0);
			}
			tc->setVel(newVel);
		}
	}
	else
		tc->setVel(tc->getVel() * -1);
}