#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMMailRemove : public IlluminatePacketProcessor
{
public:
	CMMailRemove() {};
	virtual ~CMMailRemove() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
