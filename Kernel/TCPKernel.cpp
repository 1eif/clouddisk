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
	//注册请求包
	STRU_REGISTER_RQ* psrr = (STRU_REGISTER_RQ*)szbuf;
	STRU_REGISTER_RS srr;
	srr.m_ntype = _DEF_PRTOCOL_REGISTER_RS;
	//将用户信息写入数据库（此处不是重点，不使用数据库，直接写死）
	//拼接SQL语句
	/*
	char szsql[_DEF_SQLLEN] = {0};
	sprintf_s(szsql,"insert into user values(%lld,'%s','%s');",psrr->m_userid,psrr->m_szName,psrr->m_szPassword;
	if(m_sql.UpdateMysql(szsql))
	{
		返回包中状态为注册失败
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
	//处理数据
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