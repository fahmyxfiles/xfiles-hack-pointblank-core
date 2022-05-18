
#include "cMenu.h"
//------------------------------------------------------------------------------------------------------
typedef struct
{
	int Visual;
	int PlayerHack;
	int SpecialHack;
	int ReplaceHack;
	int BrutalHack;
}tCoopFolders;
tCoopFolders cFolders;
D3D9Menu	*XFiles	= NULL;

char *Moptfolder	[]		= {"Open", "Close"};
char *Moptonoff		[]		= { "OFF", "ON"};
char *MoptVote [] = {"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx", 
	"xxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxxxx" };
char* MoptBurst [] = {"OFF", "5", "10", "25", "50", "100"};
char* MoptAbuse [] = {"OFF", "Press TAB"};
char* MoptShield [] = {"OFF", "Press L-SHIFT"};

void RebuildMenu(LPDIRECT3DDEVICE9 pDevice)
{

	XFiles->SetHeader(myClientInfo->product.Name);
	XFiles->AddFolder("[Visual Hack]", Moptfolder, &cFolders.Visual, 2); 
	if(cFolders.Visual) 
	{
		XFiles->AddText("Direct3D", "");
		XFiles->AddItem("WallHack", Moptonoff, &FeatureStruct->Visual.Direct3D.WallHack, 2);
		XFiles->AddItem("Crosshair", Moptonoff, &FeatureStruct->Visual.Direct3D.CrossHair, 2);
		XFiles->AddItem("Charms", MoptCharms, &FeatureStruct->Visual.Direct3D.Charms, 4);
		XFiles->AddItem("No Smoke", Moptonoff, &FeatureStruct->Visual.Direct3D.NoSmoke, 2);
		XFiles->AddItem("No Fog", Moptonoff, &FeatureStruct->Visual.Direct3D.NoFog, 2);
		XFiles->AddText("ESP", "");
		XFiles->AddItem("ESP Team", Moptonoff, &FeatureStruct->Visual.ESP.Team, 2);
		XFiles->AddItem("ESP Line", Moptonoff, &FeatureStruct->Visual.ESP.Line, 2);
		XFiles->AddItem("ESP Name", Moptonoff, &FeatureStruct->Visual.ESP.Name, 2);
		XFiles->AddItem("ESP Info", Moptonoff, &FeatureStruct->Visual.ESP.Info, 2);
		XFiles->AddItem("ESP Head", Moptonoff, &FeatureStruct->Visual.ESP.Head, 2);
		XFiles->AddItem("ESP Bone", Moptonoff, &FeatureStruct->Visual.ESP.Bone, 2);
		XFiles->AddItem("ESP Health", Moptonoff, &FeatureStruct->Visual.ESP.HealthBar, 2);
	}
	XFiles->AddFolder("[Game Hack]", Moptfolder, &cFolders.PlayerHack, 2); 
	if(cFolders.PlayerHack) 
	{
		XFiles->AddText("AimAssist", "");
		XFiles->AddItem("Assist Mode", MoptAssistMode, &FeatureStruct->GameHack.Assist.Mode, 3);
		XFiles->AddItem("Assist Target", MoptAssistTarget, &FeatureStruct->GameHack.Assist.Target, 2);
		XFiles->AddItem("Assist Hotkey Mode", MoptAssistHotkeyMode, &FeatureStruct->GameHack.Assist.HotkeyMode, 2);
		XFiles->AddItem("Assist Hotkey", MoptAssistHotkey, &FeatureStruct->GameHack.Assist.Hotkey, 6);

		XFiles->AddText("Player", "");		
		XFiles->AddItem("Skill Up", Moptonoff, &FeatureStruct->GameHack.Player.SkillUp, 2);
		XFiles->AddItem("Reset Weapon", MoptResetWeapon, &FeatureStruct->GameHack.Player.ResetWeapon, 4);
		XFiles->AddItem("Reborn", Moptonoff, &FeatureStruct->GameHack.Player.Reborn, 2);
		XFiles->AddItem("Free Move", Moptonoff, &FeatureStruct->GameHack.Player.FreeMove, 2);
		XFiles->AddItem("CT Plant Bomb", Moptonoff, &FeatureStruct->GameHack.Player.PlantDefuse, 2);
		XFiles->AddItem("Auto Headshot", Moptonoff, &FeatureStruct->GameHack.Player.AutoHeadshot, 2);
		XFiles->AddItem("Always Invicible", Moptonoff, &FeatureStruct->GameHack.Player.AlwaysInvicible, 2);

		XFiles->AddText("Weapon", "");
		XFiles->AddItem("Quick Change", Moptonoff, &FeatureStruct->GameHack.Weapon.QuickChange, 2);
		XFiles->AddItem("Auto Fill Sub Ammo", Moptonoff, &FeatureStruct->GameHack.Weapon.AutoFillSubAmmo, 2);
		XFiles->AddItem("Skip Reload", Moptonoff, &FeatureStruct->GameHack.Weapon.SkipReload, 2);
		XFiles->AddItem("No Recoil", Moptonoff, &FeatureStruct->GameHack.Weapon.NoRecoil, 2);
		XFiles->AddItem("Rapid Fire", MoptRapidFire, &FeatureStruct->GameHack.Weapon.RapidFire, 5);
		XFiles->AddItem("Auto Fire", Moptonoff, &FeatureStruct->GameHack.Weapon.AutoFire, 2);
		XFiles->AddText("Misc", "");
		XFiles->AddItem("Reset Abuse", MoptAbuse, &FeatureStruct->GameHack.Misc.ResetAbuse, 2);
		XFiles->AddItem("Bypass Server Full", Moptonoff, &FeatureStruct->GameHack.Misc.BypassServerFull, 2);
		XFiles->AddItem("Bypass Password", Moptonoff, &FeatureStruct->GameHack.Misc.BypassRoomPassword, 2);
		XFiles->AddItem("Anti Kick Room", Moptonoff, &FeatureStruct->GameHack.Misc.AntiKick, 2);
		XFiles->AddItem("Auto Invite Room", Moptonoff, &FeatureStruct->GameHack.Misc.AutoInviteRoom, 2);
		//XFiles->AddItem("Kick All Player", Moptonoff, &FeatureStruct->GameHack.Misc.KickAllPlayer, 2);

	}
	XFiles->AddFolder("[Brutal Hack]", Moptfolder, &cFolders.BrutalHack, 2); 
	if(cFolders.BrutalHack) 
	{
		XFiles->AddItem("Auto Killer", Moptonoff, &FeatureStruct->GameHack.Brutal.AutoKiller, 2);
		//XFiles->AddItem("Fast Killer", Moptonoff, &FeatureStruct->GameHack.Brutal.FastKiller, 2);
		XFiles->AddItem("Explosive Killer", Moptonoff, &FeatureStruct->GameHack.Brutal.ExplosiveKiller, 2);
	}
	XFiles->AddFolder("[Replace Hack]", Moptfolder, &cFolders.ReplaceHack, 2); 
	if(cFolders.ReplaceHack) 
	{
		XFiles->AddItem("Replace Weapon", Moptonoff, &FeatureStruct->GameHack.ReplaceWeapon.Status, 2);
		XFiles->AddItem("Shield BM", Moptonoff, &FeatureStruct->GameHack.ReplaceWeapon.ShieldBM, 2);
		XFiles->AddItem("Auto Teleport", Moptonoff, &FeatureStruct->GameHack.ReplaceWeapon.AutoTeleport, 2);
		XFiles->AddItemFunc("Select Weapon", ReplaceCallback, &FeatureStruct->GameHack.ReplaceWeapon.SelectWeapon, ReplaceWeapon->ReplaceList.size());
	}
}


void MenuHandler( LPDIRECT3DDEVICE9 pDevice )
{
	return;
}