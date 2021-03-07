#include "TCPKernel.h"



TCPKernel::TCPKernel()
{
	m_pNet = new TCPNet;
}

TCPKernel::~TCPKernel()
{
	if (m_pNet)
	{
		delete m_pNet;
		m_pNet = NULL;
	}

}

bool TCPKernel::Open()
{
	if (!m_pNet->InitNetWork())
	{
		return false;
	}
	return true;
}

void TCPKernel::Close()
{
	m_pNet->UnInitNetWork();
}

void TCPKernel::DealData(char* szbuf, SOCKET sock)
{
	//处理数据
}