#include <stdio.h>
#include <process.h>
#include <windows.h>

const char* mutex_name = "Mutex";

int main()
{
	HANDLE hMutex = CreateMutex(NULL, true, mutex_name);
	printf("�������Ѿ�����\n");
	
	printf("�Ƿ񴥷�������?(y/n)");
	char ch = getchar();
	if('y' == ch || 'Y' == ch)
		ReleaseMutex(hMutex);
	printf("�������Ѿ�����\n");
	
	
	CloseHandle(hMutex); 
	system("pause");
	return 0;
}
