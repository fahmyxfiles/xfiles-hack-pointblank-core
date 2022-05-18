#include "ESPFunctions.h"

void DoESP(LPDIRECT3DDEVICE9 pDevice)
{

	if(IsInBattle()){
		for(int i = 0; i <= 15; i++){
			if(pGameCharaManager->isValidChara(i)){
				CGameCharaBase* Chara = pGameCharaManager->getCharaByNetIdx(i);
				if(Chara->isEnemy() == false && FeatureStruct->Visual.ESP.Team == 0)continue;
				if(Chara->isAlive() == false)continue;

				D3DXVECTOR3 Head = Chara->getGameCharaBoneContext()->getBonePosition(7);
				D3DXVECTOR3 Root = Chara->getGameCharaBoneContext()->getBonePosition(0);
				D3DXVECTOR3 ScreenHead;
				D3DXVECTOR3 ScreenHeadNames;
				D3DXVECTOR3 ScreenHeadHealth;
				D3DXVECTOR3 ScreenRootInfo;
				if( pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.1f, Head.z),ScreenHead,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.5f, Head.z),ScreenHeadNames,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Head.x, Head.y + 0.3f, Head.z),ScreenHeadHealth,pDevice) &&
					pRenderContext->WorldToScreen(D3DXVECTOR3(Root.x, Root.y - 0.5f, Root.z),ScreenRootInfo,pDevice))
				{
					if(FeatureStruct->Visual.ESP.Name)DrawOutlineStringC(g_pFont,ScreenHeadNames.x,ScreenHeadNames.y - 15,Chara->GetTeamColor(),/*%s - %dHP*/XorStr<0xCD,10,0xF438969D>("\xE8\xBD\xEF\xFD\xF1\xF7\xB7\x9C\x85"+0xF438969D).s, Chara->getNickname(), Chara->getCurHP());
					if(FeatureStruct->Visual.ESP.Info)
					{
						GAMEINFO_CHARACTER* CharaInfo = pGameContext->getGameInfo_Chara(i);
						if(CharaInfo > NULL){
							CWeaponInfo* WeaponInfo = pWeaponInfoDatabase->getWeaponInfo(CharaInfo->WeaponClassType, CharaInfo->WeaponIndex, 0);
							if(WeaponInfo > NULL)
							{
								char WeaponName[50] = {0};
								WeaponInfo->GetTranslatedName(WeaponName);
								DrawOutlineStringC(g_pFont,ScreenRootInfo.x,ScreenRootInfo.y + 15, GREEN,"[ %s - %s ]\n[ %s ]", WeaponSlotText(CharaInfo->WeaponSlot), CharaStateText(CharaInfo->CharaState), WeaponName);	
							}
						}
						if(IsPlayerOnHackingNetwork(Chara->getNickname()))
						{
							DrawOutlineStringC(g_pFont,ScreenHeadNames.x,ScreenHeadNames.y - 30, SKYBLUE,"[ %s ]", GetPlayerHackingNetworkProduct(Chara->getNickname()));	
						}
					}
					if(FeatureStruct->Visual.ESP.Head)FillRGB((float)ScreenHead.x, (float)ScreenHead.y, 4, 4,Chara->GetTeamColor(), pDevice);
					if(FeatureStruct->Visual.ESP.HealthBar)HealthBar((int)ScreenHeadHealth.x - 25,(int)ScreenHeadHealth.y,Chara->getCurHP(),pDevice);
					if(FeatureStruct->Visual.ESP.Line)DrawLine((float)ScreenCenterX,(float)ScreenCenterY,(float)ScreenHead.x,(float)ScreenHead.y,1,Chara->GetPlayerColor());
					if(FeatureStruct->Visual.ESP.Bone)DrawPlayerBone(i,Chara->GetPlayerColorForBone());
				}
			}
		}
	}
}