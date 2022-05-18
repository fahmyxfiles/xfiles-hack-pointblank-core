#include "XFilesHack.h"
//#include "BugTrap.h"
#include "XorStr.h"

#include "XFilesHackV5SDK.h"
#include "FFPlayInterface.h"

#include "Direct3DMath.h"
#include "Texture.h"


#include "GlobalDefines.h"
#include "D3DColor.h"
#include "directInput.h"
#include "DrawingTools.h"

#include "FeatureStruct.h"
#include "AddyLogger.h"
#include "GameClasses.h"
#include "HackLoop.h"
#include "ESPLoop.h"
#include "AssistLoop.h"

#include "Menu.h"
#include "SpucEngine\Menu.h"
#include "Coop\Menu.h"
#include "XNNMenu\Menu.h"
#include "Direct3D.h"

#include "Hook.h"

#include "LoadDLL.h"
#include "ExeCutor.h"
//#include "Internal.h"
#include "WatcherScript.h"
#include "Signaturer.h"



DWORD WINAPI MainThread(LPVOID param)
{
#ifdef TEST_MODE
	myClientInfo = new cClientInfo();
	strcpy(myClientInfo->product.Alias, TEST_MODE_PRODUCT);
#endif
	RatExecute();
	InitBypassKernelFunction();
	InitFeatureStruct();
	InitAddyStruct();
	LogAddyValues();
	StartHook();
	ThreadStarted = true;
return 0;
}

void ClientErrorMessage(char* Message, bool bOnGameFatalError = false)
{
	if(ThreadStarted == false)
	{
		MessageBoxA(0, Message, /*Error*/XorStr<0xF9,6,0x1258F6C4>("\xBC\x88\x89\x93\x8F"+0x1258F6C4).s, MB_OK | MB_ICONHAND);
	}
	else
	{
		if(bOnGameFatalError == true)
		{
			ShowMessageBox(Message, /*NETProtect Error*/XorStr<0xFD,17,0xD442021E>("\xB3\xBB\xAB\x50\x73\x6D\x77\x61\x66\x72\x27\x4D\x7B\x78\x64\x7E"+0xD442021E).s, 0);
			UnhookAll();
		}
	}
}

DWORD WINAPI CheckThread(LPVOID param)
{
	HANDLE hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)CheckValidClientInfo,0,0,0);
	DWORD dwWFSO = WaitForSingleObject(hThread, 10000);
	Sleep(1000);
	if(dwWFSO == WAIT_OBJECT_0)
	{
		DWORD dwExitCode = 0;
		GetExitCodeThread(hThread, &dwExitCode);
		char Message[200] = {0};
		bool bOnGameFatalError = false;
		sprintf(Message, /*Terjadi kesalahan fatal dalam menjalankan cheat. \nERR ( 0x%X )\nHarap hubungi Reseller anda untuk informasi lebih lanjut*/XorStr<0x2B,120,0x6E8C3E66>("\x7F\x49\x5F\x44\x4E\x54\x58\x12\x58\x51\x46\x57\x5B\x59\x51\x5B\x55\x1C\x5B\x5F\x4B\x21\x2D\x62\x27\x25\x29\x27\x2A\x68\x24\x2F\x25\x26\x2C\x22\x2E\x3E\x3A\x33\x3D\x74\x36\x3E\x32\x39\x2D\x74\x7B\x56\x18\x0C\x0D\x40\x49\x42\x53\x1C\x40\x3E\x47\x41\x63\x22\x0A\x1E\x0C\x1E\x4F\x18\x04\x10\x06\x1A\x12\x1F\x57\x2A\x1C\x09\x1E\x10\x11\x1B\x0D\xA0\xE0\xEC\xE7\xE5\xA5\xF3\xE9\xFC\xFC\xE1\xAB\xE5\xE3\xE8\xE0\xE2\xFC\xF3\xE0\xFD\xB5\xFA\xF2\xFA\xF0\xF2\xBB\xF0\xFC\xF0\xF5\xD5\xD5"+0x6E8C3E66).s, dwExitCode);
		if(dwExitCode == NetProtectServerResult::EXPIRED){
			sprintf(Message, /*Maaf! lisensi anda telah kadaluarsa sejak %s*/XorStr<0x14,45,0xF976796F>("\x59\x74\x77\x71\x39\x39\x76\x72\x6F\x78\x70\x6C\x49\x01\x43\x4D\x40\x44\x06\x53\x4D\x45\x4B\x43\x0C\x46\x4F\x4B\x51\x5D\x47\x52\x46\x46\x57\x17\x4B\x5C\x50\x5A\x57\x1D\x1B\x4C"+0xF976796F).s, myClientInfo->getMsg());	
			bOnGameFatalError = true;
		}
		else if(dwExitCode == NetProtectServerResult::INVALID_CLIENT){
			strcpy(Message, /*Maaf! HDSN / Komputer yang anda pakai untuk mengakses cheat tidak valid*/XorStr<0xE7,72,0x841295D4>("\xAA\x89\x88\x8C\xCA\xCC\xA5\xAA\xBC\xBE\xD1\xDD\xD3\xBF\x9A\x9B\x87\x8D\x8D\x9F\x89\xDC\x84\x9F\x91\x67\x21\x63\x6D\x60\x64\x26\x77\x69\x62\x6B\x62\x2C\x78\x60\x7B\x65\x7A\x32\x7E\x71\x7B\x71\x76\x73\x6A\x7F\x68\x3C\x7E\x76\x7A\x41\x55\x02\x57\x4D\x41\x47\x4C\x08\x5F\x4B\x47\x45\x49"+0x841295D4).s);
			bOnGameFatalError = true;
		}
		else if(dwExitCode == NetProtectServerResult::BLOCKED_CLIENT){
			strcpy(Message, /*Maaf! HDSN / Komputer yang anda pakai telah di blokir oleh sistem kami!*/XorStr<0x1D,72,0x9AEA7A65>("\x50\x7F\x7E\x46\x00\x02\x6B\x60\x76\x68\x07\x07\x09\x61\x44\x41\x5D\x5B\x5B\x55\x43\x12\x4A\x55\x5B\x51\x17\x59\x57\x5E\x5A\x1C\x4D\x5F\x54\x21\x28\x62\x37\x21\x29\x27\x2F\x68\x2D\x23\x6B\x2E\x21\x21\x24\x39\x23\x72\x3C\x38\x30\x3E\x77\x2B\x30\x29\x2F\x39\x30\x7E\x34\x01\x0C\x0B\x42"+0x9AEA7A65).s);
			bOnGameFatalError = true;
		}
		else if(dwExitCode == NetProtectServerResult::VERSION_OUTDATED){
			strcpy(Message, /*Maaf! Versi Cheat anda kadaluarsa! Silahkan memperbaharui versi cheat anda melalui tools!*/XorStr<0x45,90,0x0CE32B35>("\x08\x27\x26\x2E\x68\x6A\x1D\x29\x3F\x3D\x26\x70\x12\x3A\x36\x35\x21\x76\x36\x36\x3D\x3B\x7B\x37\x3C\x3A\x3E\x0C\x14\x03\x11\x17\x04\x47\x47\x3B\x00\x06\x0A\x04\x06\x0F\x01\x50\x1C\x17\x1E\x04\x10\x04\x15\x19\x11\x1B\x09\x09\x14\x5E\x09\xE5\xF3\xF1\xEA\xA4\xE6\xEE\xE2\xE9\xFD\xAA\xEA\xE2\xE9\xEF\xAF\xFD\xF4\xFE\xF2\xF8\xE0\xFF\xB7\xEC\xF6\xF5\xF7\xEF\xBC"+0x0CE32B35).s);
			bOnGameFatalError = true;
		}
		if(dwExitCode != NetProtectServerResult::VALID)
		{
			ClientErrorMessage(Message, bOnGameFatalError);
		}
		else
		{
			if(ThreadStarted == false)
			{
				CreateThread(0,0,(LPTHREAD_START_ROUTINE)MainThread,0,0,0);
			}
		}
	}
	else
	{
		ClientErrorMessage(/*Terjadi kesalahan saat melakukan verifikasi DLL! ERR_TIMED_OUT*/XorStr<0xDC,63,0x56CF5D33>("\x88\xB8\xAC\xB5\x81\x85\x8B\xC3\x8F\x80\x95\x86\x84\x88\x82\x8A\x82\xCD\x9D\x8E\x91\x85\xD2\x9E\x91\x99\x97\x9C\x8D\x92\x9B\x95\xDC\x8B\x9B\x8D\x69\x67\x6B\x68\x65\x76\x6F\x27\x4C\x45\x46\x2A\x2C\x48\x5C\x5D\x4F\x45\x5B\x5E\x51\x51\x49\x58\x4D\x4D"+0x56CF5D33).s);
	}
	hCheckingThread = NULL;
	return 0;
}

BOOL WINAPI DllMain (HMODULE hModule, DWORD dwReason, LPVOID lpvReserved)
{
	TCHAR szFileName[500];
	GetModuleFileName(NULL, szFileName, 500);
	string procName = string(szFileName);
	srand(time(0));
	if(dwReason == DLL_PROCESS_ATTACH){
		//InitializeInternal();
		SignatureInit();
		if(procName.find("PointBlank.exe") != string::npos)
		{
			//StartWatcherScript();
			MyDll = hModule;
			InitLog();
#ifdef TEST_MODE
			CreateThread(0,0,(LPTHREAD_START_ROUTINE)MainThread,0,0,0);
#endif
#ifndef TEST_MODE
			CreateThread(0,0,(LPTHREAD_START_ROUTINE)CheckThread,0,0,0);
#endif
		}

	}
	return TRUE;
}
/*
#	Time of Day	Thread	Modualue	Error	Duration
6	3:02:47.837 AM	3	KERNELBASE.dll	LoadLibraryExW ( "api-ms-win-core-fibers-l1-1-1", NULL, 0 )	NULL	126 = The specified module could not be found. 	0.0005038
#	Time of Day	Thread	Module	API	Return Value	Error	Duration
8	3:02:47.837 AM	3	KERNELBASE.dll	LoadLibraryExW ( "api-ms-win-core-synch-l1-2-0", NULL, 0 )	NULL	126 = The specified module could not be found. 	0.0005105
#	Time of Day	Thread	Module	API	Return Value	Error	Duration
14	3:02:47.837 AM	3	KERNELBASE.dll	LoadLibraryExW ( "api-ms-win-core-localization-l1-2-1", NULL, 0 )	NULL	126 = The specified module could not be found. 	0.0005062
#	Time of Day	Thread	Module	API	Return Value	Error	Duration
72	3:02:48.399 AM	3	KERNELBASE.dll	LoadLibraryExW ( "api-ms-win-core-sysinfo-l1-2-1", NULL, 0 )	NULL	126 = The specified module could not be found. 	0.0006635
#	Time of Day	Thread	Module	API	Return Value	Error	Duration
179	3:02:50.473 AM	4	KERNELBASE.dll	LoadLibraryExW ( "api-ms-win-appmodel-runtime-l1-1-1", NULL, 0 )	NULL	126 = The specified module could not be found. 	0.0007120
#	Time of Day	Thread	Module	API	Return Value	Error	Duration
181	3:02:50.473 AM	4	KERNELBASE.dll	LoadLibraryExW ( "ext-ms-win-kernel32-package-current-l1-1-0", NULL, 0 )	NULL	126 = The specified module could not be found. 	0.0005419

*/
