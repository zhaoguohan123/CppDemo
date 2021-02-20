// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
int main()
{
	WORD sockVersion = MAKEWORD(2, 2); // 指定winsock版本

	WSAData wsaData;
	if (WSAStartup(sockVersion, &wsaData)!=0) //只调用一次，该函数成功后再调用进一步的Windows Sockets API函数
	{
		printf("WSAStartup error");
		return 0;
	}

	// 1. 创建套接字  socket
	//AF_INET表示IPv4，SOCK_STREAM数据传输方式，IPPROTO_TCP传输协议; 
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSocket == INVALID_SOCKET)
	{
		printf("套接字创建失败");
		WSACleanup();
		return 0;
	}

	// 2. 绑定套接字到一个IP地址和一个端口上 bind
	sockaddr_in addrListen;
	addrListen.sin_family = AF_INET;
	addrListen.sin_port = htons(8888);
	addrListen.sin_addr.S_un.S_addr = INADDR_ANY;  //表示任何IP   service.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(listenSocket, (SOCKADDR*)&addrListen, sizeof(addrListen)) == SOCKET_ERROR) 
	{
		printf("绑定失败");
		closesocket(listenSocket);
		return 0;
	}
	//3. 监听指定端口 listen

	if (listen(listenSocket, 5) == SOCKET_ERROR) // 5: 等待连接队列的最大长度。
	{
		printf("监听出错");
		closesocket(listenSocket);
		return 0;
	}


	//4. 等待连接, 连接后建立一个新的套接字 accept
	SOCKET revSocket;  //对应此时所建立连接的套接字的句柄
	sockaddr_in remoteAddr;   //接收连接到服务器上的地址信息
	int remoteAddrLen = sizeof(remoteAddr);
	printf("等待连接...\n");
	/*等待客户端请求，服务器接收请求*/
	revSocket = accept(listenSocket, (SOCKADDR*)&remoteAddr, &remoteAddrLen);  //等待客户端接入，直到有客户端连接上来为止
	if (revSocket == INVALID_SOCKET)
	{
		printf("客户端发出请求，服务器接收请求失败：%d \n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return 0;
	}
	else
	{
		printf("客服端与服务器建立连接成功\n");
	}
	// 5. recv和send
	while (1)
	{
		char revData[255] = "";
		/*通过建立的连接进行通信*/
		int res = recv(revSocket, revData, 255, 0);
		if (res > 0)
		{
			printf("Bytes received: %d\n", res);
			printf("客户端发送的数据: %s\n", revData);
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

