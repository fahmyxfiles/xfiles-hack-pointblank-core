#include <tchar.h>
#include "BugTrap\BugTrap.h"
#pragma comment(lib, "BugTrap\\BugTrap.lib")
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

void SetupBugtrapHandler()
{
	// Setup exception handler
	BT_SetAppName(_T("XFilesHack"));
	BT_SetSupportEMail(_T("fahmy.xfiles@gmail.com"));
	BT_SetFlags(BTF_DETAILEDMODE | BTF_EDITMAIL | BTF_ATTACHREPORT| BTF_SCREENCAPTURE);
	BT_SetSupportURL(_T("http://www.xfiles.co"));

	BT_InstallSehFilter();
}