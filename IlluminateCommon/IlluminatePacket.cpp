#include "IlluminatePacket.h"

IlluminatePacket::IlluminatePacket()
{
	buf = nullptr; //Default settings
	size = 0;
	pos = 0;
	dynamic = true;
	numFields = 0;
	flagLength = 0;
	packetType = 0;
	dwMask = 1;
	ulFlag = 0;
}

IlluminatePacket::IlluminatePacket(int initialSize)
{
	buf = new unsigned char[initialSize];
	size = initialSize;
	pos = 0;
	dynamic = false;
	numFields = 0;
	flagLength = 0;
	packetType = 0;
	dwMask = 1;
	ulFlag = 0;
}

IlluminatePacket::IlluminatePacket(unsigned char *buffer, int bufSize) //Incoming Packets
{
	buf = new unsigned char[bufSize];
	memcpy(buf, buffer, bufSize);
	size = bufSize;
	pos = 0;
	dynamic = false;
	numFields = 0;
	flagLength = 0;
	packetType = 0;
	dwMask = 1;
	ulFlag = 0;
}

IlluminatePacket::IlluminatePacket(UInt16 PacketType, UInt8 FlagLen) //Outgoing Packets
{
	if (FlagLen != 1 && FlagLen != 2 && FlagLen != 4)
		throw "ERROR";
	buf = new unsigned char[13+FlagLen]; //Allocate initial space for header
	size = 13+FlagLen;
	pos = 0;
	dynamic = true;
	numFields = 0;
	flagLength = FlagLen;
	packetType = PacketType;
	dwMask = 1;
	ulFlag = 0;
	guardByte = 0xD6;
	sessionID = 0;
	timestamp = 0;
	packetSize = 0;
	packetFlags = new UInt8[FlagLen];
	headerWritten = false;
	isMini = false;

	WriteHeader();
}

IlluminatePacket::IlluminatePacket(UInt8 FlagLen) //Mini(Internal) Packets
{
	if (FlagLen != 1 && FlagLen != 2 && FlagLen != 4)
		throw "ERROR";
	buf = new unsigned char[2 + FlagLen]; //Allocate initial space for header (UInt16(Size) + FlagLen)
	size = 2 + FlagLen;
	pos = 0;
	dynamic = true;
	numFields = 0;
	flagLength = FlagLen;
	packetType = 0;
	dwMask = 1;
	ulFlag = 0;
	guardByte = 0xD6;
	sessionID = 0;
	timestamp = 0;
	packetSize = 0;
	packetFlags = new UInt8[FlagLen];
	headerWritten = false;
	isMini = true;

	WriteMiniHeader();
}

IlluminatePacket::~IlluminatePacket()
{		
	if (packetFlags)
		delete[] packetFlags;
	if(buf)
		delete[] buf;

	fields.clear();
}

void IlluminatePacket::WriteHeader()
{
	WriteUInt8(0xD6); //GuardByte
	WriteUInt16(size);
	WriteUInt16(packetType);
	WriteUInt32(sessionID);
	WriteUInt32(timestamp);

	/*Flag Setup*/
	for (int i = 0; i < flagLength; i++)
		WriteUInt8(0); //Temporary zero, will be overwritten when we close the packet.

	headerWritten = true; //Flag UpdatePacket to start building flag information
}

void IlluminatePacket::WriteMiniHeader()
{
	WriteUInt16(size);

	//Setup flag space for header, then flag the system to allow it to update flags
	for (int i = 0; i < flagLength; i++)
		WriteUInt8(0); //Temporary zero, will be overwritten when we close the packet.

	headerWritten = true;
}

bool IlluminatePacket::setFieldInfo(int types[], int typeSize, int sizes[], int sizeSz)
{
	if (typeSize != sizeSz)
		return false; //Type and Size Elements are not matched!

	for (int i = 0; i < typeSize; i++)
	{
		Illuminate::IlluminatePktField field;
		field.FieldType = types[i];
		field.FieldSize = sizes[i];
		fields.push_back(field);
	}

	return true;
}

bool IlluminatePacket::setFieldInfo(vector<Illuminate::IlluminatePktField> fieldVec)
{
	return false;
}

void IlluminatePacket::UpdatePacket(UInt16 newSize, bool doFlagUpd)
{
	if(dynamic && !isMini)
		*(UInt16*)&buf[0x01] = newSize;
	else if(dynamic && isMini)
		*(UInt16*)&buf[0] = newSize - 2; //UInt16 packetSize is not counted for miniPackets

	if (headerWritten && doFlagUpd)
		ulFlag |= dwMask;
}

void IlluminatePacket::ClosePacket()
{
	//Write packetflags
	if(flagLength == 1)
		*(UInt8*)&buf[0x0D] = ulFlag;
	else if(flagLength == 2)
		*(UInt16*)&buf[0x0D] = ulFlag;
	else if(flagLength == 4)
		*(UInt32*)&buf[0x0D] = ulFlag;
	//Write footer
	WriteUInt8(0x6B);
}

void IlluminatePacket::CloseMiniPacket()
{
	//Write packetflags
	if (flagLength == 1)
		*(UInt8*)&buf[2] = ulFlag;
	else if (flagLength == 2)
		*(UInt16*)&buf[2] = ulFlag;
	else if (flagLength == 4)
		*(UInt32*)&buf[2] = ulFlag;
}

void IlluminatePacket::acquirePacketHeader()
{
	GetUInt8(guardByte);
	GetUInt16(packetSize);
	GetUInt16(packetType);
	GetUInt32(sessionID);
	GetUInt32(timestamp);
}

bool IlluminatePacket::setAndAcquireFlags(UInt8 flagLen)
{
	if (flagLen != 1 && flagLen != 2 && flagLen != 4)
		return false;

	flagLength = flagLen;
	
	packetFlags = new UInt8[flagLen];

	for (int i = 0; i < flagLen; i++)
		GetUInt8(packetFlags[i]);

	return true;
}

bool IlluminatePacket::ResetFromPkt(IlluminatePacket* pkt)
{
	if (buf)
		delete[] buf;

	if (pkt->buf)
	{
		//buf = pkt->buf;
		buf = new unsigned char[pkt->size];
		memcpy(buf, pkt->buf, pkt->size);
		size = pkt->size;
		pos = pkt->pos;
		dynamic = pkt->dynamic;
		numFields = pkt->numFields;
		flagLength = pkt->flagLength;
		packetType = pkt->packetType;
		dwMask = pkt->dwMask;
		ulFlag = pkt->ulFlag;
		return true;
	}
	else
		return false;
}

void IlluminatePacket::Resize(int newSize)
{
	if (size == newSize)
		return;
	else if (size == 0 && buf == nullptr)
	{
		unsigned char* tmp = new unsigned char[newSize];
		memset(tmp, 0, newSize);
		buf = tmp;
		size = newSize;
	}
	else
	{
		unsigned char * tmp = new unsigned char[newSize];
		//memset(tmp, 0, newSize);
		memmove(tmp, buf, newSize);
		delete[] buf;
		buf = tmp;
		size = newSize;
	}
}

void IlluminatePacket::WriteInt8(Int8 data)
{
	EnsureBufSize(pos + sizeof(Int8));
	*(Int8*)&buf[pos] = data;
	pos += sizeof(Int8);
	UpdatePacket(size);
}

void IlluminatePacket::WriteInt16(Int16 data)
{
	EnsureBufSize(pos + sizeof(Int16));
	*(Int16*)&buf[pos] = data;
	pos += sizeof(Int16);
	UpdatePacket(size);
}

void IlluminatePacket::WriteInt32(Int32 data)
{
	EnsureBufSize(pos + sizeof(Int32));
	*(Int32*)&buf[pos] = data;
	pos += sizeof(Int32);
	UpdatePacket(size);
}

void IlluminatePacket::WriteInt64(Int64 data)
{
	EnsureBufSize(pos + sizeof(Int64));
	*(Int64*)&buf[pos] = data;
	pos += sizeof(Int64);
	UpdatePacket(size);
}

void IlluminatePacket::WriteUInt8(UInt8 data)
{
	EnsureBufSize(pos + sizeof(UInt8));
	*(UInt8*)&buf[pos] = data;
	pos += sizeof(UInt8);
	UpdatePacket(size);
}

void IlluminatePacket::WriteUInt16(UInt16 data, bool flagUpd)
{
	EnsureBufSize(pos + sizeof(UInt16));
	*(UInt16*)&buf[pos] = data;
	pos += sizeof(UInt16);
	UpdatePacket(size, flagUpd);
}

void IlluminatePacket::WriteUInt32(UInt32 data)
{
	EnsureBufSize(pos + sizeof(UInt32));
	*(UInt32*)&buf[pos] = data;
	pos += sizeof(UInt32);
	UpdatePacket(size);
}

void IlluminatePacket::WriteUInt64(UInt64 data)
{
	EnsureBufSize(pos + sizeof(UInt64));
	*(UInt64*)&buf[pos] = data;
	pos += sizeof(UInt64);
	UpdatePacket(size);
}

void IlluminatePacket::WriteFloat(float data)
{
	EnsureBufSize(pos + sizeof(float));
	*(float*)&buf[pos] = data;
	pos += sizeof(float);
	UpdatePacket(size);
}

void IlluminatePacket::WriteDouble(double data)
{
	EnsureBufSize(pos + sizeof(double));
	*(double*)&buf[pos] = data;
	pos += sizeof(double);
	UpdatePacket(size);
}

void IlluminatePacket::WriteMemoryBlock(UInt16 blocksize, const UInt8* data, bool zero)
{
	EnsureBufSize(pos + sizeof(UInt16));
	*(UInt16*)&buf[pos] = blocksize;
	pos += sizeof(UInt16);

	if (zero)
	{
		for (int i = 0; i < blocksize; i++)
		{
			EnsureBufSize(pos + sizeof(UInt8));
			*(UInt8*)&buf[pos] = 0;
			pos += sizeof(UInt8);
		}
	}
	else
	{
		int datalen = (int)(strlen((char*)data));
		EnsureBufSize(pos + datalen);
		memcpy(&buf[pos], data, datalen);
		pos += datalen;
	}

	UpdatePacket(size);
}

void IlluminatePacket::WriteVec3F(Illuminate::IlluminateVec3F vec3F)
{
	WriteFloat(vec3F.x);
	WriteFloat(vec3F.y);
	WriteFloat(vec3F.z);
}

void IlluminatePacket::WriteArbitraryData(const void *data, int len)
{
	EnsureBufSize(pos + len);
	memset(&buf[pos], 0, len);
	memcpy(&buf[pos], data, (int)(strlen((const char*)data)));
	pos += len;
	UpdatePacket(size);
}

void IlluminatePacket::WritePacket(IlluminatePacket* packet)
{
	int pktSize = packet->getSize();
	unsigned char* pktData = packet->getBuffer();
	EnsureBufSize(pos + pktSize);
	memset(&buf[pos], 0, pktSize);
	memcpy(&buf[pos], pktData, pktSize);
	pos += pktSize;
	UpdatePacket(size);
}

void IlluminatePacket::WritePacket(SharedPtr<IlluminatePacket> packet)
{
	int pktSize = packet->getSize();
	unsigned char* pktData = packet->getBuffer();
	EnsureBufSize(pos + pktSize);
	memset(&buf[pos], 0, pktSize);
	memcpy(&buf[pos], pktData, pktSize);
	pos += pktSize;
	UpdatePacket(size);
}

void IlluminatePacket::WriteByteArray(const char* array)
{
	WriteArbitraryData(array, (int)(strlen(array)));
}

void IlluminatePacket::WriteByteArray(const UInt8* array)
{
	WriteArbitraryData(array, (int)(strlen((char*)array)));
}

void IlluminatePacket::GetInt8(Int8& data)
{
	ValidateReadTo(pos + sizeof(Int8));
	data = *(Int8*)&buf[pos];
	pos += sizeof(Int8);
}

void IlluminatePacket::GetInt16(Int16& data)
{
	ValidateReadTo(pos + sizeof(Int16));
	data = *(Int16*)&buf[pos];
	pos += sizeof(Int16);
}

void IlluminatePacket::GetInt32(Int32& data)
{
	ValidateReadTo(pos + sizeof(Int32));
	data = *(Int32*)&buf[pos];
	pos += sizeof(Int32);
}

void IlluminatePacket::GetInt64(Int64& data)
{
	ValidateReadTo(pos + sizeof(Int64));
	data = *(Int64*)&buf[pos];
	pos += sizeof(Int64);
}

void IlluminatePacket::GetUInt8(UInt8& data)
{
	ValidateReadTo(pos + sizeof(UInt8));
	data = *(UInt8*)&buf[pos];
	pos += sizeof(UInt8);
}

void IlluminatePacket::GetUInt16(UInt16& data)
{
	ValidateReadTo(pos + sizeof(UInt16));
	data = *(UInt16*)&buf[pos];
	pos += sizeof(UInt16);
}

void IlluminatePacket::GetUInt32(UInt32& data)
{
	ValidateReadTo(pos + sizeof(UInt32));
	data = *(UInt32*)&buf[pos];
	pos += sizeof(UInt32);
}

void IlluminatePacket::GetUInt64(UInt64& data)
{
	ValidateReadTo(pos + sizeof(UInt64));
	data = *(UInt64*)&buf[pos];
	pos += sizeof(UInt64);
}

void IlluminatePacket::GetFloat(float& data)
{
	ValidateReadTo(pos + sizeof(float));
	data = *(float*)&buf[pos];
	pos += sizeof(float);
}

void IlluminatePacket::GetDouble(double& data)
{
	ValidateReadTo(pos + sizeof(double));
	data = *(double*)&buf[pos];
	pos += sizeof(double);
}

Int8 IlluminatePacket::GetInt8()
{
	Int8 temp = 0;
	ValidateReadTo(pos + sizeof(Int8));
	temp = *(Int8*)&buf[pos];
	pos += sizeof(Int8);
	return temp;
}

Int16 IlluminatePacket::GetInt16()
{
	Int16 temp = 0;
	ValidateReadTo(pos + sizeof(Int16));
	temp = *(Int16*)&buf[pos];
	pos += sizeof(Int16);
	return temp;
}

Int32 IlluminatePacket::GetInt32()
{
	Int32 temp = 0;
	ValidateReadTo(pos + sizeof(Int32));
	temp = *(Int32*)&buf[pos];
	pos += sizeof(Int32);
	return temp;
}

Int64 IlluminatePacket::GetInt64()
{
	Int64 temp = 0;
	ValidateReadTo(pos + sizeof(Int64));
	temp = *(Int64*)&buf[pos];
	pos += sizeof(Int64);
	return temp;
}

UInt8 IlluminatePacket::GetUInt8()
{
	UInt8 temp = 0;
	ValidateReadTo(pos + sizeof(UInt8));
	temp = *(UInt8*)&buf[pos];
	pos += sizeof(UInt8);
	return temp;
}

UInt16 IlluminatePacket::GetUInt16()
{
	UInt16 temp = 0;
	ValidateReadTo(pos + sizeof(UInt16));
	temp = *(UInt16*)&buf[pos];
	pos += sizeof(UInt16);
	return temp;
}

UInt32 IlluminatePacket::GetUInt32()
{
	UInt32 temp = 0;
	ValidateReadTo(pos + sizeof(UInt32));
	temp = *(UInt32*)&buf[pos];
	pos += sizeof(UInt32);
	return temp;
}

UInt64 IlluminatePacket::GetUInt64()
{
	UInt64 temp = 0;
	ValidateReadTo(pos + sizeof(UInt64));
	temp = *(UInt64*)&buf[pos];
	pos += sizeof(UInt64);
	return temp;
}

float IlluminatePacket::GetFloat()
{
	float temp = 0;
	ValidateReadTo(pos + sizeof(float));
	temp = *(float*)&buf[pos];
	pos += sizeof(float);
	return temp;
}

double IlluminatePacket::GetDouble()
{
	double temp = 0;
	ValidateReadTo(pos + sizeof(double));
	temp = *(double*)&buf[pos];
	pos += sizeof(double);
	return temp;
}

void IlluminatePacket::GetInt8(int position, Int8 &data)
{
	ValidateReadTo(position + sizeof(Int8));
	data = *(Int8*)&buf[position];
}

void IlluminatePacket::GetInt16(int position, Int16 &data)
{
	ValidateReadTo(position + sizeof(Int16));
	data = *(Int16*)&buf[position];
}

void IlluminatePacket::GetInt32(int position, Int32 &data)
{
	ValidateReadTo(position + sizeof(Int32));
	data = *(Int32*)&buf[position];
}

void IlluminatePacket::GetInt64(int position, Int64 &data)
{
	ValidateReadTo(position + sizeof(Int64));
	data = *(Int64*)&buf[position];
}

void IlluminatePacket::GetUInt8(int position, UInt8 &data)
{
	ValidateReadTo(position + sizeof(UInt8));
	data = *(UInt8*)&buf[position];
}

void IlluminatePacket::GetUInt16(int position, UInt16 &data)
{
	ValidateReadTo(position + sizeof(UInt16));
	data = *(UInt16*)&buf[position];
}

void IlluminatePacket::GetUInt32(int position, UInt32 &data)
{
	ValidateReadTo(position + sizeof(UInt32));
	data = *(UInt32*)&buf[position];
}

void IlluminatePacket::GetUInt64(int position, UInt64 &data)
{
	ValidateReadTo(position + sizeof(UInt64));
	data = *(UInt64*)&buf[position];
}

void IlluminatePacket::GetFloat(int position, float& data)
{
	ValidateReadTo(position + sizeof(float));
	data = *(float*)&buf[position];
}

void IlluminatePacket::GetDouble(int position, double& data)
{
	ValidateReadTo(position + sizeof(double));
	data = *(double*)&buf[position];
}

void IlluminatePacket::GetDataBlock(UInt16 blockSize, char* data)
{
	ValidateReadTo(pos + blockSize);
	memcpy(data, &buf[pos], blockSize);
	pos += blockSize;
}

void IlluminatePacket::GetDataBlock(UInt16 blockSize, unsigned char* data)
{
	ValidateReadTo(pos + blockSize);
	memcpy(data, &buf[pos], blockSize);
	pos += blockSize;
}

void IlluminatePacket::GetVec3F(Illuminate::IlluminateVec3F& vec3F)
{
	GetFloat(vec3F.x);
	GetFloat(vec3F.y);
	GetFloat(vec3F.z);
}

Illuminate::IlluminateVec3F IlluminatePacket::GetVec3F()
{
	Illuminate::IlluminateVec3F vec3F;
	GetFloat(vec3F.x);
	GetFloat(vec3F.y);
	GetFloat(vec3F.z);
	return vec3F;
}

template <typename data>
void IlluminatePacket::WriteGeneric(const data val)
{
	EnsureBufSize(pos + sizeof(data));
	*(data*)&buf[pos] = val;
	pos += sizeof(data);
	UpdatePacket(size);
}

template <typename data>
void IlluminatePacket::GetGeneric(data& val)
{
	ValidateReadTo(pos + sizeof(data));
	data = *(data*)&buf[pos];
	pos += sizeof(data);
}

template <typename data>
void IlluminatePacket::GetGeneric(data& val, int size)
{
	ValidateReadTo(pos + size);
	data = *(data*)&buf[pos];
	pos += size;
}

template <typename data>
void IlluminatePacket::GetGeneric(int position, data &val, int size)
{
	ValidateReadTo(position + sizeof(data));
	val = *(data*)&buf[position];
}