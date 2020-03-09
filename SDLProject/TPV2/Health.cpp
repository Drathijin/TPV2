#include "Health.h"


Health::Health() : Component(ecs::Health)
{
	lives_ = 3;
}
Health::~Health()
{
}


void Health::draw()
{
	Texture* text = game_->getTextureMngr()->getTexture(Resources::Heart);
	int w = text->getWidth();
	int h= text->getHeight();

	for (size_t i = 0; i < lives_; i++)
	{
		SDL_Rect dest = { w*i, 0, w, h };
		text->render(dest);
	}
}