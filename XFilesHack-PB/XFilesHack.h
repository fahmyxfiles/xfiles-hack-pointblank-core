#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <d3dx9.h>
#include <Psapi.h>
#include <ctime>
#include <vector>
#include <sstream>
#include <string.h>
#include <string> 
#include <tchar.h>
#include <Psapi.h>
#include <tlhelp32.h>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma warning (disable : 4996 4244 4018)
using namespace std;
using namespace rapidjson;
#define CDllExport extern "C" __declspec( dllexport )
#define DllExport __declspec( dllexport )
#define FUNC_NOINLINE _declspec(noinline)

//#define TEST_MODE
#define TEST_MODE_PRODUCT "XFH"

char inParamCID [50];
char inParamLC [150];
bool paramInput = false;
//-------------------------------------------------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 Stream_Data;
LPDIRECT3DDEVICE9 npDevice;
D3DVIEWPORT9 g_ViewPort;
LPDIRECT3DTEXTURE9 Red;
LPDIRECT3DTEXTURE9 Blue;
LPD3DXLINE g_pLine  = NULL; //D3D Line
D3DDEVICE_CREATION_PARAMETERS dcParam;

LPD3DXFONT MenuFont = NULL;
LPD3DXFONT g_pFont = NULL;

HMODULE MyDll;

UINT Offset, Stride = 0;

DWORD ScreenCenterX, ScreenCenterY;
bool bInitDIP = false;
bool hooked = false;
bool ClassReady = false;
bool ThreadStarted = false;
typedef HRESULT (WINAPI* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene = NULL;
typedef HRESULT (WINAPI* tDrawIndexedPrimitive)(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount);
tDrawIndexedPrimitive oDrawIndexedPrimitive = NULL;
typedef HRESULT (WINAPI* tReset)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
tReset oReset = NULL;

FUNC_NOINLINE void AddLog( const char *text, ...);
string hexDump (char *desc, void *addr, int len);

DWORD WINAPI CheckThread(LPVOID param);

int EnableVisibleCheck = true;

// UserInfoBuffer
StringBuffer sUserInfoBuffer;

// HackerPlayerList Buffer
Document dHackingNetworkListBuffer;
bool IsPlayerOnHackingNetwork(const char* Nickname)
{
	for(int i = 0; i < dHackingNetworkListBuffer.Size(); i++)
	{
		if(strcmp(dHackingNetworkListBuffer[i]["Nickname"].GetString(), Nickname) == 0)
		{
			return true;
		}
	}
	return false;
}
const char* GetPlayerHackingNetworkProduct(const char* Nickname)
{
	for(int i = 0; i < dHackingNetworkListBuffer.Size(); i++)
	{
		if(strcmp(dHackingNetworkListBuffer[i]["Nickname"].GetString(), Nickname) == 0)
		{
			return dHackingNetworkListBuffer[i]["ProductName"].GetString();
		}
	}
	return "";
}

#ifdef _MSC_VER
    #if _MSC_VER >= 1600
        #include <cstdint>
    #else
        typedef __int8              int8_t;
        typedef __int16             int16_t;
        typedef __int32             int32_t;
        typedef __int64             int64_t;
        typedef unsigned __int8     uint8_t;
        typedef unsigned __int16    uint16_t;
        typedef unsigned __int32    uint32_t;
        typedef unsigned __int64    uint64_t;
    #endif
#elif __GNUC__ >= 3
    #include <cstdint>
#endif

typedef int8_t      s8;
typedef int16_t     s16;
typedef int32_t     s32;
typedef int64_t     s64;
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;


#define JunkCode				\
    __asm{push eax}            \
    __asm{xor eax, eax}        \
    __asm{setpo al}            \
    __asm{push edx}            \
    __asm{xor edx, eax}        \
    __asm{sal edx, 2}        \
    __asm{xchg eax, edx}    \
    __asm{pop edx}            \
    __asm{or eax, ecx}        \
    __asm{pop eax} 

 

#define SCRAMBLECODE_START \
  JunkCode \
  __asm _emit 0xEB \
  __asm _emit 0x09 \
  __asm _emit 0xE4 \
  __asm _emit 0x39 \
  __asm _emit 0x5F \
  __asm _emit 0xE5 \
  __asm _emit 0x3C \
  __asm _emit 0xFB \
  __asm _emit 0x4B \
  __asm _emit 0x33 \
  __asm _emit 0xFC \
  JunkCode \
  __asm _emit 0xEB \
  __asm _emit 0x04 \
  __asm _emit 0xD9 \
  __asm _emit 0x59 \
  __asm _emit 0x96 \
  __asm _emit 0x17 \
  JunkCode \
  __asm _emit 0x74 \
  __asm _emit 0x05 \
  __asm _emit 0x75 \
  __asm _emit 0x03 \
  __asm _emit 0x6A \
  __asm _emit 0xFF \
  __asm _emit 0xE8 \
  JunkCode \
  __asm _emit 0x74 \
  __asm _emit 0x05 \
  __asm _emit 0x75 \
  __asm _emit 0x03 \
  __asm _emit 0x6A \
  __asm _emit 0xFF \
  __asm _emit 0xE8  

#define SCRAMBLECODE_END \
  __asm _emit 0xF8 \
  __asm _emit 0x73 \
  __asm _emit 0x04 \
  __asm _emit 0x68 \
  __asm _emit 0x05 \
  __asm _emit 0xE8 \
  __asm _emit 0xE8 \
  JunkCode \
  __asm _emit 0xEB \
  __asm _emit 0x09 \
  __asm _emit 0xE4 \
  __asm _emit 0x39 \
  __asm _emit 0x5F \
  __asm _emit 0xE5 \
  __asm _emit 0x3C \
  __asm _emit 0xFB \
  __asm _emit 0x4B \
  __asm _emit 0x33 \
  __asm _emit 0xFC \
  JunkCode \
  __asm _emit 0xEB \
  __asm _emit 0x04 \
  __asm _emit 0xD9 \
  __asm _emit 0x59 \
  __asm _emit 0x96 \
  __asm _emit 0x17 \
  JunkCode \
  __asm _emit 0x74 \
  __asm _emit 0x05 \
  __asm _emit 0x75 \
  __asm _emit 0x03 \
  __asm _emit 0x6A \
  __asm _emit 0xFF \
  __asm _emit 0xE8  

