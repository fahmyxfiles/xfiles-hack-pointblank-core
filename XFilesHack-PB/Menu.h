

typedef struct
{
	int Visual;
	int GameHack;
	int PlayerSelect;
	int WeaponSelect;
	int Tools;
	int Info;
	int About;
}tFolders;
typedef struct
{
	int Visual;
	int GameHack;
	int PlayerSelect;
	int WeaponSelect;
	int Tools;
	int Info;
	int About;
}tTabs;

tFolders Folders;
tTabs Tabs;


#include "cMenu.h"
bool SHOW = true;

DWORD MAJORVERSION = 3;
DWORD MINORVERSION = 1;
DWORD REVISION = 0;


void DrawDottedBox(int X, int Y,int Item, LPDIRECT3DDEVICE9 pDevice)
{
	for(int i = 0; i<Item; i++)
	{
		if(!IsInBox(X+122,Y+9 + i * ItemSize ,268,18))
			DrawBox(X+122,Y+9 + i * ItemSize ,268,18, GRE2,  pDevice);
		if(IsInBox(X+122,Y+9 + i * ItemSize ,268,18))
			DrawGradientBox(X+122,Y+9 + i * ItemSize ,268,18,GRE2,DEEPSKYBLUE,pDevice);
		DrawBorders(X+122,Y+9 + i * ItemSize ,268,18,BLACK,  pDevice);
	}
}



void DrawBackground(int X, int Y, int MENU_W,int MENU_H, LPDIRECT3DDEVICE9 pDevice)
{
	//===================================================================================//
	DrawTransparentBox (X+2,Y+2,MENU_W,MENU_H-1	  ,		D3DCOLOR_ARGB(200, 000, 000, 000),		  pDevice); // Background
	DrawBorders(X+7,Y+7,MENU_W-13,MENU_H-13-1,		DEEPSKYBLUE,  pDevice);
	Line1	  (X+120,Y+8,180,MENU_H-14	  ,	    DEEPSKYBLUE,  pDevice);//Left Up
	//===================================================================================//
	Line1(X+3,Y+3,20,20,		GOLD2,  pDevice);//Left Up
	Line2(X+3,Y-142,20,145,		GOLD2,  pDevice);//Left Down
	Line1(X+MENU_W-1,Y+3,20,20,		GOLD2,  pDevice);//Right Up
	Line2(X+MENU_W-20,Y-142,20,145,	GOLD2,  pDevice);//Right Down
	//===================================================================================//
	Line1(X+3,Y+MENU_H-19,20,20,			GOLD2,  pDevice);//Left Up
	Line2(X+5,Y+12,20,MENU_H-13,			GOLD2,  pDevice);//Left Down
	Line1(X+MENU_W-1,Y+MENU_H-19,20,20,		GOLD2,  pDevice);//Right Up
	Line2(X+MENU_W-20,Y+12,20,MENU_H-13,	GOLD2,  pDevice);//Right Down
	//===================================================================================//
}

#include <time.h>
SYSTEMTIME CurrentTime = {0};
struct tm  timeinfo = { 0 };
time_t StartTime = 0;
const char * Day[] = { "Sunday", "Monday","Tuesday", "Wednesday","Thursday", "Friday", "Saturday"};
const char * Month[] = { "January", "February","March", "April","May", "June", "July", "Agust", "September", "October" , "November", "December"};

char *MoptonoFF		[]		= { "OFF", "ON"};
char *MoptCharms	[]		= {"OFF", "Light", "Ghost", "Phantom"};
char *MoptAssistMode	[]		= {"OFF", "Lock", "Bullet"};
char *MoptAssistTarget	[]		= {"Head", "Body"};
char *MoptAssistHotkey	[]		= {"OFF", "Left Control", "Left Alt", "Left SHIFT", "Caps Lock", "Tab"};
char *MoptAssistHotkeyMode	[]		= {"Hold", "Toggle"};
char *MoptResetWeapon [] = {"OFF", "Limit", "Bypass", "Ammo"};
char* MoptRapidFire [] = {"OFF", "Lv. 1", "Lv. 3", "Lv. 5", "Lv. 10"};


char *OptVisualTab[] = {"Direct3D","ESP"};
char *OptGameHackTab[] = {"Aim", "Player", "Weapon", "Misc", "Brutal"};


int MaxDrawed = 0;
void ShowMenu (int X, int Y, int MENU_W,int MENU_H, LPDIRECT3DDEVICE9 pDevice)
{
	if(!StartTime)StartTime = time(NULL);
	if(IsKeyboardKeyDownOnce(DIK_INSERT)) SHOW=(!SHOW);
	if(SHOW){
		GetCursorPos(&mpos);// Update Mouse Coordinates
		ScreenToClient(GetForegroundWindow(),&mpos); // Translate to Current Window
		DrawBackground(X,Y,MENU_W,MENU_H,pDevice);
		int mButton = 0;
		DrawMenuButton(X+12 ,Y+7,     110, 20,Folders.Visual		,"Visual Hack"	, pDevice, mButton);
		DrawMenuButton(X+12 ,Y+7,     110, 20,Folders.GameHack		,"Game Hack"	, pDevice, mButton);
		DrawMenuButton(X+12 ,Y+7,     110, 20,Folders.PlayerSelect	,"Player Select"	, pDevice, mButton);
		DrawMenuButton(X+12 ,Y+7,     110, 20,Folders.WeaponSelect	,"Weapon Select"	, pDevice, mButton);
		DrawMenuButton(X+12 ,Y+7,     110, 20,Folders.Tools			,"Tools"			, pDevice, mButton);
		DrawMenuButton(X+12 ,Y+7,     110, 20,Folders.Info			,"Local Info"		, pDevice, mButton);
		DrawMenuButton(X+12 ,Y+7,     110, 20,Folders.About			,"About"			, pDevice, mButton);
		MaxItem = mButton + 1;
		MaxDrawed = mButton + 1;
		//============================= D3D Hack ============================================//
		if(Folders.Visual)
		{
			int mD3D = 0;
			DrawTabBox(X+230,Y+13,mD3D,OptVisualTab,2,Tabs.Visual,pDevice);
			if(Tabs.Visual == 0){
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.Direct3D.WallHack ,MoptonoFF,2,"Wallhack" ,pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.Direct3D.Charms ,MoptCharms,4,"Charms" ,pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.Direct3D.CrossHair,MoptonoFF,2,"Crosshair",pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.Direct3D.NoSmoke  ,MoptonoFF,2,"No Smoke" ,pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.Direct3D.NoFog  ,MoptonoFF,2,"No Fog" ,pDevice,mD3D);
			}
			if(Tabs.Visual == 1)
			{
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.ESP.Team       ,MoptonoFF,2,"Team",pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.ESP.Name       ,MoptonoFF,2,"Name",pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.ESP.Info       ,MoptonoFF,2,"Info",pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.ESP.Head       ,MoptonoFF,2,"Head",pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.ESP.HealthBar  ,MoptonoFF,2,"Health",pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.ESP.Bone       ,MoptonoFF,2,"Bone",pDevice,mD3D);
				DrawMenuItem(X+207,Y+13,FeatureStruct->Visual.ESP.Line       ,MoptonoFF,2,"Line",pDevice,mD3D);
			}
			if(mD3D >= MaxDrawed)MaxItem = mD3D + 1;
		}		
		//=========================== Game Hack ===========================================//
		if(Folders.GameHack)
		{
			int mGame = 0;
			DrawTabBox(X+230,Y+13,mGame,OptGameHackTab,5,Tabs.GameHack,pDevice);
			if(Tabs.GameHack == 0){
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Assist.Mode       ,MoptAssistMode,3,"Mode",pDevice,mGame, "Lock : Crosshair akan mengunci ke musuh\nBullet : Peluru akan mengejar musuh tanpa mengeker");
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Assist.Target       ,MoptAssistTarget,2,"Target",pDevice,mGame, "Menentukkan bagian badan musuh yang akan dikunci oleh sistem.");
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Assist.Hotkey       ,MoptAssistHotkey,6,"Hotkey",pDevice,mGame, "Memilih hotkey keyboard yang akan digunakan untuk menyalakan Aim\nJika posisi OFF aim akan selalu menyala");
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Assist.HotkeyMode       ,MoptAssistHotkeyMode,2,"Hotkey Mode",pDevice,mGame, "Hold : Aim akan menyala apabila hotkey terpilih ditahan\nToggle : Aim akan menyala apabila hotkey terpilih ditekan sekali");
			}
			if(Tabs.GameHack == 1)
			{
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Player.SkillUp       ,MoptonoFF,2,"Skill Up",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Player.ResetWeapon   ,MoptResetWeapon,4,"Reset Weapon",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Player.Reborn        ,MoptonoFF,2,"Reborn",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Player.FreeMove        ,MoptonoFF,2,"Free Move",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Player.HealthAbsorber       ,MoptonoFF,2,"Health Absorber",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Player.PlantDefuse        ,MoptonoFF,2,"CT Plant Bomb",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Player.AutoHeadshot        ,MoptonoFF,2,"Auto Headshot",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Player.AlwaysInvicible        ,MoptonoFF,2,"Always Invicible",pDevice,mGame);
			}
			if(Tabs.GameHack == 2)
			{
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Weapon.QuickChange       ,MoptonoFF,2,"Fast Change",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Weapon.AutoFillSubAmmo       ,MoptonoFF,2,"Unlimited Sub Ammo",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Weapon.SkipReload       ,MoptonoFF,2,"Skip Reload",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Weapon.NoRecoil       ,MoptonoFF,2,"No Recoil",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Weapon.RapidFire       ,MoptRapidFire,5,"Rapid Fire",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Weapon.AutoFire       ,MoptonoFF,2,"Auto Fire",pDevice,mGame);
			}
			if(Tabs.GameHack == 3)
			{
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Misc.ResetAbuse       ,MoptonoFF,2,"Reset Abuse",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Misc.BypassServerFull   ,MoptonoFF,2,"Bypass Server Full",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Misc.BypassRoomPassword        ,MoptonoFF,2,"Bypass Room Password",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Misc.AntiKick        , MoptonoFF, 2, "Anti Kick", pDevice, mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Misc.AutoInviteRoom        ,MoptonoFF,2,"Auto Invite Room",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Misc.KickAllPlayer        ,MoptonoFF,2,"Kick All Player",pDevice,mGame);
			}
			if(Tabs.GameHack == 4)
			{
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Brutal.AutoKiller       ,MoptonoFF,2,"Auto Killer",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Brutal.ExplosiveKiller       ,MoptonoFF,2,"Explosive Killer",pDevice,mGame);
				DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.Brutal.FastKiller       ,MoptonoFF,2,"Fast Killer",pDevice,mGame);
			}
			if(mGame >= MaxDrawed)MaxItem = mGame + 1;
		}

		//=========================== PlayerSelect Menu ===================================//
		if(Folders.PlayerSelect)
		{
			int mVoteKick = 0;
			if(IsInBattle()){
				int mVoteT = 0;
				DrawMenuText(X+128,Y+13,mVoteT, RED,"Terrorist",DT_NOCLIP + DT_LEFT);
				for(int i = 0; i<=15; i+=2){
					if(!pGameCharaManager->isValidChara(i))continue;
					DrawVoteKickPlayerNames(X+128,Y+13,mVoteT,RED,pGameContext->getNickForSlot(i),i,DT_NOCLIP + DT_LEFT);
				}
				int mVoteCT = 0;
				DrawMenuText(X+128 + 160,Y+13,mVoteCT, SKYBLUE,"Counter Terrorist",DT_NOCLIP + DT_LEFT);
				for(int i = 1; i<=15; i+=2){
					if(!pGameCharaManager->isValidChara(i))continue;
					DrawVoteKickPlayerNames(X+128 + 160,Y+13,mVoteCT,SKYBLUE,pGameContext->getNickForSlot(i),i,DT_NOCLIP + DT_LEFT);
				}
				if(mVoteT > mVoteCT)mVoteKick = mVoteT;
				else mVoteKick = mVoteCT;
			}
			else DrawMenuText(X+128,Y+13,mVoteKick, RED,"Not Available.",DT_NOCLIP + DT_LEFT);
			if(mVoteKick >= MaxDrawed)MaxItem = mVoteKick + 1;
		}
		//=========================== ReplaceWeapon Menu ===================================//
		if(Folders.WeaponSelect)
		{
			int mWeapon = 0;
			DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.ReplaceWeapon.Status, MoptonoFF,2,"Replace Weapon",pDevice,mWeapon, "Tutorial Memakai Replace :\nON kan Shield BM (WAJIB), lalu onkan AutoTeleport jika diinginkan, tunggu sampai Ronde berganti, setelah respawn tekan SHIFT untuk mengubah senjata\nJika ingin Auto Teleport tekan SPASI, kill musuh dengan menembak");
			DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.ReplaceWeapon.ShieldBM, MoptonoFF,2,"Shield BM",pDevice,mWeapon);
			DrawMenuItem(X+207,Y+13,FeatureStruct->GameHack.ReplaceWeapon.AutoTeleport, MoptonoFF,2,"Auto Teleport",pDevice,mWeapon);
			DrawMenuItemFunc(X+207,Y+13,FeatureStruct->GameHack.ReplaceWeapon.SelectWeapon, ReplaceCallback,ReplaceWeapon->ReplaceList.size(),"Select Weapon",pDevice,mWeapon);
			if(mWeapon >= MaxDrawed)MaxItem = mWeapon + 1;
		}
		//=========================== Tools ===========================================//
		if(Folders.Tools)
		{
			int mTools = 0;
			DrawMenuItem(X+207,Y+13,UseTransparentMenu ,MoptonoFF,2,"Use Transparent Menu",pDevice,mTools);
			DrawMenuItem(X+207,Y+13,MoveMenu ,MoptonoFF,2,"Move Menu",pDevice,mTools,"Berfungsi untuk memindahkan posisi menu. Tekan ENTER untuk mengunci posisi menu.");
			if(mTools >= MaxDrawed)MaxItem = mTools + 1;
		}

		//======================== Information ==============================================//
		if(Folders.Info)
		{
			int mInfo = 0;
			string Username = ": " + string(myClientInfo->profile.Username);
			string Durasi   = ": " + std::to_string((long double)myClientInfo->profile.Duration) + " Hari";
			string Expired  = ": " + string(myClientInfo->profile.Expiration);
			DrawMenuText(X+128,Y+13,mInfo, RED,   "Nama Pengguna"					,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+128,Y+13,mInfo, RED,   "Durasi"							,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+128,Y+13,mInfo, RED,   "Kadaluarsa"						,DT_NOCLIP + DT_LEFT);
			mInfo = 0;
			DrawMenuText(X+228,Y+13,mInfo, RED,   Username.c_str()					,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+228,Y+13,mInfo, RED,   Durasi.c_str()					,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+228,Y+13,mInfo, RED,   Expired.c_str()					,DT_NOCLIP + DT_LEFT);
			if(mInfo >= MaxDrawed)MaxItem = mInfo + 1;
		}
		//============================= About ==============================================//
		if(Folders.About)
		{
			int mAbout = 0;

			DrawMenuText(X+128,Y+13,mAbout, RED,   "XFiles Hack PointBlank D3DMenu Hack 2017"					,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+128,Y+13,mAbout, PURPLE,"Thanks to D'Darkness Immortall"									,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+128,Y+13,mAbout, WHITE,"Website"									,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+128,Y+13,mAbout, WHITE,"Facebook"									,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+128,Y+13,mAbout, WHITE,"Instagram"									,DT_NOCLIP + DT_LEFT);
			mAbout = 2;
			DrawMenuText(X+228,Y+13,mAbout, WHITE,":"									,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+228,Y+13,mAbout, WHITE,":"									,DT_NOCLIP + DT_LEFT);
			DrawMenuText(X+228,Y+13,mAbout, WHITE,":"									,DT_NOCLIP + DT_LEFT);
			mAbout = 2;
			DrawMenuLink(X+238,Y+13,mAbout, WHITE, "XFiles Website","http://www.xfiles.co/"							,DT_NOCLIP + DT_LEFT);
			DrawMenuLink(X+238,Y+13,mAbout, WHITE, "XFilesHack","http://www.facebook.com/XFilesHack"							,DT_NOCLIP + DT_LEFT);
			DrawMenuLink(X+238,Y+13,mAbout, WHITE, "@XFilesHack","http://www.instagram.com/XFilesHack"							,DT_NOCLIP + DT_LEFT);


			if(mAbout >= MaxDrawed)MaxItem = mAbout + 1;
		}
	}
}
