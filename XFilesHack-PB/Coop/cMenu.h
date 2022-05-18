#define WIN32_LEAN_AND_MEAN
#pragma warning (disable: 4244 4996 4800)
#include <windows.h>
#include <d3dx9.h>
#include <stdio.h>

#ifndef D3DFONT_RIGHT
#define D3DFONT_RIGHT		0x0008
#endif

#define 	MENUMAXITEMS	100
#define 	MENUFOLDER		1
#define 	MENUTEXT		2
#define 	MENUITEM		3
#define		MENUCAT			4
#define 	MENUITEMFNC		5

typedef struct {
  int  typ;		
  char *txt;	
  char **opt;	
  void *func;
  int  *var;	  
  int  maxvalue;
} tMENU;

class D3D9Menu
{
public:
	D3D9Menu(char *Title = 0)
	{
		Mtitle=Title;	 
		Mpos=0;			
		Mmax=0;		
		Mxofs =150.0f;	// jarak text ke samping
		Mysize=15.0f;	// jarak text ke atas
		Mvisible=1;
		MENU=(tMENU **)malloc(4*MENUMAXITEMS);
		for (int i=0; i<MENUMAXITEMS; i++) MENU[i]=(tMENU *)malloc(sizeof(tMENU));
	}
	~D3D9Menu() {
		for (int i=0; i<MENUMAXITEMS; i++) free(MENU[i]);
		free(MENU);
	}

	char* Header;
	int		Mmax;
	int		Mvisible;
	tMENU		**MENU;
	void SetHeader(char *txt);
	void AddItem(char *txt, char **opt, int *var, int maxvalue);
	void AddItemFunc(char *txt, void* func, int *var, int maxvalue);
	void AddFolder(char *txt, char **opt, int *var, int maxvalue);
	void AddCategory(char *txt, char **opt, int *var, int maxvalue);
	void MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice);
	void Crosshair(LPDIRECT3DDEVICE9 pDevice, D3DVIEWPORT9 pViewPort, D3DCOLOR Color);
	void AddText(char *txt, char *opt);
	void MenuNav(void);
	void DrawTextR(int x,int y,DWORD color,char *text);
	void DrawTextL(int x,int y,DWORD color,char *text);
	void DrawTextC(int x,int y,DWORD color,char *text);
	void FontCreate(LPDIRECT3DDEVICE9 pDevice);
	BOOL Font();
	void OnLostDevice();
	void FontReset();
	void FontRelease();
	BOOL _cInMenu();

private:
	
	char	*Mtitle;
	int 	Mpos;
	float	Mxofs;	  
	float	Mysize;	
	POINT posMenu;
	POINT maxMenu;
	int FindItem();
};


ID3DXFont	*pFont1;

void D3D9Menu::SetHeader(char *txt)
{
	Header = txt;
}

void D3D9Menu::AddFolder(char *txt, char **opt, int *var, int maxvalue)
{
  MENU[Mmax]->typ=MENUFOLDER;
  MENU[Mmax]->txt=txt;
  MENU[Mmax]->opt=opt;
  MENU[Mmax]->var=var;
  MENU[Mmax]->maxvalue=maxvalue;
  Mmax++;
}


void D3D9Menu::AddItem(char *txt, char **opt, int *var, int maxvalue)
{
  MENU[Mmax]->typ=MENUITEM;
  MENU[Mmax]->txt=txt;
  MENU[Mmax]->opt=opt;
  MENU[Mmax]->var=var;
  MENU[Mmax]->maxvalue=maxvalue;
  Mmax++;
}
void D3D9Menu::AddItemFunc(char *txt, void* func, int *var, int maxvalue)
{
  MENU[Mmax]->typ=MENUITEMFNC;
  MENU[Mmax]->txt=txt;
  MENU[Mmax]->opt=NULL;
  MENU[Mmax]->func=func;
  MENU[Mmax]->var=var;
  MENU[Mmax]->maxvalue=maxvalue;
  Mmax++;
}

void D3D9Menu::DrawTextR(int x,int y,DWORD color,char *text)
{
    RECT rect, rect2;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect2, x - 0.1, y + 0.2, x - 0.1, y + 0. );
    pFont1->DrawTextA(NULL,text,-1,&rect, DT_LEFT|DT_NOCLIP, color );
}

BOOL D3D9Menu::Font()
{
	if(pFont1)
		return FALSE;
	else return TRUE;
}

void D3D9Menu::FontCreate(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateFontA(pDevice, 15, 0, FW_EXTRALIGHT | FW_BOLD, 2, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Arial", &pFont1);
}

void D3D9Menu::FontReset()
{
	pFont1->OnLostDevice();
	pFont1->OnResetDevice();
	pFont1->Release();
	pFont1 = NULL;
}


void D3D9Menu::OnLostDevice()
{
	pFont1->OnLostDevice();	
}

void D3D9Menu::FontRelease()
{
	pFont1->Release();
	pFont1 = NULL;
}

void D3D9Menu::DrawTextL(int x,int y,DWORD color,char *text)
{
    RECT rect, rect2;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect2, x - 0.1, y + 0.2, x - 0.1, y + 0. );
    pFont1->DrawTextA(NULL,text,-1,&rect, DT_RIGHT|DT_NOCLIP, color );
}


void D3D9Menu::AddText(char *txt, char *opt)
{
	MENU[Mmax]->typ=MENUTEXT;
	MENU[Mmax]->txt=txt;
	MENU[Mmax]->opt=(char **)opt;
	MENU[Mmax]->var=0;
	MENU[Mmax]->maxvalue=0;
	Mmax++;
}

void D3D9Menu::DrawTextC(int x,int y,DWORD color,char *text){
    RECT rect, rect2;
    SetRect( &rect, x, y, x, y );
	SetRect( &rect2, x - 0.1, y + 0.2, x - 0.1, y + 0. );
    pFont1->DrawTextA(NULL,text,-1,&rect, DT_CENTER|DT_NOCLIP, color );
}

void D3D9Menu::Crosshair(LPDIRECT3DDEVICE9 pDevice, D3DVIEWPORT9 pViewPort, D3DCOLOR Color)
{
	pDevice->GetViewport(&pViewPort);
	D3DRECT RectA, RectB;
	RectA.x1 = (pViewPort.Width/2)-10;
	RectA.x2 = (pViewPort.Width/2)+ 10;
	RectA.y1 = (pViewPort.Height/2);
	RectA.y2 = (pViewPort.Height/2)+1;
	RectB.x1 = (pViewPort.Width/2);
	RectB.x2 = (pViewPort.Width/2)+ 1;
	RectB.y1 = (pViewPort.Height/2)-10;
	RectB.y2 = (pViewPort.Height/2)+10;
	pDevice->Clear(1, &RectA, D3DCLEAR_TARGET, Color, 0,  0);
	pDevice->Clear(1, &RectB, D3DCLEAR_TARGET, Color, 0,  0);
}

void DrawSBorders(int x, int y, int w, int h, D3DCOLOR Color,IDirect3DDevice9* pDevice)
{
	DrawBox(x,  y, 1,  h,Color,pDevice); //Kiri
	DrawBox(x,y+h, w,  1,Color,pDevice); //Bawah
	DrawBox(x,  y, w,  1,Color,pDevice); //Atas
	DrawBox(x+w,y, 1,h+1,Color,pDevice); //Kanan
}

#define DEFAULT_COLOR_SELECTION RED
#define DEFAULT_COLOR_MENUFOLDER YELLOW
#define DEFAULT_COLOR_MENUTEXT SKYBLUE
#define DEFAULT_COLOR_ITEM_OFF WHITE
#define DEFAULT_COLOR_ITEM_ON GREEN

#define DEFAULT_COLOR_BACKGROUND D3DCOLOR_ARGB(220, 50, 50, 50)
#define DEFAULT_COLOR_BORDER GREEN

#define DEFAULT_HDR_COLOR_TEXT SKYBLUE
#define DEFAULT_HDR_COLOR_BACKGROUND D3DCOLOR_ARGB(220, 50, 50, 50)
#define DEFAULT_HDR_COLOR_BORDER SKYBLUE

DWORD MNU_COLOR_SELECTION, MNU_COLOR_MENUFOLDER, MNU_COLOR_MENUTEXT, MNU_COLOR_ITEM_OFF, MNU_COLOR_ITEM_ON, MNU_COLOR_BACKGROUND, MNU_COLOR_BORDER, HDR_COLOR_TEXT, HDR_COLOR_BACKGROUND, HDR_COLOR_BORDER = 0;
bool ColorInitialized = false;
void D3D9Menu::MenuShow(float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
  float posY = y;
  int i, val;
  DWORD color;

  if(ColorInitialized == false){
	  if(strcmp(myClientInfo->product.Alias, "GGH") == 0){
		  MNU_COLOR_SELECTION = RED;
		  MNU_COLOR_MENUFOLDER = YELLOW;
		  MNU_COLOR_MENUTEXT = SKYBLUE;
		  MNU_COLOR_ITEM_OFF = ORANGE;
		  MNU_COLOR_ITEM_ON = GREEN;

		  MNU_COLOR_BACKGROUND = NULL;
		  MNU_COLOR_BORDER = NULL;

		  HDR_COLOR_TEXT = DEFAULT_HDR_COLOR_TEXT;
		  HDR_COLOR_BACKGROUND = NULL;
		  HDR_COLOR_BORDER = NULL;
	  }
	  else
	  {
		  // Default Value
		  MNU_COLOR_SELECTION = DEFAULT_COLOR_SELECTION;
		  MNU_COLOR_MENUFOLDER = DEFAULT_COLOR_MENUFOLDER;
		  MNU_COLOR_MENUTEXT = DEFAULT_COLOR_MENUTEXT;
		  MNU_COLOR_ITEM_OFF = DEFAULT_COLOR_ITEM_OFF;
		  MNU_COLOR_ITEM_ON = DEFAULT_COLOR_ITEM_ON;

		  MNU_COLOR_BACKGROUND = DEFAULT_COLOR_BACKGROUND;
		  MNU_COLOR_BORDER = DEFAULT_COLOR_BORDER;

		  HDR_COLOR_TEXT = DEFAULT_HDR_COLOR_TEXT;
		  HDR_COLOR_BACKGROUND = DEFAULT_HDR_COLOR_BACKGROUND;
		  HDR_COLOR_BORDER = DEFAULT_HDR_COLOR_BORDER;
	  }
	  ColorInitialized = true;
  }
  char text[100];
  if (!Mvisible) return;
  if(MNU_COLOR_BACKGROUND)DrawTransparentBox(x, posY-5, 190, (Mmax*15) + 15, MNU_COLOR_BACKGROUND, pDevice);
  if(MNU_COLOR_BORDER)DrawSBorders(x-1, posY-6, 191, (Mmax*15) + 16, MNU_COLOR_BORDER, pDevice);
  for (i=0; i<Mmax; i++) {
	   val=(MENU[i]->var)?(*MENU[i]->var):0;
	   sprintf(text, "%s", MENU[i]->txt);
	   if (i==Mpos){
		   //sprintf(text, "~> %s <~", MENU[i]->txt);
           color=MNU_COLOR_SELECTION;
	   }
       else if (MENU[i]->typ==MENUFOLDER)
           color=MNU_COLOR_MENUFOLDER;
       else if (MENU[i]->typ==MENUTEXT)
           color=MNU_COLOR_MENUTEXT;
       else
		   color=(val)?MNU_COLOR_ITEM_ON:MNU_COLOR_ITEM_OFF;

	   if (MENU[i]->typ!=MENUITEMFNC) 
	   {
		   if (MENU[i]->typ==MENUFOLDER){
				DrawTextR(x+10, y, color,text);
				y = y + 1;
		   }else{
				DrawTextR(x+10, y, color,text);
		   }
	   }
	   else{
		   DrawTextR(x+10, y, color,text);
	   }

       if (MENU[i]->typ!=MENUITEMFNC) {
		   if (MENU[i]->typ==MENUTEXT)
			   DrawTextR((x+Mxofs), y-1, color,(char *)MENU[i]->opt);
		   else {
			   DrawTextR((x+Mxofs), y-1, color,(char *)MENU[i]->opt[val]);
		   }
		      
	   }
	   else {
		   typedef char* (*func_type)(int);
		   DrawTextR((x+Mxofs), y-1, color,((func_type) MENU[i]->func)(val));
	   }

       y+=Mysize;
  }

  

  if(HDR_COLOR_BACKGROUND)DrawTransparentBox(x, posY-30, 190, 18, HDR_COLOR_BACKGROUND, pDevice);
  if(HDR_COLOR_BORDER)DrawSBorders(x-1, posY-31, 191, 19, HDR_COLOR_BORDER, pDevice);
  if(HDR_COLOR_TEXT)DrawTextC(x+(190/2), posY-29, HDR_COLOR_TEXT, Header);

  
}

void D3D9Menu::MenuNav(void)
{

	if (IsKeyboardKeyDownOnce(DIK_DELETE)) {
		Mvisible = !Mvisible;
	}
//=============================
	if (!Mvisible) return;


	if (IsKeyboardKeyDownOnce(DIK_UP)){//32bit
		do {
			Mpos--;
			if (Mpos<0) Mpos = Mmax - 1;
		} while (MENU[Mpos]->typ == MENUTEXT);
	}

	else if (IsKeyboardKeyDownOnce(DIK_DOWN)){//32bit
		do {
			Mpos++;
			if (Mpos == Mmax) Mpos = 0;
		} while (MENU[Mpos]->typ == MENUTEXT);
	}
	else if (MENU[Mpos]->var) {
		int dir = 0;
//=============================== 32 BIT============================================
		if (IsKeyboardKeyDownOnce(DIK_LEFT) && *MENU[Mpos]->var > 0) dir = -1;
		if (IsKeyboardKeyDownOnce(DIK_RIGHT) && *MENU[Mpos]->var <(MENU[Mpos]->maxvalue - 1)) dir = 1;
		if (dir) {
			*MENU[Mpos]->var += dir;
			if (MENU[Mpos]->typ == MENUFOLDER) 	Mmax = 0;
			if (MENU[Mpos]->typ == MENUCAT) Mmax = 0;
		}
	}
}

