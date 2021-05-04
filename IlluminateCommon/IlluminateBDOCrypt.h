#pragma once

#include "IlluminateTypes.h"
#include "wolfssl/wolfcrypt/aes.h"
#include "wolfssl/wolfcrypt/rabbit.h"

class BDOCrypt
{
public:
		BDOCrypt();
		~BDOCrypt();

		void cryptoHandshake();
		void cryptoProcess(UInt8* buffer, size_t size);
		const UInt8* getRabbitKey() { return rabbitKey; }

private:

	void initRabbit();
	static UInt8* extractAesKey(UInt8* state, const size_t size);
	static UInt8 extractAESKeySelectStateByteA(UInt8* state, UInt8 index);
	static UInt8 extractAESKeySelectStateByteB(UInt8* state, UInt8 index);
	static UInt8 extractAESKeyComputeValue(UInt8 keyPosition, UInt8 stateValue);

	UInt8 rabbitKey[108];
	Rabbit rabbitCrypt;
};