#include "IlluminatePacket.h"

IlluminatePacket::IlluminatePacket()
{
	buf = nullptr; //Default settings
	size = 0;
	pos = 0;
}

IlluminatePacket::IlluminatePacket(int initialSize)
{
	buf = new unsigned char[initialSize];
	size = initialSize;
	pos = 0;
}

IlluminatePacket::IlluminatePacket(unsigned char *buffer, int bufSize) //Incoming Packets
{
	buf = new unsigned char[bufSize];
	memcpy(buf, buffer, bufSize);
	size = bufSize;
	pos = 0;
}

IlluminatePacket::IlluminatePacket(UInt16 OpCode) //Outgoing Packets
{
	buf = nullptr; //Default settings
	size = 0;
	pos = 0;
	isEncrypted = true;
}

IlluminatePacket::~IlluminatePacket()
{		
	if (buf)
		delete[] buf;
}

void IlluminatePacket::WriteHeader()
{
	WriteUInt16(size);
	WriteBool(isEncrypted);
}

void IlluminatePacket::acquirePacketHeader()
{
	GetUInt16(packetSize);
	GetBool(isEncrypted);
}

void IlluminatePacket::acquireOpCode()
{
	GetUInt16(opCode);
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
		packetSize = pkt->packetSize;
		isEncrypted = pkt->isEncrypted;
		opCode = pkt->opCode;
		return true;
	}
	else
		return false;
}

void IlluminatePacket::Resize(int newSize)
{
	if (size == newSize)
		return;
	else if (size == 0 && buf == nullptr) //empty buffer
	{
		unsigned char* tmp = new unsigned char[newSize];
		memset(tmp, 0, newSize);
		buf = tmp;
		size = newSize;
	}
	else
	{
		unsigned char * tmp = new unsigned char[newSize];
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
}

void IlluminatePacket::WriteInt16(Int16 data)
{
	EnsureBufSize(pos + sizeof(Int16));
	*(Int16*)&buf[pos] = data;
	pos += sizeof(Int16);
}

void IlluminatePacket::WriteInt32(Int32 data)
{
	EnsureBufSize(pos + sizeof(Int32));
	*(Int32*)&buf[pos] = data;
	pos += sizeof(Int32);
}

void IlluminatePacket::WriteInt64(Int64 data)
{
	EnsureBufSize(pos + sizeof(Int64));
	*(Int64*)&buf[pos] = data;
	pos += sizeof(Int64);
}

void IlluminatePacket::WriteUInt8(UInt8 data)
{
	EnsureBufSize(pos + sizeof(UInt8));
	*(UInt8*)&buf[pos] = data;
	pos += sizeof(UInt8);
}

void IlluminatePacket::WriteUInt16(UInt16 data)
{
	EnsureBufSize(pos + sizeof(UInt16));
	*(UInt16*)&buf[pos] = data;
	pos += sizeof(UInt16);
}

void IlluminatePacket::WriteUInt32(UInt32 data)
{
	EnsureBufSize(pos + sizeof(UInt32));
	*(UInt32*)&buf[pos] = data;
	pos += sizeof(UInt32);
}

void IlluminatePacket::WriteUInt64(UInt64 data)
{
	EnsureBufSize(pos + sizeof(UInt64));
	*(UInt64*)&buf[pos] = data;
	pos += sizeof(UInt64);
}

void IlluminatePacket::WriteFloat(float data)
{
	EnsureBufSize(pos + sizeof(float));
	*(float*)&buf[pos] = data;
	pos += sizeof(float);
}

void IlluminatePacket::WriteDouble(double data)
{
	EnsureBufSize(pos + sizeof(double));
	*(double*)&buf[pos] = data;
	pos += sizeof(double);
}

void IlluminatePacket::WriteBool(bool data)
{
	EnsureBufSize(pos + sizeof(bool));
	*(bool*)&buf[pos] = data;
	pos += sizeof(bool);
}

void IlluminatePacket::WriteArbitraryData(const void *data, int len)
{
	EnsureBufSize(pos + len);
	memset(&buf[pos], 0, len);
	memcpy(&buf[pos], data, len);
	pos += len;
}

void IlluminatePacket::WriteByteArray(const char* array)
{
	WriteArbitraryData(array, (int)(strlen(array)));
}

void IlluminatePacket::WriteByteArray(const UInt8* array)
{
	WriteArbitraryData(array, (int)(strlen((char*)array)));
}

void IlluminatePacket::WriteString(const string str)
{
	WriteArbitraryData(str.c_str(), str.size());
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

void IlluminatePacket::GetBool(bool& data)
{
	ValidateReadTo(pos + sizeof(bool));
	data = *(bool*)&buf[pos];
	pos += sizeof(bool);
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

bool IlluminatePacket::GetBool()
{
	bool temp = 0;
	ValidateReadTo(pos + sizeof(bool));
	temp = *(bool*)&buf[pos];
	pos += sizeof(bool);
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

void IlluminatePacket::GetBool(int position, bool& data)
{
	ValidateReadTo(position + sizeof(bool));
	data = *(bool*)&buf[position];
}

void IlluminatePacket::GetString(std::string& str)
{
	str.clear();
	while (pos < size)
	{
		char c = GetInt8();
		if (c == 0)
			break;
		str += c;
	}
}

void IlluminatePacket::GetString(std::string& str, int len)
{
	str.clear();
	for (int i = 0; i < len; i++)
	{
		char c = GetInt8();
		if (c == 0)
			break;
		str += c;
	}
}

template <typename data>
void IlluminatePacket::WriteGeneric(const data& val)
{
	EnsureBufSize(pos + sizeof(data));
	*(data*)&buf[pos] = val;
	pos += sizeof(data);
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

void IlluminatePacket::Skip(int val)
{
	ValidateReadTo(pos + val);
	pos += val;
}

IlluminatePacket& IlluminatePacket::operator<<(Int8 data)
{
	WriteInt8(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(Int16 data)
{
	WriteInt16(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(Int32 data)
{
	WriteInt32(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(Int64 data)
{
	WriteInt64(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(UInt8 data)
{
	WriteUInt8(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(UInt16 data)
{
	WriteUInt16(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(UInt32 data)
{
	WriteUInt32(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(UInt64 data)
{
	WriteUInt64(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(float data)
{
	WriteFloat(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(double data)
{
	WriteDouble(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(bool data)
{
	WriteBool(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator<<(const string data)
{
	WriteString(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(Int8& data)
{
	GetInt8(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(Int16& data)
{
	GetInt16(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(Int32& data)
{
	GetInt32(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(Int64& data)
{
	GetInt64(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(UInt8& data)
{
	GetUInt8(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(UInt16& data)
{
	GetUInt16(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(UInt32& data)
{
	GetUInt32(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(UInt64& data)
{
	GetUInt64(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(double& data)
{
	GetDouble(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(float& data)
{
	GetFloat(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(bool& data)
{
	GetBool(data);
	return *this;
}

IlluminatePacket& IlluminatePacket::operator>>(std::string& str)
{
	GetString(str);
	return *this;
}