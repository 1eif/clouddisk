#pragma once 

#include "INet.h"
#include <stdio.h>
#include <process.h>
#include <list>
using namespace std;
class TCPNet :public INet
{
public:
	TCPNet();
	virtual ~TCPNet();
public:
	virtual bool InitNetWork();
	virtual void UnInitNetWork();
	virtual void RecvData();
	virtual bool SendData(SOCKET sock,char* szbuf,int nLen);
public:

    static unsigned  __stdcall ThreadProc( void * );
	static unsigned  __stdcall ThreadRecv( void * );
private:
	SOCKET  m_sockListen;
	HANDLE  m_hThread;
	list<HANDLE> m_lstThread;
static 	bool    m_bFlagQuit;
};