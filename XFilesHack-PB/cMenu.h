#define ItemSize 18
//Normal Colors
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED				D3DCOLOR_ARGB(255, 255, 000, 000)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLUE			D3DCOLOR_ARGB(255, 000, 000, 255) 
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define PURPLE			D3DCOLOR_ARGB(255, 125, 000, 255) 
#define GREY			D3DCOLOR_ARGB(255, 128, 128, 128) 
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define DEEPSKYBLUE     D3DCOLOR_ARGB(255, 30, 144, 255)
#define DEEPSKYBLUE1     D3DCOLOR_ARGB(255, 0, 145, 181)
#define CHOCOLATE2      D3DCOLOR_ARGB(255, 238, 118, 33)
#define GOLD2			D3DCOLOR_ARGB(255, 238, 201, 0) 
#define PURPLE1			D3DCOLOR_ARGB(255,77, 0, 12) 
#define GRE2			D3DCOLOR_ARGB(200,27,27, 27) 
#define DEEPSKYBLUE3     D3DCOLOR_ARGB(255,48, 164, 200)
#define DEEPSKYBLUE4     D3DCOLOR_ARGB(255, 3, 78, 144)
#define MENUON          D3DCOLOR_ARGB(250, 0, 255, 127) 
#define MENUOFF         D3DCOLOR_ARGB(255, 152, 245, 255)
#define FOLDER          D3DCOLOR_ARGB(255, 238, 201, 0)
#define VERSION			D3DCOLOR_ARGB(150, 000, 255, 000)
#define C_CUR			D3DCOLOR_ARGB(255, 238, 201, 0)
#define C_V             D3DCOLOR_ARGB(255, 255, 0  , 255)
#define MENUCOLOR_F     D3DCOLOR_ARGB(255, 255, 250, 250)
#define C_TITL			D3DCOLOR_ARGB(255, 160, 32 ,240)
////////////////////////////////////////////////////////////////////////////////
#define ButtonSelect1	D3DCOLOR_ARGB(255, 238, 201, 0) 
#define ButtonSelect2	D3DCOLOR_ARGB(255, 215, 201, 0)
////////////////////////////////////////////////////////////////////////////////
#define ButtonOff        D3DCOLOR_ARGB(255, 81, 81  , 81)
#define ButtonOff2       D3DCOLOR_ARGB(200, 81, 81  , 81)
////////////////////////////////////////////////////////////////////////////////
#define ButtonOn         D3DCOLOR_ARGB(255, 124, 0, 0)
#define ButtonOn2		 D3DCOLOR_ARGB(100, 124, 0, 0)
////////////////////////////////////////////////////////////////////////////////
#define TextOn           D3DCOLOR_ARGB(255, 224, 136, 60)
////////////////////////////////////////////////////////////////////////////////

#pragma warning (disable:4554 4800)
bool lClicked = false;
bool IsLMouseClick()
{
	if(pGameFramework->geti3InputMouse()->GetButtonState() == 1 && !lClicked)
	{
		lClicked = true;
		return true;
	}
	if(pGameFramework->geti3InputMouse()->GetButtonState() == 0)lClicked = false;
	return false;
}
bool rClicked = false;
bool IsRMouseClick()
{
	if(pGameFramework->geti3InputMouse()->GetButtonState() == 2 && !rClicked)
	{
		rClicked = true;
		return true;
	}
	if(pGameFramework->geti3InputMouse()->GetButtonState() == 0)rClicked = false;
	return false;
}

bool mClicked = false;
bool IsMMouseClick()
{
	if(pGameFramework->geti3InputMouse()->GetButtonState() == 4 && !mClicked)
	{
		mClicked = true;
		return true;
	}
	if(pGameFramework->geti3InputMouse()->GetButtonState() == 0)mClicked = false;
	return false;
}
POINT mpos;
void DrawItemText(int x, int y , DWORD color, const char *fmt, DWORD dwFlags, ...)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	MenuFont->DrawText(NULL, buf, -1, &FontPos, dwFlags, color);
}
void DrawItemTextNonSprintf(int x, int y , DWORD color, const char *fmt, DWORD dwFlags)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	MenuFont->DrawText(NULL, fmt, -1, &FontPos, dwFlags, color);
}
BOOL IsInBox(int x,int y,int w,int h)
{
	POINT MousePosition; 
	MousePosition.x = pGameFramework->geti3InputMouse()->GetX();
	MousePosition.y = pGameFramework->geti3InputMouse()->GetY();
	return(MousePosition.x >= x && MousePosition.x <= x + w && MousePosition.y >= y && MousePosition.y <= y + h);
}
void DrawMenuText(int x, int Y, int &mMax , DWORD color, const char *fmt, DWORD dwFlags)
{
	int y = Y + mMax * ItemSize;
	mMax = mMax + 1;
	RECT FontPos = { x, y, x + 120, y + 16 };
	MenuFont->DrawText(NULL, fmt, -1, &FontPos, dwFlags, color);
}
void DrawVoteKickPlayerNames (int x, int Y, int &mMax , DWORD color, const char *fmt,int Index, DWORD dwFlags, ...)
{
	DWORD cColor = color;
	int y = Y + mMax * ItemSize;
	mMax = mMax + 1;
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	if(IsInBox(x,y,strlen(buf)*7,16) ){
		cColor = GREEN;
		//if(IsLMouseClick())KickPlayer(Index,GlobalVoteReason);
	}

	MenuFont->DrawText(NULL, buf, -1, &FontPos, dwFlags, cColor);
}
void DrawMenuLink(int x, int Y, int &mMax , DWORD color, const char *fmt,const char *url, DWORD dwFlags, ...)
{
	DWORD cColor = color;
	int y = Y + mMax * ItemSize;
	mMax = mMax + 1;
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	if(IsInBox(x,y,120,16) ){
		cColor = GREEN;
		if(IsLMouseClick())ShellExecute (NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
	}

	MenuFont->DrawText(NULL, buf, -1, &FontPos, dwFlags, cColor);
}



void DrawBox( int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;

	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 1, 1 );
}

void DrawBorders(int x, int y, int w, int h, D3DCOLOR Color,IDirect3DDevice9* pDevice)
{
	DrawBox(x,  y, 2,  h,Color,pDevice);
	DrawBox(x,y+h, w,  2,Color,pDevice);
	DrawBox(x,  y, w,  2,Color,pDevice);
	DrawBox(x+w,y, 2,h+2,Color,pDevice);
}
void  Line2(int x, int y, int w, int h, D3DCOLOR Color,IDirect3DDevice9* pDevice)
{

	DrawBox(x,y+h, w,  2,Color,pDevice);
}
void  Line1(int x, int y, int w, int h, D3DCOLOR Color,IDirect3DDevice9* pDevice)
{
	DrawBox(x,  y, 2,  h,Color,pDevice);
}
void DrawTabBox(int x, int Y,int &mMax, char **typ,int max, int &Var,LPDIRECT3DDEVICE9 pDevice)
{
	int y = Y + mMax * 18 - 1;
	mMax = mMax + 1;
	DWORD SelectColorA = DEEPSKYBLUE;
	DWORD SelectColorB = DEEPSKYBLUE;
	int dir = 0;
	//==================== Kiri ===================//
	if(Var > 0){
		if(IsInBox(x-30,y+1,15,15))
		{
			SelectColorA = GOLD2;
			if(IsLMouseClick())dir = -1;
		}
		else SelectColorA = DEEPSKYBLUE;
	}
	//====================== Kanan =====================//
	if(Var < max-1){
		if(IsInBox(x + 75,y+1,15,15))
		{
			SelectColorB = GOLD2;
			if(IsLMouseClick())dir = 1;
		}
		else SelectColorB = DEEPSKYBLUE;
	}

	if (dir) {
		Var += dir;
	}

	DrawItemText(x-30,y,SelectColorA,"<<",DT_NOCLIP + DT_LEFT);//Geser kiri
	DrawItemText(x+75,y,SelectColorB,">>",DT_NOCLIP + DT_LEFT);//Geser kanan
	DrawItemText(x-29,y,TextOn,typ[Var],DT_NOCLIP + DT_CENTER);//ON / OFF
}
void DrawGradientBox(int x, int y,int w, int h, DWORD Color_1, DWORD Color_2,LPDIRECT3DDEVICE9 pDevice)
{
	float aPer,rPer,gPer,bPer;
	DWORD Colorit;
	DWORD a_1 = (Color_1>>24)&0xFF;
	DWORD r_1 = (Color_1>>16)&0xFF;
	DWORD g_1 = (Color_1>>8) &0xFF;
	DWORD b_1 =  Color_1     &0xFF;
	DWORD a_2 = (Color_2>>24)&0xFF;
	DWORD r_2 = (Color_2>>16)&0xFF;
	DWORD g_2 = (Color_2>>8) &0xFF;
	DWORD b_2 =  Color_2     &0xFF;
	aPer = ((float)a_2-(float)a_1)/h;
	rPer = ((float)r_2-(float)r_1)/h;
	gPer = ((float)g_2-(int)  g_1)/h;
	bPer = ((float)b_2-(float)b_1)/h;
	for(int i = 0;i<h;i++){
		Colorit = 
			(a_1+(int)(aPer*i) << 24)
			|(r_1+(int)(rPer*i) <<16)
			|(g_1+(int)(gPer*i) << 8)
			|(b_1+(int)(bPer*i));
		DrawTransparentBox(x,y+i,w,1,Colorit, pDevice); 
	}
}
void DrawMenuButton(int x ,int Y , int w , int h ,int &Var ,char *Button_Text ,LPDIRECT3DDEVICE9 pDevice, int &mMax)
{
	int y = Y + mMax * ItemSize;
	mMax = mMax + 1;
	DWORD SelectColorA = 0;
	DWORD SelectColorB = 0;
	int y_ = (y) + (h/2)-7;
	int x_ = x + 3+20;
	int y__ = ((h) - (h/1));
	int x__ = (x + w/1);
	if(IsInBox(x,y,w,h)){
		SelectColorA = DEEPSKYBLUE;
		SelectColorB = BLACK;
		if(IsLMouseClick()){
			if(Var == 1 && Var !=0){
				Var = 0;
			}
			else if(Var == 0){
				if(Var == 0){
					Folders.Visual = Folders.GameHack = Folders.PlayerSelect = Folders.WeaponSelect = Folders.Tools = Folders.Info = Folders.About = 0;
					Var = 1;
				}
			}
		}
	}
	else
	{
		SelectColorA = ButtonOff;
		SelectColorB = ButtonOff2;
	}
	if(Var == 0)
	{
		//DrawBox(x_-27,y_,113,9, SelectColorA,  pDevice);
		//DrawBox(x_-27,y_+9,113,8.7,  SelectColorB,  pDevice);
		DrawGradientBox(x_-25,y_,109,17.7,  SelectColorA, SelectColorB,  pDevice);
		//DrawBorders(x-5,y+2,113,h-2,DEEPSKYBLUE, pDevice);
		DrawItemText(x_-30,y_+1,TextOn,Button_Text,DT_NOCLIP + DT_CENTER);
	}
	if(Var == 1)
	{
		DrawGradientBox(x_-25,y_,109,17.7,  ButtonOn, ButtonOn2,  pDevice);
		//DrawBorders(x-5,y+2,113,h-2,DEEPSKYBLUE, pDevice);
		DrawItemText(x_-30,y_+1,TextOn,Button_Text,DT_NOCLIP + DT_CENTER);
	}
}

void DrawMenuItem(int x,int Y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice, int &mMax,char* helptext = NULL)
{
	int y = Y + mMax * ItemSize - 1;
	DWORD SelectColorA = DEEPSKYBLUE;
	DWORD SelectColorB = DEEPSKYBLUE;
	DWORD HelpColor = RED;
	int dir = 0;
	if(IsInBox(x+96,y+2,15,15))
	{
		if(Var > 0){
			SelectColorA = GOLD2;
			if(IsLMouseClick())dir = -1;
		}
	}
	else
	{
		SelectColorA = DEEPSKYBLUE;
	}
	if(IsInBox(x + 160,y+2,15,10))
	{
		if(Var < max-1){
			SelectColorB = GOLD2;
			if(IsLMouseClick())dir = 1;
		}
	}
	else
	{
		SelectColorB = DEEPSKYBLUE;
	}



	if(IsInBox(x+74,y+2,17,10) && helptext > NULL){
		HelpColor=GREEN;
		if(IsLMouseClick())ShowMessageBox(helptext, "Petunjuk", 0);
	}
	else HelpColor = RED;

	if(IsInBox(x-85,Y-4 + mMax * ItemSize ,268,18)){
		DrawGradientBox(x-84,(Y-2) + mMax * ItemSize ,268,17,DEEPSKYBLUE,D3DCOLOR_ARGB(200, 000, 000, 000),pDevice);
	}
	else 
	{	
		DrawTransparentBox(x-84,(Y-2) + mMax * ItemSize ,268,17, GRE2,  pDevice);
	}



	if (dir) {
		Var += dir;
	}

	if(helptext){
		DrawItemText(x+73,y,HelpColor,"[ ? ]",DT_NOCLIP + DT_LEFT);//Help
	}

	DrawItemText(x+96,y,SelectColorA,"<<",DT_NOCLIP + DT_LEFT);//Geser kiri
	DrawItemText(x+160,y,SelectColorB,">>",DT_NOCLIP + DT_LEFT);//Geser kanan
	DrawItemText(x+76,y,TextOn,typ[Var],DT_NOCLIP + DT_CENTER);//ON / OFF
	DrawItemText(x-80,y,TextOn,text,DT_NOCLIP);//Text / Func item name
	//DrawBorders(x-85,Y-4 + mMax * ItemSize ,268,18,BLACK,  pDevice);
	mMax = mMax + 1;
}

void DrawMenuItemFunc(int x,int Y,int &Var,void* func,int max,char* text,LPDIRECT3DDEVICE9 pDevice, int &mMax,char* helptext = NULL)
{
	int y = Y + mMax * ItemSize - 1;
	DWORD SelectColorA = DEEPSKYBLUE;
	DWORD SelectColorB = DEEPSKYBLUE;
	DWORD HelpColor = RED;
	int dir = 0;
	if(IsInBox(x+16,y+2,15,15))
	{
		if(Var > 0){
			SelectColorA = GOLD2;
			if(IsLMouseClick())dir = -1;
		}
	}
	else
	{
		SelectColorA = DEEPSKYBLUE;
	}
	if(IsInBox(x + 34,y+2,15,10))
	{
		if(Var < max-1){
			SelectColorB = GOLD2;
			if(IsLMouseClick())dir = 1;
		}
	}
	else
	{
		SelectColorB = DEEPSKYBLUE;
	}



	if(IsInBox(x+74,y+2,17,10) && helptext > NULL){
		HelpColor=GREEN;
		if(IsLMouseClick())ShowMessageBox(helptext, "Petunjuk", 0);
	}
	else HelpColor = RED;

	if(IsInBox(x-85,Y-4 + mMax * ItemSize ,268,18)){
		DrawGradientBox(x-84,(Y-2) + mMax * ItemSize ,268,17,DEEPSKYBLUE,D3DCOLOR_ARGB(200, 000, 000, 000),pDevice);
	}
	else 
	{	
		DrawTransparentBox(x-84,(Y-2) + mMax * ItemSize ,268,17, GRE2,  pDevice);
	}



	if (dir) {
		Var += dir;
	}

	if(helptext){
		DrawItemText(x+73,y,HelpColor,"[ ? ]",DT_NOCLIP + DT_LEFT);//Help
	}

	typedef char* (*func_type)(int);

	
	DrawItemTextNonSprintf(x+56,y,TextOn,((func_type) func)(Var),DT_NOCLIP + DT_RIGHT);//ON / OFF
	DrawItemText(x-80,y,TextOn,text,DT_NOCLIP);//Text / Func item name
	DrawItemText(x+8,y,SelectColorA,"<<",DT_NOCLIP + DT_LEFT);//Geser kiri
	DrawItemText(x+28,y,SelectColorB,">>",DT_NOCLIP + DT_LEFT);//Geser kanan
	//DrawBorders(x-85,Y-4 + mMax * ItemSize ,268,18,BLACK,  pDevice);
	mMax = mMax + 1;
}

void DrawMenuItemWithCounter(int x,int Y,int &Var,char **typ,int max,char* text,LPDIRECT3DDEVICE9 pDevice, int &mMax,char* helptext = NULL)
{
	int y = Y + mMax * ItemSize - 1;
	DWORD SelectColorA = DEEPSKYBLUE;
	DWORD SelectColorB = DEEPSKYBLUE;
	DWORD HelpColor = RED;
	int dir = 0;
	if(IsInBox(x+96,y+2,15,15))
	{
		if(Var > 0){
			SelectColorA = GOLD2;
			if(IsLMouseClick())dir = -1;
		}
	}
	else
	{
		SelectColorA = DEEPSKYBLUE;
	}
	if(IsInBox(x + 160,y+2,15,10))
	{
		if(Var < max-1){
			SelectColorB = GOLD2;
			if(IsLMouseClick())dir = 1;
		}
	}
	else
	{
		SelectColorB = DEEPSKYBLUE;
	}



	if(IsInBox(x+74,y+2,17,10) && helptext > NULL){
		HelpColor=GREEN;
		if(IsLMouseClick())ShowMessageBox(helptext, "Petunjuk", 0);
	}
	else HelpColor = RED;

	if(IsInBox(x-85,Y-4 + mMax * ItemSize ,268,18)){
		DrawGradientBox(x-85,Y-4 + mMax * ItemSize ,268,18,DEEPSKYBLUE,D3DCOLOR_ARGB(200, 000, 000, 000),pDevice);
	}
	else 
	{	
		DrawTransparentBox(x-85,Y-4 + mMax * ItemSize ,268,18, GRE2,  pDevice);
	}



	if (dir) {
		Var += dir;
	}

	if(helptext){
		DrawItemText(x+73,y,HelpColor,"[ ? ]",DT_NOCLIP + DT_LEFT);//Help
	}

	DrawItemText(x+53,y,RED,"%d / %d",DT_NOCLIP + DT_LEFT, Var + 1, max);//Help

	DrawItemText(x+96,y,SelectColorA,"<<",DT_NOCLIP + DT_LEFT);//Geser kiri
	DrawItemText(x+160,y,SelectColorB,">>",DT_NOCLIP + DT_LEFT);//Geser kanan
	DrawItemText(x+76,y,TextOn,typ[Var],DT_NOCLIP + DT_CENTER);//ON / OFF
	DrawItemText(x-80,y,TextOn,text,DT_NOCLIP);//Text / Func item name

	DrawBorders(x-85,Y-4 + mMax * ItemSize ,268,18,BLACK,  pDevice);
	mMax = mMax + 1;
}