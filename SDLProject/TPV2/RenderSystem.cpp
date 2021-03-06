#include "RenderSystem.h"

#include "ecs.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include "Image.h"
#include "Transform.h"
#include "Texture.h"

RenderSystem::RenderSystem() :
	System(ecs::_sys_Render) {
}

void RenderSystem::update() {
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullets))
		drawImage(e); // auto cast from unique_ptr to Entity*

	drawCtrlMessages();
	drawScore();
}

void RenderSystem::drawImage(Entity* e) {
	Transform* tr = e->getComponent<Transform>(ecs::Transform);
	Texture* tex = e->getComponent<Image>(ecs::Image)->tex_;

	SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawCtrlMessages() {
	auto gameState =
		mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getState();
	if (gameState != GameCtrlSystem::RUNNING) {
		if (gameState == GameCtrlSystem::WAITING)
		{
			auto msgTex = game_->getTextureMngr()->getTexture(
				Resources::WaitingForPlayer);
			msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight() - 10));
		}
		else if (gameState == GameCtrlSystem::READY || gameState == GameCtrlSystem::ROUNDOVER)
		{
			auto msgTex = game_->getTextureMngr()->getTexture(
				Resources::PressEnter);
			msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight() - 10));
		}
	}

	if (gameState == GameCtrlSystem::GAMEOVER) {
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::GameOver);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight()) / 2);


		auto drawTex = game_->getTextureMngr()->getTexture(Resources::Draw);
		auto winTex = game_->getTextureMngr()->getTexture(Resources::YouWin);
		auto loseTex = game_->getTextureMngr()->getTexture(Resources::YouLose);

		if (mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getScore(0) == 3 &&
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getScore(1) == 3)
		{
			drawTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - 2*msgTex->getHeight()));
		}
		else if (mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getScore(mngr_->getClientId()) == 3)
		{
			winTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - 2 * msgTex->getHeight()));
		}
		else
		{
			loseTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - 2 * msgTex->getHeight()));
		}
	}

}

void RenderSystem::drawScore() {
	auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(),
			to_string(gameCtrl->getScore(0)) + " - "
					+ to_string(gameCtrl->getScore(1)),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);


	Texture name(game_->getRenderer(), mngr_->getName(),
		game_->getFontMngr()->getFont(Resources::ARIAL24),
		{ COLOR(0x111122ff) });


	int nX = (mngr_->getClientId() == 0) ? 50 : game_->getWindowWidth() -50-name.getWidth();

	SDL_SetRenderDrawColor(game_->getRenderer(), 255, 255, 255, 255);
	SDL_Rect r = { nX, 10, name.getWidth(), name.getHeight() };
	SDL_RenderFillRect(game_->getRenderer(), &r);
	name.render(nX, 10);

	Texture oName(game_->getRenderer(), mngr_->getOtherName(),
		game_->getFontMngr()->getFont(Resources::ARIAL24),
		{ COLOR(0x111122ff) });

	int onX = (mngr_->getClientId() == 0) ? game_->getWindowWidth() -50-oName.getWidth() : 50;
	oName.render(onX, 10);

}
