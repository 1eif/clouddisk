#pragma once
#include <mysql.h>
//#include <WinSock2.h>
#pragma comment(lib,"libmysql.lib")
//
#include <list>
using namespace std;

class CMySql
{
public:
    CMySql(void);
    ~CMySql(void);
public:                   //ip       ,root,      password,database,port
    bool  ConnectMySql( char *host, char *user, char *pass, char *db,short nport = 3306);
    void  DisConnect();
    bool  SelectMySql(char* szSql,int nColumn,list<string>& lstStr);
	//������ݿ��еı�
    bool GetTables(char* szSql,list<string>& lstStr);
    //���£�ɾ�������롢�޸�
    bool  UpdateMySql(char* szSql);
 
private:
    MYSQL *sock;   
	MYSQL_RES *results;   
	MYSQL_ROW record; 
   
};
