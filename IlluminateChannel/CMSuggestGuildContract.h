#include <string>
using std::string;

#include "IlluminateTypes.h"
#include "IlluminatePacketProcessor.h"

class CMSuggestGuildContract : public IlluminatePacketProcessor
{
public:
	CMSuggestGuildContract() {};
	virtual ~CMSuggestGuildContract() {};

	virtual bool processPacket(const localInfo& local);

	bool extraPacketProcessing(localInfo& local, int& data);
};
