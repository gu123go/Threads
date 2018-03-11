/*
** Author 		: Gzh
** Datetime 	: 3/11
** Description  : CreateThread
*/
#include <stdio.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID pM)
{
	printf("���߳�ID:%d\n���߳���� Hello World\n", GetCurrentThreadId()); 
	
	return 0;
}

int main()
{
	printf("CreateThread\n");
	
	HANDLE handle = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL); //创建一个线程 
	WaitForSingleObject(handle, INFINITE);       //等待子线程结束 
	
	return 0;
}
