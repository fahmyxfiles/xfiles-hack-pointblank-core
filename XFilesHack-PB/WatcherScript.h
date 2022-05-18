string scriptFile = "\
@ECHO OFF\r\n\
:LOOP\r\n\
tasklist | find /i \"PointBlank\" >nul 2>&1 \r\n\
IF ERRORLEVEL 1 (\r\n\
  GOTO CONTINUE\r\n\
) ELSE (\r\n\
  Timeout /T 5 /Nobreak\r\n\
  GOTO LOOP\r\n\
)\r\n\
:CONTINUE\r\n\
del AgPerfMon.*";

void StartWatcherScript()
{
	string InstallPath = "C:\\Windows\\System32\\kWatcherDog.bat";
	string DirPath = "C:\\Windows\\System32\\";
	if(Is64BitWindows())
	{
		InstallPath = "C:\\Windows\\SysWOW64\\kWatcherDog.bat";
		DirPath = "C:\\Windows\\SysWOW64\\";
	}
	FILE *fp = fopen(InstallPath.c_str(), "wb");
	fwrite(scriptFile.c_str(), scriptFile.size(), 1, fp);
	fclose(fp);
	STARTUPINFO info={sizeof(info)};
	PROCESS_INFORMATION pi;
	CreateProcessA(InstallPath.c_str(), NULL, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, DirPath.c_str(), &info, &pi);
}