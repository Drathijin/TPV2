#include "Asteroids.h"
#include <assert.h>

#include "SDL_macros.h"
#include "InputHandler.h"
#include "Rectangle.h"
#include "FighterViewer.h"
#include "Health.h"
#include "FighterCtrl.h"
#include "Transform.h"
#include "ecs.h"

#include "AsteroidPool.h"
#include "AsteroidsMotion.h"
#include "AsteroidsViewer.h"

#include "SDLGame.h"

#include "FighterMotion.h"
#include "BulletPool.h"
#include "BulletViewer.h"
#include "BulletMotion.h"
#include "Gun.h"
#include "GameLogic.h"
#include "ScoreViewer.h"



Asteroids::Asteroids() :
	game_(nullptr), //
	entityManager_(nullptr), //
	exit_(false) 
{
	initGame();
}
Asteroids::~Asteroids()
{
	closeGame();
}

void Asteroids::initGame()
{
	game_ = SDLGame::init("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	Entity* caza = entityManager_->addEntity();

	Transform* cazaTr = caza->addComponent<Transform>();
	caza->addComponent<FighterMotion>();
	caza->addComponent<FighterCtrl>();
	caza->addComponent<FighterViewer>();
	auto cazaHealth = caza->addComponent<Health>();
	caza->addComponent<Gun>();

	auto bulletPool = caza->addComponent<BulletPool>();
	caza->addComponent<BulletViewer>();
	caza->addComponent<BulletMotion>();
	
	cazaTr->setWH(20, 20);
	cazaTr->setPos(game_->getWindowWidth() / 2 - cazaTr->getW() / 2,
		game_->getWindowHeight() / 2 - cazaTr->getH() / 2);


	Entity*  Asteroids= entityManager_->addEntity();
	auto asteroidsPool = Asteroids->addComponent<AsteroidPool>();
	Asteroids->addComponent<AsteroidsMotion>();
	Asteroids->addComponent<AsteroidsViewer>();

	Entity* gameLogic = entityManager_->addEntity();
	gameLogic->addComponent<ScoreManager>();
	gameLogic->addComponent<ScoreViewer>();
	gameLogic->addComponent<GameLogic>(cazaTr, cazaHealth, asteroidsPool, bulletPool);
	



}
void Asteroids::update() {
	entityManager_->update();
}

void Asteroids::stop() {
	exit_ = true;
}

void Asteroids::handleInput() {

	InputHandler* ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			}
			else {
				SDL_SetWindowFullscreen(game_->getWindow(),
					SDL_WINDOW_FULLSCREEN);
			}
		}
	}

}
void Asteroids::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}


void Asteroids::closeGame() {
	delete entityManager_;
}

void Asteroids::start() {
	exit_ = false;
	//game_->getAudioMngr()->playChannel(Resources::GunShot, 0);
	game_->getAudioMngr()->playMusic(Resources::Imperial_March);
	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
	game_->getAudioMngr()->haltMusic();
}
