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

void TCPKernel::RegisterRq(char* szbuf, SOCKET sock)
{
	//ע�������
	STRU_REGISTER_RQ* psrr = (STRU_REGISTER_RQ*)szbuf;
	STRU_REGISTER_RS srr;
	srr.m_ntype = _DEF_PRTOCOL_REGISTER_RS;
	//���û���Ϣд�����ݿ⣨�˴������ص㣬��ʹ�����ݿ⣬ֱ��д����
	//ƴ��SQL���
	/*
	char szsql[_DEF_SQLLEN] = {0};
	sprintf_s(szsql,"insert into user values(%lld,'%s','%s');",psrr->m_userid,psrr->m_szName,psrr->m_szPassword;
	if(m_sql.UpdateMysql(szsql))
	{
		���ذ���״̬Ϊע��ʧ��
	}
	
	*/
	srr.m_szResult = _register_success;
	m_pNet->SendData(sock, (char*)&srr, sizeof(srr));

}

void TCPKernel::LoginRq(char* szbuf, SOCKET sock)
{

}

void TCPKernel::DealData(char* szbuf, SOCKET sock)
{
	//��������
	switch (*szbuf)
	{
	case _DEF_PRTOCOL_REGISTER_RQ:
		RegisterRq(szbuf, sock);
		break;
	case _DEF_PRTOCOL_LOGIN_RQ:
		LoginRq(szbuf, sock);
		break;
	default:
		break;
	}
}