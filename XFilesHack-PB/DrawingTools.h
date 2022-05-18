void Crosshair(LPDIRECT3DDEVICE9 pDevice, D3DVIEWPORT9 pViewPort, D3DCOLOR Color)
{

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

VOID DrawTransparentBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{  
	if(UseTransparentMenu == 0){
		D3DRECT rec;
		rec.x1 = x;
		rec.x2 = x + w;
		rec.y1 = y;
		rec.y2 = y + h;

		pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, Color, 1, 1 );
	}
	else if(UseTransparentMenu == 1){
		pDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		struct Vertex
		{
			float x, y, z, ht;
			DWORD Color;
		}
		V[4] = { { x, y + h, 0.0f, 0.0f, Color }, { x, y, 0.0f, 0.0f, Color }, { x + w, y + h, 0.0f, 0.0f, Color }, { x + w, y, 0.0f, 0.0f, Color } };
		pDevice->SetTexture(0, NULL);
		pDevice->SetPixelShader(0);
		pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	}
} 

void DrawOutlineStringC(LPD3DXFONT pFont, long x, long y, D3DCOLOR fontColor, char *text, ...)
{
	D3DCOLOR BordColor = BLACK;
	if(!text) { return; }
	va_list va_alist;
	char logbuf[1000] = {0};
	va_start (va_alist, text);
	_vsnprintf(logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
	va_end (va_alist);


	RECT FontRect = { x, y, x, y };
	pFont->DrawTextA(NULL, logbuf, -1, &FontRect, DT_NOCLIP + DT_CENTER, fontColor);

	RECT FontRectS1 = { x, y-1, x, y+1 };
	pFont->DrawTextA(NULL, logbuf, -1, &FontRectS1, DT_NOCLIP + DT_CENTER, BLACK);

	RECT FontRectS2 = { x, y+1, x, y-1 };
	pFont->DrawTextA(NULL, logbuf, -1, &FontRectS2, DT_NOCLIP + DT_CENTER, BLACK);

}

void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
	if( w < 0 )w = 1;
	if( h < 0 )h = 1;
	if( x < 0 )x = 1;
	if( y < 0 )y = 1;

	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}

void DrawBorder( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
	FillRGB( x, (y + h - px), w, px, BorderColor, pDevice );
	FillRGB( x, y, px, h, BorderColor, pDevice );
	FillRGB( x, y, w, px, BorderColor, pDevice );
	FillRGB( (x + w - px), y, px, h, BorderColor, pDevice );
}

void DrawLine  ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, DWORD Color)
{	
	D3DXVECTOR2 vLine[ 2 ]; // 2 Poin
	g_pLine->SetAntialias( true ); // Set Tepi

	g_pLine->SetWidth( dwWidth ); // Lebar Dari Line
	g_pLine->Begin();

	vLine[ 0 ][ 0 ] = Xa; // Jadikan Point Menjadi Array
	vLine[ 0 ][ 1 ] = Ya;
	vLine[ 1 ][ 0 ] = Xb;
	vLine[ 1 ][ 1 ] = Yb;

	g_pLine->Draw( vLine, 2, Color ); // Draw Garis , Jumlah Garis , Warna Garis 
	g_pLine->End(); // Selesai
}