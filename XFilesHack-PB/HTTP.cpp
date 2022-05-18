#pragma comment(lib, "wininet.lib")
#include "HTTP.h"

BOOL isHttps(LPCSTR url);

BOOL isHttp(LPCSTR url);

BOOL isHttpProtocol(LPCSTR url);

BOOL strEqual(LPCSTR a, LPCSTR b);

LPSTR getDomain(LPCSTR url);

LPSTR getPath(LPCSTR url);

LPCSTR postMIME = "Content-Type: application/x-www-form-urlencoded";

HINTERNET hSession = NULL;

LPCSTR userAgent = "Mozilla/5.0 (Windows NT 6.3;)";

DWORD HTTPInitRequest(HTTP_REQUEST* id, LPCSTR url) {

    id->url = new CHAR[lstrlen(url) + 1];

    lstrcpy(id->url, url);

    BOOL https = isHttps(id->url);

    if (!isHttpProtocol(id->url)) return FALSE;

    if (!hSession) hSession = InternetOpen(userAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);

    if (!hSession) {
        return HTTP_ERR_NO_SESSION;
    }

    id->connection = InternetConnect(hSession, getDomain(id->url), https ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, NULL, NULL);

    if (id->connection) {
        return HTTP_ERR_COULD_NOT_CONNECT;
    }

    return HTTP_ERR_SUCCESS;
}

DWORD HTTPSetHeader(HTTP_REQUEST* id, LPCSTR name, LPCSTR data) {
    LPSTR header = new CHAR[lstrlen(name) + lstrlen(": ") + lstrlen(data) + 1];

    lstrcpy(header, name);
    lstrcat(header, ": ");
    lstrcat(header, data);
    header[lstrlen(header)] = NULL;

    if (!HttpAddRequestHeaders(id->request, header, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE)) {
        return HTTP_ERR_HEADER_NOT_SET;
    }

    return HTTP_ERR_SUCCESS;
}

DWORD HTTPSendRequest(HTTP_REQUEST* id, LPDWORD responseCode, LPDWORD contentLength, LPCSTR verb, LPCSTR postData) {

    BOOL post = strEqual(verb, "POST");

    BOOL https = isHttps(id->url);

    id->request = HttpOpenRequest(id->connection, verb, getPath(id->url), "HTTP/1.1", NULL, NULL, https ? INTERNET_FLAG_SECURE : NULL, NULL);

    if (!HttpSendRequest(id->request, post ? postMIME : NULL, post ? lstrlen(postMIME) : NULL, (LPVOID) (post ? postData : NULL), post ? lstrlen(postData) : NULL)) {
        return HTTP_ERR_COULD_NOT_SEND_REQUEST;
    }

	TIME_ZONE_INFORMATION TimeZoneInfo;
	SecureZeroMemory(&TimeZoneInfo, sizeof(TIME_ZONE_INFORMATION));
	TimeZoneInfo.Bias = -420;

	SYSTEMTIME cloudFlareTime;
	SecureZeroMemory(&id->srvTime, sizeof(SYSTEMTIME));
	SecureZeroMemory(&cloudFlareTime, sizeof(SYSTEMTIME));


	DWORD buffSize = sizeof(DWORD);

    if (!HttpQueryInfo(id->request, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, responseCode, &buffSize, NULL)) {
        return HTTP_ERR_QUERY_FAILED;
    }
	
	DWORD dwSize = sizeof(SYSTEMTIME);
	if (!HttpQueryInfo(id->request, HTTP_QUERY_DATE | HTTP_QUERY_FLAG_SYSTEMTIME, &cloudFlareTime, &dwSize, NULL))
	{
		 return HTTP_ERR_QUERY_FAILED;
	}

	SystemTimeToTzSpecificLocalTime(&TimeZoneInfo, &cloudFlareTime, &id->srvTime);

	

    if (!HttpQueryInfo(id->request, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, contentLength, &buffSize, NULL)) {
        return HTTP_ERR_QUERY_FAILED;
    }

    return HTTP_ERR_SUCCESS;
}

DWORD HTTPReadRequest(HTTP_REQUEST* id, LPSTR responseBuffer, DWORD bufferLength, LPDWORD bytesRead) {
    if (!id->request || !id->connection) return HTTP_ERR_INVALID_CONNECTION;

    if (!InternetReadFile(id->request, responseBuffer, bufferLength, bytesRead)) {
        InternetCloseHandle(id->request);
        InternetCloseHandle(id->connection);
        return HTTP_ERR_COULD_NOT_READ_FILE;
    }


    responseBuffer[*bytesRead] = NULL;

    InternetCloseHandle(id->request);
    InternetCloseHandle(id->connection);

    return HTTP_ERR_SUCCESS;
}

LPSTR getDomain(LPCSTR url) {

    BOOL https = isHttps(url);

    LPCSTR sig = https ? "https://" : "http://";

    LPVOID lv = (LPVOID) url;

    LPSTR index = (LPSTR) lv;

    for (int i = 0; i < lstrlen(sig); i++) {
        if (url[i] == sig[i])  {
            index++;
            continue;
        }
        else return NULL;
    }

    DWORD domainLength = 0;

    int i = 0;
    while (index[i++] != '/') domainLength++;

    LPSTR result = new CHAR[domainLength+1];

    memcpy(result, index, domainLength);

    result[domainLength] = NULL;

    return result;
}

LPSTR getPath(LPCSTR url) {

    BOOL https = isHttps(url);

    LPCSTR sig = https ? "https://" : "http://";

    LPVOID lv = (LPVOID)url;

    LPSTR index = (LPSTR)lv;

    for (int i = 0; i < lstrlen(sig); i++) {
        if (url[i] == sig[i])  {
            index++;
            continue;
        }
        else return NULL;
    }

    DWORD domainLength = 0;

    int i = 0;
    while (index[i++] != '/') domainLength++;
    i = 0;

    index += domainLength;

    DWORD pathLength = 0;

    while (index[i++] != NULL) pathLength++;

    LPSTR result = new CHAR[pathLength];

    lstrcpy(result, index);

    return result;
}

BOOL isHttpProtocol(LPCSTR url) {
    return isHttps(url) ? TRUE : isHttp(url);
}

BOOL isHttps(LPCSTR url) {
    LPSTR https = "https://";

    for (int i = 0; i < lstrlen(https); i++) if (url[i] != https[i]) return FALSE;

    return TRUE;
}

BOOL isHttp(LPCSTR url) {
    LPSTR http = "http://";

    for (int i = 0; i < lstrlen(http); i++) if (url[i] != http[i]) return FALSE;

    return TRUE;
}

BOOL strEqual(LPCSTR a, LPCSTR b) {
    return !lstrcmp(a, b);
}