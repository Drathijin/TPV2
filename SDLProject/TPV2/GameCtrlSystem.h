#pragma once

#include "ecs.h"
#include "System.h"
#include "SDLGame.h"
#include "Manager.h"

class GameCtrlSystem: public System {
public:
	enum State : uint8_t {
		READY, RUNNING, ROUNDOVER, GAMEOVER, WAITING
	};

	GameCtrlSystem();
	void init() override;
	void update() override;
	State getState() {
		return state_;
	}
	void onFighterDeath(uint8_t fighterId);
	void bothDie();
	uint8_t getScore(uint8_t fighterId) {
		//assert(fighterId >= 0 && fighterId <= 1);
		if(!(fighterId >= 0 && fighterId <= 1))
			throw "cuidado con el score";
		return score[fighterId];
	}
	virtual void recieve(const msg::Message& msg) override;
private:
	void resetScore();
	void startGame();
	void sendMyInfo();

	uint8_t score[2];
	State state_;
	bool requested = false;
};

