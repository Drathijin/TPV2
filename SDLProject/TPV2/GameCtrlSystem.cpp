#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"
#include "Transform.h"
#include "BulletsSystem.h"
using namespace msg;




using ecs::CmpId;




GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	state_ = READY;
	resetScore();
}

void GameCtrlSystem::init() {
	state_ = WAITING;
	mngr_->send<msg::ConnectedMsg>(mngr_->getClientId());
	mngr_->send<msg::PlayerInfoMsg>(mngr_->getName());
}

void GameCtrlSystem::update() {

	if (state_ != RUNNING && state_!= WAITING) {
		InputHandler *ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			mngr_->send<Message>(msg::_START_REQUEST);
		}
	}
}

void GameCtrlSystem::startGame() {
	if (state_ == GAMEOVER) {
		resetScore();
	}
	mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();
	state_ = RUNNING;
}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) {
	assert(fighterId >= 0 && fighterId <= 1);
	uint8_t id = 1 - fighterId; // the id of the other player fighter

	state_ = ROUNDOVER;
	score[id]++;
	if (score[id] == 3)
		state_ = GAMEOVER;
}
void GameCtrlSystem::bothDie()
{
	state_ = ROUNDOVER;
}
void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}


void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_START_REQUEST:
	{
		if (msg.senderClientId == 0)
		{
			requested = false;
			startGame();
		}
		else if(msg.senderClientId == 1)
		{
			requested = true;
		}
		break;
	}
	case msg::_CLIENT_DISCONNECTED:
	{
		state_ = WAITING;
		requested = false;
		resetScore();
		mngr_->setOtherName(" ");
		break;
	}
	case msg::_CONNECTED:
	{
		if (state_ == READY || msg.senderClientId == mngr_->getClientId())
			return;
		cout <<"PREVIOUS STATE: " <<(int)state_ <<endl;
		state_ = READY;
		mngr_->send<ConnectedMsg>(mngr_->getClientId());
		break;
	}
	case msg::_PLAYER_INFO:
	{
		if (msg.senderClientId == mngr_->getClientId() || mngr_->getOtherName() != " ")
			return;
		mngr_->setOtherName(((const PlayerInfoMsg&)msg).name);
		mngr_->send<PlayerInfoMsg>(mngr_->getName());
		cout << "mensaje\n";
		break;
	}
	case msg::_FIGHTER_DEAD:
	{
		cout << "FIGHER DEAD \n";
		onFighterDeath(((const FighterDeadMsg&)msg).fighterID);
		mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
		break;
	}
	case msg::_BOTH_DIE:
	{
		bothDie();
		break; //todo
	}
	default:
		break;
	}
}