/*
** Author 		: Gzh
** Datetime 	: 3/11
** Description  : CreateThread
*/
#include <stdio.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID pM)
{
	printf("子线程ID:%d\n子线程输出 Hello World\n", GetCurrentThreadId()); 
	
	return 0;
}

int main()
{
	printf("CreateThread\n");
	
	HANDLE handle = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL); //鍒涘缓涓�涓嚎绋� 
	WaitForSingleObject(handle, INFINITE);       //绛夊緟瀛愮嚎绋嬬粨鏉� 
	
	return 0;
}
