#include "HTTP.h"
#include "SMART.h"
#include "base64.h"
#include "md5.h"




#ifdef _MSC_VER
    #if _MSC_VER >= 1600
        #include <cstdint>
    #else
        typedef __int8              int8_t;
        typedef __int16             int16_t;
        typedef __int32             int32_t;
        typedef __int64             int64_t;
        typedef unsigned __int8     uint8_t;
        typedef unsigned __int16    uint16_t;
        typedef unsigned __int32    uint32_t;
        typedef unsigned __int64    uint64_t;
    #endif
#elif __GNUC__ >= 3
    #include <cstdint>
#endif

typedef int8_t      s8;
typedef int16_t     s16;
typedef int32_t     s32;
typedef int64_t     s64;
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;

char* CleanString(char* input)                                         
{
    signed int i,j;
    char *output=input;
    for (i = 0, j = 0; i<strlen(input); i++,j++)          
    {
        if (input[i]!=' ')                           
            output[j]=input[i];                     
        else
            j--;                                     
    }
    output[j]=0;
    return output;
}

SYSTEMTIME pTime = {0};
DWORD GenerateRandomNumber(int min, int max)
{
	
	
	GetSystemTime(&pTime);
	
	int randNum = pTime.wMilliseconds * rand()%(max-min + 1) + min;
	return randNum;
}
char* GenerateReplyClientKey() {
	char s[130] = {0};
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 128; ++i) {
        s[i] = alphanum[GenerateRandomNumber(20,150) % (sizeof(alphanum) - 1)];
    }

    s[128] = 0;
	return s;
}

char* GenerateEncryptClientKey() {
	char s[130] = {0};
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 128; ++i) {
        s[i] = alphanum[GenerateRandomNumber(20,150) % (sizeof(alphanum) - 1)];
    }

    s[128] = 0;
	return s;
}

string strtoupper(string str)
{
    int leng=str.length();
    for(int i=0; i<leng; i++)
        if (97<=str[i]&&str[i]<=122)//a-z
            str[i]-=32;
    return str;
}
string strtolower(string str)
{
    int leng=str.length();
    for(int i=0; i<leng; i++)
        if (65<=str[i]&&str[i]<=90)//A-Z
            str[i]+=32;
    return str;
}
string getVolumeSerialNum()       
{        
	DWORD serialNum = 0;   
	stringstream ss;

	// Determine if this volume uses an NTFS file system.      
	GetVolumeInformation( /*C:\\*/XorStr<0xF4,4,0xB2E95FD6>("\xB7\xCF\xAA"+0xB2E95FD6).s, NULL, 0, &serialNum, NULL, NULL, NULL, 0 );    
	ss << serialNum;
	return md5(ss.str());                    
}


u16 getVolumeHash()       
{        
	DWORD serialNum = 0;   

	// Determine if this volume uses an NTFS file system.      
	GetVolumeInformation( "C:\\", NULL, 0, &serialNum, NULL, NULL, NULL, 0 );    
	u16 hash = (u16)(( serialNum + ( serialNum >> 16 )) & 0xFFFF );              

	return hash;           
}

u16 getCpuHash()          
{        
	int cpuinfo[4] = { 0, 0, 0, 0 };                  
	__cpuid( cpuinfo, 0 );          
	u16 hash = 0;          
	u16* ptr = (u16*)(&cpuinfo[0]); 
	for ( u32 i = 0; i < 8; i++ )   
		hash += ptr[i];     

	return hash;           
}

const char* getMachineName()       
{        
	static char computerName[16]; 
	DWORD dwSize = 16;
	GetComputerName( computerName, &dwSize );           
	return computerName;   
}

std::string bin2hex(const std::string& input)
{
    std::string res;
    const char hex[] = "0123456789ABCDEF";
    for(int i = 0; i < input.size(); i++) { 
		char sc = input[i];
        unsigned char c = static_cast<unsigned char>(sc);
        res += hex[c >> 4];
        res += hex[c & 0xf];
    }

    return res;
}

std::string hex2bin(std::string s) {
    std::string rc;
    int nLen = s.length();
    int tmp;
    for (int i(0); i + 1 < nLen; i += 2) {
        if (std::istringstream(s.substr(i, 2)) >> std::hex >> tmp) {
            rc.push_back(tmp);
        }
    }
    return rc;
}

string bitxor(string toEncrypt, string key) {
    string output = toEncrypt;
    
    for (int i = 0; i < toEncrypt.length(); i++)
        output[i] = toEncrypt[i] ^ key[ i % key.length() ];
    
    return output;
}

ULONGLONG CalcDeltaSec(SYSTEMTIME CFTime, SYSTEMTIME XFTime)
{
    FILETIME ft1, ft2;
	ULARGE_INTEGER t1, t2;
	ULONGLONG diff;
	SystemTimeToFileTime(&CFTime, &ft1);
	SystemTimeToFileTime(&XFTime, &ft2);
	memcpy(&t1, &ft1, sizeof(t1));
	memcpy(&t2, &ft2, sizeof(t1));
	diff = (t1.QuadPart<t2.QuadPart)?(t2.QuadPart-t1.QuadPart):(t1.QuadPart-t2.QuadPart);
	return diff/10000000;
}

void convertStringToSystemTime(const char *dateTimeString, SYSTEMTIME& systime)
{
	int d, m, y, h, min, s;
    memset(&systime,0,sizeof(systime));
	sscanf_s(dateTimeString, /*%2d/%2d/%4d %2d:%2d:%2d*/XorStr<0x9C,24,0xEED0DE5A>("\xB9\xAF\xFA\xB0\x85\x93\xC6\x8C\x81\x91\xC2\x87\x8D\x9B\xCE\x91\x89\x9F\xCA\x95\x95\x83\xD6"+0xEED0DE5A).s, 
							&d,
							&m,
							&y,
							&h,
							&min,
							&s);
	systime.wDay = d;
	systime.wMonth = m;
	systime.wYear = y;
	systime.wHour = h;
	systime.wMinute = min;
	systime.wSecond = s;
}

bool StrEq(char* c1, char* c2)
{
	return(strcmp(c1, c2) == 0);
}
struct NetProtectServerResult{
	enum 
	{
		//================= Failed code ===============//
		TRANSMISSION_FAIL			= 0x94000101,
		INVALID_CID					= 0x94000102,
		INVALID_GID					= 0x94000103,
		INVALID_PRODUCT_STATUS		= 0x94000104,
		NOTFOUND					= 0x94000105,
		INVALID_STATUS				= 0x94000106,
		EXPIRED						= 0x94000107,
		INVALID_CLIENT				= 0x94000108,
		BLOCKED_CLIENT				= 0x94000109,
		MAXCLIENT_REACHED			= 0x94000110,
		VERSION_OUTDATED			= 0x94000111,
		UNKNOWN_RESULT				= 0x94000900,


		//================= Success Code ==============//
		VALID						= 0x94000200,
	};
};

struct S_PROFILE
{
	DWORD Id;
	char Username[30];
	DWORD Type;
	DWORD Duration;
	char ClientList[100];
	char Expiration[50];
};

struct S_PRODUCT
{
	char Name[50];
	char Alias[20];
	char Flags[50];
};

struct S_HACKPLAYERLIST
{
	
};

class cClientInfo
{
	char SelfPath[500];
	char ClientId[100];
	char LicenseKey[200];
	DWORD TimeDif;
	DWORD dwResult;
	DWORD dwGlobKey;
	char Message[250];
	

public:
	S_PROFILE profile;
	S_PRODUCT product;
	cClientInfo()
	{
		TimeDif = -1;
		dwResult = -1;
		dwGlobKey = -1;

		ZeroMemory(SelfPath,500);
		ZeroMemory(ClientId,50);
		ZeroMemory(LicenseKey,200);
		ZeroMemory(Message,250);
		ZeroMemory(&profile,sizeof(S_PROFILE));
		ZeroMemory(&product,sizeof(S_PRODUCT));

		GetModuleFileNameA(MyDll,SelfPath,500);
	}
	void SetProfile(S_PROFILE* NewProfile)
	{
		memcpy(&this->profile, NewProfile, sizeof(S_PROFILE));
	}
	void SetProduct(S_PRODUCT* NewProduct)
	{
		memcpy(&this->product, NewProduct, sizeof(S_PRODUCT));
	}
	void SetResult(DWORD dwStatus)
	{
		dwResult = dwStatus;
	}
	void SetMessage(const char *text, ...)
	{
		if(!text) { return; }
		va_list va_alist;
		char logbuf[250] = {0};
		va_start (va_alist, text);
		_vsnprintf(logbuf+strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
		va_end (va_alist);
		strcpy(Message, logbuf);
	}
	char* getMsg()
	{
		return Message;
	}
	char* getSelfClientId()
	{
		//return "iTGv1z6mszHVRuToRQcShMjYR1hw3q1ljIRlhXIJ";
		HANDLE hFile = CreateFileA(SelfPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, 0);
		if(hFile){
			DWORD ReadedBytes;
			SetFilePointer(hFile,0x400,NULL,FILE_BEGIN );
			ReadFile(hFile,ClientId,100,&ReadedBytes,0);
			CloseHandle(hFile);
			ClientId[32] = '\0';
			return ClientId;
		}
		return "";
	}
	char* getSelfLicenseKey(char* UnlockKey)
	{
		//return "iTGv1z6mszHVRuToRQcShMjYR1hw3q1ljIRlhXIJ";
		HANDLE hFile = CreateFileA(this->SelfPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, 0);
		if(hFile){
			DWORD ReadedBytes;
			SetFilePointer(hFile,0x420,NULL,FILE_BEGIN );
			ReadFile(hFile,LicenseKey,100,&ReadedBytes,0);
			CloseHandle(hFile);

			for(int i = 0; i < 50; i++)
				LicenseKey[i] = LicenseKey[i] ^ UnlockKey[i % strlen(UnlockKey)];

			char* License = strstr(LicenseKey,/*LICENSEKEY*/XorStr<0x6B,11,0xAA4C9E4A>("\x27\x25\x2E\x2B\x21\x23\x34\x39\x36\x2D"+0xAA4C9E4A).s);
			if(!License)return "";
			License[50] = '\0';
			return License + 10;
		}
		return "";
	}
};



cClientInfo* myClientInfo;

#define CLIENT_KEY /*ba4c52fee5acc9ea6f1c022d3f00e1c3*/XorStr<0x71,33,0xA23C6912>("\x13\x13\x47\x17\x40\x44\x11\x1D\x1C\x4F\x1A\x1F\x1E\x47\x1A\xE1\xB7\xE4\xB2\xE7\xB5\xB4\xB5\xEC\xBA\xEC\xBB\xBC\xE8\xBF\xEC\xA3"+0xA23C6912).s
#define SERVER_KEY /*f3abb28c84ed0efaa42be9851d41bf46*/XorStr<0x29,33,0xFB5287B2>("\x4F\x19\x4A\x4E\x4F\x1C\x17\x53\x09\x06\x56\x50\x05\x53\x51\x59\x58\x0E\x09\x5E\x58\x07\x07\x75\x70\x26\x77\x75\x27\x20\x73\x7E"+0xFB5287B2).s
#define CLIENT_UNLOCK_KEY /*f3abb28c84ed0efaa42be9851d41bf46*/XorStr<0xAA,33,0xBDE98F12>("\xCC\x98\xCD\xCF\xCC\x9D\x88\xD2\x8A\x87\xD1\xD1\x86\xD2\xDE\xD8\xDB\x8F\x8E\xDF\xDB\x86\xF8\xF4\xF3\xA7\xF0\xF4\xA4\xA1\xFC\xFF"+0xBDE98F12).s
#define GAME_ID /*PB*/XorStr<0x9A,3,0x05C0F5BD>("\xCA\xD9"+0x05C0F5BD).s
#define HACK_VERSION 10004

DWORD WINAPI CheckValidClientInfo(LPVOID param)
{
	if(!myClientInfo)
		myClientInfo = new cClientInfo();

	char ClientMainKey[40] = {0};
	strcpy(ClientMainKey, CLIENT_KEY);

	char ServerMainKey[40] = {0};
	strcpy(ServerMainKey, SERVER_KEY);

	// Generate Request Key
	char RequestKey[130] = {0};
	strcpy(RequestKey, GenerateEncryptClientKey());
	
	string encRequestKey = bitxor(string(RequestKey), string(ClientMainKey));

	std::string hexRequestKey = bin2hex(encRequestKey);
	// ------------------------------------------------------- GENERATE IDENTITY -----------------------------------------
	DiskInfo *SMARTDisk = new DiskInfo(0);
	SMARTDisk->LoadDiskInfo();

	char ClientFingerprint[50] = {0};
	sprintf(ClientFingerprint, /*%x-%x-%s*/XorStr<0x71,9,0x3CDC7A49>("\x54\x0A\x5E\x51\x0D\x5B\x52\x0B"+0x3CDC7A49).s, getCpuHash(), getVolumeHash(), getMachineName());
	strcpy(ClientFingerprint, md5(string(ClientFingerprint)).c_str());

	char ClientSerialNumber[50] = {0};
	strcpy(ClientSerialNumber, CleanString(SMARTDisk->SerialNumber()));

	if(strlen(ClientSerialNumber) < 5)
	{
		sprintf(ClientSerialNumber, "DS-%s", strtoupper(ClientFingerprint).c_str());
	}

	char ReplyClientKey[130] = {0};
	strcpy(ReplyClientKey, GenerateReplyClientKey());

	StringBuffer sMainDataBuffer;
	Writer<StringBuffer> writer(sMainDataBuffer);
	writer.StartObject(); 
	writer.Key(/*ClientID*/XorStr<0x30,9,0x01806980>("\x73\x5D\x5B\x56\x5A\x41\x7F\x73"+0x01806980).s);
	writer.String(myClientInfo->getSelfClientId());
	writer.Key(/*LicenseKey*/XorStr<0x93,11,0x54B21BA5>("\xDF\xFD\xF6\xF3\xF9\xEB\xFC\xD1\xFE\xE5"+0x54B21BA5).s);
	writer.String(myClientInfo->getSelfLicenseKey(CLIENT_UNLOCK_KEY));
	writer.Key(/*Fingerprint*/XorStr<0x81,12,0x44FA455C>("\xC7\xEB\xED\xE3\xE0\xF4\xF7\xFA\xE0\xE4\xFF"+0x44FA455C).s);
	writer.String(ClientFingerprint);
	writer.Key(/*ClientSerialNumber*/XorStr<0x10,19,0x0BEACE3F>("\x53\x7D\x7B\x76\x7A\x61\x45\x72\x6A\x70\x7B\x77\x52\x68\x73\x7D\x45\x53"+0x0BEACE3F).s);
	writer.String(ClientSerialNumber);
	writer.Key(/*GameID*/XorStr<0xF3,7,0x2D5D2A29>("\xB4\x95\x98\x93\xBE\xBC"+0x2D5D2A29).s);
	writer.String(GAME_ID);
	writer.Key(/*HackVersion*/XorStr<0xA2,12,0xCB1D0FA6>("\xEA\xC2\xC7\xCE\xF0\xC2\xDA\xDA\xC3\xC4\xC2"+0xCB1D0FA6).s);
	writer.Uint(HACK_VERSION);
	writer.Key(/*ReplyClientKey*/XorStr<0xEF,15,0x97334CC7>("\xBD\x95\x81\x9E\x8A\xB7\x99\x9F\x92\x96\x8D\xB1\x9E\x85"+0x97334CC7).s);
	writer.String(ReplyClientKey);
	writer.Key(/*ThreadStatus*/XorStr<0x31,13,0xA320171F>("\x65\x5A\x41\x51\x54\x52\x64\x4C\x58\x4E\x4E\x4F"+0xA320171F).s);
	writer.Bool(ThreadStarted);
	writer.EndObject();

	string encMainData = bitxor(string(sMainDataBuffer.GetString()), string(RequestKey));

	std::string hexMainData = bin2hex(encMainData);
	// ------------------------------------------------------- GENERATE USERINFO -----------------------------------------
	string encUserInfo = bitxor(string(sUserInfoBuffer.GetString()), string(RequestKey));

	std::string hexUserInfo = bin2hex(encUserInfo);
	// ------------------------------------------------------- GENERATE POST DATA -----------------------------------------
	std::string PostData = "x1=" + hexRequestKey + "&x2=" + hexMainData + "&x3=" + hexUserInfo;


	HTTP_REQUEST* myRequest = new HTTP_REQUEST;
	DWORD dwCode = 0, dwResponseCode = 0, dwContentLength = 0, dwBytesRead = 0;
	dwCode = HTTPInitRequest(myRequest, /*http://www.xfiles.co/v5/ClientHandler*/XorStr<0x8C,38,0xC93BD05B>("\xE4\xF9\xFA\xFF\xAA\xBE\xBD\xE4\xE3\xE2\xB8\xEF\xFE\xF0\xF6\xFE\xEF\xB3\xFD\xF0\x8F\xD7\x97\x8C\xE7\xC9\xCF\xC2\xC6\xDD\xE2\xCA\xC2\xC9\xC2\xCA\xC2"+0xC93BD05B).s);
	dwCode = HTTPSendRequest(myRequest, &dwResponseCode, &dwContentLength, /*POST*/XorStr<0x19,5,0xB34A8711>("\x49\x55\x48\x48"+0xB34A8711).s, PostData.c_str());
	if(dwContentLength == 0)
	{
		dwContentLength = 1000;
	}
	if(dwResponseCode == 200)
	{
		LPSTR Buffer = new TCHAR[dwContentLength];
		HTTPReadRequest(myRequest, Buffer, dwContentLength, &dwBytesRead);

		stringstream sbuf;
		string line;

		// START DECRYPT SEQUENCE ------------------------------------------------
		sbuf << Buffer;
		// Get MainData
		getline(sbuf, line);
		string MainResponse = hex2bin(line);

		// Get ReplyServerKey
		getline(sbuf, line);
		string ReplyServerKey = hex2bin(line);

		sbuf.clear();
		line.clear();

		char dcReplyServerKey[130] = {0};
		for(int i = 0; i < ReplyServerKey.size(); i++)
		{
			dcReplyServerKey[i] = ReplyServerKey.c_str()[i] ^ ServerMainKey [ i % strlen(ServerMainKey) ];
		}
		dcReplyServerKey[ReplyServerKey.size()] = '\0';

		string handShakeKey;

		for(int i = 0; i < 128; i++)
		{
			handShakeKey += dcReplyServerKey[i];
			handShakeKey += ReplyClientKey[i];
		}

		char* dcMainResponse = new char[MainResponse.size() + 1];
		SecureZeroMemory(dcMainResponse, MainResponse.size());
		for(int i = 0; i < MainResponse.size(); i++)
		{
			dcMainResponse[i] = MainResponse.c_str()[i] ^ handShakeKey.c_str() [ i % handShakeKey.length() ];
		}
		dcMainResponse[MainResponse.size()] = '\0';
		// END DECRYPT SEQUENCE ------------------------------------------------
		// START PARSE SEQUENCE ------------------------------------------------
		sbuf << dcMainResponse;
		// PARSE DATE ----------------------------------------------------------
		getline(sbuf, line);

		SYSTEMTIME ServerTime;
		convertStringToSystemTime(line.c_str(), ServerTime);
		ULONGLONG dif = CalcDeltaSec(myRequest->srvTime, ServerTime);
		if(dif > 60 || dif < 0)
		{
			myClientInfo->SetResult(NetProtectServerResult::TRANSMISSION_FAIL);
			return NetProtectServerResult::TRANSMISSION_FAIL;
		}
		// PARSE FIRST RESULT -------------------------------------------------
		getline(sbuf, line);
		if(!line.compare(/*INVALID_CID*/XorStr<0x28,12,0x640683CA>("\x61\x67\x7C\x6A\x60\x64\x6A\x70\x73\x78\x76"+0x640683CA).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::INVALID_CID);
			return NetProtectServerResult::INVALID_CID;
		}
		else if(!line.compare(/*INVALID_GID*/XorStr<0xB1,12,0xAA967962>("\xF8\xFC\xE5\xF5\xF9\xFF\xF3\xE7\xFE\xF3\xFF"+0xAA967962).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::INVALID_GID);
			return NetProtectServerResult::INVALID_GID;
		}
		else if(!line.compare(/*INVALID_PRODUCT_STATUS*/XorStr<0xF6,23,0xE3737D53>("\xBF\xB9\xAE\xB8\xB6\xB2\xB8\xA2\xAE\xAD\x4F\x45\x57\x40\x50\x5A\x55\x53\x49\x5D\x5F\x58"+0xE3737D53).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::INVALID_PRODUCT_STATUS);
			return NetProtectServerResult::INVALID_PRODUCT_STATUS;
		}
		else if(!line.compare(/*NOTFOUND*/XorStr<0x0F,9,0xB89EC527>("\x41\x5F\x45\x54\x5C\x41\x5B\x52"+0xB89EC527).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::NOTFOUND);
			return NetProtectServerResult::NOTFOUND;
		}
		else if(!line.compare(/*INVALID_STATUS*/XorStr<0x19,15,0x3447059E>("\x50\x54\x4D\x5D\x51\x57\x5B\x7F\x72\x76\x62\x70\x70\x75"+0x3447059E).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::INVALID_STATUS);
			return NetProtectServerResult::INVALID_STATUS;
		}
		else if(!line.compare(/*EXPIRED*/XorStr<0xD5,8,0xB6EF6841>("\x90\x8E\x87\x91\x8B\x9F\x9F"+0xB6EF6841).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::EXPIRED);

			getline(sbuf, line);
			myClientInfo->SetMessage(line.c_str());
			return NetProtectServerResult::EXPIRED;
		}
		else if(!line.compare(/*INVALID_CLIENT*/XorStr<0x12,15,0xEE5895B8>("\x5B\x5D\x42\x54\x5A\x5E\x5C\x46\x59\x57\x55\x58\x50\x4B"+0xEE5895B8).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::INVALID_CLIENT);
			return NetProtectServerResult::INVALID_CLIENT;
		}
		else if(!line.compare(/*BLOCKED_CLIENT*/XorStr<0x4B,15,0x1E2EF6B8>("\x09\x00\x02\x0D\x04\x15\x15\x0D\x10\x18\x1C\x13\x19\x0C"+0x1E2EF6B8).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::BLOCKED_CLIENT);
			return NetProtectServerResult::BLOCKED_CLIENT;
		}
		else if(!line.compare(/*MAXCLIENT_REACHED*/XorStr<0xB6,18,0x164EBE3B>("\xFB\xF6\xE0\xFA\xF6\xF2\xF9\xF3\xEA\xE0\x92\x84\x83\x80\x8C\x80\x82"+0x164EBE3B).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::MAXCLIENT_REACHED);
			return NetProtectServerResult::MAXCLIENT_REACHED;
		}
		else if(!line.compare(/*VERSION_OUTDATED*/XorStr<0x7F,17,0x9C475ED1>("\x29\xC5\xD3\xD1\xCA\xCB\xCB\xD9\xC8\xDD\xDD\xCE\xCA\xD8\xC8\xCA"+0x9C475ED1).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::VERSION_OUTDATED);
			return NetProtectServerResult::VERSION_OUTDATED;
		}
		else if(line.compare(/*VALID*/XorStr<0x64,6,0xF2A2986F>("\x32\x24\x2A\x2E\x2C"+0xF2A2986F).s))
		{
			myClientInfo->SetResult(NetProtectServerResult::UNKNOWN_RESULT);
			return NetProtectServerResult::UNKNOWN_RESULT;
		}
		
		//-----------------------------------------------------------------------
		S_PROFILE profile;
		SecureZeroMemory(&profile, sizeof(S_PROFILE));

		// UserId
		getline(sbuf, line);
		profile.Id = atoi(line.c_str());

		// Username
		getline(sbuf, line);
		strcpy(profile.Username, line.c_str());

		// LicenseType
		getline(sbuf, line);
		profile.Type = atoi(line.c_str());

		// License Duration
		getline(sbuf, line);
		profile.Duration = atoi(line.c_str());

		// ClientList
		getline(sbuf, line);
		if(line.find(ClientSerialNumber) == string::npos)
		{
			myClientInfo->SetResult(NetProtectServerResult::INVALID_CLIENT);
			return NetProtectServerResult::INVALID_CLIENT;
		}
		strcpy(profile.ClientList, line.c_str());

		// Expiration
		getline(sbuf, line);
		strcpy(profile.Expiration, line.c_str());

		myClientInfo->SetProfile(&profile);

		//-----------------------------------------------------------------------
		S_PRODUCT product;
		SecureZeroMemory(&product, sizeof(S_PRODUCT));
		// Name
		getline(sbuf, line);
		strcpy(product.Name, line.c_str());

		// Alias
		getline(sbuf, line);
		strcpy(product.Alias, line.c_str());

		// Alias
		getline(sbuf, line);
		strcpy(product.Flags, line.c_str());

		myClientInfo->SetProduct(&product);

		//-----------------------------------------------------------------------
		// HackingNetwork Player List
		getline(sbuf, line);
		dHackingNetworkListBuffer.Parse(line.c_str());
		
		myClientInfo->SetResult(NetProtectServerResult::VALID);
		
		return NetProtectServerResult::VALID;
	}
	return NetProtectServerResult::TRANSMISSION_FAIL;
}