#pragma once 

#include <Winsock2.h>
class IKernel
{
public:
	IKernel()
	{}
	virtual ~IKernel()
	{}
public:
	virtual bool Open() =0;
	virtual  void Close() =0;
	virtual void DealData(char *szbuf,SOCKET sock) =0;
};