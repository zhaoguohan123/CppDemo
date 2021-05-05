#include "stdafx.h"
#include "CommonTool.h"

#define REQ_JSON "{}" 
#define PUT_PUT_DEBUG_BUF_LEN   1024

void OutputDebugVal(const char * strOutputString, ...)
{
	char strBuffer[PUT_PUT_DEBUG_BUF_LEN] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);
	va_end(vlArgs);
	OutputDebugStringA(strBuffer);  
}


BOOL ClearHandle(HINTERNET &hInternet, HINTERNET &hSession, HINTERNET &hRequest)
{
	if (hInternet != NULL)
	{
		InternetCloseHandle(hInternet);
		hInternet = NULL;
	}
	if (hSession != NULL)
	{
		InternetCloseHandle(hSession);
		hSession = NULL;
	}
	if (hRequest != NULL)
	{
		InternetCloseHandle(hRequest);
		hRequest = NULL;
	}
	return TRUE;
}

BOOL ConnectServ(const char *pURL, HANDLE &hInternet, HANDLE &hSession, HANDLE &hRequest, const char *pSERVAddress, WORD wPort = 0)
{
	if (pURL == NULL)
	{
		OutputDebugStringA("### [ConnectServer] falied, pURL is NULL");
		return FALSE;
	}
	hInternet = NULL;
	hSession = NULL;
	hRequest = NULL;

	
	hInternet = InternetOpenA("TestCS",INTERNET_OPEN_TYPE_DIRECT, NULL,NULL,0);
	if (hInternet == NULL)
	{
		OutputDebugStringA("### [ConnectServer] InternetOpenA falied");
		return FALSE;
	}

	DWORD dwTimeOut = 1000 * 6 * 2;
	InternetSetOption(hInternet, INTERNET_OPTION_CONNECT_TIMEOUT, &dwTimeOut, sizeof(DWORD));
	InternetSetOption(hInternet, INTERNET_OPTION_SEND_TIMEOUT, &dwTimeOut, sizeof(DWORD));
	InternetSetOption(hInternet, INTERNET_OPTION_DATA_SEND_TIMEOUT, &dwTimeOut, sizeof(DWORD));
	InternetSetOption(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &dwTimeOut, sizeof(DWORD));

	hSession = InternetConnectA(hInternet, pSERVAddress, wPort, "", "", INTERNET_SERVICE_HTTP, 0, 0);
	if (hSession == NULL)
	{
		OutputDebugStringA("### [ConnectServer] InternetConnectA falied");
		ClearHandle(hInternet, hSession, hRequest);
		return FALSE;
	}
	//DWORD 	secureFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_NO_CACHE_WRITE |
	//	INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
	DWORD 	secureFlags =  SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID | SECURITY_FLAG_IGNORE_CERT_CN_INVALID;
	const char *pAccept = NULL;
	hRequest = HttpOpenRequestA(hSession, "POST", pURL, NULL, NULL, &pAccept, secureFlags, 0);
	if (hRequest == NULL)
	{
		OutputDebugStringA("### [ConnectServer] HttpOpenRequestA falied");
		ClearHandle(hInternet, hSession, hRequest);
		return FALSE;
	}
	OutputDebugStringA("### [ConnectServer] ConnectServ success");
	return TRUE;
}

BOOL SendRequestToServ(HINTERNET hRequest, const char*pData, int iDataLen) 
{
	if (hRequest == NULL )
	{
		OutputDebugStringA("### [SendRequestToServ] falied, hRequest is NULL");
		return FALSE;
	}
	CHAR hdrs[] = "Content-Type: application/json";
	DWORD dwTryTime = 5;   //����5��
	BOOL bSendSucc = FALSE;

	while (dwTryTime--)
	{
		bSendSucc = HttpSendRequestA(hRequest, hdrs, strlen(hdrs), (void *)pData, iDataLen);
		DWORD dwErrCode = GetLastError(); // ���� ����ֵ����������ʧ�ܵ����
		if (bSendSucc == TRUE)
		{
			break;
		}
		if (dwErrCode == ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED)//�ͻ�����Ҫ�ύ֤��
		{
			OutputDebugStringA("### [SendRequestToServ][HttpSendRequestA] falied �ͻ�����Ҫ�ύ֤��");
		}
		else if (dwErrCode == ERROR_INTERNET_INVALID_CA)//������֤����Ч
		{
			OutputDebugStringA("### [SendRequestToServ][HttpSendRequestA] falied ������֤����Ч");
		}
		else
		{
			OutputDebugVal("### [SendRequestToServ][HttpSendRequestA] falied. %u\n", dwErrCode);
			break;
		}
	}
	return  bSendSucc;
}

BOOL ReadServBackData(HINTERNET hRequest, char *&pData, DWORD &Len, BOOL bNeedReport) 
{
	  if (hRequest == NULL)
	  {
		  OutputDebugStringA("[ReadServBackData] falied, hRequest is NULL");
		  return FALSE;
	  }

	  DWORD dwResourceSize = 0;
	  DWORD dwIndex = 0;
	  char strSize[1024] = { 0 };
	  DWORD dwSize = sizeof(strSize);
	  DWORD dwBufflen = 64 * 1024;//64k

	  BOOL bRet = HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE, strSize, &dwSize, &dwIndex);//��ȡͷ��״̬
	  if (bRet == NULL)
	  {
		  OutputDebugStringA("[ReadServBackData] HttpQueryInfo falied, bRet is NULL");
		  return FALSE;
	  }
	  else
	  {
		  int ret = atoi(strSize);
		  if (ret != HTTP_STATUS_OK)
		  {
			  OutputDebugStringA("[ReadServBackData] HttpQueryInfo falied, bRet is not HTTP_STATUS_OK");
			  return FALSE;
		  }
	  }

	  dwSize = sizeof(strSize);
	  bRet = HttpQueryInfo(hRequest, HTTP_QUERY_CONTENT_LENGTH, strSize, &dwSize, &dwIndex);//��ȡͷ����С
	  if (bRet == TRUE)
	  {
		  dwResourceSize = atoi(strSize);
	  }
	  if (dwResourceSize != 0)
	  {
		  dwBufflen = dwResourceSize + 1;
	  }

	  char * pReadData = new char[dwBufflen];
	  if (pReadData == NULL)
	  {
		  OutputDebugStringA("[ReadServBackData] pReadData is NULL");
		  return FALSE;
	  }
	  memset(pReadData, 0, dwBufflen);
	  BOOL bSucc = FALSE;
	  DWORD dwTotalReadLen = 0;
	  while (true) 
	  {
		  DWORD dwReadLen = 0;
		  BOOL bRet = InternetReadFile(hRequest, pReadData + dwTotalReadLen, dwBufflen - dwTotalReadLen, &dwReadLen);
		  DWORD dwErrCode = GetLastError();
		  if (bRet == TRUE)//�ɹ�
		  {
			  dwTotalReadLen += dwReadLen;//�ۼӼ�����

			  if ((dwReadLen == 0) || (dwTotalReadLen == dwResourceSize))//����
			  {
				  bSucc = TRUE;
				  break;
			  }
			  if (bNeedReport == TRUE)
			  {
				  //��Ҫ���лص�
			  }
		  }
		  else  if ((dwErrCode != ERROR_INSUFFICIENT_BUFFER) && (dwErrCode != ERROR_NO_MORE_ITEMS))
		  {
			  OutputDebugStringA("[ReadServBackData] InternetReadFile  Fail %u");
			  break;
		  }
		  //ִ�е����������ȡ���ݳɹ������ߴ��󣬵��Ǵ���ԭ����û�л�������
		  if ((dwBufflen - dwTotalReadLen == 0) || ((bRet == FALSE) &&
			  (dwErrCode == ERROR_INSUFFICIENT_BUFFER || dwErrCode == ERROR_NO_MORE_ITEMS)))
		  {
			  dwBufflen *= 2;//����һ����С
			  char *pNewData = new char[dwBufflen];
			  if (pNewData == NULL)
			  {
				  delete[] pReadData;
				  break;
			  }
			  memset(pNewData, 0, dwBufflen);
			  memcpy(pNewData, pReadData, dwTotalReadLen);
			  delete[] pReadData;
			  pReadData = pNewData;
		  }
	  }
	if (bSucc == TRUE)
	{
		pData = pReadData;
		Len = dwTotalReadLen;
	}
	else
	{
		delete[] pReadData;
		pReadData = NULL;
	}
	return bSucc;
}

void ClearJson(cJSON* json)
{
	if (json)
	{
		cJSON_free(json);
		json = NULL;
	}
}

BOOL CreateJsonReqData(char * pReq) 
{
	const int dataLen = 32;
	BOOL bRet = FALSE;
	cJSON *pPostData = NULL;
	char *pJsonReqData = NULL;
	pPostData = cJSON_Parse(REQ_JSON);
	if (pPostData == NULL)
	{
		OutputDebugStringA("### [CreateJsonReqData]  pPostData is NULL");
		return FALSE;
	}
	// ���json�ڵ�����
	char username[dataLen] = "zgh";
	if (cJSON_AddStringToObject(pPostData, "username", username) == NULL)
	{
		goto clean;
	}
	char password[dataLen] = "123456789";
	if (cJSON_AddStringToObject(pPostData, "password", password) == NULL)
	{
		goto clean;
	}
	pJsonReqData = cJSON_Print(pPostData);
	if (pJsonReqData == NULL)
	{
		OutputDebugStringA("### [CreateJsonReqData] JsonReqData is NULL");
	}
	else
	{
		bRet = TRUE;
		StringCchCopy(pReq, 1024, pJsonReqData);
	}
	OutputDebugStringA("### [CreateJsonReqData] success");
clean:
	ClearJson(pPostData);
	return bRet;
}

BOOL AnalyzeRecvData(char* pData) 
{
	BOOL bRet = NULL;
	cJSON *pRecvData = NULL;
	cJSON *pResult = NULL;
	cJSON *pChildData = NULL;
	cJSON *pAccessToken = NULL;

	//��������Ϣת��ΪJSON��ʽ
	pRecvData = cJSON_Parse(pData);
	if (pRecvData == NULL)
	{
		goto clean;
	}
	//�ж��Ƿ�ɹ���ȡaccesstoken
	pResult = cJSON_GetObjectItem(pRecvData, "success");
	if (pResult == NULL)
	{
		goto clean;
	}

	//��ȡ�ӽڵ�data
	pChildData = cJSON_GetObjectItem(pRecvData, "data");
	if (pChildData == NULL)
	{
		goto clean;
	}
	//��ȡ��accesstoken
	pAccessToken = cJSON_GetObjectItem(pChildData, "access_token");
	if (pAccessToken == NULL)
	{
		goto clean;
	}
	char ret[512] = { 0 };
	StringCchCopyA(ret, 512, cJSON_GetStringValue(pAccessToken));
	
	OutputDebugStringA("### [AnalyzeRecvData] success");
	OutputDebugVal("##### access_token : %s", cJSON_GetStringValue(pAccessToken));
	OutputDebugStringA("### [AnalyzeRecvData] print success");

clean:
	ClearJson(pRecvData);
	ClearJson(pResult);
	ClearJson(pAccessToken);
	ClearJson(pChildData);
	return bRet;
}