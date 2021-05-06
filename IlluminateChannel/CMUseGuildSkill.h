#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMUseGuildSkill : public IlluminatePacketProcessor
{
public:
	CMUseGuildSkill() {};
	virtual ~CMUseGuildSkill() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};

