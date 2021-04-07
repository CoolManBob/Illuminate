#pragma once

#include "Poco/Net/StreamSocket.h"
using Poco::Net::StreamSocket;

#include "IlluminatePacketProcessor.h"
#include "IlluminateSocket.h"

class IlluminateLoginClientLogin : public IlluminatePacketProcessor
{
public:
	IlluminateLoginClientLogin();
	virtual ~IlluminateLoginClientLogin();

	//virtual bool processPacket(localInfo& local);
	virtual bool processPacket(const localInfo& local);
	bool processHashKeyPacket(localInfo& local);
	bool processUserLoginPacket(localInfo& local, const char* acct, UInt8 acctLen, const char* pw, UInt8 pwLen);
	bool processUnionInfo(localInfo& local);
	bool processCharacterList(localInfo& local);
	bool processCharacterCreation(localInfo& local);
	bool processWorldEnterRequest(localInfo& local);

	enum CLIENTLOGINOPERATION
	{
		CLIENTLOGIN_HASHKEY,
		CLIENTLOGIN_USERLOGIN,
		CLIENTLOGIN_UNIONINFO = 3,
		CLIENTLOGIN_CHARLIST = 6,
		CLIENTLOGIN_WORLDENTER = 8,
		CLIENTLOGIN_CHARCREATION = 10,
		CLIENTLOGIN_LOGINRESULT = 15,
	};

	enum LOGINRESULT
	{
		INCORRECTUSER = 0,
		GIBBERISH = 1,
		TOOMANYATTEMPTS,
		TOSAGREEMENT,
	};

	enum LOGINSTEP
	{
		HASHKEY = 0,
		AUTHENTICATED,
		CHARLIST,
		CHARCREATE,
		ENTERWORLD,
	};
	
private:
	void sendDummyCharacter(IlluminateSocket& sock);
	void sendLoginResult(IlluminateSocket& sock, int loginResult);

	enum class BASECHAR : UInt32
	{
		KNIGHT = 1,
		ARCHER,
		MAGE,
		ZERKER,
		HUNTER,
		SORC,
		SWASH,
		RANGER,
		ELEMENTALIST,
		SCION,
		SLAYER,
		ORBITER,
	};

	bool sendBaseCharPackets(IlluminateSocket& sock);
	SharedPtr<IlluminatePacket> getBaseCharPacket(BASECHAR baseChar);
	SharedPtr<IlluminatePacket> buildCharPacket(CharacterData &data);
	SharedPtr<IlluminatePacket> buildCharMovePacket(CharacterMove& move);
	SharedPtr<IlluminatePacket> buildFactorPacket(CharacterFactors& factors);
	SharedPtr<IlluminatePacket> buildFactorResultPacket(CharacterFactorResult& result);
	clientCharDataVec baseChars;
};