/*
** Author 	   : Gzh
** Datetime    : 3/11
** Description : _beginthreadex
*/

#include <stdio.h>
#include <windows.h> 
#include <process.h>
unsigned __stdcall ThreadFunc(LPVOID pM)
{
	printf("子线程ID:%d\n子线程输出 Hello World\n", GetCurrentThreadId()); 
	return 0;
}

int main()
{
	printf("_beginthreadex\n");
	
	const int THREAD_NUM = 5;
	
	HANDLE handle[THREAD_NUM];
	for(int i = 0; i < THREAD_NUM; ++i)
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, NULL);
		
	WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);
	return 0;
}
