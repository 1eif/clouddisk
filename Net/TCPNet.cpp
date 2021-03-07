#include "TCPNet.h"

bool   TCPNet::m_bFlagQuit  = true;
TCPNet::TCPNet()
{
	m_sockListen = NULL;
	m_hThread = NULL;
	//m_bFlagQuit= true;
}

TCPNet::~TCPNet()
{}


bool TCPNet::InitNetWork()
{
	//1.加载库
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;


    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        return false;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        printf("Could not find a usable version of Winsock.dll\n");
        UnInitNetWork();
        return false;
    }
    else
        printf("The Winsock 2.2 dll was found okay\n");

	//2.创建socket
	m_sockListen = socket(AF_INET,SOCK_STREAM ,IPPROTO_TCP);
	if(INVALID_SOCKET == m_sockListen)
	{
		UnInitNetWork();
        return false; 

	}
	//3.bind
	sockaddr_in  addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;//本机任意网卡
	addrServer.sin_port = htons(8899);
	if(SOCKET_ERROR == bind(m_sockListen,(const sockaddr*)&addrServer,sizeof(addrServer)))
	{
		UnInitNetWork();
        return false;
	}

	//4.listen
	if(SOCKET_ERROR == listen(m_sockListen,10))
	{
		UnInitNetWork();
        return false;
	}

	//5.--创建线程--accept()  不创建会阻塞主线程
	m_hThread =(HANDLE) _beginthreadex(0,0,&ThreadProc,this,0,0);
	if(m_hThread)
		m_lstThread.push_back(m_hThread);
	


	return true;
}


unsigned  __stdcall TCPNet::ThreadProc( void * lpvoid)
{
	TCPNet *pthis = (TCPNet*)lpvoid;
	HANDLE hThread;
	while(pthis->m_bFlagQuit)
	{
		SOCKET sockWaiter =	accept(pthis->m_sockListen,0,0);
		//服务员与顾客沟通--创建线程
		hThread = (HANDLE) _beginthreadex(0,0,&ThreadRecv,(void*)sockWaiter,0,0);
		 if(hThread)
			 pthis->m_lstThread.push_back(hThread);
		//recv
	}
	return 0;
}

unsigned  __stdcall TCPNet::ThreadRecv( void * lpvoid)
{
	SOCKET sockWaiter = (SOCKET)lpvoid;
	int nPackSize;
	int nRelReadNum;
	char *pszbuf = NULL;
	while(TCPNet::m_bFlagQuit)
	{
		//recv --接收数据
		//接收包大小
		nRelReadNum = recv(sockWaiter, (char*)&nPackSize, sizeof(int), 0);
		if (nRelReadNum <= 0)
		{
			printf("error code :%d\n", GetLastError());
			continue;
		}
			
		//接收包内容
		pszbuf = new char[nPackSize];
		int offset = 0; //解决粘包问题
		while (nPackSize)
		{
			nRelReadNum = recv(sockWaiter, pszbuf + offset, nPackSize, 0);
			offset += nRelReadNum;
			nPackSize -= nRelReadNum;
		}
		
	}
	return 0;
}

void TCPNet::UnInitNetWork()
{
	m_bFlagQuit = false;
	auto ite = m_lstThread.begin();
	while( ite != m_lstThread.end())
	{		
		//判断线程是否能够退出
		if(WAIT_TIMEOUT ==  WaitForSingleObject(*ite,200))
			TerminateThread(*ite,-1);

		CloseHandle(*ite);
		*ite = NULL;
	
		ite++;

	}
	m_lstThread.clear();

	if(m_sockListen)
	{
		closesocket(m_sockListen);
		m_sockListen = NULL;
	}
	  WSACleanup();
}

void TCPNet::RecvData()
{}

bool TCPNet::SendData(SOCKET sock,char* szbuf,int nLen)
{
	if(!sock || !szbuf || nLen <=0)
		return false;

	//send 发送包大小
	if(send(sock,(const char*)&nLen,sizeof(int),0) <=0)
		return false;
	//send包数据
	if(send(sock,szbuf,nLen,0) <=0)
		return false;

	return true;
}
