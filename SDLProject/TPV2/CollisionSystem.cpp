#include "CollisionSystem.h"

#include "Collisions.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "Manager.h"

CollisionSystem::CollisionSystem() :
		System(ecs::_sys_Collision) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {
	if (mngr_->getClientId() == 1)
		return;
	auto gameCtrlSys = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (gameCtrlSys->getState() != GameCtrlSystem::RUNNING)
		return;


	bool roundOver = false;

	for (auto &f : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		auto fTR = f->getComponent<Transform>(ecs::Transform);

		for (auto &b : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
			if (!b->isActive())
				continue;

			auto bTR = b->getComponent<Transform>(ecs::Transform);

			if (Collisions::collidesWithRotation(bTR->position_, bTR->width_,
					bTR->height_, bTR->rotation_, fTR->position_, fTR->width_,
					fTR->height_, fTR->rotation_)) {

				roundOver = true;
				auto id = f->getComponent<FighterInfo>(ecs::FighterInfo)->fighterId;
				//mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath(id);
				mngr_->send<msg::FighterDeadMsg>(id);
			}
		}
	}
	Transform* f0Tr = mngr_->getHandler(ecs::_hdlr_Fighter0)->getComponent<Transform>(ecs::Transform);
	Transform* f1Tr = mngr_->getHandler(ecs::_hdlr_Fighter1)->getComponent<Transform>(ecs::Transform);
	if(Collisions::collidesWithRotation(f0Tr->position_, f0Tr->width_,
		f0Tr->height_, f0Tr->rotation_, f1Tr->position_, f1Tr->width_,
		f1Tr->height_, f1Tr->rotation_))
		mngr_->send<msg::Message>(msg::_BOTH_DIE);

	if (roundOver)
		mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
}

