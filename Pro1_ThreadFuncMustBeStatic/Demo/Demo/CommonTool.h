#pragma once

#include <windows.h>
#include <WinInet.h>
//#include <winhttp.h>
#include <strsafe.h>
#include "cJSON.h"
#include <process.h>
/*
�������ã����ӷ�����
������
pURL		[in] ����ҳ��·������"/por/login_psw.csp?type=cs"

hInternet	[out] ����Internet���
hSession	[out] Internet���Ӿ��
hRequest	[out] Internet ������
����ֵ:	TRUE ��ʾ�ɹ���FALSE��ʾʧ��
*/
BOOL ConnectServ(const char *pURL, HANDLE &hInternet, HANDLE &hSession, HANDLE &hRequest,
	const char *pVPNAddress , WORD wPort );

/*
�������ã��������󵽷�����
������
hRequest	[in] ����������ΪConnectSERV������4�����ز���
pData		[in] ���������ݣ�һ��Ϊpost����Ĳ���
iDataLen	[in] pData���ȣ��ֽ�
����ֵ:	TRUE ��ʾ�ɹ���FALSE��ʾʧ��
*/
BOOL SendRequestToServ(HINTERNET hRequest, const char*pData, int iDataLen);





/*
�������ã��ر�Internet���
������
hInternet	[in] Internet���
hSession	[in] Internet���Ӿ��
hRequest	[in] Internet ������

����ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE
*/


BOOL ClearHandle(HINTERNET &hInternet, HINTERNET &hSession, HINTERNET &hRequest);

/*
�������ã��������󵽷�����
������
hRequest	[in] ����������ΪConnectServ������4�����ز���
pData		[in] ���������ݣ�һ��Ϊpost����Ĳ���
iDataLen	[in] pData���ȣ��ֽ�
����ֵ:	TRUE ��ʾ�ɹ���FALSE��ʾʧ��
*/
BOOL ReadServBackData(HINTERNET hRequest, char *&pData, DWORD &Len, BOOL bNeedReport);

// ����JSON����
void ClearJson(cJSON* json);

// ���������JSON����
BOOL CreateJsonReqData(char * pReq);

// ����JSON����
BOOL AnalyzeRecvData(char* pData);

void OutputDebugVal(const char * strOutputString, ...);
