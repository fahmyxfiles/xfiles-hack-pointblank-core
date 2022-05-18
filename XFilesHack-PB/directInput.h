#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")

/////////////////////////////////////////////////////////////////////////////////
LPDIRECTINPUT8 Input;
void InitializeDirectInput();
void UpdateDirectInput();
void DirectInputLoop();
/////////////////////////////////////////////////////////////////////////////////
LPDIRECTINPUTDEVICE8 Keyboard;
void InitializeKeyboard();
void UpdateKeyboard();
char* getKeyboardState();   
bool IsKeyboardKeyDownOnce(int Index);

char KeyboardState[256];
bool KeyPressed[256] = {0};
/////////////////////////////////////////////////////////////////////////////////
void InitializeDirectInput()
{
	 DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&Input, NULL);
}
void UpdateDirectInput()
{
	if(Keyboard == NULL)InitializeKeyboard();
	else UpdateKeyboard();
}
void DirectInputLoop()
{

	if(Input == NULL)InitializeDirectInput();
	else UpdateDirectInput();
}
/////////////////////////////////////////////////////////////////////////////////
void InitializeKeyboard()
{  
    Input->CreateDevice(GUID_SysKeyboard, &Keyboard, NULL);
    Keyboard->SetDataFormat(&c_dfDIKeyboard);
    Keyboard->SetCooperativeLevel(GetForegroundWindow(), DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
    Keyboard->Acquire();
}
void UpdateKeyboard()
{
	HRESULT res = Keyboard->GetDeviceState(sizeof(KeyboardState),(LPVOID)&KeyboardState); 
	if FAILED(res)
	{ 
		Keyboard->Release();
		Keyboard = NULL;
		return;
	}
}
bool GetKeyboardPressState(int nIndex)
{
    return (KeyboardState[nIndex] && 0x80);
}
bool IsKeyboardKeyDownOnce(int Index){
	if(GetKeyboardPressState(Index)){
		if(KeyPressed[Index] == false){
			KeyPressed[Index] = true;
			return true;
		} else return false;
	} else KeyPressed[Index] = false;
	return false;
}