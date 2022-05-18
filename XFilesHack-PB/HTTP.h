#include <Windows.h>
#include <WinInet.h>

typedef struct {
    LPSTR url;
    HINTERNET request;
    HINTERNET connection;
	SYSTEMTIME srvTime;
} HTTP_REQUEST;

DWORD HTTPInitRequest(HTTP_REQUEST* id, LPCSTR url);
DWORD HTTPSetHeader(HTTP_REQUEST* id, LPCSTR name, LPCSTR data);
DWORD HTTPSendRequest(HTTP_REQUEST* id, LPDWORD responseCode, LPDWORD contentLength, LPCSTR verb = "GET", LPCSTR postData = NULL);
DWORD HTTPReadRequest(HTTP_REQUEST* id, LPSTR responseBuffer, DWORD bufferLength, LPDWORD bytesRead);
//Errors

#define HTTP_ERR_SUCCESS 0x0 //Everything completed successfully

#define HTTP_ERR_COULD_NOT_CONNECT 0x1 //The computer is either not connected to the internet or an invalid domain was specified

#define HTTP_ERR_NO_SESSION 0x2 //The function failed to create a session

#define HTTP_ERR_COULD_NOT_SEND_REQUEST 0x3

#define HTTP_ERR_QUERY_FAILED 0x4

#define HTTP_ERR_INVALID_CONNECTION 0x5

#define HTTP_ERR_COULD_NOT_READ_FILE 0x6

#define HTTP_ERR_HEADER_NOT_SET 0x7