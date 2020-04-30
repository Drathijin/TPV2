#pragma once

#include "Component.h"
#include "Texture.h"

struct ImageComponent: Component {
	ImageComponent(Texture *tex) :
			Component(ecs::ImageComponent), //
			tex_(tex) //
	{
		clip_ = { 0,0,tex_->getWidth(), tex_->getHeight() };
	}
	Texture *tex_;
	SDL_Rect clip_;
};

