#include <iostream>
#include "TCPKernel.h"
using namespace std;

int main()
{
	IKernel* pKernel = new TCPKernel;
	if (pKernel->Open())
	{
		printf("服务器启动成功\n");
	}

	system("pause");
	return 0;
}