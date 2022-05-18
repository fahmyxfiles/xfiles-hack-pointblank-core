#include "AssistFunctions.h"

bool bIsAimTargetValid = false;
void DisableAimAssist()
{
	if(bIsAimTargetValid == true){
		SetEndVector->Disable();
		bIsAimTargetValid = false;
	}
}

void DoAimAssist(LPDIRECT3DDEVICE9 pDevice)
{
	if(IsInBattle()){
		
		switch(FeatureStruct->GameHack.Assist.Target)
		{
		case 0:
			BoneIndexSelector = 7;
			break;
		case 1:
			BoneIndexSelector = 5;
			break;
		}
		CGameCharaBase* LocalChara = pGameCharaManager->getLocalChara();
		if(LocalChara && LocalChara->isAlive()){
			if(FeatureStruct->GameHack.Assist.Mode){
				if(GetAimAssistState()){
					CGameCharaBase* Target = pGameCharaManager->getCharaToAim();
					if(Target){
						bIsAimTargetValid = true;
						D3DXVECTOR3 AimTarget = Target->getGameCharaBoneContext()->getBonePosition(BoneIndexSelector);
						AimTarget.y += 0.1f;
						if(FeatureStruct->GameHack.Assist.Mode == 1)SetLocalPawnAimTarget(AimTarget);
						if(FeatureStruct->GameHack.Assist.Mode == 2)SetEndVector->SetTargetVector(AimTarget);
					} else DisableAimAssist();
				} else DisableAimAssist();
			} else DisableAimAssist();
		} else DisableAimAssist();
	} else DisableAimAssist();

}