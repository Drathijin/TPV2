#include "ScoreManager.h"
#include "Entity.h"
#include "GameCtrl.h"
ScoreManager::ScoreManager() :
		Component(ecs::ScoreManager), //
		score_(0) //
{
}

ScoreManager::~ScoreManager() {
}


