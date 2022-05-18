#include "InternalDll.h"
//==============================================================================================
DWORD Jump[300] = {0};
//==============================================================================================
//======================== AgPmChainEvent ========================
CDllExport void AgPmChainEvent();
_declspec(naked) void AgPmChainEvent()
{
	__asm jmp dword ptr Jump[0*4];
}
//======================== AgPmCreateSinkConnection ========================
CDllExport void AgPmCreateSinkConnection();
_declspec(naked) void AgPmCreateSinkConnection()
{
	__asm jmp dword ptr Jump[1*4];
}
//======================== AgPmCreateSourceConnection ========================
CDllExport void AgPmCreateSourceConnection();
_declspec(naked) void AgPmCreateSourceConnection()
{
	__asm jmp dword ptr Jump[2*4];
}
//======================== AgPmDestroySinkConnection ========================
CDllExport void AgPmDestroySinkConnection();
_declspec(naked) void AgPmDestroySinkConnection()
{
	__asm jmp dword ptr Jump[3*4];
}
//======================== AgPmDestroySourceConnection ========================
CDllExport void AgPmDestroySourceConnection();
_declspec(naked) void AgPmDestroySourceConnection()
{
	__asm jmp dword ptr Jump[4*4];
}
//======================== AgPmDisableAllEvents ========================
CDllExport void AgPmDisableAllEvents();
_declspec(naked) void AgPmDisableAllEvents()
{
	__asm jmp dword ptr Jump[5*4];
}
//======================== AgPmDisableEvent ========================
CDllExport void AgPmDisableEvent();
_declspec(naked) void AgPmDisableEvent()
{
	__asm jmp dword ptr Jump[6*4];
}
//======================== AgPmDisablePcmEvents ========================
CDllExport void AgPmDisablePcmEvents();
_declspec(naked) void AgPmDisablePcmEvents()
{
	__asm jmp dword ptr Jump[7*4];
}
//======================== AgPmEnableAllEvents ========================
CDllExport void AgPmEnableAllEvents();
_declspec(naked) void AgPmEnableAllEvents()
{
	__asm jmp dword ptr Jump[8*4];
}
//======================== AgPmEnableEvent ========================
CDllExport void AgPmEnableEvent();
_declspec(naked) void AgPmEnableEvent()
{
	__asm jmp dword ptr Jump[9*4];
}
//======================== AgPmEnableLocalEvents ========================
CDllExport void AgPmEnableLocalEvents();
_declspec(naked) void AgPmEnableLocalEvents()
{
	__asm jmp dword ptr Jump[10*4];
}
//======================== AgPmEnablePcmEvents ========================
CDllExport void AgPmEnablePcmEvents();
_declspec(naked) void AgPmEnablePcmEvents()
{
	__asm jmp dword ptr Jump[11*4];
}
//======================== AgPmEventAvailable ========================
CDllExport void AgPmEventAvailable();
_declspec(naked) void AgPmEventAvailable()
{
	__asm jmp dword ptr Jump[12*4];
}
//======================== AgPmEventEnabled ========================
CDllExport void AgPmEventEnabled();
_declspec(naked) void AgPmEventEnabled()
{
	__asm jmp dword ptr Jump[13*4];
}
//======================== AgPmEventLoggingEnabled ========================
CDllExport void AgPmEventLoggingEnabled();
_declspec(naked) void AgPmEventLoggingEnabled()
{
	__asm jmp dword ptr Jump[14*4];
}
//======================== AgPmGetCurrentEventPtr ========================
CDllExport void AgPmGetCurrentEventPtr();
_declspec(naked) void AgPmGetCurrentEventPtr()
{
	__asm jmp dword ptr Jump[15*4];
}
//======================== AgPmGetDeviceType ========================
CDllExport void AgPmGetDeviceType();
_declspec(naked) void AgPmGetDeviceType()
{
	__asm jmp dword ptr Jump[16*4];
}
//======================== AgPmGetEventID ========================
CDllExport void AgPmGetEventID();
_declspec(naked) void AgPmGetEventID()
{
	__asm jmp dword ptr Jump[17*4];
}
//======================== AgPmGetEventName ========================
CDllExport void AgPmGetEventName();
_declspec(naked) void AgPmGetEventName()
{
	__asm jmp dword ptr Jump[18*4];
}
//======================== AgPmGetNextEvent ========================
CDllExport void AgPmGetNextEvent();
_declspec(naked) void AgPmGetNextEvent()
{
	__asm jmp dword ptr Jump[19*4];
}
//======================== AgPmPopEventPtr ========================
CDllExport void AgPmPopEventPtr();
_declspec(naked) void AgPmPopEventPtr()
{
	__asm jmp dword ptr Jump[20*4];
}
//======================== AgPmRegisterEvent ========================
CDllExport void AgPmRegisterEvent();
_declspec(naked) void AgPmRegisterEvent()
{
	__asm jmp dword ptr Jump[21*4];
}
//======================== AgPmRemoveEventChain ========================
CDllExport void AgPmRemoveEventChain();
_declspec(naked) void AgPmRemoveEventChain()
{
	__asm jmp dword ptr Jump[22*4];
}
//======================== AgPmStartLogging ========================
CDllExport void AgPmStartLogging();
_declspec(naked) void AgPmStartLogging()
{
	__asm jmp dword ptr Jump[23*4];
}
//======================== AgPmStopLogging ========================
CDllExport void AgPmStopLogging();
_declspec(naked) void AgPmStopLogging()
{
	__asm jmp dword ptr Jump[24*4];
}
//======================== AgPmSubmitEvent ========================
CDllExport void AgPmSubmitEvent();
_declspec(naked) void AgPmSubmitEvent()
{
	__asm jmp dword ptr Jump[25*4];
}
//======================== AgPmSubmitPerfCounterConfig ========================
CDllExport void AgPmSubmitPerfCounterConfig();
_declspec(naked) void AgPmSubmitPerfCounterConfig()
{
	__asm jmp dword ptr Jump[26*4];
}
//======================== AgPmSubmitTimerConfig ========================
CDllExport void AgPmSubmitTimerConfig();
_declspec(naked) void AgPmSubmitTimerConfig()
{
	__asm jmp dword ptr Jump[27*4];
}


typedef LOAD_DLL_INFO* MODULE_HANDLE;
MODULE_HANDLE LoadModule(const void* data, int size)
{
	LOAD_DLL_INFO* p = new LOAD_DLL_INFO;
	DWORD res = LoadDLLFromMemory(data, size, 0, p);
	if (res != ELoadDLLResult_OK)
	{
		delete p;
		return NULL;
	}
	return p;
}

bool UnloadModule(MODULE_HANDLE handle)
{
	bool res = FALSE != UnloadDLL(handle);
	delete handle;
	return res;
}

void* GetModuleFunction(MODULE_HANDLE handle, const char* func_name)
{
	return (void*)myGetProcAddress_LoadDLLInfo(handle, func_name);
}

int get_file_size(std::string filename) // path to file
{
	FILE *p_file = NULL;
	p_file = fopen(filename.c_str(),"rb");
	if(p_file){
		fseek(p_file,0,SEEK_END);
		int size = ftell(p_file);
		fclose(p_file);
		return size;
	}
	return 0;
}



DWORD InitializeInternal(void)
{
	
	MODULE_HANDLE origLib = LoadModule((const void*)rawData, sizeof(rawData));
	if (!origLib)
	{
		MessageBoxA(0, "Internal Failed To Load!", "ERR!", MB_OK);
		return 1;
	}
	Jump[0] = (DWORD)GetModuleFunction(origLib,"AgPmChainEvent");
	Jump[1] = (DWORD)GetModuleFunction(origLib,"AgPmCreateSinkConnection");
	Jump[2] = (DWORD)GetModuleFunction(origLib,"AgPmCreateSourceConnection");
	Jump[3] = (DWORD)GetModuleFunction(origLib,"AgPmDestroySinkConnection");
	Jump[4] = (DWORD)GetModuleFunction(origLib,"AgPmDestroySourceConnection");
	Jump[5] = (DWORD)GetModuleFunction(origLib,"AgPmDisableAllEvents");
	Jump[6] = (DWORD)GetModuleFunction(origLib,"AgPmDisableEvent");
	Jump[7] = (DWORD)GetModuleFunction(origLib,"AgPmDisablePcmEvents");
	Jump[8] = (DWORD)GetModuleFunction(origLib,"AgPmEnableAllEvents");
	Jump[9] = (DWORD)GetModuleFunction(origLib,"AgPmEnableEvent");
	Jump[10] = (DWORD)GetModuleFunction(origLib,"AgPmEnableLocalEvents");
	Jump[11] = (DWORD)GetModuleFunction(origLib,"AgPmEnablePcmEvents");
	Jump[12] = (DWORD)GetModuleFunction(origLib,"AgPmEventAvailable");
	Jump[13] = (DWORD)GetModuleFunction(origLib,"AgPmEventEnabled");
	Jump[14] = (DWORD)GetModuleFunction(origLib,"AgPmEventLoggingEnabled");
	Jump[15] = (DWORD)GetModuleFunction(origLib,"AgPmGetCurrentEventPtr");
	Jump[16] = (DWORD)GetModuleFunction(origLib,"AgPmGetDeviceType");
	Jump[17] = (DWORD)GetModuleFunction(origLib,"AgPmGetEventID");
	Jump[18] = (DWORD)GetModuleFunction(origLib,"AgPmGetEventName");
	Jump[19] = (DWORD)GetModuleFunction(origLib,"AgPmGetNextEvent");
	Jump[20] = (DWORD)GetModuleFunction(origLib,"AgPmPopEventPtr");
	Jump[21] = (DWORD)GetModuleFunction(origLib,"AgPmRegisterEvent");
	Jump[22] = (DWORD)GetModuleFunction(origLib,"AgPmRemoveEventChain");
	Jump[23] = (DWORD)GetModuleFunction(origLib,"AgPmStartLogging");
	Jump[24] = (DWORD)GetModuleFunction(origLib,"AgPmStopLogging");
	Jump[25] = (DWORD)GetModuleFunction(origLib,"AgPmSubmitEvent");
	Jump[26] = (DWORD)GetModuleFunction(origLib,"AgPmSubmitPerfCounterConfig");
	Jump[27] = (DWORD)GetModuleFunction(origLib,"AgPmSubmitTimerConfig");
	
	return 0;
}