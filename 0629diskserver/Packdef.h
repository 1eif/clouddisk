#ifndef _PACKDEF_H
#define _PACKDEF_H

#define SERVER_IP "127.0.0.1"
//防冲突
#define _DEF_PROTOCOL_BASE  10

//注册
#define _DEF_PRTOCOL_REGISTER_RQ  _DEF_PROTOCOL_BASE +1
#define _DEF_PRTOCOL_REGISTER_RS  _DEF_PROTOCOL_BASE +2
//登录
#define _DEF_PRTOCOL_LOGIN_RQ  _DEF_PROTOCOL_BASE +3
#define _DEF_PRTOCOL_LOGIN_RS  _DEF_PROTOCOL_BASE +4

//获取文件列表请求
#define _DEF_PRTOCOL_GETFILELIST_RQ  _DEF_PROTOCOL_BASE +5
#define _DEF_PRTOCOL_GETFILELIST_RS  _DEF_PROTOCOL_BASE +6

//上传文件头
#define _DEF_PRTOCOL_UPLOAD_FILEHEADER_RQ  _DEF_PROTOCOL_BASE +7
#define _DEF_PRTOCOL_UPLOAD_FILEHEADER_RS  _DEF_PROTOCOL_BASE +8

//断点续传
#define _DEF_PRTOCOL_UPLOAD_CONTINUEFILEHEADER_RQ  _DEF_PROTOCOL_BASE +9
#define _DEF_PRTOCOL_UPLOAD_CONTINUEFILEHEADER_RS  _DEF_PROTOCOL_BASE +10
//下载文件内容
#define _DEF_PRTOCOL_FILECONTENT_RQ  _DEF_PROTOCOL_BASE +11
#define _DEF_PRTOCOL_FILECONTENT_RS  _DEF_PROTOCOL_BASE +12

//下载文件信息头
#define _DEF_PRTOCOL_DOWNLOAD_FILEHEADER_RQ  _DEF_PROTOCOL_BASE +13
#define _DEF_PRTOCOL_DOWNLOAD_FILEHEADER_RS  _DEF_PROTOCOL_BASE +14

#define _DEF_PRTOCOL_DOWNLOAD_CONTINUEFILEHEADER_RQ  _DEF_PROTOCOL_BASE +15
#define _DEF_PRTOCOL_DOWNLOAD_CONTINUEFILEHEADER_RS  _DEF_PROTOCOL_BASE +16
//下载文件内容
#define _DEF_PRTOCOL_DOWNLOAD_FILECONTENT_RQ  _DEF_PROTOCOL_BASE +17
#define _DEF_PRTOCOL_DOWNLOAD_FILECONTENT_RS  _DEF_PROTOCOL_BASE +18

//分享链接
#define _DEF_PRTOCOL_SHARELINK_RQ  _DEF_PROTOCOL_BASE +19
#define _DEF_PRTOCOL_SHARELINK_RS  _DEF_PROTOCOL_BASE +20
//提取链接
#define _DEF_PRTOCOL_GETLINK_RQ  _DEF_PROTOCOL_BASE +21
#define _DEF_PRTOCOL_GETLINK_RS  _DEF_PROTOCOL_BASE +22

//退出登录
#define _DEF_PRTOCOL_QUITLOGIN_RQ  _DEF_PROTOCOL_BASE +23
#define _DEF_PRTOCOL_QUITLOGIN_RS  _DEF_PROTOCOL_BASE +24


#define _register_fail   0
#define _register_success 1
#define _login_fail   0
#define _login_success 1

#define _fileheader_uploaded  0 
#define _fileheader_uploadsuccess  1
#define _fileheader_continueupload   2



#define _DEF_SQLLEN  300
#define _DEF_SIZE  45
#define _DEF_FILENUM  50
#define _DEF_FILECONTENT 4096

//msg
#define UM_LOGINMSG  WM_USER + 1
#define UM_GETFILELISTMSG  WM_USER + 2
#define UM_UPLOADSUCCESSMSG  WM_USER +3
#define UM_UPLOADFILEPOSMSG  WM_USER +4

//包类型
typedef char PackType;
//注册包
struct STRU_REGISTER_RQ
{
	PackType  m_ntype;
	long long m_userid;
	char   m_szName[_DEF_SIZE];
	char   m_szPassword[_DEF_SIZE];
};
//注册回复包
struct STRU_REGISTER_RS
{
	PackType  m_ntype;
	char      m_szResult;
};
//登录包
struct STRU_LOGIN_RQ
{
	PackType  m_ntype;
	long long m_userid;
	//char   m_szName[_DEF_SIZE];
	char   m_szPassword[_DEF_SIZE];
};
//登录回复包
struct STRU_LOGIN_RS
{
	PackType  m_ntype;
	char      m_szResult;
};

//获取文件列表请求
struct STRU_GETFILELIST_RQ
{
	PackType  m_ntype;
	long long m_userid;
};
//单个文件信息
struct FileInfo
{
	char m_szFileName[_DEF_SIZE];
	char m_szUpLoadTime[_DEF_SIZE];
	long long m_FileSize;
};
//获取文件列表回复
struct STRU_GETFILELIST_RS
{
	PackType  m_ntype;
	FileInfo m_aryFile[_DEF_FILENUM];//文件列表
	int      m_nFileNum;
};

struct STRU_UPLOADFILEHEADER_RQ
{
	PackType  m_ntype;
	long long m_userid;
	long long m_FileSize;
	char      m_szFileName[_DEF_SIZE];
	char      m_szUpLoadTime[_DEF_SIZE];
	char      m_szMD5[_DEF_SIZE];
};

struct STRU_UPLOADFILEHEADER_RS
{
	//可以上传  已经上传过来 别人传过了（秒传）
	PackType  m_ntype;
	long long m_fileid;
	char      m_szMD5[_DEF_SIZE];
	char      m_szResult;
	
};

struct STRU_UPLOADFILECONTENT_RQ
{
	PackType  m_ntype;
	long long m_userid;
	long long m_fileid;
	char      m_szContent[_DEF_FILECONTENT];
	int       m_nLen;
};
struct STRU_UPLOADFILECONTENT_RS
{
	PackType  m_ntype;
	long long m_fileid;
	char      m_szResult;
};



/*
   数据库表

   user 表   (u_id,u_name,u_password)
   file 表  （f_id,f_name,f_uploadtime,f_size,f_path,f_count,f_MD5）

   user_file (u_id,f_id)

*/


#endif