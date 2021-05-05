#pragma once

#include <windows.h>
#include <WinInet.h>
//#include <winhttp.h>
#include <strsafe.h>
#include "cJSON.h"
#include <process.h>
/*
函数作用：连接服务器
参数：
pURL		[in] 请求页面路径，如"/por/login_psw.csp?type=cs"

hInternet	[out] 返回Internet句柄
hSession	[out] Internet连接句柄
hRequest	[out] Internet 请求句柄
返回值:	TRUE 表示成功，FALSE表示失败
*/
BOOL ConnectServ(const char *pURL, HANDLE &hInternet, HANDLE &hSession, HANDLE &hRequest,
	const char *pVPNAddress , WORD wPort );

/*
函数作用：发送请求到服务器
参数：
hRequest	[in] 该请求句柄，为ConnectSERV函数第4个返回参数
pData		[in] 附带的数据，一般为post请求的参数
iDataLen	[in] pData长度，字节
返回值:	TRUE 表示成功，FALSE表示失败
*/
BOOL SendRequestToServ(HINTERNET hRequest, const char*pData, int iDataLen);





/*
函数作用：关闭Internet句柄
参数：
hInternet	[in] Internet句柄
hSession	[in] Internet连接句柄
hRequest	[in] Internet 请求句柄

返回值：成功返回TRUE，失败返回FALSE
*/


BOOL ClearHandle(HINTERNET &hInternet, HINTERNET &hSession, HINTERNET &hRequest);

/*
函数作用：发送请求到服务器
参数：
hRequest	[in] 该请求句柄，为ConnectServ函数第4个返回参数
pData		[in] 附带的数据，一般为post请求的参数
iDataLen	[in] pData长度，字节
返回值:	TRUE 表示成功，FALSE表示失败
*/
BOOL ReadServBackData(HINTERNET hRequest, char *&pData, DWORD &Len, BOOL bNeedReport);

// 清理JSON数据
void ClearJson(cJSON* json);

// 创建请求的JSON数据
BOOL CreateJsonReqData(char * pReq);

// 解析JSON数据
BOOL AnalyzeRecvData(char* pData);

void OutputDebugVal(const char * strOutputString, ...);
