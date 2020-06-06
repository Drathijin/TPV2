#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>

namespace msg {

using msgSizeType = uint32_t;

enum MsgId : uint8_t {
	_CONNECTED, //
	_CONNECTION_REFUSED, //
	_CLIENT_DISCONNECTED, //
	_FIGHTER_SHOOT,
	_FIGHTER_INFO,
	_PLAYER_INFO,
	_FIGHTER_DEAD,
	_BOTH_DIE,
	_START_REQUEST,
	_START_ROUND,

	//
	_last_MsgId_
};

#pragma pack(push,1)

struct Message {
	Message(msgSizeType size, MsgId id) :
			size(size), senderClientId(0), id(id) {
	}
	Message(MsgId id) :
			Message(sizeof(Message), id) {
	}
	msgSizeType size;
	uint32_t senderClientId;
	MsgId id;
};
struct PlayerInfoMsg : Message
{
	PlayerInfoMsg(const char* n) :Message(sizeof(PlayerInfoMsg), _PLAYER_INFO)
	{
		strcpy_s(name, 11, n);
	}
	char name[11];

};
struct ConnectedMsg: Message {
	ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) 
	{
	}
	uint32_t clientId;
};

struct ClientDisconnectedMsg: Message {
	ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(
					clientId) {
	}
	uint32_t clientId;
};

struct FighterInfoMsg : Message
{
	FighterInfoMsg(double_t x, double_t y, double_t rot) :
		Message(sizeof(FighterInfoMsg), _FIGHTER_INFO), x(x),y(y),rot(rot) {}
	
	double_t x;
	double_t y;
	double_t rot;
};

struct FighterDeadMsg : Message
{
	FighterDeadMsg(uint32_t fighterID) :
		Message(sizeof(FighterDeadMsg), _FIGHTER_DEAD), fighterID(fighterID) {}
	uint32_t fighterID;
};
#pragma pack(pop)

}
