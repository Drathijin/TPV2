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
			GETCMP1_(BulletPool)->shoot();
		}
	}
}
void Gun::init()
{
	tr_ = GETCMP1_(Transform);
}