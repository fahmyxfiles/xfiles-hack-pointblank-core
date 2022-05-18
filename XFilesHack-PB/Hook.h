DWORD m_pCaps, SelectShader = 0;

class i3Shader
{
public:

};


class i3RenderContext;
class i3Vertex;
class i3DrawPrimSize;
class m_pCaps;

class i3RenderContext
{
public:
char _0x0000[20]; //0x0000 
	DWORD DrawCount; //0x0014 
char _0x0018[224];
	DWORD DrawPrimCount; //0x00F8 
char _0x00FC[100];
	BYTE VertexCount; //0x0160 
char _0x0161[1987];
	i3Vertex* Vertex; //0x0924 
char _0x0928[448];
	i3Shader* Shader; //0x0AE8 
char _0x0AEC[18620];
	LPDIRECT3DDEVICE9 pDevice; //0x53A8 
char _0x53AC[168];
	DWORD DrawSize; //0x5454 
char _0x5458[4];
	i3DrawPrimSize* DrawPrimitiveSize; //0x545C 
char _0x5460[8];
	DWORD dwSize; //0x5468 
	DWORD isReady; //0x546C 

};//Size=0x5DEC

class i3Vertex
{
public:
char _0x0000[368];
	DWORD NumVertices; //0x0170 

};//Size=0x0174

class i3DrawPrimSize
{
public:
char _0x0000[392];
	DWORD Count; //0x0188 
char _0x018C[84];
	LPDIRECT3DVERTEXBUFFER9 VertexBufferData; //0x01E0 

};

class cCaps
{
public:
char _0x0000[336];
	DWORD ShaderMode; //0x0150 

};//Size=0x0184

int Counter = 0;
void __fastcall hkEndRender(void *p, void *Unknown)
{
	i3RenderContext* pRC = (i3RenderContext*)(p);
	
	if(Counter == 0 || Counter == 2)
	{
		hkEndScene(pRC->pDevice);
		if(Counter == 0)Counter = 1;
	}
	else if(Counter == 1)
	{
		pRC->pDevice->EndScene();
		Counter = 2;
	}
	

}

typedef void (__thiscall* tSelectShader)(void *p, i3Shader* , int);
tSelectShader oSelectShader;
i3Shader* __fastcall myDrawIndexedPrim(void *p, void *Unknown, i3Shader *Shader, D3DPRIMITIVETYPE I3G_PRIMITIVE, unsigned int startIdx, unsigned int primCount)
{
	oSelectShader = (tSelectShader)SelectShader;
	i3RenderContext* pRC = (i3RenderContext*)(p);
	
	pRC->DrawPrimCount += primCount;
	pRC->DrawCount++;


	cCaps* pCaps = (cCaps*)(*(DWORD*)(m_pCaps));	
	if(pCaps->ShaderMode > 0)
	{
		oSelectShader(p, Shader, 0);
	}
	if(pRC->VertexCount > 0 && pRC->isReady == 1)
	{
		DWORD dwOffset = pRC->dwSize * pRC->DrawPrimitiveSize->Count;
		if(pRC->DrawSize > 0){
			for(unsigned i = 0; i < pRC->DrawSize; i++)
			{
				pRC->pDevice->SetStreamSource(1, pRC->DrawPrimitiveSize->VertexBufferData, dwOffset, 0);
				hkDrawIndexedPrimitive(pRC->pDevice, I3G_PRIMITIVE, 0, 0, pRC->Vertex->NumVertices, startIdx, primCount);
				//pRC->pDevice->DrawIndexedPrimitive(I3G_PRIMITIVE, 0, 0, pRC->Vertex->NumVertices, startIdx, primCount);
				dwOffset += pRC->DrawPrimitiveSize->Count;
			}
		}
	}
	else {
		hkDrawIndexedPrimitive(pRC->pDevice, I3G_PRIMITIVE, 0, 0, pRC->Vertex->NumVertices, startIdx, primCount);
		//pRC->pDevice->DrawIndexedPrimitive(I3G_PRIMITIVE, 0, 0, pRC->Vertex->NumVertices, startIdx, primCount);
	}
	return pRC->Shader;
}

typedef int (__thiscall* tResetDevice)(void *p);
tResetDevice oResetDevice;
int __fastcall hkResetDevice(void *p, void *Unknown)
{
	
	ResetD3DInterface();
	return oResetDevice(p);
}

void HookResetDevice()
{
	oResetDevice = (tResetDevice)DetourB8((DWORD)(GetProcAddress(GetModuleHandle(MainModule->i3GfxDx), "?ResetDevice@i3RenderContext@@QAEHXZ")),(DWORD)hkResetDevice, 7);
}

HWND FirstHWND = NULL;
HWND SecondHWND = NULL;
BOOL CALLBACK MyWindowEnumerator(HWND hwnd,LPARAM lParam)
{
    DWORD lpdwProcessId;
    GetWindowThreadProcessId(hwnd,&lpdwProcessId);
    if(lpdwProcessId==lParam)
    {
        FirstHWND = hwnd;
		if(SecondHWND == NULL)SecondHWND = hwnd;
        return FALSE;
    }
    return TRUE;
}

void ThreadAfterXigncodeLoad()
{
	Sleep(1000);
	while(true)
	{
		EnumWindows(MyWindowEnumerator, GetCurrentProcessId());
		if(SecondHWND != FirstHWND)break;
		Sleep(50);
	}
	Sleep(1000);
	HookSetEvent();
	
}

DWORD xMakePTR(BYTE *MemoryTarget, DWORD FunctionTarget)
{
	//XFiles make PTR
	//2014 FahmyXFiles
	DWORD dwOldProtect;
	DWORD dwRetn = *(DWORD*)(MemoryTarget);

	//VirtualProtect(MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	oVirtualProtectEx((HANDLE)-1, (VOID*)MemoryTarget, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect );
	*((DWORD *)(MemoryTarget)) = FunctionTarget;
	oVirtualProtectEx((HANDLE)-1, (VOID*)MemoryTarget, 4, dwOldProtect, &dwOldProtect );
	return dwRetn;
}

DWORD dwHookBackup[3] = {0};

void StartHook()
{
	//CreateThread(0,0,(LPTHREAD_START_ROUTINE)ThreadAfterXigncodeLoad,0,0,0);
	//Sleep(1000);
	
	HookLocalTime();
	HookSetEnd();
	InitializeCollideeLine();
	m_pCaps		 = (DWORD)GetProcAddress(GetModuleHandle(MainModule->i3GfxDx),/*?m_pCaps@i3RenderContext@@1PAVi3GfxCaps@@A*/XorStr<0x62,43,0x8B7A8862>("\x5D\x0E\x3B\x15\x25\x06\x18\x1A\x2A\x02\x5F\x3F\x0B\x01\x14\x14\x00\x30\x1B\x1B\x02\x12\x00\x0D\x3A\x3B\x4D\x2D\x3F\x29\xE9\xB2\xC5\xE5\xFC\xC6\xE7\xF7\xFB\xC9\xCA\xCA"+0x8B7A8862).s);
	SelectShader = (DWORD)GetProcAddress(GetModuleHandle(MainModule->i3GfxDx),/*?SelectShader@i3RenderContext@@QAEXPAVi3Shader@@H@Z*/XorStr<0xC5,52,0xC83CBDC7>("\xFA\x95\xA2\xA4\xAC\xA9\xBF\x9F\xA5\xAF\xAB\xB5\xA3\x92\xBA\xE7\x87\xB3\xB9\xBC\xBC\xA8\x98\xB3\xB3\xAA\xBA\x98\x95\xA2\xA3\xB5\xA4\xA3\xBF\xB8\xA8\xBC\x82\xDF\xBE\x86\x8E\x94\x94\x80\xB3\xB4\xBD\xB6\xAD"+0xC83CBDC7).s);
	
	dwHookBackup[0] = xMakePTR((PBYTE)AddyStruct->XFHPB.Import.i3RenderContext_EndRender,(DWORD)hkEndRender);
	dwHookBackup[1] = xMakePTR((PBYTE)AddyStruct->XFHPB.Import.i3RenderContext_DrawIndexedPrim ,(DWORD)myDrawIndexedPrim);

}

void UnhookAll()
{
	// Reset Features
	ZeroMemory(FeatureStruct, sizeof(sFeatureStruct));

	xMakePTR((PBYTE)AddyStruct->XFHPB.Import.i3RenderContext_EndRender,(DWORD)dwHookBackup[0]);
	xMakePTR((PBYTE)AddyStruct->XFHPB.Import.i3RenderContext_DrawIndexedPrim ,(DWORD)dwHookBackup[1]);
}