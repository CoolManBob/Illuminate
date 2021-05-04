#pragma once
//#pragma pack(push,1)

#include <Poco/SharedPtr.h>

using Poco::SharedPtr;

#include <vector>
#include <string>

using std::vector;
using std::string;

#include "IlluminateTypes.h"

class IlluminatePacket
{
public:
	IlluminatePacket();
	IlluminatePacket(int initialSize);
	IlluminatePacket(unsigned char* buffer, int bufSize);
	IlluminatePacket(UInt16 OpCode);
	
	~IlluminatePacket();

	void Resize(int newSize);
	bool ResetFromPkt(IlluminatePacket* packet);

	void WriteHeader();

	void WriteInt8(Int8 data);
	void WriteInt16(Int16 data);
	void WriteInt32(Int32 data);
	void WriteInt64(Int64 data);

	void WriteUInt8(UInt8 data);
	void WriteUInt16(UInt16 data);
	void WriteUInt32(UInt32 data);
	void WriteUInt64(UInt64 data);

	void WriteFloat(float data);
	void WriteDouble(double data);
	void WriteBool(bool data);

	void WriteByteArray(const char* array);
	void WriteByteArray(const UInt8* array);

	void WriteString(const string str);

	void WriteArbitraryData(const void *data, int len);

	template<typename data>
	void WriteGeneric(const data& val);

	IlluminatePacket& operator<<(Int8 data);
	IlluminatePacket& operator<<(Int16 data);
	IlluminatePacket& operator<<(Int32 data);
	IlluminatePacket& operator<<(Int64 data);

	IlluminatePacket& operator<<(UInt8 data);
	IlluminatePacket& operator<<(UInt16 data);
	IlluminatePacket& operator<<(UInt32 data);
	IlluminatePacket& operator<<(UInt64 data);

	IlluminatePacket& operator<<(float data);
	IlluminatePacket& operator<<(double data);
	IlluminatePacket& operator<<(bool data);
	IlluminatePacket& operator<<(const string data);
	IlluminatePacket& operator<<(const char* data);
	
	Int8 GetInt8();
	Int16 GetInt16();
	Int32 GetInt32();
	Int64 GetInt64();
	UInt8 GetUInt8();
	UInt16 GetUInt16();
	UInt32 GetUInt32();
	UInt64 GetUInt64();

	float GetFloat();
	double GetDouble();
	bool GetBool();

	void GetInt8(Int8& data);
	void GetInt16(Int16& data);	
	void GetInt32(Int32& data);
	void GetInt64(Int64& data);
	void GetUInt8(UInt8& data);	
	void GetUInt16(UInt16& data);	
	void GetUInt32(UInt32& data);
	void GetUInt64(UInt64& data);

	void GetFloat(float& data);
	void GetDouble(double& data);
	void GetBool(bool& data);

	void GetInt8(int position, Int8 &data);
	void GetInt16(int position, Int16 &data);
	void GetInt32(int position, Int32 &data);
	void GetInt64(int position, Int64 &data);

	void GetUInt8(int position, UInt8 &data);
	void GetUInt16(int position, UInt16 &data);
	void GetUInt32(int position, UInt32 &data);
	void GetUInt64(int position, UInt64 &data);

	void GetFloat(int position, float &data);
	void GetDouble(int position, double &data);
	void GetBool(int position, bool& data);

	void GetString(std::string& str);
	void GetString(std::string& str, int size);

	//void GetDataBlock(UInt16 blocksize, char* data);
	//void GetDataBlock(UInt16 blocksize, unsigned char* data);
	//void GetVec3F(Illuminate::IlluminateVec3F& vec3F);
	//Illuminate::IlluminateVec3F GetVec3F();
	
	template<typename data>
	void GetGeneric(data& val);

	template<typename data>
	void GetGeneric(data& val, int size);

	template<typename data>
	void GetGeneric(int position, data &val, int size);

	IlluminatePacket& operator>>(Int8& data);
	IlluminatePacket& operator>>(Int16& data);
	IlluminatePacket& operator>>(Int32& data);
	IlluminatePacket& operator>>(Int64& data);

	IlluminatePacket& operator>>(UInt8& data);
	IlluminatePacket& operator>>(UInt16& data);
	IlluminatePacket& operator>>(UInt32& data);
	IlluminatePacket& operator>>(UInt64& data);

	IlluminatePacket& operator>>(float& data);
	IlluminatePacket& operator>>(double& data);
	IlluminatePacket& operator>>(bool& data);
	IlluminatePacket& operator>>(string& data);


	/*template<typename data>
	void SetDataAt(int position, const data val);*/

	/*Public Header Operations*/

	void	acquirePacketHeader();
	void	acquireOpCode();
	UInt16	GetPacketSize() { return packetSize; }
	bool	GetCrypted() { return isEncrypted; }
	UInt16	GetOpCode() { return opCode; }

	void	SetPacketSz(UInt16 sz) { packetSize = sz; }
	void	SetOpCode(UInt16 op) { opCode = op; }
	void	SetCrypt(bool crypt) { isEncrypted = crypt; }

	/*End Public Header Operations*/

	//inline char* getBuffer() { return &buf[pos]; };
	inline unsigned char*	getBuffer() { return buf; };
	inline unsigned char*	getBufferAt(int pos) { if (pos == 0) return nullptr; else return &buf[pos - 1]; }
	inline unsigned char*	getBufferAtCurPos() { return &buf[pos]; }
	inline unsigned char	getSingleElement(int pos) { return buf[pos]; };
	inline int				getPosition() { return pos; };

	inline void	setPosition(int newPos) { pos = newPos; };
	inline void setSize(int newSize) { size = newSize; }

	inline int getSize() { return size; }

private:
	unsigned char * buf;
	int size;
	int pos;

	/*Packet Info*/

	/*Header*/
	
	//First 3 bytes are always cleartext
	UInt16 packetSize;
	bool isEncrypted;

	//OpCode is Encrypted in transit
	UInt16 opCode;
	
	/*End Header Info*/

	/*End Packet Info*/

	void EnsureBufSize(int checkSize)
	{
		if (checkSize > size)
			Resize(checkSize);
		else
			return;
	}

	inline void ValidateReadTo(int position)
	{
		if (position > size)
			throw "Buffer overread";
	}
};