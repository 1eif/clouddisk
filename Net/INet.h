#pragma once 

#include <Winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class INet
{
public:
	INet()
	{}
	virtual ~INet()
	{}
public:
	virtual bool InitNetWork() =0;
	virtual void UnInitNetWork() =0;
	virtual void RecvData() =0;
	virtual bool SendData(SOCKET sock,char* szbuf,int nLen)=0;
};