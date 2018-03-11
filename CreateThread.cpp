/*
** Author 		: Gzh
** Datetime 	: 3/11
** Description  : CreateThread
*/
#include <stdio.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID pM)
{
	printf("×ÓÏß³ÌID:%d\n×ÓÏß³ÌÊä³ö Hello World\n", GetCurrentThreadId()); 
	
	return 0;
}

int main()
{
	printf("CreateThread\n");
	
	HANDLE handle = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL); //åˆ›å»ºä¸€ä¸ªçº¿ç¨‹ 
	WaitForSingleObject(handle, INFINITE);       //ç­‰å¾…å­çº¿ç¨‹ç»“æŸ 
	
	return 0;
}
