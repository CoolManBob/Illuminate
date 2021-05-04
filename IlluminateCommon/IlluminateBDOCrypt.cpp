#include "IlluminateBDOCrypt.h"
#include <random>

static const UInt8 s_RabbitDefaultKey[] = {
		0x33, 0xFE, 0xB4, 0x95, 0x23, 0x8B, 0x90, 0xCB, 0x23, 0xB2, 0x9B, 0xBB, 0x32, 0x9A, 0xA7, 0x14
};
static const UInt8 s_RabbitDefaultIV[] = {
	0x54, 0x0E, 0xFB, 0x5B, 0xFF, 0xA6, 0x6A, 0x81
};

BDOCrypt::BDOCrypt() : rabbitCrypt()
{
	wc_RabbitSetKey(&rabbitCrypt, s_RabbitDefaultKey, s_RabbitDefaultIV);
	initRabbit();
}

BDOCrypt::~BDOCrypt()
{

}

void BDOCrypt::cryptoHandshake()
{
	UInt8* aesBlockKey = extractAesKey(rabbitKey, sizeof rabbitKey);
	////////////////////////////////////////////////////////////////////
	Aes* aes = new Aes{};
	UInt8 sesKey[64] = { 0 };
	UInt8 out[16] = { 0 };
	UInt8 iv[16] = { 0 };
	wc_AesSetKey(aes, aesBlockKey, AES_BLOCK_SIZE, iv, AES_DECRYPTION);

	unsigned targetKey[] = { 64, 17, 40, 87 };
	for (unsigned i = 0; i < 4; ++i)
	{
		wc_AesCbcDecrypt(aes, out, &rabbitKey[targetKey[i]], 16);
		memcpy(sesKey + (i * 16), out, 16);
	}
	delete aes;
	delete aesBlockKey;
	////////////////////////////////////////////////////////////////////
	UInt8 rabbitKey[16];
	UInt8 rabbitIv[8];

	memcpy(rabbitKey, sesKey, 16);
	memcpy(rabbitIv, rabbitKey + 2, 8);

	rabbitCrypt = Rabbit();
	wc_RabbitSetKey(&rabbitCrypt, rabbitKey, rabbitIv);
}

void BDOCrypt::cryptoProcess(UInt8* buffer, size_t size)
{
	if (size < 1)
		return;

	wc_RabbitProcess(&rabbitCrypt, buffer, buffer, word32(size));
}

void BDOCrypt::initRabbit()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 255);

	for (unsigned i = 0; i < 108; ++i)
		rabbitKey[i] = dis(gen);
	rabbitKey[0] = 0x00;
	rabbitKey[1] = 0x00;

	UInt8* aesBlockKey = extractAesKey(rabbitKey, sizeof rabbitKey);
	////////////////////////////////////////////////////////////////////
	Aes* aes = new Aes{};
	UInt8 out[16] = { 0 };
	UInt8 iv[16] = { 0 };

	wc_AesSetKey(aes, aesBlockKey, AES_BLOCK_SIZE, iv, AES_ENCRYPTION);

	unsigned targetKey[] = { 64, 17, 40, 87 };
	for (unsigned i = 0; i < 4; ++i)
	{
		wc_AesCbcEncrypt(aes, out, &rabbitKey[targetKey[i]], 16);
		memcpy(rabbitKey + (i * 16), out, 16);
	}
	delete aes;
	delete aesBlockKey;
	////////////////////////////////////////////////////////////////////
	rabbitKey[0] = 0x03;
	rabbitKey[1] = 0xEB;
}

UInt8* BDOCrypt::extractAesKey(UInt8* state, const size_t size)
{
	UInt8* key = new UInt8[16];

	int8_t writePosition = 0;
	int8_t remainingSize = 16;

	do
	{
		UInt8 keyA = extractAESKeySelectStateByteA(state, writePosition);
		UInt8 computeA = extractAESKeyComputeValue(writePosition, keyA);

		UInt8 keyB = extractAESKeySelectStateByteB(state, computeA);
		UInt8 computeB = extractAESKeyComputeValue(writePosition, keyB);

		key[writePosition++] = computeB;
		--remainingSize;

	} while (remainingSize);
	return key;
}

UInt8 BDOCrypt::extractAESKeySelectStateByteA(UInt8* state, UInt8 index)
{
	UInt8 result = state[15];

	switch (index)
	{
	case 0x01: result = state[3];   break;
	case 0x02: result = state[62];  break;
	case 0x03: result = state[5];   break;
	case 0x04: result = state[39];  break;
	case 0x05: result = state[37];  break;
	case 0x06: result = state[33];  break;
	case 0x07: result = state[59];  break;
	case 0x08: result = state[10];  break;
	case 0x09: result = state[7];   break;
	case 0x0A: result = state[104]; break;
	case 0x0B: result = state[82];  break;
	case 0x0C: result = state[38];  break;
	case 0x0D: result = state[13];  break;
	case 0x0E: result = state[84];  break;
	case 0x0F: result = state[12];  break;
	default: break;
	}

	return result;
}

UInt8 BDOCrypt::extractAESKeySelectStateByteB(UInt8* state, UInt8 index)
{
	UInt8 result = state[4];

	switch (index)
	{
	case 0x01: result = state[81];  break;
	case 0x02: result = state[9];   break;
	case 0x03: result = state[107]; break;
	case 0x04: result = state[36];  break;
	case 0x05: result = state[106]; break;
	case 0x06: result = state[14];  break;
	case 0x07: result = state[11];  break;
	case 0x08: result = state[34];  break;
	case 0x09: result = state[56];  break;
	case 0x0A: result = state[6];   break;
	case 0x0B: result = state[60];  break;
	case 0x0C: result = state[85];  break;
	case 0x0D: result = state[35];  break;
	case 0x0E: result = state[61];  break;
	case 0x0F: result = state[16];  break;
	case 0x10: result = state[8];   break;
	case 0x11: result = state[63];  break;
	case 0x12: result = state[57];  break;
	case 0x13: result = state[2];   break;
	case 0x14: result = state[80];  break;
	case 0x15: result = state[105]; break;
	case 0x16: result = state[58];  break;
	case 0x17: result = state[86];  break;
	case 0x18: result = state[103]; break;
	case 0x19: result = state[83];  break;
	default: break;
	}

	return result;
}

UInt8 BDOCrypt::extractAESKeyComputeValue(UInt8 keyPosition, UInt8 stateValue)
{
	char subIdxLP;
	char subIdxRP;

	if (keyPosition % 3)
	{
		if (keyPosition % 3 == 1)
		{
			UInt8 valueRot = keyPosition % 8;

			if (valueRot < 1u)
				valueRot = 1;

			subIdxLP = stateValue << valueRot;
			subIdxRP = stateValue >> (8 - valueRot);
		}
		else
		{
			subIdxLP = stateValue >> 4;
			subIdxRP = 16 * stateValue;
		}
	}
	else
	{
		UInt8 valueRot = keyPosition % 8;

		if (valueRot < 1u)
			valueRot = 1;

		subIdxLP = stateValue >> valueRot;
		subIdxRP = stateValue << (8 - valueRot);
	}

	return subIdxLP | subIdxRP;
}