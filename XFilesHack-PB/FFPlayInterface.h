bool bAdsPlayed = false;
bool bProcessCreated = false;
bool bWindowAppeared = false;
bool bThreadCreated = false;
HANDLE hThread = NULL;
HWND MyOriginalWindow = NULL;
STARTUPINFO info={0};
PROCESS_INFORMATION processInfo;
void TopMostThread()
{
	while(bAdsPlayed == false)
	{
		DWORD dwExitCode = 0;
		if(GetExitCodeProcess(processInfo.hProcess,&dwExitCode)){
			if(dwExitCode==STILL_ACTIVE) {
				HWND hFind = FindWindow(NULL, "XF_FFPlay_IFace");
				::ShowWindow(hFind, SW_SHOW);
				::SetForegroundWindow(hFind);
				::BringWindowToTop(hFind);
			}
			else {
				while(GetForegroundWindow() != MyOriginalWindow)
				{
					::ShowWindow(MyOriginalWindow, SW_SHOW);
					::SetForegroundWindow(MyOriginalWindow);
					::BringWindowToTop(MyOriginalWindow);
				}
				bAdsPlayed = true;
			}
		}
		Sleep(10);
	}
}

bool AdsPlay()
{
	if(bAdsPlayed == false){
		if(bProcessCreated == false){
			MyOriginalWindow = GetForegroundWindow();
			::ShowWindow(MyOriginalWindow, SW_MINIMIZE);
			CreateProcessA("C:\\ffplay.exe", 
				" -noborder -x 1366 -y 768 -window_title XF_FFPlay_IFace -autoexit http://www.xfiles.co/files/play.mp4" , 
				NULL, 
				NULL, 
				TRUE, 
				CREATE_NO_WINDOW, 
				NULL,
				"C:\\",
				&info, 
				&processInfo);
			bProcessCreated = true;
		}
		if(bProcessCreated){
			if(hThread == NULL)hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)TopMostThread,0,0,0);
		}
	}
	return bAdsPlayed;
}