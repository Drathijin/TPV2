#include "SDL_macros.h"
#include "PacMan.h"
#include <assert.h>

#include "ImageComponent.h"
#include "InputHandler.h"
#include "Transform.h"
#include "SDLGame.h"
#include "BulletsPool.h"

#include "SDL_macros.h"

using namespace std;

PacMan::PacMan() :
		game_(nullptr), //
		mngr_(nullptr), //
		exit_(false) {
	initGame();
}

PacMan::~PacMan() {
	closeGame();
}
void PacMan::initGame() {

	game_ = SDLGame::init("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	game_->getAudioMngr()->setChannelVolume(10);

	AsteroidsPool::init(100);
	BulletsPool::init(30);
	mngr_ = new Manager(game_);

	renderSystem_ = mngr_->addSystem<RenderSystem>();
	asteroidsSystem_ = mngr_->addSystem<AsteroidsSystem>();
	bulletsSystem_ = mngr_->addSystem<BulletsSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	fighterSystem_ = mngr_->addSystem<FighterSystem>();
	fighterGunSystem_ = mngr_->addSystem<FighterGunSystem>();
}

void PacMan::closeGame() {
	delete mngr_;
}

void PacMan::start() {
	exit_ = false;
	auto ih = InputHandler::instance();

	while (!exit_) {
		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());

		ih->update();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
				break;
			}
		}

		mngr_->refresh();

		gameCtrlSystem_->update();
		fighterSystem_->update();
		fighterGunSystem_->update();
		bulletsSystem_->update();
		asteroidsSystem_->update();
		collisionSystem_->update();
		renderSystem_->update();


		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}


