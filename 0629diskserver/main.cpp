#include <iostream>
#include "TCPKernel.h"
using namespace std;

int main()
{
	IKernel* pKernel = new TCPKernel;
	if (pKernel->Open())
	{
		printf("�����������ɹ�\n");
	}

	system("pause");
	return 0;
}