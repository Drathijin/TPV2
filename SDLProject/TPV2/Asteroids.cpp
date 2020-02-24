#include "SDL_macros.h"
#include "Asteroids.h"
#include <assert.h>


#include "InputHandler.h"


#include "Rectangle.h"
#include "FighterViewer.h"
#include "Health.h"
#include "SimpleMoveBahviour.h"
#include "FighterCtrl.h"
#include "Transform.h"
#include "ecs.h"

#include "SDLGame.h"
#include "FighterMotion.h"
#include "BulletPool.h"
#include "BulletViewer.h"
#include "BulletMotion.h"
#include "Gun.h"



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
	game_ = SDLGame::init("Ping Pong", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	Entity* caza = entityManager_->addEntity();

	Transform* cazaTr = caza->addComponent<Transform>();
	caza->addComponent<FighterMotion>();
	caza->addComponent<FighterCtrl>();
	caza->addComponent<FighterViewer>();
	caza->addComponent<Health>();
	caza->addComponent<Gun>();

	caza->addComponent<BulletPool>();
	caza->addComponent<BulletViewer>();
	caza->addComponent<BulletMotion>();
	

	cazaTr->setPos(5, game_->getWindowHeight() / 2 - 25);
	cazaTr->setWH(160, 160);
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

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}
