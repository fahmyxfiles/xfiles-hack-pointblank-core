DWORD ModifyTargetBase[100] = {0};
typedef float (__thiscall * tGetLocalTime)(DWORD Base);
tGetLocalTime pGetLocalTime;
float __fastcall hkGetLocalTime(DWORD Base){

	float retVal = pGetLocalTime(Base);
	for(int i = 0; i < 100; i++)
	{
		if(ModifyTargetBase[i] > NULL && ModifyTargetBase[i] == Base){
			if(i == 0)retVal = 2.519999862f;
			if(i == 1 || i == 2){
				if(GetKeyboardPressState(DIK_R)){
					__asm {
						lea edx,retVal
							mov [edx + 3],0x41
					}
				}
			}
			break;
		}
	}
	return retVal;
}

bool bHookedLT = false;
void HookLocalTime()
{
	if(bHookedLT)return;
	pGetLocalTime = (tGetLocalTime)MakePTR((PBYTE)(AddyStruct->XFHPB.Import.i3AiContext_getLocalTime),(DWORD)hkGetLocalTime);
	bHookedLT = true;
}

DWORD pSetEnd;
_declspec(naked) void hkSetEnd(){
	__asm 
	{
		sub esp, 0x8
			push esi
	}
	DWORD dwOrigLine;
	__asm
	{
		mov eax,[esp + 0x10];
		mov [dwOrigLine],eax
	}
	dwOrigLine = SetEndVector->GetSetEndVector(dwOrigLine);
	__asm
	{
		mov eax,[dwOrigLine];
		mov [esp + 0x10],eax
	}
	__asm 
	{
		pop esi
			add esp, 0x8
	}
	__asm jmp pSetEnd;
}

bool bHookedTele = false;
void HookSetEnd()
{
	if(bHookedTele)return;
	SetEndVector = new pSetEndVector();
	pSetEnd = MakePTR((PBYTE)(AddyStruct->XFHPB.Import.i3CollideeLine_SetEnd),(DWORD)hkSetEnd);
	bHookedTele = true;
}
bool tCreated = false;

void WaitForResp()
{
	Sleep(5000);
	pGameCharaManager->RespawnChara(LocalChara->getCharaNetIndex(), true);
	tCreated = false;
}

typedef void (__thiscall* tSetEvent)(void *p, int, const void*, const void*,const void*, const char*, int);
tSetEvent oSetEvent;
void __fastcall hkSetEvent(void *p, void *Unknown, int a1, const void* a2, const void* a3,const void* a4, const char* a5, int a6)
{
	
	if(FeatureStruct->GameHack.ReplaceWeapon.ShieldBM)
	{
		if(a1 == EventCode.Respawn){
			
			if(tCreated == false){
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WaitForResp, 0, 0, 0);
				tCreated = true;
			}
			return;
		}
	}

	if(DebugMode == true){
		sprintf(LastEvent, "void __thiscall CGameContext::SetEvent(int, const void*, const void*,const void*, const char*, int)\na1: 0x%X\n%s\n%s\n%s\n%s\na6: 0x%X", a1, hexDump("a2", (void*)a2, 0x20).c_str(), hexDump("a3", (void*)a3, 0x20).c_str(), hexDump("a4", (void*)a4, 0x20).c_str(), hexDump("a5", (void*)a5, 0x20).c_str(), a6);
		//AddLog(LastEvent);
	}
	if(FeatureStruct->GameHack.Misc.BypassRoomPassword)
	{
		if(a1 == EventCode.JoinRoom && a2 == NULL){
			BYTE UnRoom = 1;
			a2 = &UnRoom;
		}
	}


	return oSetEvent(p, a1, a2, a3, a4, a5, a6); 
}  

void HookSetEvent()
{
	oSetEvent = (tSetEvent)DetourB8((DWORD)(AddyStruct->GameContext.Function.setEvent),(DWORD)hkSetEvent, 10);
}