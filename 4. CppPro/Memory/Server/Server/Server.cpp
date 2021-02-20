// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
int main()
{
	WORD sockVersion = MAKEWORD(2, 2); // ָ��winsock�汾

	WSAData wsaData;
	if (WSAStartup(sockVersion, &wsaData)!=0) //ֻ����һ�Σ��ú����ɹ����ٵ��ý�һ����Windows Sockets API����
	{
		printf("WSAStartup error");
		return 0;
	}

	// 1. �����׽���  socket
	//AF_INET��ʾIPv4��SOCK_STREAM���ݴ��䷽ʽ��IPPROTO_TCP����Э��; 
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("�׽��ִ���ʧ��");
		WSACleanup();
		return 0;
	}

	// 2. ���׽��ֵ�һ��IP��ַ��һ���˿��� bind
	sockaddr_in addrListen;
	addrListen.sin_family = AF_INET;
	addrListen.sin_port = htons(8888);
	addrListen.sin_addr.S_un.S_addr = INADDR_ANY;  //��ʾ�κ�IP   service.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(listenSocket, (SOCKADDR*)&addrListen, sizeof(addrListen)) == SOCKET_ERROR) 
	{
		printf("��ʧ��");
		closesocket(listenSocket);
		return 0;
	}
	//3. ����ָ���˿� listen

	if (listen(listenSocket, 5) == SOCKET_ERROR) // 5: �ȴ����Ӷ��е���󳤶ȡ�
	{
		printf("��������");
		closesocket(listenSocket);
		return 0;
	}


	//4. �ȴ�����, ���Ӻ���һ���µ��׽��� accept
	SOCKET revSocket;  //��Ӧ��ʱ���������ӵ��׽��ֵľ��
	sockaddr_in remoteAddr;   //�������ӵ��������ϵĵ�ַ��Ϣ
	int remoteAddrLen = sizeof(remoteAddr);
	printf("�ȴ�����...\n");
	/*�ȴ��ͻ������󣬷�������������*/
	revSocket = accept(listenSocket, (SOCKADDR*)&remoteAddr, &remoteAddrLen);  //�ȴ��ͻ��˽��룬ֱ���пͻ�����������Ϊֹ
	if (revSocket == INVALID_SOCKET)
	{
		printf("�ͻ��˷������󣬷�������������ʧ�ܣ�%d \n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return 0;
	}
	else
	{
		printf("�ͷ�����������������ӳɹ�\n");
	}
	// 5. recv��send
	while (1)
	{
		char revData[255] = "";
		/*ͨ�����������ӽ���ͨ��*/
		int res = recv(revSocket, revData, 255, 0);
		if (res > 0)
		{
			printf("Bytes received: %d\n", res);
			printf("�ͻ��˷��͵�����: %s\n", revData);
		}
		else if (res == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());
	}
	closesocket(revSocket);
	closesocket(listenSocket);
	WSACleanup();
	getchar();
    return 0;
}

