#include "IlluminatePacketInterface.h"

IlluminatePacketInterface::IlluminatePacketInterface()
{
}

IlluminatePacketInterface::~IlluminatePacketInterface()
{
}

IlluminatePacket * IlluminatePacketInterface::buildPacket(UInt16 packetType, ...)
{
	va_list args;
	va_start(args, packetType);
	int dwMask = 1;
	//Using the packetType we get the field data for this packet. Then we create a new IlluminatePacket, and build it using the variadic arugment list.
	
	UInt8 flagLen = flagLookup.lookUp(packetType);
	if (flagLen == 0xFF)
		return nullptr;

	IlluminatePacket * response = new IlluminatePacket(packetType, flagLen);

	bool fieldsOkay = fieldLookup.getFieldInfo(response->GetFieldVec(), packetType);

	if (!fieldsOkay)
		return nullptr;

	for (vector<Illuminate::IlluminatePktField>::iterator itr = response->GetFieldVec().begin(); itr != response->GetFieldVec().end(); itr++) //iterate through our fields
	{
		switch (itr->FieldType)
		{
			case Illuminate::IlluminateType::CHAR: //Assumes character data is already setup with proper sizing before passing into buildPacket
			{
				unsigned char* arg = va_arg(args, unsigned char*);
				if (arg)
					response->WriteArbitraryData(arg, itr->FieldSize);
			} break;
			case Illuminate::IlluminateType::INT8:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Int8* arg = va_arg(args, Int8*);
					if(arg)
						response->WriteInt8(*arg);
				}
			} break;
			case Illuminate::IlluminateType::UINT8:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt8* arg = va_arg(args, UInt8*);
					if(arg)
						response->WriteUInt8(*arg);
				}
			} break;
			case Illuminate::IlluminateType::INT16:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Int16* arg = va_arg(args, Int16*);
					if(arg)
						response->WriteInt16(*arg);
				}
			} break;
			case Illuminate::IlluminateType::UINT16:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt16* arg = va_arg(args, UInt16*);
					if(arg)
						response->WriteUInt16(*arg);
				}
			} break;
			case Illuminate::IlluminateType::INT32:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Int32* arg = va_arg(args, Int32*);
					if(arg)
						response->WriteInt32(*arg);
				}
			} break;
			case Illuminate::IlluminateType::UINT32:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt32* arg = va_arg(args, UInt32*);
					if(arg)
						response->WriteUInt32(*arg);
				}
			} break;
			case Illuminate::IlluminateType::INT64:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Int64* arg = va_arg(args, Int64*);
					if(arg)
						response->WriteInt64(*arg);
				}
			} break;
			case Illuminate::IlluminateType::UINT64:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt64* arg = va_arg(args, UInt64*);
					if(arg)
						response->WriteUInt64(*arg);
				}
			} break;
			case Illuminate::IlluminateType::FLOAT:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					float* arg = va_arg(args, float*);
					if(arg)
						response->WriteFloat(*arg);
				}
			} break;
			case Illuminate::IlluminateType::VEC3F:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Illuminate::IlluminateVec3F* arg = va_arg(args, Illuminate::IlluminateVec3F*);
					if(arg)
						response->WriteVec3F(*arg);
				}
			} break;
			case Illuminate::IlluminateType::MATRIX:
			{

			} break;
			case Illuminate::IlluminateType::PACKET:
			{
				if (itr->FieldSize > 1) //&numOfPkts, &Packet1, &Packet2
				{
					UInt8* arg = va_arg(args, UInt8*);
					if (arg)
					{
						UInt8 numOfPkts = *arg;
						//Write amount of packets to be contained first
						response->WriteUInt8(numOfPkts);
						for (int i = 0; i < numOfPkts; i++)
						{
							//write our packets.
							SharedPtr<IlluminatePacket>* arg = va_arg(args, SharedPtr<IlluminatePacket>*);
							if (arg)
								response->WritePacket(arg->get());
						}
					}
				}
				else
				{
					SharedPtr<IlluminatePacket>* arg = va_arg(args, SharedPtr<IlluminatePacket>*);

					if (arg)
						response->WritePacket(arg->get());
				}
			} break;
			case Illuminate::IlluminateType::MEMORY_BLOCK:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt16* arg_sz = va_arg(args, UInt16*);
					if (arg_sz) //If arg_sz is 0 we can assume there will be no data so we never look for the arg
					{
						response->WriteUInt16(*arg_sz, false);

						if (*arg_sz) //size of mem block != 0 
						{
							char* arg = va_arg(args, char*);
							response->WriteArbitraryData(arg, *arg_sz);
						}
					}
				}
			} break;
			case Illuminate::IlluminateType::POS_BASEMETER:
			{

			} break;
			case Illuminate::IlluminateType::WCHAR:
			{

			} break;
		}

		dwMask *= 2;
		response->UpdateMask(dwMask);
	}
	
	response->ClosePacket();
	va_end(args);
	return response;
}

IlluminatePacket * IlluminatePacketInterface::buildMiniPacket(UInt16 miniType, ...)
{
	va_list args;
	va_start(args, miniType);
	int dwMask = 1;
	//Using the packetType we get the field data for this packet. Then we create a new IlluminatePacket, and build it using the variadic arugment list.
	
	UInt8 flagLen = flagLookup.lookUp(miniType);
	if (flagLen == 0xFF)
		return nullptr;

	IlluminatePacket * response = new IlluminatePacket(flagLen);

	bool fieldsOkay = fieldLookup.getFieldInfo(response->GetFieldVec(), miniType);

	if (!fieldsOkay)
		return nullptr;

	for (vector<Illuminate::IlluminatePktField>::iterator itr = response->GetFieldVec().begin(); itr != response->GetFieldVec().end(); itr++) //iterate through our fields
	{
		switch (itr->FieldType)
		{
			case Illuminate::IlluminateType::CHAR: //Assumes character data is already setup with proper sizing before passing into buildPacket
			{
				char* arg = va_arg(args, char*);
				if (arg)
					response->WriteArbitraryData(arg, itr->FieldSize);
			} break;
			case Illuminate::IlluminateType::INT8:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Int8* arg = va_arg(args, Int8*);
					if (arg)
						response->WriteInt8(*arg);
				}
			} break;
			case Illuminate::IlluminateType::UINT8:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt8* arg = va_arg(args, UInt8*);
					if (arg)
						response->WriteUInt8(*arg);
				}
			} break;
			case Illuminate::IlluminateType::INT16:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Int16* arg = va_arg(args, Int16*);
					if (arg)
						response->WriteInt16(*arg);
				}
			} break;
			case Illuminate::IlluminateType::UINT16:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt16* arg = va_arg(args, UInt16*);
					if (arg)
						response->WriteUInt16(*arg);
				}
			} break;
			case Illuminate::IlluminateType::INT32:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Int32* arg = va_arg(args, Int32*);
					if (arg)
						response->WriteInt32(*arg);
				}
			} break;
			case Illuminate::IlluminateType::UINT32:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt32* arg = va_arg(args, UInt32*);
					if (arg)
						response->WriteUInt32(*arg);
				}
			} break;
			case Illuminate::IlluminateType::INT64:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Int64* arg = va_arg(args, Int64*);
					if (arg)
						response->WriteInt64(*arg);
				}
			} break;
			case Illuminate::IlluminateType::UINT64:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt64* arg = va_arg(args, UInt64*);
					if (arg)
						response->WriteUInt64(*arg);
				}
			} break;
			case Illuminate::IlluminateType::FLOAT:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					float* arg = va_arg(args, float*);
					if (arg)
						response->WriteFloat(*arg);
				}
			} break;
			case Illuminate::IlluminateType::VEC3F:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					Illuminate::IlluminateVec3F* arg = va_arg(args, Illuminate::IlluminateVec3F*);
					if (arg)
						response->WriteVec3F(*arg);
				}
			} break;
			case Illuminate::IlluminateType::MATRIX:
			{

			} break;
			case Illuminate::IlluminateType::PACKET:
			{
				//for (int i = 0; i < itr->FieldSize; i++)
				//{
					SharedPtr<IlluminatePacket>* arg = va_arg(args, SharedPtr<IlluminatePacket>*);

					if (arg)
						response->WritePacket(arg->get());
				//}
			} break;
			case Illuminate::IlluminateType::MEMORY_BLOCK:
			{
				for (int i = 0; i < itr->FieldSize; i++)
				{
					UInt16* arg_sz = va_arg(args, UInt16*);
					if (arg_sz) //If arg_sz is 0 we can assume there will be no data so we never look for the arg
					{
						response->WriteUInt16(*arg_sz, false);

						if (*arg_sz) //size of mem block != 0 
						{
							char* arg = va_arg(args, char*);
							response->WriteArbitraryData(arg, *arg_sz);
						}
					}
				}
			} break;
			case Illuminate::IlluminateType::POS_BASEMETER:
			{

			} break;
			case Illuminate::IlluminateType::WCHAR:
			{

			} break;
		}

		dwMask *= 2;
		response->UpdateMask(dwMask);
	}

	response->CloseMiniPacket();
	va_end(args);
	return response;
}

bool IlluminatePacketInterface::processPacket(IlluminatePacket * packet, ...)
{
	//Packet should've already been setup at this point. Retrieve data using already defined field type data, and place into variadic argument list
	UInt32	pktFlag = 0;
	UInt32	readFlag = 1U << 0;
	va_list args;

	va_start(args, packet);
	switch (packet->GetFlagLength())
	{
		case 1:
			pktFlag = *(UInt8*)packet->GetPacketFlags(); break;
		case 2:
			pktFlag = *(UInt16*)packet->GetPacketFlags(); break;
		case 4:
			pktFlag = *(UInt32*)packet->GetPacketFlags(); break;
		default:
			pktFlag = 0; break;
	}

	for (vector<Illuminate::IlluminatePktField>::iterator itr = packet->GetFieldVec().begin(); itr != packet->GetFieldVec().end(); itr++, readFlag <<= 1) //iterate through our fields
	{
		if (readFlag > pktFlag)
			break;

		void* arg = va_arg(args, void*);

		if (pktFlag & readFlag)
		{
			switch (itr->FieldType)
			{
				case Illuminate::IlluminateType::CHAR:
				{
					if (arg)
					{
						UInt32 charSize = itr->FieldSize; //Is the size ALWAYS static?

						unsigned char* temp = new unsigned char[charSize];
						packet->GetDataBlock(charSize, temp);

						memcpy(arg, temp, charSize);

						delete[] temp;
					}	
				} break;
				case Illuminate::IlluminateType::INT8:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if (arg)
							*(((Int8*)arg)) = packet->GetInt8();
					}
				} break;
				case Illuminate::IlluminateType::UINT8:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if(arg)
							*(((UInt8*)arg)) = packet->GetUInt8();
					}
				} break;
				case Illuminate::IlluminateType::INT16:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if(arg)
							*(((Int16*)arg)) = packet->GetInt16();
					}
				} break;
				case Illuminate::IlluminateType::UINT16:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if(arg)
							*(((UInt16*)arg)) = packet->GetUInt16();

					}
				} break;
				case Illuminate::IlluminateType::INT32:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if(arg)
							*(((Int32*)arg)) = packet->GetInt32();
					}
				} break;
				case Illuminate::IlluminateType::UINT32:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if(arg)
							*(((UInt32*)arg)) = packet->GetUInt32();
					}
				} break;
				case Illuminate::IlluminateType::INT64:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if(arg)
							*(((Int64*)arg)) = packet->GetInt64();
					}
				} break;
				case Illuminate::IlluminateType::UINT64:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if(arg)
							*(((UInt64*)arg)) = packet->GetUInt64();
					}
				} break;
				case Illuminate::IlluminateType::FLOAT:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if(arg)
							*(((float*)arg)) = packet->GetFloat();
					}
				} break;
				case Illuminate::IlluminateType::VEC3F:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						if (arg)
						{
							Illuminate::IlluminateVec3F temp = packet->GetVec3F();
							(*(((Illuminate::IlluminateVec3F*)arg))).x = temp.x;
							(*(((Illuminate::IlluminateVec3F*)arg))).y = temp.y;
							(*(((Illuminate::IlluminateVec3F*)arg))).z = temp.z;
						}
					}
				} break;
				case Illuminate::IlluminateType::MATRIX:
				{
				} break;
				//A potential issue exists in that the packet tells us there are X amount of packets, but the data just isn't there causing an overflow.
				//The number of packets is read in first, then afterwards they can be treated as discrete memory blocks
				//&numOfPkts, &Packet1, &Packet2, ...
				//A potential improvement can be to read in a vector<IlluminatePacket*> instead of a bunch of individual packets
				case Illuminate::IlluminateType::PACKET:
				{
					if(arg)
					{
						if (itr->FieldSize > 1)
						{
							*(((UInt8*)arg)) = packet->GetUInt8(); //Number of "miniPackets" contained within the outer packet.
							UInt8 numOfPkts = *(((UInt8*)arg));
							if (numOfPkts)
							{
								//NOTE: Check if reading in these packets will cause a read overrun
								for (int i = 0; i < numOfPkts; i++)
								{
									if (i > itr->FieldSize) //NOTE: Additional checks should be added here to ensure validity of packet data
										break;

									UInt16 blockSize = 0;
									packet->GetUInt16(blockSize);

									SharedPtr<IlluminatePacket>* pkt = va_arg(args, SharedPtr<IlluminatePacket>*);
									char* pktData = new char[blockSize];

									packet->GetDataBlock(blockSize, pktData);

									IlluminatePacket* temp = new IlluminatePacket((unsigned char*)pktData, (int)blockSize);

									pkt->get()->ResetFromPkt(temp);

									delete[] pktData;
									delete temp;
									
								}
							}
						}
						else //itr->FieldSize <= 1
						{
							UInt16 blockSize = 0;
							packet->GetUInt16(blockSize);

							char* pktData = new char[blockSize];

							packet->GetDataBlock(blockSize, pktData);

							IlluminatePacket* temp = new IlluminatePacket((unsigned char*)pktData, (int)blockSize);

							static_cast<SharedPtr<IlluminatePacket>*>(arg)->get()->ResetFromPkt(temp);

							delete[] pktData;
							delete temp;
						}
					}
				} break;
				case Illuminate::IlluminateType::MEMORY_BLOCK:
				{
					for (int i = 0; i < itr->FieldSize; i++)
					{
						UInt16 blocksize = 0;
						packet->GetUInt16(blocksize);

						char* temp = new char[blocksize];

						packet->GetDataBlock(blocksize, temp);
						if (arg)
							memcpy(arg, temp, blocksize);

						delete[] temp;
					}
				} break;
				case Illuminate::IlluminateType::POS_BASEMETER:
				{
				} break;
				case Illuminate::IlluminateType::WCHAR:
				{
				} break;
			}
		}
	}

	va_end(args);
	return true;
}

bool IlluminatePacketInterface::setupPkt(IlluminatePacket * packet)
{
	//call acquireHeader() from packet pointer,then use packettype to set the flaglength, and field type data.
	packet->acquirePacketHeader();
	bool flagsOkay = packet->setAndAcquireFlags(flagLookup.lookUp(packet->GetPacketType())); //This needs to be simplified somehow

	if (!flagsOkay)
		return false;

	//Get FieldInfo
	bool fieldsOkay = fieldLookup.getFieldInfo(packet->GetFieldVec(), packet->GetPacketType());

	if (!fieldsOkay)
		return false;

	return true;
}