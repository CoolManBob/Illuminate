#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

#include "IlluminateLoginGlobal.h"
#include "IlluminateLoginServerSystems.h"
#include "IlluminateLoginClientLogin.h"
#include "IlluminateHash.h"

IlluminateLoginClientLogin::IlluminateLoginClientLogin()
{

}

IlluminateLoginClientLogin::~IlluminateLoginClientLogin()
{

}

bool IlluminateLoginClientLogin::processPacket(const localInfo& local)
{
	/*AuPacket::GetField(
		v10,
		1,
		pvPacket,
		nSize,
		&pvFirst,
		&lResult,
		&pvCharDetailInfo,
		&lCID,
		&cAccountLen,
		&pszPassword,
		&lIsProtected,
		&pszAccountID,
		&pszExtraForForeign,
		&pszEncryptCode,
		&v35,
		&cPasswordLen,
		&pvPacketVersionInfo,
		&pvDetailServerInfo,
		&pszChallenge,
		&lIsLimited);*/
	/*  GetField(_param_3,(int)&this->m_pAgpmLogin->m_csPacket,&DAT_00000001,(short)param_2,_param_3,
           (int)&pszAccountID + 3,&uStack8,&pszExtraForForeign,&lIsProtected,&lCID,&cAccountLen,
           &lIsLimited,&pvCharDetailInfo,&pvPacketVersionInfo,&lResult,auStack4,&pszPassword,
           &cPasswordLen,&pszEncryptCode,&pvDetailServerInfo,&pszChallenge);*/
	/*Illuminate::INT8, Illuminate::CHAR, Illuminate::CHAR, Illuminate::INT8, Illuminate::CHAR, Illuminate::INT8, Illuminate::INT32, Illuminate::CHAR, Illuminate::PACKET, Illuminate::PACKET, Illuminate::INT32, Illuminate::PACKET, Illuminate::CHAR, Illuminate::CHAR, Illuminate::INT32, Illuminate::INT32*/
	/* 1, 32, 49, 1, 33, 1, 1, 32, 1, 1, 1, 1, 2049, 5, 1, 1*/
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* packet = localObj.packet;
	Int8 i8Operation = 0;
	//char cKey[32] = { 0 }, cAcct[49] = { 0 }, cPW[33] = { 0 }, cUnk1[32] = { 0 }, cUnk2[2049] = { 0 }, cUnk3[5] = { 0 };
	string cKey = "", cAcct = "", cPW = "", cUnk1 = "", cUnk2 = "", cUnk3 = "";
	cKey.reserve(32);
	cAcct.reserve(49);
	cPW.reserve(33);
	cUnk1.reserve(32);
	cUnk2.reserve(2049);
	cUnk3.reserve(5);
	UInt8 ui8AcctLen = 0, ui8PWLen = 0;
	Int32 i32Unk1 = 0, i32Unk2 = 0, i32IsLimited = 0, i32IsProtected = 0;
	SharedPtr<IlluminatePacket> packets[3] = { new IlluminatePacket(), new IlluminatePacket(), new IlluminatePacket() };

	pktInterface->processPacket(packet, &i8Operation, cKey.c_str(), cAcct.c_str(), &ui8AcctLen, cPW.c_str(), &ui8PWLen, &i32Unk1, cUnk1.c_str(), &packets[0], &packets[1], &i32Unk2, &packets[2], cUnk2.c_str(), cUnk3.c_str(), &i32IsLimited, &i32IsProtected);
	switch(i8Operation)
	{
		case CLIENTLOGIN_HASHKEY: //Initial Packet Opcode
			return processHashKeyPacket(localObj); break;
		case CLIENTLOGIN_USERLOGIN: //User Login Packet Opcode
			return processUserLoginPacket(localObj, cAcct.c_str(), ui8AcctLen, cPW.c_str(), ui8PWLen); break;
		case CLIENTLOGIN_UNIONINFO: //User World Union Info
			return processUnionInfo(localObj); break;
		case CLIENTLOGIN_CHARLIST: //User Character List Request
			return processCharacterList(localObj); break;
		case CLIENTLOGIN_WORLDENTER: //World Enter
			return processWorldEnterRequest(localObj); break;
		case CLIENTLOGIN_CHARCREATION: //Character Creation Request
			return processCharacterCreation(localObj); break;
		default:
		{
			stringstream errorMsg;
			errorMsg << "User Connect processPacket Unhandled Operation: " << (int)i8Operation;
			LOG(errorMsg.str(), FATAL);
			return false;
		}
	}
	return false;
}

bool IlluminateLoginClientLogin::processHashKeyPacket(localInfo& local)
{
	LOG("processHashKeyPacket");

	//Can check for version information here

	Int8 i8Operation = CLIENTLOGIN_HASHKEY;

	string hashKey = _localSys->_localAcct()->generateHashKey();

	_localSys->_localAcct()->setLoginStep(HASHKEY);

	SharedPtr<IlluminatePacket> response = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, hashKey.c_str(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	_localSock.sendPacket(response);

	return true;
}

bool IlluminateLoginClientLogin::processUserLoginPacket(localInfo& local, const char* acct, UInt8 acctLen, const char* pw, UInt8 pwLen)
{
	LOG("processUserLoginPacket");
	string user = acct, pass = pw;

	if (!_localSys->_localAcct()->decryptUserInfo(user, acctLen, pass, pwLen))
	{
		LOG("processUserLoginPacket: decryptUserInfo FAIL!", FATAL);
		return false;
	}

	string hashPW = IlluminateHash::getHash(pass);

	if (!serverLoginSys->checkLogin(user, hashPW))
	{
		sendLoginResult(_localSock, INCORRECTUSER); //Incorrect User ID
		return true;
	}

	_localSys->_localAcct()->setLoginStep(AUTHENTICATED);

	//get character data
	//serverLoginSys->getCharData(_localSys->_localChar());

	Int8 i8Operation = CLIENTLOGIN_USERLOGIN;
	Int32 i32IsLimited = 0, i32IsProtected = 0;
	SharedPtr<IlluminatePacket> signOnResponse = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, 0, acct, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &i32IsLimited, &i32IsProtected);

	_localSock.sendPacket(signOnResponse);

	return true;
}

bool IlluminateLoginClientLogin::processUnionInfo(localInfo& local)
{
	int unionType = 0;
	//Illuminate::INT32, Illuminate::CHAR, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::CHAR
	SharedPtr<IlluminatePacket> miniCharInfo = pktInterface->buildMiniPacket(Illuminate::AGPMLOGIN_CHAR_INFO, 0, 0, 0, 0, &unionType, 0, 0, 0, 0);

	/*Illuminate::INT8, Illuminate::CHAR, Illuminate::CHAR, Illuminate::INT8, Illuminate::CHAR, Illuminate::INT8, Illuminate::INT32, Illuminate::CHAR, Illuminate::PACKET, Illuminate::PACKET, Illuminate::INT32, Illuminate::PACKET, Illuminate::CHAR, Illuminate::CHAR, Illuminate::INT32, Illuminate::INT32*/
	Int8 i8Operation = 3;
	SharedPtr<IlluminatePacket> unionResponse = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, 0, 0, 0, 0, 0, 0, 0, &miniCharInfo, 0, 0, 0, 0, 0, 0, 0);

	_localSock.sendPacket(unionResponse);

	unsigned char name[] = "test";
	int maxChars = 1, index = 0;

	SharedPtr<IlluminatePacket> charName = pktInterface->buildMiniPacket(Illuminate::AGPMLOGIN_CHAR_INFO, 0, name, &maxChars, &index, 0, 0, 0, 0, 0);

	i8Operation = 4;

	SharedPtr<IlluminatePacket> charNameResponse = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, 0, 0, 0, 0, 0, 0, 0, &charName, 0, 0, 0, 0, 0, 0, 0);

	_localSock.sendPacket(charNameResponse);

	i8Operation = 5;
	unsigned char acct[] = "acct";

	SharedPtr<IlluminatePacket> charNameFinish = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, 0, acct, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	_localSock.sendPacket(charNameFinish);

	return true;
}

bool IlluminateLoginClientLogin::processCharacterList(localInfo& local)
{
	_localSys->_localAcct()->setLoginStep(CHARLIST);
	sendDummyCharacter(_localSock);

	Int8 i8Operation = 7;
	Int32 cID = 0;
	unsigned char acct[] = "acct";

	SharedPtr<IlluminatePacket> sendCharInfoFinish = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, 0, acct, 0, 0, 0, &cID, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	_localSock.sendPacket(sendCharInfoFinish);

	return true;
}

bool IlluminateLoginClientLogin::processCharacterCreation(localInfo& local)
{
	_localSys->_localAcct()->setLoginStep(CHARCREATE);

	if (!sendBaseCharPackets(_localSock))
		return false;

	//{	Illuminate::INT32, Illuminate::CHAR, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::CHAR }
	Int32 numChar = 15;
	Int32 race = 1;
	SharedPtr<IlluminatePacket> loginCharInfo = pktInterface->buildMiniPacket(Illuminate::AGPMLOGIN_CHAR_INFO, 0, 0, &numChar, 0, 0, &race, 0, 0, 0);

	Int8 i8Operation = 10;
	SharedPtr<IlluminatePacket> sendCharCreateFinish = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, 0, 0, 0, 0, 0, 0, 0, &loginCharInfo, 0, 0, 0, 0, 0, 0, 0);

	_localSock.sendPacket(sendCharCreateFinish);

	return true;
}

bool IlluminateLoginClientLogin::processWorldEnterRequest(localInfo& local)
{
	LOG("World Enter Request");
	_localSys->_localAcct()->setLoginStep(ENTERWORLD);

	//{	Illuminate::INT8, Illuminate::CHAR, Illuminate::INT32, Illuminate::CHAR, Illuminate::INT32, Illuminate::VEC3F, Illuminate::INT32 }
	Int8 i8Operation = 11;
	Int32 authKey = 12345; //What sorta number is expected here?
	unsigned char name[] = "Dummy#test";
	SharedPtr<IlluminatePacket> authKeyPkt = pktInterface->buildPacket(Illuminate::AGSMCHARMANAGER_PACKET_TYPE, &i8Operation, 0, 0, name, 0, 0, &authKey);

	_localSock.sendPacket(authKeyPkt);

	//{Illuminate::INT32, Illuminate::CHAR, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::CHAR}
	Int32 i32TID = 96;
	memset(name, 0, 10);//clear name
	strcpy((char*)name, "test");
	SharedPtr<IlluminatePacket> miniCharInfo = pktInterface->buildMiniPacket(Illuminate::AGPMLOGIN_CHAR_INFO, &i32TID, name, 0, 0, 0, 0, 0, 0, 0);

	//TODO: acquire serverAddress from serverListSys
	//{	Illuminate::CHAR }
	std::string serverAddress = loginConfig->getWorldAddress();
	
	SharedPtr<IlluminatePacket> miniServerInfo = pktInterface->buildMiniPacket(Illuminate::AGPMLOGIN_SERVER_INFO, serverAddress.c_str());

	//{	Illuminate::INT8, Illuminate::CHAR, Illuminate::CHAR, Illuminate::INT8, Illuminate::CHAR, Illuminate::INT8, Illuminate::INT32, Illuminate::CHAR, Illuminate::PACKET, Illuminate::PACKET, Illuminate::INT32, Illuminate::PACKET, Illuminate::CHAR, Illuminate::CHAR, Illuminate::INT32, Illuminate::INT32}
	i8Operation = 8;
	Int32 i32CID = 0;
	SharedPtr<IlluminatePacket> serverInfoPkt = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, 0, 0, 0, 0, 0, &i32CID, 0, miniCharInfo, miniServerInfo, 0, 0, 0, 0, 0, 0);

	_localSock.sendPacket(serverInfoPkt);

	return true;
}

void IlluminateLoginClientLogin::sendDummyCharacter(IlluminateSocket& sock)
{
	Int32 i32Dummy = 100, i32One = 1, i32Zero = 0;
	float fZero = 0;
	Int8 i8Zero = 0;

	//IlluminateCharacter char = IlluminateServerCharacterSys->getCharacterData();

	//{	Illuminate::VEC3F, Illuminate::VEC3F, Illuminate::INT32, Illuminate::INT32, Illuminate::FLOAT, Illuminate::FLOAT, Illuminate::INT8, Illuminate::INT8 }
	Illuminate::IlluminateVec3F pos, destPos;
	SharedPtr<IlluminatePacket> charMovePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_MOVE, &pos, &destPos, &i32Zero, &i32Zero, &fZero, &fZero, &i8Zero, &i8Zero);
	//SharedPtr<IlluminatePacket> charMovePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_MOVE, &char.Pos, &char.destPos, &i32Zero, &i32Zero, &fZero, &fZero, &i8Zero, &i8Zero);

#pragma region FACTORPACKETS

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorStatusPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_STATUS, &i32Dummy, &i32Dummy, &i32Dummy, &i32Dummy, &i32Dummy, 0, &i32Dummy, &i32Dummy, &i32Dummy, &i32Dummy, 0, &i32Zero, 0);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorTypePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_TYPE, &i32One, &i32One, &i32One);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32}
	SharedPtr<IlluminatePacket> factorPointPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_POINT, &i32Dummy, &i32Dummy, &i32Dummy, &i32Dummy, &i32Dummy, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorPointMaxPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_POINTMAX, &i32Dummy, &i32Dummy, &i32Zero, &i32Zero, &i32Zero, 0, 0, 0, 0, 0, 0);

	//Illuminate::AGPMCHAR_FACTOR_RECOVERY Skipped

	//Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE Skipped

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorAttributeEmpty = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	//{ Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorDmgPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DMG, factorAttributeEmpty, factorAttributeEmpty);

	//{ Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorDefPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DEFENSE, factorAttributeEmpty, factorAttributeEmpty);

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	Int32 i32AtkRng = 50, i32AtkSpd = 60;
	SharedPtr<IlluminatePacket> factorAttackPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTACK, &i32Dummy, &i32AtkRng, &i32AtkSpd, 0, 0, 0, 0, 0);

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorDirtPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DIRT, 0, 0, 0, 0, 0, &i32Zero, 0, &i32Zero);

	//Illuminate::AGPMCHAR_FACTOR_PRICE Skipped

	//{	Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorResPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTORS, 0, factorStatusPkt, factorTypePkt, 0, factorPointMaxPkt, 0, 0, factorDmgPkt, factorDefPkt, factorAttackPkt, 0, factorDirtPkt, 0);

	//{	Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTORS, factorResPkt, factorStatusPkt, factorTypePkt, factorPointPkt, factorPointMaxPkt, 0, 0, factorDmgPkt, factorDefPkt, factorAttackPkt, 0, factorDirtPkt, 0);

#pragma endregion	

	Int8 i8Operation = 0;
	Int16 i16Zero = 0;
	Int32 charID = 1012, charTID = 6, nameLen = 4;
	Int64 i64Zero = 0;
	unsigned char charName[] = "test", skillInit[33] = { 0 }, signature[] = "Signature";
	/*{	Illuminate::INT8, Illuminate::INT32, Illuminate::INT32, Illuminate::MEMORY_BLOCK, Illuminate::INT8, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET,
	Illuminate::INT64, Illuminate::INT64, Illuminate::INT64, Illuminate::INT8, Illuminate::INT8, Illuminate::INT32, Illuminate::INT8, Illuminate::UINT8, Illuminate::UINT8,
	Illuminate::UINT64, Illuminate::INT8, Illuminate::CHAR, Illuminate::INT8, Illuminate::INT8, Illuminate::INT32, Illuminate::INT8, Illuminate::UINT16, Illuminate::INT32,
	Illuminate::INT32, Illuminate::CHAR, Illuminate::MEMORY_BLOCK, Illuminate::UINT32 }*/
	SharedPtr<IlluminatePacket> charInfoPkt = pktInterface->buildPacket(Illuminate::AGPMCHARACTER_PACKET_TYPE,	&i8Operation, &charID, &charTID, &nameLen, charName, &i8Zero, charMovePkt, 0, factorPkt, &i64Zero, &i64Zero, &i64Zero, &i8Zero,
																							&i8Zero, &i32Zero, &i8Zero, &i8Zero, &i8Zero, &i64Zero, &i8Zero, skillInit, &i8Zero, &i8Zero, &i32Zero, &i8Zero, &i16Zero, &i32Zero,
																							&i32Zero, signature, &i16Zero, 0, &i32Zero);

	sock.sendPacket(charInfoPkt);
}

void IlluminateLoginClientLogin::sendLoginResult(IlluminateSocket& sock, int loginStatus)
{
	/*v4 = this;
  v5 = &this->m_pAgpmLogin->m_csPacketCharInfo;
  v10 = 15;
  v6 = AuPacket::MakePacket(v5, 0, (__int16 *)&pszCharName, 13, 0, pszCharName, 0, 0, 0, 0, 0, 0, 0);
  v7 = AuPacket::MakePacket(
         &v4->m_pAgpmLogin->m_csPacket,
         1,
         (__int16 *)&pszCharName,
         13,
         &v10,
         0,
         0,
         0,
         0,
         0,
         0,
         0,
         v6,
         0,
         &lResult,
         0,
         0,
         0,
         0,
         0);*/

	SharedPtr<IlluminatePacket> charName = pktInterface->buildMiniPacket(Illuminate::AGPMLOGIN_CHAR_INFO, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	Int8 i8Operation = CLIENTLOGIN_LOGINRESULT;

	SharedPtr<IlluminatePacket> loginResult = pktInterface->buildPacket(Illuminate::AGPMLOGIN_PACKET_TYPE, &i8Operation, 0, 0, 0, 0, 0, 0, 0, charName, 0, &loginStatus, 0, 0, 0, 0, 0);

	sock.sendPacket(loginResult);
}

bool IlluminateLoginClientLogin::sendBaseCharPackets(IlluminateSocket& sock)
{
	SharedPtr<IlluminatePacket> baseChar = getBaseCharPacket(BASECHAR::KNIGHT);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::ARCHER);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::MAGE);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::ZERKER);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::HUNTER);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::SORC);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::SWASH);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::RANGER);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::ELEMENTALIST);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::SCION);

	sock.sendPacket(baseChar);

	/*baseChar = getBaseCharPacket(BASECHAR::SLAYER);

	sock.sendPacket(baseChar);

	baseChar = getBaseCharPacket(BASECHAR::ORBITER);

	sock.sendPacket(baseChar);*/

	return true;
}


SharedPtr<IlluminatePacket> IlluminateLoginClientLogin::getBaseCharPacket(BASECHAR base)
{
	SharedPtr<CharDataInfo> baseChar;

	baseChar = serverDataSys->getCharDataFromDBID(static_cast<UInt32>(base));

	if (!baseChar)
		return nullptr;

	CharacterData charData;

	charData.charTID = baseChar->tID;
	charData.charName = baseChar->name;

	return buildCharPacket(charData);
}

/*struct CharacterData
{
	string charName;
	Int32 charID;
	Int32 charTID; //Template ID
	CharacterMove charMove;
	CharacterFactors charFactors;
	UInt64 money;
	UInt64 bankMoney;
	UInt64 cashMoney;
	Int8 actionStatus;
	Int8 criminalStatus;
	Int8 face;
	Int8 hair;
	Int32 optionFlag;
	Int8 bankSize;
	UInt32 remainingCrimTime;
	UInt32 remainingMurderTime;
	string signature;
};

{	Illuminate::INT8, Illuminate::INT32, Illuminate::INT32, Illuminate::MEMORY_BLOCK, Illuminate::INT8, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET,
	Illuminate::INT64, Illuminate::INT64, Illuminate::INT64, Illuminate::INT8, Illuminate::INT8, Illuminate::INT32, Illuminate::INT8, Illuminate::UINT8, Illuminate::UINT8,
	Illuminate::UINT64, Illuminate::INT8, Illuminate::CHAR, Illuminate::INT8, Illuminate::INT8, Illuminate::INT32, Illuminate::INT8, Illuminate::UINT16, Illuminate::INT32,
	Illuminate::INT32, Illuminate::CHAR, Illuminate::MEMORY_BLOCK, Illuminate::UINT32 }
SharedPtr<IlluminatePacket> charInfoPkt = pktInterface->buildPacket(Illuminate::AGPMCHARACTER_PACKET_TYPE, &i8Operation, &charID, &charTID, &nameLen, charName, &i8Zero, charMovePkt, 0, factorPkt, &i64Zero, &i64Zero, &i64Zero, &i8Zero,
	&i8Zero, &i32Zero, &i8Zero, &i8Zero, &i8Zero, &i64Zero, &i8Zero, skillInit, &i8Zero, &i8Zero, &i32Zero, &i8Zero, &i16Zero, &i32Zero,
	&i32Zero, signature, &i16Zero, 0, &i32Zero);
*/


SharedPtr<IlluminatePacket> IlluminateLoginClientLogin::buildCharPacket(CharacterData& data)
{
	CharacterMove charMove = data.charMove;
	CharacterFactors charFactors = data.charFactors;

	//IlluminateCharacter char = IlluminateServerCharacterSys->getCharacterData();

	SharedPtr<IlluminatePacket> charMovePkt = buildCharMovePacket(charMove);
	SharedPtr<IlluminatePacket> charActionPkt = nullptr;
	SharedPtr<IlluminatePacket> factorPkt = buildFactorPacket(charFactors);

	Int32 nameLen = data.charName.length();
	Int8 i8Operation = 0;
	Int16 i16Zero = 0;
	/*Int32 charID = 1012, charTID = 6, nameLen = 4;
	Int64 i64Zero = 0;
	unsigned char charName[] = "test", skillInit[33] = { 0 }, signature[] = "Signature";*/
	/*{	Illuminate::INT8, Illuminate::INT32, Illuminate::INT32, Illuminate::MEMORY_BLOCK, Illuminate::INT8, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET,
	Illuminate::INT64, Illuminate::INT64, Illuminate::INT64, Illuminate::INT8, Illuminate::INT8, Illuminate::INT32, Illuminate::INT8, Illuminate::UINT8, Illuminate::UINT8,
	Illuminate::UINT64, Illuminate::INT8, Illuminate::CHAR, Illuminate::INT8, Illuminate::INT8, Illuminate::INT32, Illuminate::INT8, Illuminate::UINT16, Illuminate::INT32,
	Illuminate::INT32, Illuminate::CHAR, Illuminate::MEMORY_BLOCK, Illuminate::UINT32 }*/
	SharedPtr<IlluminatePacket> charInfoPkt = pktInterface->buildPacket(Illuminate::AGPMCHARACTER_PACKET_TYPE, &i8Operation, &data.charSessionID, &data.charTID, &nameLen, data.charName.c_str(), &data.charStatus, charMovePkt, /*charActionPkt*/0, factorPkt,
		&data.money, &data.bankMoney, &data.cashMoney, &data.actionStatus, &data.criminalStatus, &data.attackerID, &data.isNewChar, &data.lastBindingIdx, &data.socialAnimIdx, &data.specialStatus, &data.transformStatus, data.skillInit.c_str(), 
		&data.face, &data.hair, &data.optionFlag, &data.bankSize, &data.eventStatusFlag, &data.remainingCrimTime, &data.remainingMurderTime, data.signature.c_str(), &data.GGSize, 0, &data.lastKilledBSquare);

	return charInfoPkt;
}

SharedPtr<IlluminatePacket> IlluminateLoginClientLogin::buildCharMovePacket(CharacterMove& move)
{
	SharedPtr<IlluminatePacket> charMovePkt;

	//{	Illuminate::VEC3F, Illuminate::VEC3F, Illuminate::INT32, Illuminate::INT32, Illuminate::FLOAT, Illuminate::FLOAT, Illuminate::INT8, Illuminate::INT8 }
	charMovePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_MOVE, &move.curPos, &move.destPos, &move.followTargetId, &move.followDistance, &move.axisX, &move.axisY, &move.flags, &move.direction);

	return charMovePkt;
}

SharedPtr<IlluminatePacket> IlluminateLoginClientLogin::buildFactorPacket(CharacterFactors& factors)
{
	CharacterFactorStatus charStatus = factors.status;
	CharacterFactorType charType = factors.type;
	CharacterFactorPoint charPoint = factors.point;
	CharacterFactorPointMax charPointMax = factors.pointMax;
	CharacterFactorRecovery charRecovery = factors.recovery;
	CharacterFactorAttribute charAttribute = factors.attribute;
	CharacterFactorDamage charDmg = factors.damage;
	CharacterFactorDefense charDef = factors.defense;
	CharacterFactorAttack charAtk = factors.attack;
	CharacterFactorDirt charDirt = factors.dirt;
	CharacterFactorPrice charPrice = factors.price;
	CharacterFactorItem charItem = factors.item;
	CharacterFactorResult charRes = factors.result;

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorStatusPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_STATUS, 
		&charStatus.stamina, &charStatus.strength, &charStatus.intelligence, &charStatus.dexterity, &charStatus.charisma, &charStatus.luck, 
		&charStatus.wisdom, &charStatus.level, &charStatus.moveSpeed, &charStatus.runSpeed, &charStatus.unionRank, &charStatus.villainPoints, &charStatus.unk);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorTypePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_TYPE, &charType.charRace, &charType.charGender, &charType.charClass);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32}
	SharedPtr<IlluminatePacket> factorPointPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_POINT, &charPoint.hp, &charPoint.mana, &charPoint.skillPoints, &charPoint.xpLow, 
		&charPoint.xpHigh, &charPoint.AP, &charPoint.MAP, &charPoint.MI, &charPoint.agro, &charPoint.damage, &charPoint.damageMagic, &charPoint.damageWater, &charPoint.damageFire, 
		&charPoint.damageEarth, &charPoint.damageAir, &charPoint.damagePoison, &charPoint.damageLightning, &charPoint.damageIce, &charPoint.bonusXP, &charPoint.damageHeroic);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorPointMaxPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_POINTMAX, &charPointMax.maxHP, &charPointMax.maxMana, &charPointMax.maxSkillPoints, 
		&charPointMax.xpLow, &charPointMax.xpHigh, &charPointMax.AP, &charPointMax.MAP, &charPointMax.MI, &charPointMax.AR, &charPointMax.DR, &charPointMax.MAR);

	//Illuminate::AGPMCHAR_FACTOR_RECOVERY Skipped
	SharedPtr<IlluminatePacket> factorRecoveryPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_RECOVERY, &charRecovery.hpRecover, &charRecovery.manaRecovery, &charRecovery.spRecovery);

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorAttributePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charAttribute.physical, &charAttribute.magic, &charAttribute.water, &charAttribute.fire,
		&charAttribute.earth, &charAttribute.air, &charAttribute.poison, &charAttribute.lightning, &charAttribute.ice, &charAttribute.physBlock, &charAttribute.skillBlock, &charAttribute.heroic,
		&charAttribute.heroicMelee, &charAttribute.heroicRange, &charAttribute.heroicMagic);

	//{ Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorDmgMinPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charDmg.min.physical, &charDmg.min.magic, &charDmg.min.water, &charDmg.min.fire,
		&charDmg.min.earth, &charDmg.min.air, &charDmg.min.poison, &charDmg.min.lightning, &charDmg.min.ice, &charDmg.min.physBlock, &charDmg.min.skillBlock, &charDmg.min.heroic,
		&charDmg.min.heroicMelee, &charDmg.min.heroicRange, &charDmg.min.heroicMagic);

	SharedPtr<IlluminatePacket> factorDmgMaxPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charDmg.max.physical, &charDmg.max.magic, &charDmg.max.water, &charDmg.max.fire,
		&charDmg.max.earth, &charDmg.max.air, &charDmg.max.poison, &charDmg.max.lightning, &charDmg.max.ice, &charDmg.max.physBlock, &charDmg.max.skillBlock, &charDmg.max.heroic,
		&charDmg.max.heroicMelee, &charDmg.max.heroicRange, &charDmg.max.heroicMagic);

	SharedPtr<IlluminatePacket> factorDmgPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DMG, factorDmgMinPkt, factorDmgMaxPkt);

	//{ Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorDefPointPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charDef.point.physical, &charDef.point.magic, &charDef.point.water, &charDef.point.fire,
		&charDef.point.earth, &charDef.point.air, &charDef.point.poison, &charDef.point.lightning, &charDef.point.ice, &charDef.point.physBlock, &charDef.point.skillBlock, &charDef.point.heroic,
		&charDef.point.heroicMelee, &charDef.point.heroicRange, &charDef.point.heroicMagic);

	SharedPtr<IlluminatePacket> factorDefRatePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charDef.rate.physical, &charDef.rate.magic, &charDef.rate.water, &charDef.rate.fire,
		&charDef.rate.earth, &charDef.rate.air, &charDef.rate.poison, &charDef.rate.lightning, &charDef.rate.ice, &charDef.rate.physBlock, &charDef.rate.skillBlock, &charDef.rate.heroic,
		&charDef.rate.heroicMelee, &charDef.rate.heroicRange, &charDef.rate.heroicMagic);

	SharedPtr<IlluminatePacket> factorDefPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DEFENSE, factorDefPointPkt, factorDefRatePkt);

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	//Int32 i32AtkRng = 50, i32AtkSpd = 60;
	SharedPtr<IlluminatePacket> factorAttackPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTACK, &charAtk.range, &charAtk.hitRange, &charAtk.attackSpeed, &charAtk.cast, &charAtk.cooldown, 
		&charAtk.accuracy, &charAtk.meleeDodge, &charAtk.rangeDodge);

	//
	SharedPtr<IlluminatePacket> factorItemPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ITEM, &charItem.durability, &charItem.hand, &charItem.rank, &charItem.physRank, &charItem.maxDura, &charItem.gacha);

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorDirtPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DIRT, &charDirt.duration, &charDirt.intensity, &charDirt.range, &charDirt.target, &charDirt.skillLevel, &charDirt.skillPoint, &charDirt.skillXP, &charDirt.heroicPoint);

	//Illuminate::AGPMCHAR_FACTOR_PRICE Skipped
	SharedPtr<IlluminatePacket> factorPricePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_PRICE, &charPrice.npcPrice, &charPrice.playerPrice, &charPrice.moneyHigh, &charPrice.moneyLow);

	//{	Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorResPkt = buildFactorResultPacket(charRes);

	//{	Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTORS, factorResPkt, factorStatusPkt, factorTypePkt, factorPointPkt, factorPointMaxPkt, factorRecoveryPkt, factorAttributePkt, factorDmgPkt, factorDefPkt, factorAttackPkt, factorItemPkt, factorDirtPkt, factorPricePkt);

	return factorPkt;
}

SharedPtr<IlluminatePacket> IlluminateLoginClientLogin::buildFactorResultPacket(CharacterFactorResult& result)
{
	CharacterFactorStatus charStatus = result.status;
	CharacterFactorType charType = result.type;
	CharacterFactorPoint charPoint = result.point;
	CharacterFactorPointMax charPointMax = result.pointMax;
	CharacterFactorRecovery charRecovery = result.recovery;
	CharacterFactorAttribute charAttribute = result.attribute;
	CharacterFactorDamage charDmg = result.damage;
	CharacterFactorDefense charDef = result.defense;
	CharacterFactorAttack charAtk = result.attack;
	CharacterFactorDirt charDirt = result.dirt;
	CharacterFactorPrice charPrice = result.price;
	CharacterFactorItem charItem = result.item;

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorStatusPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_STATUS,
		&charStatus.stamina, &charStatus.strength, &charStatus.intelligence, &charStatus.dexterity, &charStatus.charisma, &charStatus.luck,
		&charStatus.wisdom, &charStatus.level, &charStatus.moveSpeed, &charStatus.runSpeed, &charStatus.unionRank, &charStatus.villainPoints, &charStatus.unk);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorTypePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_TYPE, &charType.charRace, &charType.charGender, &charType.charClass);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32}
	SharedPtr<IlluminatePacket> factorPointPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_POINT, &charPoint.hp, &charPoint.mana, &charPoint.skillPoints, &charPoint.xpLow,
		&charPoint.xpHigh, &charPoint.AP, &charPoint.MAP, &charPoint.MI, &charPoint.agro, &charPoint.damage, &charPoint.damageMagic, &charPoint.damageWater, &charPoint.damageFire,
		&charPoint.damageEarth, &charPoint.damageAir, &charPoint.damagePoison, &charPoint.damageLightning, &charPoint.damageIce, &charPoint.bonusXP, &charPoint.damageHeroic);

	//{	Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorPointMaxPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_POINTMAX, &charPointMax.maxHP, &charPointMax.maxMana, &charPointMax.maxSkillPoints,
		&charPointMax.xpLow, &charPointMax.xpHigh, &charPointMax.AP, &charPointMax.MAP, &charPointMax.MI, &charPointMax.AR, &charPointMax.DR, &charPointMax.MAR);

	//Illuminate::AGPMCHAR_FACTOR_RECOVERY Skipped
	SharedPtr<IlluminatePacket> factorRecoveryPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_RECOVERY, &charRecovery.hpRecover, &charRecovery.manaRecovery, &charRecovery.spRecovery);

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorAttributePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charAttribute.physical, &charAttribute.magic, &charAttribute.water, &charAttribute.fire,
		&charAttribute.earth, &charAttribute.air, &charAttribute.poison, &charAttribute.lightning, &charAttribute.ice, &charAttribute.physBlock, &charAttribute.skillBlock, &charAttribute.heroic,
		&charAttribute.heroicMelee, &charAttribute.heroicRange, &charAttribute.heroicMagic);

	//{ Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorDmgMinPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charDmg.min.physical, &charDmg.min.magic, &charDmg.min.water, &charDmg.min.fire,
		&charDmg.min.earth, &charDmg.min.air, &charDmg.min.poison, &charDmg.min.lightning, &charDmg.min.ice, &charDmg.min.physBlock, &charDmg.min.skillBlock, &charDmg.min.heroic,
		&charDmg.min.heroicMelee, &charDmg.min.heroicRange, &charDmg.min.heroicMagic);

	SharedPtr<IlluminatePacket> factorDmgMaxPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charDmg.max.physical, &charDmg.max.magic, &charDmg.max.water, &charDmg.max.fire,
		&charDmg.max.earth, &charDmg.max.air, &charDmg.max.poison, &charDmg.max.lightning, &charDmg.max.ice, &charDmg.max.physBlock, &charDmg.max.skillBlock, &charDmg.max.heroic,
		&charDmg.max.heroicMelee, &charDmg.max.heroicRange, &charDmg.max.heroicMagic);

	SharedPtr<IlluminatePacket> factorDmgPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DMG, factorDmgMinPkt, factorDmgMaxPkt);

	//{ Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorDefPointPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charDef.point.physical, &charDef.point.magic, &charDef.point.water, &charDef.point.fire,
		&charDef.point.earth, &charDef.point.air, &charDef.point.poison, &charDef.point.lightning, &charDef.point.ice, &charDef.point.physBlock, &charDef.point.skillBlock, &charDef.point.heroic,
		&charDef.point.heroicMelee, &charDef.point.heroicRange, &charDef.point.heroicMagic);

	SharedPtr<IlluminatePacket> factorDefRatePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTRIBUTE, &charDef.rate.physical, &charDef.rate.magic, &charDef.rate.water, &charDef.rate.fire,
		&charDef.rate.earth, &charDef.rate.air, &charDef.rate.poison, &charDef.rate.lightning, &charDef.rate.ice, &charDef.rate.physBlock, &charDef.rate.skillBlock, &charDef.rate.heroic,
		&charDef.rate.heroicMelee, &charDef.rate.heroicRange, &charDef.rate.heroicMagic);

	SharedPtr<IlluminatePacket> factorDefPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DEFENSE, factorDefPointPkt, factorDefRatePkt);

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	//Int32 i32AtkRng = 50, i32AtkSpd = 60;
	SharedPtr<IlluminatePacket> factorAttackPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ATTACK, &charAtk.range, &charAtk.hitRange, &charAtk.attackSpeed, &charAtk.cast, &charAtk.cooldown,
		&charAtk.accuracy, &charAtk.meleeDodge, &charAtk.rangeDodge);

	SharedPtr<IlluminatePacket> factorItemPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_ITEM, &charItem.durability, &charItem.hand, &charItem.rank, &charItem.physRank, &charItem.maxDura, &charItem.gacha);

	//{ Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32, Illuminate::INT32 }
	SharedPtr<IlluminatePacket> factorDirtPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_DIRT, &charDirt.duration, &charDirt.intensity, &charDirt.range, &charDirt.target, &charDirt.skillLevel, &charDirt.skillPoint, &charDirt.skillXP, &charDirt.heroicPoint);

	//Illuminate::AGPMCHAR_FACTOR_PRICE Skipped
	SharedPtr<IlluminatePacket> factorPricePkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTOR_PRICE, &charPrice.npcPrice, &charPrice.playerPrice, &charPrice.moneyHigh, &charPrice.moneyLow);

	//{	Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET, Illuminate::PACKET }
	SharedPtr<IlluminatePacket> factorResPkt = pktInterface->buildMiniPacket(Illuminate::AGPMCHAR_FACTORS, 0, factorStatusPkt, factorTypePkt, factorPointPkt, factorPointMaxPkt, factorRecoveryPkt, factorAttributePkt, factorDmgPkt, factorDefPkt, factorAttackPkt, factorItemPkt, factorDirtPkt, factorPricePkt);

	return factorResPkt;
}