#pragma once 

#include "IKernel.h"
#include "TCPNet.h"

class TCPKernel : public IKernel
{
public:
	TCPKernel();
	virtual ~TCPKernel();
public:
	virtual bool Open();
	virtual void Close();
	virtual void DealData(char* szbuf, SOCKET sock);
private:
	INet* m_pNet;
};