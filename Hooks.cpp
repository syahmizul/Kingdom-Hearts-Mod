#include "Hooks.hpp"
#include <wtypes.h>
#include "minhook/include/MinHook.h"
#include <exception>
#include "Utils.hpp"
#include "Globals.h"
#include <string>
#define LODWORD(x) (*((unsigned int*)&(x)))
typedef unsigned __int64 QWORD;
namespace Hooks
{
	void Initialize()
	{
		if (MH_Initialize() == MH_STATUS::MH_OK)
		{
			// Find address of functions
			aApplyHealth = (uintptr_t*)(Globals::BaseProcess + 0x744AD0);
			aFormChange1 = (uintptr_t*)(Globals::BaseProcess + 0x19A3F90);
			asub_173A560 = (uintptr_t*)(Globals::BaseProcess + 0x173A560);
			// Create the hook
			//MH_CreateHook(aApplyHealth, &hkApplyHealth, reinterpret_cast<LPVOID*>(&oApplyHealth) );
			MH_CreateHook(aFormChange1, &hkFormChange1, reinterpret_cast<LPVOID*>(&oFormChange1));
			MH_CreateHook(asub_173A560, &hksub_173A560, reinterpret_cast<LPVOID*>(&osub_173A560));
			// Enable hook
			//MH_EnableHook(aApplyHealth);
			MH_EnableHook(MH_ALL_HOOKS);
		}
		else
			Utils::ConsolePrint("MinHook initialization failed!");

		return;
	}

	void Uninitialize()
	{
		MH_Uninitialize();
	}



	__int64 __fastcall hkApplyHealth(__int64 a1, int DamageDone)
	{
		unsigned int v3;
		int CalculatedHealth; 
		int HealthDiff = 0;  


		v3 = *(DWORD*)(a1 + 1532); 

		CalculatedHealth = (*(__int64(__fastcall**)(__int64))(*(QWORD*)a1 + 0x1820i64))(a1);
		if (CalculatedHealth > DamageDone)
			HealthDiff = CalculatedHealth - DamageDone;
		if (DamageDone >= 0)
		{
			if (DamageDone < CalculatedHealth)
				CalculatedHealth = DamageDone;
				
		}
		else
		{
			CalculatedHealth = 0;
		}
		
		__int64 LocalHealthBase = (__int64)Utils::PointerResolver(Globals::BaseProcess, { 0x0A70B4A0,0x48,0x3E8 });
		int* LocalHealthPtr = (int*)((uintptr_t)LocalHealthBase + 0x5FC);


		DWORD* HealthPtr = (DWORD*)(a1 + 0x5FC);
		if (a1 != LocalHealthBase) 
		{
			*HealthPtr = CalculatedHealth;
			if (*LocalHealthPtr <= 240)
			{
				*LocalHealthPtr += 5;
				if (*LocalHealthPtr > 240)
					*LocalHealthPtr = 240;
			}
				
		}
		
			
		return (*(__int64(__fastcall**)(__int64, QWORD))(*(QWORD*)(a1 + 1096) + 544i64))(a1 + 1096, v3);
	}
	
	__int64 __fastcall hkFormChange1(__int64 a1, float a2)
	{

		
		QWORD v3; // rbp
		QWORD result; // rax
		QWORD* v5; // rsi
		QWORD v6; // rbx
		int v7; // ebx
		QWORD v8; // [rsp+28h] [rbp-50h] BYREF
		QWORD v9; // [rsp+30h] [rbp-48h]
		//char v10[16]; // [rsp+38h] [rbp-40h] BYREF
		struct Temp {
			BYTE v1, v2;
			DWORD v3, v4;
			QWORD v5, v6, v7, v8, v9;
		}v10{};
		QWORD v11 = 0; // [rsp+48h] [rbp-30h]
		QWORD v12 = 0; // [rsp+58h] [rbp-20h]


		static auto sub_19A4160 = reinterpret_cast<__int64(__fastcall*)(QWORD a1)>(Globals::BaseProcess + 0x19A4160);
		static auto sub_19A40F0 = reinterpret_cast<__int64(__fastcall*)(QWORD a1)>(Globals::BaseProcess + 0x19A40F0);
		static auto sub_58BA90	= reinterpret_cast<__int64 (__fastcall*) (QWORD a1)>(Globals::BaseProcess + 0x58BA90);
		static auto sub_18E6FA0 = reinterpret_cast<__int64(__fastcall*) (QWORD a1, QWORD a2, QWORD a3, int a4)>(Globals::BaseProcess + 0x18E6FA0);
		static auto sub_31AAFA0 = reinterpret_cast<__int64(__fastcall*)(QWORD a1)>(Globals::BaseProcess + 0x31AAFA0);


		*(float*)(a1 + 0x9D0) = a2;
		v3 = 0i64;
		
		if (a2 >= *(float*)(Globals::BaseProcess + 0x7F5B8FC)) //0.25 
		{
			if (a2 >= *(float*)(Globals::BaseProcess + 0x7F5B9F4)) //0.50
			{
				if (a2 >= *(float*)(Globals::BaseProcess + 0x7F5BACC)) //0.75
				{
					if (a2 >= *(float*)(Globals::BaseProcess + 0x7F5BBC8)) //1.00
					{
						return sub_19A4160(a1);
					}
					result = 3i64;
				}
				else
				{
					result = 2i64;
				}
			}
			else
			{
				result = 1i64;
			}
		}
		else
		{
			result = 0i64;
		}
		if (*(DWORD*)(a1 + 0x9D4) == (DWORD)result)//return on nothing occuring,gets skipped if form counter bar needs to be incremented
		{
			return result;
		}
		*(DWORD*)(a1 + 0x9D4) = result;
		if (!(DWORD)result) //triggers on form end,a2 == 0,
		{
     			return sub_19A4160(a1);
		}
		result = (__int64)sub_19A40F0(a1);
		if (*(QWORD*)(a1 + 0x58))
		{
			v5 = (QWORD*)(Globals::BaseProcess + 0x7187140); 
			if ((QWORD*)(Globals::BaseProcess + 0x8D2F218))
			{
				v5 = (QWORD*)(Globals::BaseProcess + 0x8D2F210); 
			}
			v8 = 0i64;
			v9 = 0i64;
			if (v5 && *v5)
			{
				v6 = -1i64;
				do
				{
					++v6;
				} while (v5[v6]);
				v7 = v6 + 1;
				LODWORD(v9) = v7;
				if (v7 > 0)
				{
					sub_58BA90((QWORD)&v8);
					v3 = v8;
				}
				if(v3)
					memcpy((void*)v3, v5, 2i64 * v7);
			}
			result = sub_18E6FA0(*(QWORD*)(a1 + 0x58), (__int64)&v10, (__int64)v8, *(DWORD*)(a1 + 0x9D4));
			if (v12)
			{
				result = sub_31AAFA0(v12);
			}
			if (v11)
			{
				result = sub_31AAFA0(v11);
			}
			if (v8)
			{
				return sub_31AAFA0((__int64)v8);
			}
		}
		return result;
	}
	//char __fastcall hksub_173A560(__int64* a1, float a2)
	//{
	//	/*__int64 v70 = 0xDFi64;
	//	QWORD v60 = ((QWORD)(Globals::BaseProcess + 0x1B14EE0));
	//	static int i = 0;
	//	if( i % 32 == 0)
	//		(*(void(__fastcall**)(__int64*, __int64, QWORD, QWORD))(*a1 + 0x1578))(a1, v70, v60, 0i64);
	//	i++;
	//	return osub_173A560(a1, a2);*/
 //       __int64 v2; // rsi
 //       __int64 v4; // rax
 //       __int64 v5; // rdx
 //       __int64 v6; // r8
 //       __int64 v7; // rax
 //       char v8; // al
 //       int v9; // eax
 //       __int64 v10; // rdx
 //       char v11; // al
 //       __int64 v12; // rax
 //       __int64 v13; // r13
 //       int v14; // ecx
 //       __int64 v15; // rax
 //       bool(__fastcall * v17)(__int64); // rdx
 //       unsigned __int8 v18; // r14
 //       char v19; // r15
 //       void** v20; // r8
 //       unsigned int v21; // edi
 //       __int64(__fastcall * v22)(__int64); // rdx
 //       int v23; // eax
 //       unsigned int v24; // eax
 //       __int64 v25; // rcx
 //       __int64(__fastcall * v26)(); // rax
 //       char v27; // al
 //       __int64(__fastcall * v28)(); // rax
 //       char v29; // al
 //       __int64(__fastcall * v30)(); // rax
 //       char v31; // al
 //       __int64(__fastcall * v32)(); // rdx
 //       char v33; // al
 //       __int64(__fastcall * v34)(); // rdx
 //       char v35; // al
 //       __int64(__fastcall * v36)(); // rdx
 //       char v37; // al
 //       __int64(__fastcall * v38)(); // rdx
 //       char v39; // al
 //       DWORD* v41; // rcx
 //       int v42; // eax
 //       __int64 v43; // rdx
 //       int v44; // eax
 //       int v45; // eax
 //       int v46; // eax
 //       int v47; // eax
 //       int v48; // eax
 //       int v49; // eax
 //       int v50; // eax
 //       int v51; // eax
 //       int v52; // eax
 //       __int64(__fastcall * v53)(); // rdx
 //       char v54; // al
 //       __int64 v55; // rdx
 //       float v56; // xmm7_4
 //       bool v57; // cf
 //       __int64 v58; // rax
 //       __int64 v59; // rdx
 //       void** v60; // r8
 //       __int64(__fastcall * v61)(); // rdx
 //       char v62; // al
 //       __int64(__fastcall * v63)(); // rdx
 //       char v64; // al
 //       __int64(__fastcall * v65)(); // rdx
 //       char v66; // al
 //       bool v67; // zf
 //       __int64(__fastcall * v68)(); // rax
 //       int v69; // eax
 //       __int64 v70; // rdx
 //       int v71; // eax
 //       DWORD* v72; // rcx
 //       int v73; // eax
 //       int v74; // eax
 //       int v75; // eax
 //       int v76; // eax
 //       int v77; // eax
 //       int v78; // eax
 //       int v79; // eax
 //       int v80; // eax
 //       int v81; // eax
 //       int v82; // eax

 //       static auto sub_2D1D510 = reinterpret_cast<__int64(*)()>(Globals::BaseProcess + 0x2D1D510);
 //       static auto sub_1718EE0 = reinterpret_cast<__int64(*)(__int64)>(Globals::BaseProcess + 0x1718EE0);
 //       static auto sub_745870  = reinterpret_cast<bool (__fastcall*)(__int64 a1)>(Globals::BaseProcess + 0x1718EE0);
 //       static auto sub_8081F0  = reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(Globals::BaseProcess+0x8081F0);
 //       static auto sub_13C2B30 = reinterpret_cast<__int64(__fastcall*) (__int64 a1)>(Globals::BaseProcess + 0x13C2B30);
 //       v2 = a1[0x7D];
 //       if (!v2
 //           || ((v4 = sub_2D1D510(),
 //               v5 = *(QWORD*)(v2 + 0x18),
 //               v6 = v4 + 0xA0,
 //               v7 = *(int*)(v4 + 0xA8),
 //               (int)v7 > *(DWORD*)(v5 + 0xA8))
 //               || *(QWORD*)(*(QWORD*)(v5 + 0xA0) + 8 * v7) != v6
 //               ? (v8 = 0)
 //               : (v8 = 1),
 //               !v8))
 //       {
 //           v2 = 0i64;
 //       LABEL_13:
 //           v11 = 0;
 //           goto LABEL_14;
 //       }
 //       v9 = (2 * *(DWORD*)(v2 + 0xC)) >> 1;
 //       if (v9 >= *(int*)(Globals::BaseProcess + 0x8D4BDFC))
 //           v10 = 0i64;
 //       else
 //           v10 = (*(QWORD*)(Globals::BaseProcess + 0x8D4BDF0)) + 0x18i64 * v9;
 //       if ((*(DWORD*)(v10 + 8) & 0x20000000) != 0)
 //           goto LABEL_13;
 //       v11 = 1;
 //   LABEL_14:
 //       if (!v11)
 //           return 0;
 //       v12 = sub_1718EE0((__int64)a1);
 //       v13 = v12;
 //       if (!v12)
 //           return 0;
 //       v14 = (2 * *(DWORD*)(v12 + 0xC)) >> 1;
 //       v15 = v14 >= *(int*)(Globals::BaseProcess + 0x8D4BDFC) ? 0i64 : *(QWORD*)(Globals::BaseProcess + 0x8D4BDF0) + 0x18i64 * v14;
 //       if ((*(DWORD*)(v15 + 8) & 0x20000000) != 0)
 //           return 0;
 //       v17 = *(bool(__fastcall**)(__int64))(*(QWORD*)v2 + 0x17E0i64);
 //       if (v17 == sub_745870)
 //           v18 = (*(BYTE*)(v2 + 0x7C0) & 2) != 0;
 //       else
 //           v18 = ((__int64(__fastcall*)(__int64))v17)(v2);
 //       v19 = 0;
 //       v20 = (void**)Globals::BaseProcess;
 //       v21 = 0;
 //       if (*((BYTE*)a1 + 0xB5D))
 //       {
 //           v22 = *(__int64(__fastcall**)(__int64))(*a1 + 0x1A70);
 //           if (v22 == sub_8081F0)
 //           {
 //               v23 = *((DWORD*)a1 + 0x2CE);
 //           }
 //           else
 //           {
 //               v23 = ((__int64(__fastcall*)(__int64*, __int64(__fastcall*)(__int64), struct HINSTANCE__*))v22)(
 //                   a1,
 //                   v22,
 //                   (struct HINSTANCE__*)Globals::BaseProcess);
 //               v20 = (void**)Globals::BaseProcess;
 //           }
 //           switch (v23)
 //           {
 //           case 0x82:
 //               v21 = 0x9C;
 //               goto LABEL_49;
 //           case 0x83:
 //           case 0x8F:
 //               v21 = 0x9D;
 //               goto LABEL_49;
 //           case 0x84:
 //           case 0x93:
 //               v21 = 0x9E;
 //               goto LABEL_49;
 //           case 0x85:
 //               v21 = 0x9F;
 //               goto LABEL_49;
 //           case 0x86:
 //               v21 = 0xA0;
 //               goto LABEL_49;
 //           case 0x87:
 //               v21 = 0xA1;
 //               goto LABEL_49;
 //           case 0x88:
 //               v21 = 0xA2;
 //               goto LABEL_49;
 //           case 0x89:
 //           case 0x91:
 //               v21 = 0xA3;
 //               goto LABEL_49;
 //           case 0x8B:
 //               if (*((DWORD*)a1 + 0x222) == 0x8B)
 //               {
 //                   v21 = 0x6D;
 //               }
 //               else
 //               {
 //                   v22 = *(__int64(__fastcall**)(__int64))(*(QWORD*)(v2 + 0x460) + 0xA8i64);
 //                   if (v22 == sub_13C2B30)
 //                       v24 = *(DWORD*)(v2 + 0xE58);
 //                   else
 //                       v24 = ((__int64(__fastcall*)(__int64, __int64(__fastcall*)(__int64), struct HINSTANCE__*))v22)(
 //                           v2 + 0x460,
 //                           v22,
 //                           (struct HINSTANCE__*)Globals::BaseProcess);
 //                   v21 = 0xB3;
 //                   if (v24 >= 3)
 //                       v21 = 0xA5;
 //               }
 //               goto LABEL_49;
 //           case 0x8D:
 //               v21 = 0xA6;
 //               goto LABEL_49;
 //           case 0x94:
 //           case 0x95:
 //           case 0x96:
 //           case 0x97:
 //           case 0x98:
 //               goto LABEL_77;
 //           case 0x99:
 //               v21 = 0xA7;
 //               goto LABEL_49;
 //           case 0x9A:
 //               v21 = 0xA8;
 //               goto LABEL_49;
 //           case 0xDF:
 //               v21 = 0xE1;
 //               goto LABEL_49;
 //           case 0xE0:
 //               v21 = 0xE2;
 //               goto LABEL_49;
 //           default:
 //           LABEL_49:
 //               v25 = *(QWORD*)v2;
 //               v26 = *(__int64(__fastcall**)())(*(QWORD*)v2 + 0xD70i64);
 //               if (v26 == sub_6B2A40)
 //               {
 //                   v27 = *(BYTE*)(v2 + 0x5F0);
 //               }
 //               else
 //               {
 //                   v27 = ((__int64(__fastcall*)(__int64, __int64(__fastcall*)(), void**))v26)(v2, v22, v20);
 //                   v25 = *(QWORD*)v2;
 //               }
 //               if (v27 == 2)
 //               {
 //                   v28 = *(__int64(__fastcall**)())(v25 + 0xD80);
 //                   if (v28 == sub_13C31C0)
 //                       v29 = *(BYTE*)(v2 + 0x15B4);
 //                   else
 //                       v29 = ((__int64(__fastcall*)(__int64, __int64(__fastcall*)(), void**))v28)(v2, v22, v20);
 //                   if (v29 == 9)
 //                   {
 //                       v21 = 0xA9;
 //                       goto LABEL_64;
 //                   }
 //               }
 //               else
 //               {
 //                   v30 = *(__int64(__fastcall**)())(v25 + 0xD70);
 //                   if (v30 == sub_6B2A40)
 //                       v31 = *(BYTE*)(v2 + 0x5F0);
 //                   else
 //                       v31 = ((__int64(__fastcall*)(__int64, __int64(__fastcall*)(), void**))v30)(v2, v22, v20);
 //                   if (v31 == 3)
 //                   {
 //                       v21 = 0xE4;
 //                       goto LABEL_64;
 //                   }
 //                   v32 = *(__int64(__fastcall**)())(*(QWORD*)v2 + 0xD70i64);
 //                   if (v32 == sub_6B2A40)
 //                       v33 = *(BYTE*)(v2 + 0x5F0);
 //                   else
 //                       v33 = ((__int64(__fastcall*)(__int64, __int64(__fastcall*)(), void**))v32)(v2, v32, v20);
 //                   if (v33 == 7)
 //                       goto LABEL_77;
 //               }
 //               if (!v21)
 //                   goto LABEL_65;
 //           LABEL_64:
 //               if ((unsigned __int8)sub_18DDF50(v13, v21))
 //                   goto LABEL_77;
 //           LABEL_65:
 //               if (*((DWORD*)a1 + 0x220) != 0xB3)
 //                   *((BYTE*)a1 + 0xB5D) = 0;
 //               break;
 //           }
 //           goto LABEL_77;
 //       }
 //       if (*((BYTE*)a1 + 0xB5C))
 //       {
 //           v34 = *(__int64(__fastcall**)())(*(QWORD*)v2 + 0xD70i64);
 //           if (v34 == sub_6B2A40)
 //               v35 = *(BYTE*)(v2 + 0x5F0);
 //           else
 //               v35 = ((__int64(__fastcall*)(__int64, __int64(__fastcall*)(), struct HINSTANCE__*))v34)(v2, v34, &_ImageBase);
 //           if (v35 == 2)
 //           {
 //           LABEL_76:
 //               v19 = *((BYTE*)a1 + 0xB5C);
 //               goto LABEL_77;
 //           }
 //           v36 = *(__int64(__fastcall**)())(*(QWORD*)v2 + 0xD70i64);
 //           if (v36 == sub_6B2A40)
 //               v37 = *(BYTE*)(v2 + 0x5F0);
 //           else
 //               v37 = ((__int64(__fastcall*)(__int64, __int64(__fastcall*)(), void**))v36)(v2, v36, v20);
 //           if (v37 == 6)
 //           {
 //               if (!(unsigned __int8)sub_18DDF50(v13, 0x99i64) && !(unsigned __int8)sub_18DDF50(v13, 0x9Ai64))
 //               {
 //               LABEL_145:
 //                   *((BYTE*)a1 + 0xB5C) = 0;
 //                   goto LABEL_77;
 //               }
 //               goto LABEL_76;
 //           }
 //           v20 = *(void***)(*(QWORD*)v2 + 0x12C8i64);
 //           if (v20 == (void**)sub_757F90)
 //           {
 //               v41 = *(DWORD**)(v2 + 0x598);
 //               if (!v41)
 //               {
 //                   v42 = 0;
 //                   goto LABEL_86;
 //               }
 //               v20 = *(void***)(*(QWORD*)v41 + 0x428i64);
 //               if (v20 == &off_1B14EE0)
 //               {
 //                   v42 = v41[0x88];
 //                   goto LABEL_86;
 //               }
 //           }
 //           else
 //           {
 //               v41 = (DWORD*)v2;
 //           }
 //           v42 = ((__int64(__fastcall*)(DWORD*, __int64))v20)(v41, 0xFFFFFFFFi64);
 //       LABEL_86:
 //           switch (v42)
 //           {
 //           case 1:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x94i64;
 //               goto LABEL_143;
 //           case 2:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x89i64;
 //               goto LABEL_143;
 //           case 3:
 //               v44 = *((DWORD*)a1 + 0x2CD);
 //               if (!v44)
 //               {
 //                   v43 = 0x80i64;
 //                   goto LABEL_143;
 //               }
 //               if (v44 != 1)
 //                   goto LABEL_145;
 //               v43 = 0x83i64;
 //               goto LABEL_143;
 //           case 4:
 //               v45 = *((DWORD*)a1 + 0x2CD);
 //               if (!v45)
 //               {
 //                   v43 = 0x81i64;
 //                   goto LABEL_143;
 //               }
 //               if (v45 != 1)
 //                   goto LABEL_145;
 //               v43 = 0x84i64;
 //               goto LABEL_143;
 //           case 5:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x88i64;
 //               goto LABEL_143;
 //           case 6:
 //               v48 = *((DWORD*)a1 + 0x2CD);
 //               if (!v48)
 //               {
 //                   v43 = 0x8Ai64;
 //                   goto LABEL_143;
 //               }
 //               if (v48 != 1)
 //                   goto LABEL_145;
 //               v43 = 0x82i64;
 //               goto LABEL_143;
 //           case 7:
 //               v49 = *((DWORD*)a1 + 0x2CD);
 //               if (!v49)
 //               {
 //                   v43 = 0x90i64;
 //                   goto LABEL_143;
 //               }
 //               if (v49 != 1)
 //                   goto LABEL_145;
 //               v43 = 0x85i64;
 //               goto LABEL_143;
 //           case 8:
 //               v47 = *((DWORD*)a1 + 0x2CD);
 //               if (!v47)
 //               {
 //                   v43 = 0x8Ei64;
 //                   goto LABEL_143;
 //               }
 //               if (v47 != 1)
 //                   goto LABEL_145;
 //               v43 = 0x8Fi64;
 //               goto LABEL_143;
 //           case 9:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x86i64;
 //               goto LABEL_143;
 //           case 0xA:
 //               v46 = *((DWORD*)a1 + 0x2CD);
 //               if (!v46)
 //               {
 //                   v43 = 0x8Ci64;
 //                   goto LABEL_143;
 //               }
 //               if (v46 != 1)
 //                   goto LABEL_145;
 //               v43 = 0x8Di64;
 //               goto LABEL_143;
 //           case 0xB:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x91i64;
 //               goto LABEL_143;
 //           case 0xC:
 //               v50 = *((DWORD*)a1 + 0x2CD);
 //               if (!v50)
 //               {
 //                   v43 = 0x92i64;
 //                   goto LABEL_143;
 //               }
 //               if (v50 != 1)
 //                   goto LABEL_145;
 //               v43 = 0x93i64;
 //               goto LABEL_143;
 //           case 0xD:
 //               v51 = *((DWORD*)a1 + 0x2CD);
 //               if (!v51)
 //               {
 //                   v43 = 0xDDi64;
 //                   goto LABEL_143;
 //               }
 //               if (v51 != 1)
 //                   goto LABEL_145;
 //               v43 = 0xDFi64;
 //               goto LABEL_143;
 //           case 0xE:
 //               v52 = *((DWORD*)a1 + 0x2CD);
 //               if (v52)
 //               {
 //                   if (v52 != 1)
 //                       goto LABEL_145;
 //                   v43 = 0xE0i64;
 //               }
 //               else
 //               {
 //                   v43 = 0xDEi64;
 //               }
 //           LABEL_143:
 //               if (!(unsigned __int8)sub_18DDF50(v13, v43))
 //                   goto LABEL_145;
 //               v19 = *((BYTE*)a1 + 0xB5C);
 //               break;
 //           case 0xF:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x87i64;
 //               goto LABEL_143;
 //           case 0x10:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x96i64;
 //               goto LABEL_143;
 //           case 0x11:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x97i64;
 //               goto LABEL_143;
 //           case 0x12:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x95i64;
 //               goto LABEL_143;
 //           case 0x13:
 //               if (*((DWORD*)a1 + 0x2CD))
 //                   goto LABEL_145;
 //               v43 = 0x98i64;
 //               goto LABEL_143;
 //           default:
 //               goto LABEL_145;
 //           }
 //       }
 //   LABEL_77:
 //       v38 = *(__int64(__fastcall**)())(*a1 + 0x1528);
 //       if (v38 == sub_15582F0)
 //           v39 = *((float*)a1 + 0x232) > 0.0;
 //       else
 //           v39 = ((__int64(__fastcall*)(__int64*, __int64(__fastcall*)(), void**))v38)(a1, v38, v20);
 //       if (v39)
 //           return *((BYTE*)a1 + 0xB5C);
 //       LOBYTE(v38) = 5;
 //       if ((unsigned __int8)sub_75B870(v2, v38, v20))
 //       {
 //           v53 = *(__int64(__fastcall**)())(*(QWORD*)v2 + 0x1ED8i64);
 //           v54 = v53 == sub_174E4E0 ? (*(DWORD*)(v2 + 0xE60) & 0x8000) != 0 : ((__int64(__fastcall*)(__int64))v53)(v2);
 //           if (!v54)
 //           {
 //               if ((*(unsigned __int8(__fastcall**)(__int64))(*(QWORD*)v2 + 0x2A88i64))(v2))
 //               {
 //                   v56 = a2 + *((float*)a1 + 0x2DD);
 //                   v57 = v56 < dword_7F5BBC8;
 //                   *((float*)a1 + 0x2DD) = v56;
 //                   if (!v57)
 //                   {
 //                       v58 = *a1;
 //                       *((DWORD*)a1 + 0x2DD) = 0;
 //                       (*(void(__fastcall**)(__int64*, __int64, __int64))(v58 + 0x1A80))(a1, v55, 3i64);
 //                   }
 //               }
 //           }
 //       }
 //       if ((float)*(int*)(v2 + 0xCA8) <= *((float*)a1 + 0x2D0)
 //           && !(*(unsigned __int8(__fastcall**)(__int64))(*(QWORD*)v2 + 0x1C30i64))(v2))
 //       {
 //           LOBYTE(v59) = 1;
 //           (*(void(__fastcall**)(__int64*, __int64, QWORD))(*a1 + 0x1A28))(a1, v59, 0i64);
 //           if (*((DWORD*)a1 + 0x222) == 0x8B)
 //               return *((BYTE*)a1 + 0xB5D) == 0;
 //           if ((*(unsigned __int8(__fastcall**)(__int64*, QWORD, QWORD))(*a1 + 0x1A30))(a1, v18, 0i64)
 //               || *((BYTE*)a1 + 0xB5D))
 //           {
 //               goto LABEL_238;
 //           }
 //           v61 = *(__int64(__fastcall**)())(*(QWORD*)v2 + 0xD70i64);
 //           v62 = v61 == sub_6B2A40 ? *(BYTE*)(v2 + 0x5F0) : ((__int64(__fastcall*)(__int64))v61)(v2);
 //           if (v62 == 2)
 //               goto LABEL_238;
 //           v63 = *(__int64(__fastcall**)())(*(QWORD*)v2 + 0xD70i64);
 //           v64 = v63 == sub_6B2A40 ? *(BYTE*)(v2 + 0x5F0) : ((__int64(__fastcall*)(__int64))v63)(v2);
 //           if (v64 == 7)
 //               goto LABEL_238;
 //           v65 = *(__int64(__fastcall**)())(*(QWORD*)v2 + 0xD70i64);
 //           if (v65 == sub_6B2A40)
 //               v66 = *(BYTE*)(v2 + 0x5F0);
 //           else
 //               v66 = ((__int64(__fastcall*)(__int64))v65)(v2);
 //           v67 = v66 == 6;
 //           v68 = *(__int64(__fastcall**)())(*a1 + 0x1A70);
 //           if (v67)
 //           {
 //               if (v68 == sub_8081F0)
 //                   v69 = *((DWORD*)a1 + 0x2CE);
 //               else
 //                   v69 = ((__int64(__fastcall*)(__int64*))v68)(a1);
 //               if ((unsigned int)(v69 - 0x99) > 1)
 //               {
 //                   v70 = 0x99i64;
 //               LABEL_237:
 //                   (*(void(__fastcall**)(__int64*, __int64, void**, QWORD))(*a1 + 0x1578))(a1, v70, v60, 0i64);
 //               }
 //               goto LABEL_238;
 //           }
 //           v71 = v68 == sub_8081F0 ? *((DWORD*)a1 + 0x2CE) : ((__int64(__fastcall*)(__int64*))v68)(a1);
 //           if (v71 == 0x8B || (unsigned int)(v71 - 0x94) <= 4)
 //           {
 //           LABEL_238:
 //               *((DWORD*)a1 + 0x2D0) = 0;
 //               *(__int64*)((char*)a1 + 0xB4C) = 0i64;
 //               v67 = *((DWORD*)a1 + 0x2E9) == 0;
 //               *((DWORD*)a1 + 0x2E8) = 0;
 //               if (!v67)
 //                   sub_5D1F40(a1 + 0x173, 0i64);
 //               sub_5D2790(a1 + 0x173, 8i64);
 //               v67 = *((DWORD*)a1 + 0x2ED) == 0;
 //               *((DWORD*)a1 + 0x2EC) = 0;
 //               if (!v67)
 //                   sub_5D1F40(a1 + 0x175, 0i64);
 //               sub_157DC10(a1 + 0x175);
 //               sub_18DF210(v13);
 //               return *((BYTE*)a1 + 0xB5D) == 0;
 //           }
 //           v60 = *(void***)(*(QWORD*)v2 + 0x12C8i64);
 //           if (v60 == (void**)sub_757F90)
 //           {
 //               v72 = *(DWORD**)(v2 + 0x598);
 //               if (!v72)
 //               {
 //                   v73 = 0;
 //                   goto LABEL_180;
 //               }
 //               v60 = *(void***)(*(QWORD*)v72 + 0x428i64);
 //               if (v60 == &off_1B14EE0)
 //               {
 //                   v73 = v72[0x88];
 //                   goto LABEL_180;
 //               }
 //           }
 //           else
 //           {
 //               v72 = (DWORD*)v2;
 //           }
 //           v73 = ((__int64(__fastcall*)(DWORD*, __int64))v60)(v72, 0xFFFFFFFFi64);
 //       LABEL_180:
 //           switch (v73)
 //           {
 //           case 1:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x94i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 2:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x89i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 3:
 //               v74 = *((DWORD*)a1 + 0x2CD);
 //               if (!v74)
 //               {
 //                   v70 = 0x80i64;
 //                   goto LABEL_237;
 //               }
 //               if (v74 == 1)
 //               {
 //                   v70 = 0x83i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 4:
 //               v75 = *((DWORD*)a1 + 0x2CD);
 //               if (!v75)
 //               {
 //                   v70 = 0x81i64;
 //                   goto LABEL_237;
 //               }
 //               if (v75 == 1)
 //               {
 //                   v70 = 0x84i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 5:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x88i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 6:
 //               v78 = *((DWORD*)a1 + 0x2CD);
 //               if (!v78)
 //               {
 //                   v70 = 0x8Ai64;
 //                   goto LABEL_237;
 //               }
 //               if (v78 == 1)
 //               {
 //                   v70 = 0x82i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 7:
 //               v79 = *((DWORD*)a1 + 0x2CD);
 //               if (!v79)
 //               {
 //                   v70 = 0x90i64;
 //                   goto LABEL_237;
 //               }
 //               if (v79 == 1)
 //               {
 //                   v70 = 0x85i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 8:
 //               v77 = *((DWORD*)a1 + 0x2CD);
 //               if (!v77)
 //               {
 //                   v70 = 0x8Ei64;
 //                   goto LABEL_237;
 //               }
 //               if (v77 == 1)
 //               {
 //                   v70 = 0x8Fi64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 9:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x86i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0xA:
 //               v76 = *((DWORD*)a1 + 0x2CD);
 //               if (!v76)
 //               {
 //                   v70 = 0x8Ci64;
 //                   goto LABEL_237;
 //               }
 //               if (v76 == 1)
 //               {
 //                   v70 = 0x8Di64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0xB:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x91i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0xC:
 //               v80 = *((DWORD*)a1 + 0x2CD);
 //               if (!v80)
 //               {
 //                   v70 = 0x92i64;
 //                   goto LABEL_237;
 //               }
 //               if (v80 == 1)
 //               {
 //                   v70 = 0x93i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0xD:
 //               v81 = *((DWORD*)a1 + 0x2CD);
 //               if (!v81)
 //               {
 //                   v70 = 0xDDi64;
 //                   goto LABEL_237;
 //               }
 //               if (v81 == 1)
 //               {
 //                   v70 = 0xDFi64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0xE:
 //               v82 = *((DWORD*)a1 + 0x2CD);
 //               if (!v82)
 //               {
 //                   v70 = 0xDEi64;
 //                   goto LABEL_237;
 //               }
 //               if (v82 == 1)
 //               {
 //                   v70 = 0xE0i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0xF:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x87i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0x10:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x96i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0x11:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x97i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0x12:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x95i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           case 0x13:
 //               if (!*((DWORD*)a1 + 0x2CD))
 //               {
 //                   v70 = 0x98i64;
 //                   goto LABEL_237;
 //               }
 //               break;
 //           default:
 //               goto LABEL_238;
 //           }
 //           goto LABEL_238;
 //       }
 //       return v19;
	//}
}