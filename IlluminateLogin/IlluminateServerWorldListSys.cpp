#include "IlluminateServerWorldListSys.h"

IlluminateServerWorldListSys::IlluminateServerWorldListSys()
{
	//dbWorldList = new IlluminateDBWorldListSys();
}

IlluminateServerWorldListSys::~IlluminateServerWorldListSys()
{
	/*delete dbWorldList;
	worldList.clear();*/
}

bool IlluminateServerWorldListSys::initWorldList()
{
	/*LOG("Loading WorldList...", WARNING);

	if (!getGroupInfo())
		return false;
	if (!getWorldInfo())
		return false;

	LOG("WorldList Loaded!", WARNING);

	return true;*/
	return false;
}

bool IlluminateServerWorldListSys::updateWorldList()
{
	/*worldList.clear();
	if (!getGroupInfo())
		return false;
	if (!getWorldInfo())
		return false;

	return true;*/
	//Is this the best way to do this?
	return false;
}

string IlluminateServerWorldListSys::buildWorldInfoStr()
{
	/*stringstream worldListStr;
	if (worldList.size() == 0)
	{
		LOG("buildWorldInfoPkt : getWorldList() FAIL", FATAL);
		return "ERROR";
	}
	
	//WorldString ServerName-GroupName-Priority-Status-IsNew-NoEffect-NoEffect-NoEffect-NoEffect-
	//Dummy=ALEmu=0=4=1=0=0=0=0;
	//Note: ServerNames can never be the same for two seperate groups.
	for (worldListGroupVec::iterator groupItr = worldList.begin(); groupItr != worldList.end(); groupItr++)
	{
		for (worldListWorldVec::iterator worldItr = (*groupItr)->worldVec.begin(); worldItr != (*groupItr)->worldVec.end(); worldItr++)
		{
			worldListStr << (*worldItr)->worldName << "=";
			worldListStr << (*groupItr)->groupName << "=";
			worldListStr << "0=" << (*worldItr)->worldStatus << "=" << (*worldItr)->worldFlag << "=";
			worldListStr << "0=0=0=0;";
		}
	}

	return worldListStr.str();*/
	return "";
}

string IlluminateServerWorldListSys::getWorldAddress(string worldName)
{
	/*for (worldListGroupVec::iterator groupItr = worldList.begin(); groupItr != worldList.end(); groupItr++)
	{
		for (worldListWorldVec::iterator worldItr = (*groupItr)->worldVec.begin(); worldItr != (*groupItr)->worldVec.end(); worldItr++)
		{
			if ((*worldItr)->worldName == worldName)
				return (*worldItr)->worldAddress;
		}
	}

	return "ERROR";*/
	return "";
}

bool IlluminateServerWorldListSys::getGroupInfo()
{
	/*SharedPtr<RecordSet> rs = dbWorldList->dbGetGroupInfo();

	if (!rs)
		return false;

	if (rs->getTotalRowCount() == 0)
	{
		LOG("dbGetGroupInfo() row count : 0", FATAL);
		return false;
	}

	for (RecordSet::Iterator itr = rs->begin(); itr != rs->end(); itr++)
	{
		SharedPtr<WorldListGroup> group = new WorldListGroup;
		group->groupID = itr->get(COLIDX(GROUPCOL::ID));
		group->groupName = itr->get(COLIDX(GROUPCOL::NAME)).toString();
		worldList.push_back(group);
	}

	return true;*/
	return false;
}

bool IlluminateServerWorldListSys::getWorldInfo()
{
	/*for (worldListGroupVec::iterator groupItr = worldList.begin(); groupItr != worldList.end(); groupItr++)
	{
		SharedPtr<RecordSet> rs = dbWorldList->dbGetWorldInfo((*groupItr)->groupID);

		if (!rs)
			return false;

		if (rs->getTotalRowCount() == 0)
		{
			LOG("dbGetWorldInfo() row count : 0", FATAL);
			return false;
		}

		for (RecordSet::Iterator rowItr = rs->begin(); rowItr != rs->end(); rowItr++)
		{
			SharedPtr<WorldListWorld> world = new WorldListWorld;
			world->worldID = rowItr->get(COLIDX(WORLDCOL::ID));
			world->worldName = rowItr->get(COLIDX(WORLDCOL::NAME)).toString();
			world->worldAddress = rowItr->get(COLIDX(WORLDCOL::ADDRESS)).toString();
			world->worldStatus = rowItr->get(COLIDX(WORLDCOL::STATUS));
			world->worldFlag = rowItr->get(COLIDX(WORLDCOL::FLAG));
			(*groupItr)->worldVec.push_back(world);
		}
	}

	return true;*/
	return false;
}