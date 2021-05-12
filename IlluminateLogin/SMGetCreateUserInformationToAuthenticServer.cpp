#include "SMGetCreateUserInformationToAuthenticServer.h"

bool SMGetCreateUserInformationToAuthenticServer::processPacket(const localInfo& local)
{
	localInfo& localObj = const_cast<localInfo&>(local);
	IlluminatePacket* outBound = localObj.packet;

	Int8 i8unk1 = 8, i8unk2 = 0, i8unk3 = 0, i8unk4 = 64, isEmpty = 0;
	Int64 getPin = 000000;
	std::string getAccount, getObjectId, strunk1 = "62"; //this.client.getAccount().getObjectId()), 62

	*outBound << strunk1 << getObjectId << getAccount;
	*outBound << i8unk1;
	*outBound << i8unk2;
	*outBound << i8unk3;
	*outBound << i8unk4;
	*outBound << isEmpty << getAccount << getPin;
	//generate pin table // generatePinTable(paramSendByteBuffer); // how do we implement this?


	return true;
}

/*bool SMGetCreateUserInformationToAuthenticServer::extraProcessPacket(localInfo& local, int& data)
{
	Int8 i8unk1, i8unk2 = 0, i8unk3 = 0;
	Int32 i = 20;
	Int32 pinArray[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	Int64 longVal;
	
	*outBound << i << i8unk1;
	*outBound << i8unk2;
	*outBound << i8unk3;

	/*for (byte b = 0; b < 20; b++) {
	List<Integer> list = IntStream.of(arrayOfInt).boxed().collect((Collector)Collectors.toList());
	StringBuilder stringBuilder = new StringBuilder();
	while (!list.isEmpty()) {
		int j = Rnd.get(list.size());
		Integer integer = list.remove(j);
		stringBuilder.append(integer);
	}
	if (i == b)
	this.client.setPinTable(stringBuilder.toString()); 
      Long long_ = Long.valueOf(Long.parseLong(stringBuilder.toString()));

	
	*outBound << longVal;

	return true;
}*/