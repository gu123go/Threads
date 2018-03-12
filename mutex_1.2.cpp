#include <stdio.h>
#include <process.h>
#include <windows.h>

const char* mutex_name = "Mutex";

int main()
{
	HANDLE hMutex = CreateMutex(NULL, true, mutex_name);
	printf("互斥量已经创建\n");
	
	printf("是否触发互斥量?(y/n)");
	char ch = getchar();
	if('y' == ch || 'Y' == ch)
		ReleaseMutex(hMutex);
	printf("互斥量已经触发\n");
	
	
	CloseHandle(hMutex); 
	system("pause");
	return 0;
}
