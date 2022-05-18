
void HealthBar(float x, float y, float Health, LPDIRECT3DDEVICE9 pDevice)
{
	DWORD HPcol = GREEN;
	if (Health < 90)HPcol = YELLOW;
	if (Health < 80) HPcol = ORANGE;
	if (Health < 40) HPcol = RED;
	if(Health > 100)Health = 100;
	DrawBorder(x-1,y-1,52,5,1,BLACK,pDevice );
	FillRGB(x,y,Health/2,3,HPcol,pDevice );
}

void DrawBone(int CharaIndex, int BoneIndexStart, int BoneIndexEnd, DWORD Color)
{
	D3DXVECTOR3 OnScreenA, OnScreenB;

	D3DXVECTOR3 OnWorldA = pGameCharaManager->getCharaByNetIdx(CharaIndex)->getGameCharaBoneContext()->getBonePosition(BoneIndexStart);
	D3DXVECTOR3 OnWorldB = pGameCharaManager->getCharaByNetIdx(CharaIndex)->getGameCharaBoneContext()->getBonePosition(BoneIndexEnd);
	if(pRenderContext->WorldToScreen(OnWorldA,OnScreenA,npDevice) && pRenderContext->WorldToScreen(OnWorldB,OnScreenB,npDevice))
	{
		DrawLine(OnScreenA.x,OnScreenA.y,OnScreenB.x,OnScreenB.y,1,Color);
	}
}

void DrawPlayerBone(int Index, DWORD Color)
{
	DrawBone(Index,7,6,Color);//Kepala - leher
	DrawBone(Index,6,5,Color);// Leher - Dada
	DrawBone(Index,5,4,Color);// Dada - perut
	DrawBone(Index,4,2,Color);// Perut - pantat
	DrawBone(Index,2,0,Color);// Perut - root
	DrawBone(Index,6,11,Color);//Tangan kanan
	DrawBone(Index,6,10,Color);//tangan kiri
	DrawBone(Index,0,13,Color);//Paha kanan
	DrawBone(Index,0,12,Color);//Paha kiri
	DrawBone(Index,13,15,Color);//Lutut kiri
	DrawBone(Index,12,14,Color);//Lutut kanan
	DrawBone(Index,15,9,Color);//telapak kaki kiri
	DrawBone(Index,14,8,Color);//telapak kaki kanan
}
