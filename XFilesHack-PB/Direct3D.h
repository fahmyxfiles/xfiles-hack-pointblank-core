HANDLE hCheckingThread = NULL;
DWORD dwValidateTick = NULL;
__forceinline void ValidateClient()
{
	if(dwValidateTick <= GetTickCount()){
		if(hCheckingThread == NULL)
		{
			char szMyNickname[24] = {0};
			if(pGameContext)
			{
				strcpy(szMyNickname, pGameContext->getNickForSlot(pGameContext->getMySlotIdx()));
			}
			sUserInfoBuffer.Clear();
			Writer<StringBuffer> writer(sUserInfoBuffer);
			writer.StartObject(); 
			writer.Key("Nickname");
			writer.String(szMyNickname);
			writer.Key("PlayerList");
			writer.StartArray();
			for (unsigned i = 0; i < 16; i++)
			{
				if(pGameCharaManager && LocalChara)
				{
					if(pGameCharaManager->isValidChara(i) && LocalChara->getCharaNetIndex() != i)
					{
						writer.String(pGameCharaManager->getCharaByNetIdx(i)->getNickname());
					}
				}
			}
			writer.EndArray();
			writer.EndObject(); 
			
			hCheckingThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)CheckThread,0,0,0);
			dwValidateTick = GetTickCount() + 300000;
		}
	}
}

void Event_JoinRoom()
{
	dwValidateTick = 0;
}

void Event_PlayerListChange()
{
	dwValidateTick = 0;
}

void CheckEvent()
{
	static int evtJoinRoom = 0;
	static char oldNicknameList[16][24];
	if(IsInBattle())
	{
		if(evtJoinRoom == 0)
		{
			evtJoinRoom = 1;
		}
		if(evtJoinRoom == 1)
		{
			Event_JoinRoom();
			evtJoinRoom = 2;
		}

		for(int i = 0; i < 16; i++)
		{
			if(pGameCharaManager->isValidChara(i))
			{
				if(strcmp(oldNicknameList[i], pGameCharaManager->getCharaByNetIdx(i)->getNickname()) != 0)
				{
					Event_PlayerListChange();
				}
			}
		}

		for(int i = 0; i < 16; i++)
		{
			if(pGameCharaManager->isValidChara(i))
			{
				strcpy(oldNicknameList[i], pGameCharaManager->getCharaByNetIdx(i)->getNickname());
			}
		}
	}
	else
	{
		evtJoinRoom = 0;
	}
}

HRESULT WINAPI hkEndScene(LPDIRECT3DDEVICE9 pDevice){

	while(!npDevice){
		npDevice = pDevice;	
		pDevice->GetViewport(&g_ViewPort);
	}

	static bool bInitEs = false;
	while(!bInitEs)
	{
		
		//pDevice->GetCreationParameters(&dcParam);
		HookResetDevice();
		MenuPos.x = 20;
		MenuPos.y = 50;
		//SetupBugtrapHandler();
		HookSetEvent();
		bInitEs = true; 
	}

	if(bInitDIP)
	{
		CheckEvent();
		ValidateClient();
	}
	
	

	if(!g_pLine)D3DXCreateLine(pDevice,&g_pLine);
	if(!MenuFont)D3DXCreateFontA(pDevice, 14, 0, FW_EXTRALIGHT + FW_BOLD, 2, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Segoe UI", &MenuFont);
	if(!g_pFont)D3DXCreateFontA(pDevice, 13, 0, FW_EXTRALIGHT, 2, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Tahoma", &g_pFont);
	if(!MessaMenuFont)D3DXCreateFontA(pDevice, 14, 0, FW_EXTRALIGHT, 2, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, (LPCSTR)"Arial", &MessaMenuFont);
	if(!XNNFont)D3DXCreateFontA(pDevice, 14, 0, FW_HEAVY, 0, 0, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Black", &XNNFont);

	ScreenCenterX = g_ViewPort.Width / 2;
	ScreenCenterY = g_ViewPort.Height / 2;

	//AdsPlay();

	DirectInputLoop();
	UpdateClass();

	DoESP(pDevice);
	DoAimAssist(pDevice);
	MemHack();

	if(strcmp(myClientInfo->product.Alias, "XFH") == 0){
		int MenuH = ( MaxItem * ItemSize )- 1;
		ShowMenu(MenuPos.x,MenuPos.y,398,MenuH,pDevice);
		if(MoveMenu)
		{
			MenuPos.x = pGameFramework->geti3InputMouse()->GetX(); 
			MenuPos.y = pGameFramework->geti3InputMouse()->GetY()+2;
			if(IsKeyboardKeyDownOnce(DIK_RETURN))MoveMenu = 0;
		}
	}
	else if(strcmp(myClientInfo->product.Alias, "SPC") == 0){
		GoldBase( pDevice);
	}
	else if(strcmp(myClientInfo->product.Alias, "XNN") == 0){
		if(XNNMmax == 0)XNNRebuildMenu(pDevice);
		XNNMenuShow(mx,my,pDevice);
		XNNMenuNav();
		XNNMenuHandler();
	}
	else
	{
		if(XFiles == NULL)XFiles = new D3D9Menu();
		if(XFiles->Font())XFiles->FontCreate(pDevice);
		if(XFiles->Mmax == 0)RebuildMenu(pDevice);
		XFiles->MenuShow(20,50,pDevice);
		XFiles->MenuNav();
	}

	DWORD CrosshairColor = GREEN;
	if( IsInBattle() ){
		if( pGameCharaManager->getLocalChara()->getGameCharaCollisionContext()->GetCrosshairTarget() > NULL )CrosshairColor = RED;
		if( FeatureStruct->Visual.Direct3D.CrossHair )Crosshair(pDevice, g_ViewPort, CrosshairColor);
	}

	return pDevice->EndScene();

}
//-------------------------------------------------------------------------------------------------------------------------

HRESULT WINAPI hkDrawIndexedPrimitive(LPDIRECT3DDEVICE9 pDevice, D3DPRIMITIVETYPE PrimType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
	if(!bInitDIP)
	{
		bInitDIP = true;
	}
	if(!Red)D3DXCreateTextureFromFileInMemory(pDevice, &_texRed, sizeof(_texRed), &Red);
	if(!Blue)D3DXCreateTextureFromFileInMemory(pDevice, &_texBlue, sizeof(_texBlue), &Blue);
	if(IsInBattle()){	
		if(FeatureStruct->Visual.Direct3D.WallHack || FeatureStruct->Visual.Direct3D.Charms){
			if(allp2){  
				if(FeatureStruct->Visual.Direct3D.Charms){
					if(FeatureStruct->Visual.Direct3D.Charms == 1){ //Light Charms
						pDevice->SetRenderState(D3DRS_ZENABLE,false);
						if(PlayerTerorist||TeroHead||C5||K400)pDevice->SetTexture(0,Red);
						if(PlayerCT||CTHead)pDevice->SetTexture(0,Blue);
						pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
						pDevice->SetRenderState(D3DRS_ZENABLE,true);

					}
					if(FeatureStruct->Visual.Direct3D.Charms == 2){ //Ghost Charms
						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCCOLOR);
						pDevice->SetRenderState(D3DRS_ZENABLE,false);	
						pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCCOLOR);
						pDevice->SetRenderState(D3DRS_ZENABLE,true);
					}
					if(FeatureStruct->Visual.Direct3D.Charms == 3){ //Phantom Charms
						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCALPHA);
						pDevice->SetRenderState(D3DRS_ZENABLE,false);
						pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
						pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
						pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVDESTCOLOR);
						pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_INVSRCALPHA);
						pDevice->SetRenderState(D3DRS_ZENABLE,false);
					}
				}
				else
				{
					pDevice->SetRenderState(D3DRS_ZENABLE, false);
					pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);
					pDevice->SetRenderState(D3DRS_ZENABLE, true);
				}
			}
		}


		if(FeatureStruct->Visual.Direct3D.NoSmoke)
			if((NumVertices == 192) || (NumVertices == 256))return D3D_OK;

		if(FeatureStruct->Visual.Direct3D.NoFog)pDevice->SetRenderState(D3DRS_FOGENABLE, false);

	}
	return pDevice->DrawIndexedPrimitive(PrimType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);	
}

void ResetD3DInterface()
{
	if(g_pFont){
		g_pFont->OnLostDevice();
		g_pFont->OnResetDevice();
		g_pFont->Release();
		g_pFont = NULL;
	}
	if(MenuFont)
	{
		MenuFont->OnLostDevice();
		MenuFont->OnResetDevice();
		MenuFont->Release();
		MenuFont = NULL;
	}
	if(MessaMenuFont)
	{
		MessaMenuFont->OnLostDevice();
		MessaMenuFont->OnResetDevice();
		MessaMenuFont->Release();
		MessaMenuFont = NULL;
	}
	if(XNNFont)
	{
		XNNFont->OnLostDevice();
		XNNFont->OnResetDevice();
		XNNFont->Release();
		XNNFont = NULL;
	}
	if(XFiles > NULL)
	{
		XFiles->FontReset();
	}
	if(g_pLine){
		g_pLine->OnLostDevice();
		g_pLine->OnResetDevice();
		g_pLine->Release();
		g_pLine = NULL;
	}
	if(Red)	{
		Red->Release();
		Red = NULL;
	}
	if(Blue) {
		Blue->Release();
		Blue = NULL;
	}
	if(npDevice)
		npDevice = NULL;
}