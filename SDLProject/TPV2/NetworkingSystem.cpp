#include "NetworkingSystem.h"

#include "messages.h"
#include "Manager.h"

NetworkingSystem::NetworkingSystem() :
		System(ecs::_sys_NetWorking) {

}

NetworkingSystem::~NetworkingSystem() {
}

void NetworkingSystem::recieve(const msg::Message &msg) {
	if (msg.senderClientId == mngr_->getClientId()) {
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() {
	auto net = game_->getNetworking();
	msg::Message *msg = nullptr;

	while ((msg = net->recieve()) != nullptr) {
		switch (msg->id) {
		case msg::_CLIENT_DISCONNECTED:
			mngr_->forwardMsg<msg::ClientDisconnectedMsg>(msg->senderClientId,
					static_cast<msg::ClientDisconnectedMsg*>(msg)->clientId);
			break;
		case msg::_CONNECTED:
			mngr_->forwardMsg<msg::ConnectedMsg>(msg->senderClientId, 
				static_cast<msg::ConnectedMsg*>(msg)->clientId);
			break;
		case msg::_PLAYER_INFO:
			mngr_->forwardMsg<msg::PlayerInfoMsg>(
				msg->senderClientId,
				static_cast<msg::PlayerInfoMsg*>(msg)->name);
			break;
		case msg::_FIGHTER_INFO:
			mngr_->forwardMsg<msg::FighterInfoMsg>(msg->senderClientId,
				static_cast<msg::FighterInfoMsg*>(msg)->x,
				static_cast<msg::FighterInfoMsg*>(msg)->y,
				static_cast<msg::FighterInfoMsg*>(msg)->rot);
			break;

		case msg::_FIGHTER_DEAD:
			mngr_->forwardMsg<msg::FighterDeadMsg>(msg->senderClientId,
				static_cast<msg::FighterDeadMsg*>(msg)->fighterID);
			break;

		case msg::_BOTH_DIE:
			break;

		case msg::_FIGHTER_SHOOT: case msg::_START_REQUEST:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId,
				static_cast<msg::Message*>(msg)->id);
			break;
		default:
			//assert(false);
			cout << "que si se lee";
			throw string("Se manda un mensaje incorrecto");
			break;
		}
	}

}
