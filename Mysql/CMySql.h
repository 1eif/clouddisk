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
	//获得数据库中的表
    bool GetTables(char* szSql,list<string>& lstStr);
    //更新：删除、插入、修改
    bool  UpdateMySql(char* szSql);
 
private:
    MYSQL *sock;   
	MYSQL_RES *results;   
	MYSQL_ROW record; 
   
};

