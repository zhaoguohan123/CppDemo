// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket !");
		return 0; 
	}

	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	//serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", &(serAddr.sin_addr.S_un.S_addr)); // vs2013后不使用inet_addr
	if (connect(sclient, (struct sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}
	

	char * sendData = "csi接收  二进制文件未解析\n";
	send(sclient, sendData, strlen(sendData), 0);
		/*char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0)
		{

		recData[ret] = 0x00;
		//printf(recData);
		printf("%d%s",i,recData);
		}
		*/
	while(1)
	{
		printf("请输入要发送的数据：\n");
		char senddata[128] = { 0 };
		cin.getline(senddata,20);
		send(sclient, senddata, strlen(senddata), 0);
	}
	getchar();
	closesocket(sclient);
	WSACleanup();

	return 0;

}

