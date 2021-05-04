#include "IlluminateBDOCRC.h"

#define __ROL4__(x, y) _rotl(x, y)
#define __ROR4__(x, y) _rotr(x, y)

UInt32 BDOCRC::processString(std::string str, UInt32 type)
{
	return process((UInt8*)str.c_str(), static_cast<UInt32>(str.length()), type);
}

UInt32 BDOCRC::processLowerString(std::string str, UInt32 type)
{
	std::transform(str.begin(), str.end(), str.begin(), tolower);
	return process((UInt8*)str.c_str(), static_cast<UInt32>(str.length()), type);
}

UInt32 BDOCRC::process(UInt8* a1, UInt32 a2, UInt32 type)
{
	unsigned int v2; // eax@1
	int v3; // ebx@1
	int v4; // ecx@1
	int v5; // esi@1
	BYTE* v6; // edi@1
	int v7; // ebx@5
	int v8; // ecx@5
	int v9; // eax@5
	int v10; // eax@5
	int v11; // ebx@5
	int v12; // edx@5
	int v13; // edx@5
	int v14; // eax@5
	int v15; // edi@5
	int v16; // edi@5
	int v17; // edx@5
	int v18; // esi@5
	int v19; // esi@5
	int v20; // edi@5
	int v21; // ecx@5
	int v22; // ecx@5
	int v23; // ebx@5
	int v24; // eax@18
	int v26; // edx@23
	int v27; // eax@23
	int v28; // eax@23
	int v29; // edx@23
	int v30; // ecx@23
	int v31; // ecx@23
	int v32; // eax@23
	int v33; // ebx@23
	int v34; // ebx@23
	int v35; // ecx@23
	int v36; // esi@23
	int v37; // esi@23
	int v38; // ebx@23
	int v39; // eax@23
	int v40; // ecx@23
	int v41; // edx@23
	int v42; // ebx@40
	int v43; // eax@40
	int v44; // eax@40
	int v45; // ebx@40
	int v46; // ecx@40
	int v47; // ecx@40
	int v48; // eax@40
	int v49; // edx@40
	int v50; // edx@40
	int v51; // ecx@40
	int v52; // esi@40
	int v53; // esi@40
	int v54; // edx@40
	int v55; // eax@40
	int v56; // ecx@40
	int v57; // ebx@40
	int v58; // edx@56
	int v59; // ebx@56
	int v60; // eax@56
	int v61; // edx@56
	int v62; // eax@56
	int v63; // ecx@56
	int v64; // eax@56
	int v65; // ebx@56
	int v66; // edi@56
	int v67; // esi@56
	int v68; // edx@56
	int v69; // ecx@56
	int v70; // edx@56
	unsigned int v71; // [sp+Ch] [bp-4h]@3
	unsigned int v72; // [sp+Ch] [bp-4h]@22
	unsigned int v73; // [sp+Ch] [bp-4h]@39
	int v74; // [sp+18h] [bp+8h]@23
	int v75; // [sp+18h] [bp+8h]@40

	v2 = a2;
	v3 = a2 - 558228019;
	v4 = a2 - 558228019;
	v5 = a2 - 558228019;
	v6 = a1;
	if (type != 3) // (UInt32)a1 & 3
	{
		if (type != 1) // (UInt32)a1 & 1
		{
			if (a2 > 0xC)
			{
				v73 = (a2 - 13) / 0xC + 1;
				do
				{
					v75 = ((*(BYTE*)(v6 + 5) + ((*(BYTE*)(v6 + 6) + (*(BYTE*)(v6 + 7) << 8)) << 8)) << 8)
						+ v4
						+ *(BYTE*)(v6 + 4);
					v42 = ((*(BYTE*)(v6 + 9) + ((*(BYTE*)(v6 + 10) + (*(BYTE*)(v6 + 11) << 8)) << 8)) << 8)
						+ *(BYTE*)(v6 + 8)
						+ v3;
					v43 = __ROL4__(v42, 4);
					v44 = (v5
						+ *(BYTE*)v6
						+ ((*(BYTE*)(v6 + 1) + ((*(BYTE*)(v6 + 2) + (*(BYTE*)(v6 + 3) << 8)) << 8)) << 8)
						- v42) ^ v43;
					v45 = v75 + v42;
					v46 = __ROL4__(v44, 6);
					v47 = (v75 - v44) ^ v46;
					a2 -= 12;
					v48 = v45 + v44;
					v49 = __ROL4__(v47, 8);
					v50 = (v45 - v47) ^ v49;
					v51 = v48 + v47;
					v52 = __ROL4__(v50, 16);
					v53 = (v48 - v50) ^ v52;
					v54 = v51 + v50;
					v55 = __ROR4__(v53, 13);
					v56 = v55 ^ (v51 - v53);
					v5 = v54 + v53;
					v57 = __ROL4__(v56, 4);
					v3 = (v54 - v56) ^ v57;
					v4 = v5 + v56;
					v6 += 12;
					--v73;
				} while (v73);
				v2 = a2;
			}
			switch (v2)
			{
			case 0u:
				return v3;
			case 0xCu:
				v3 += *(BYTE*)(v6 + 11) << 24;
				goto LABEL_44;
			case 0xBu:
			LABEL_44:
				v3 += *(BYTE*)(v6 + 10) << 16;
				goto LABEL_45;
			case 0xAu:
			LABEL_45:
				v3 += *(BYTE*)(v6 + 9) << 8;
				goto LABEL_46;
			case 9u:
			LABEL_46:
				v3 += *(BYTE*)(v6 + 8);
				goto LABEL_47;
			case 8u:
			LABEL_47:
				v4 += *(BYTE*)(v6 + 7) << 24;
				goto LABEL_48;
			case 7u:
			LABEL_48:
				v4 += *(BYTE*)(v6 + 6) << 16;
				goto LABEL_49;
			case 6u:
			LABEL_49:
				v4 += *(BYTE*)(v6 + 5) << 8;
				goto LABEL_50;
			case 5u:
			LABEL_50:
				v4 += *(BYTE*)(v6 + 4);
				goto LABEL_51;
			case 4u:
			LABEL_51:
				v5 += *(BYTE*)(v6 + 3) << 24;
				goto LABEL_52;
			case 3u:
			LABEL_52:
				v5 += *(BYTE*)(v6 + 2) << 16;
				goto LABEL_53;
			case 2u:
			LABEL_53:
				v5 += *(BYTE*)(v6 + 1) << 8;
				break;
			case 1u:
				break;
			default:
				goto LABEL_56;
			}
		LABEL_54:
			v24 = *(BYTE*)v6;
		LABEL_55:
			v5 += v24;
		}
		else
		{
			if (a2 > 0xC)
			{
				v72 = (a2 - 13) / 0xC + 1;
				do
				{
					v74 = (*(WORD*)(v6 + 6) << 16) + v4 + *(WORD*)(v6 + 4);
					v26 = (*(WORD*)(v6 + 10) << 16) + v3 + *(WORD*)(v6 + 8);
					v27 = __ROL4__(v26, 4);
					v28 = (v5 + (*(WORD*)(v6 + 2) << 16) - v26 + *(WORD*)v6) ^ v27;
					v29 = v74 + v26;
					v30 = __ROL4__(v28, 6);
					v31 = (v74 - v28) ^ v30;
					a2 -= 12;
					v32 = v29 + v28;
					v33 = __ROL4__(v31, 8);
					v34 = (v29 - v31) ^ v33;
					v35 = v32 + v31;
					v36 = __ROL4__(v34, 16);
					v37 = (v32 - v34) ^ v36;
					v38 = v35 + v34;
					v39 = __ROR4__(v37, 13);
					v40 = v39 ^ (v35 - v37);
					v5 = v38 + v37;
					v41 = __ROL4__(v40, 4);
					v3 = v41 ^ (v38 - v40);
					v4 = v5 + v40;
					v6 += 12;
					--v72;
				} while (v72);
				v2 = a2;
			}
			switch (v2)
			{
			case 0u:
				return v3;
			case 0xCu:
				v3 += (*(WORD*)(v6 + 10) << 16) + *(WORD*)(v6 + 8);
				goto LABEL_27;
			case 4u:
				goto LABEL_28;
			case 0xBu:
				v3 += *(BYTE*)(v6 + 10) << 16;
				goto LABEL_30;
			case 0xAu:
			LABEL_30:
				v3 += *(WORD*)(v6 + 8);
			LABEL_27:
				v4 += (*(WORD*)(v6 + 6) << 16) + *(WORD*)(v6 + 4);
			LABEL_28:
				v24 = *(WORD*)(v6 + 2) << 16;
				v5 += *(WORD*)v6;
				goto LABEL_55;
			case 9u:
				v3 += *(BYTE*)(v6 + 8);
				goto LABEL_32;
			case 8u:
			LABEL_32:
				v4 += (*(WORD*)(v6 + 6) << 16) + *(WORD*)(v6 + 4);
				v5 += (*(WORD*)(v6 + 2) << 16) + *(WORD*)v6;
				break;
			case 7u:
				v4 += *(BYTE*)(v6 + 6) << 16;
				goto LABEL_34;
			case 6u:
			LABEL_34:
				v4 += *(WORD*)(v6 + 4);
				v5 += (*(WORD*)(v6 + 2) << 16) + *(WORD*)v6;
				break;
			case 5u:
				v4 += *(BYTE*)(v6 + 4);
				v24 = *(WORD*)(v6 + 2) << 16;
				v5 += *(WORD*)v6;
				goto LABEL_55;
			case 3u:
				v5 += *(BYTE*)(v6 + 2) << 16;
				goto LABEL_37;
			case 2u:
			LABEL_37:
				v5 += *(WORD*)v6;
				break;
			case 1u:
				goto LABEL_54;
			default:
				break;
			}
		}
	}
	else
	{
		if (a2 <= 0xC)
			goto LABEL_8;
		while (1)
		{
			v71 = (v2 - 13) / 0xC + 1;
			while (1)
			{
				v7 = *(DWORD*)(v6 + 8) + v3;
				v8 = *(DWORD*)(v6 + 4) + v4;
				v9 = __ROL4__(v7, 4);
				v10 = (v5 + *(DWORD*)v6 - v7) ^ v9;
				v11 = v8 + v7;
				v12 = __ROL4__(v10, 6);
				v13 = (v8 - v10) ^ v12;
				v14 = v11 + v10;
				v15 = __ROL4__(v13, 8);
				v16 = (v11 - v13) ^ v15;
				v17 = v14 + v13;
				v18 = __ROL4__(v16, 16);
				v19 = (v14 - v16) ^ v18;
				v20 = v17 + v16;
				v21 = __ROR4__(v19, 13);
				v22 = (v17 - v19) ^ v21;
				v5 = v20 + v19;
				v23 = __ROL4__(v22, 4);
				a2 -= 12;
				a1 += 12;
				v3 = (v20 - v22) ^ v23;
				v4 = v5 + v22;
				if (!--v71)
					break;
				v6 = a1;
			}
			if (a2 > 0xC)
				break;
			v2 = a2;
			v6 = a1;
		LABEL_8:
			switch (v2)
			{
			case 0xCu:
				v3 += *(DWORD*)(v6 + 8);
				goto LABEL_10;
			case 8u:
			LABEL_10:
				v4 += *(DWORD*)(v6 + 4);
				goto LABEL_11;
			case 4u:
			LABEL_11:
				v5 += *(DWORD*)v6;
				goto LABEL_56;
			case 0xBu:
				v4 += *(DWORD*)(v6 + 4);
				v3 += *(DWORD*)(v6 + 8) & 0xFFFFFF;
				v5 += *(DWORD*)v6;
				goto LABEL_56;
			case 0xAu:
				v4 += *(DWORD*)(v6 + 4);
				v3 += *(WORD*)(v6 + 8);
				v5 += *(DWORD*)v6;
				goto LABEL_56;
			case 9u:
				v4 += *(DWORD*)(v6 + 4);
				v3 += *(BYTE*)(v6 + 8);
				v5 += *(DWORD*)v6;
				goto LABEL_56;
			case 7u:
				v4 += *(DWORD*)(v6 + 4) & 0xFFFFFF;
				v5 += *(DWORD*)v6;
				goto LABEL_56;
			case 6u:
				v4 += *(WORD*)(v6 + 4);
				v5 += *(DWORD*)v6;
				goto LABEL_56;
			case 5u:
				v4 += *(BYTE*)(v6 + 4);
				v5 += *(DWORD*)v6;
				goto LABEL_56;
			case 3u:
				v24 = *(DWORD*)v6 & 0xFFFFFF;
				goto LABEL_55;
			case 0u:
				return v3;
			case 2u:
				goto LABEL_37;
			case 1u:
				goto LABEL_54;
			default:
				continue;
			}
		}
	}
LABEL_56:
	v58 = __ROL4__(v4, 14);
	v59 = (v4 ^ v3) - v58;
	v60 = __ROL4__(v59, 11);
	v61 = (v5 ^ v59) - v60;
	v62 = __ROR4__(v61, 7);
	v63 = (v61 ^ v4) - v62;
	v64 = __ROL4__(v63, 16);
	v65 = (v63 ^ v59) - v64;
	v66 = __ROL4__(v65, 4);
	v67 = (v61 ^ v65) - v66;
	v68 = __ROL4__(v67, 14);
	v69 = (v67 ^ v63) - v68;
	v70 = __ROR4__(v69, 8);
	return UInt32((v69 ^ v65) - v70);
}