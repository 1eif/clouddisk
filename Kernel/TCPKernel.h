#pragma once 

#include "IKernel.h"
#include "TCPNet.h"
#include "../0629diskserver/Packdef.h"


class TCPKernel : public IKernel
{
public:
	TCPKernel();
	virtual ~TCPKernel();
public:
	virtual bool Open();
	virtual void Close();
	virtual void DealData(char* szbuf, SOCKET sock);
	void RegisterRq(char* szbuf, SOCKET sock);
	void LoginRq(char* szbuf, SOCKET sock);
private:
	INet* m_pNet;
};