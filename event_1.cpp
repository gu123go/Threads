/*
** Author  	 	: Gzh
** Datetmie   	: 3/12
** Description  : event
*/ 


#include <stdio.h>
#include <process.h>
#include <windows.h>

enum { THREAD_NUM=5};
volatile long count;
HANDLE hEvent;

unsigned __stdcall func1(void *pM)
{
	printf("In thread1\n");
	
	DWORD dwRet = WaitForSingleObject(hEvent, INFINITE);
	
	if(WAIT_OBJECT_0  == dwRet)
		printf("thread1 signaled\n");
	
	printf("In thread1  --signaled\n");
	
	SetEvent(hEvent);
}


unsigned __stdcall func2(void *pM)
{
	printf("In thread2\n");
	
	DWORD dwRet = WaitForSingleObject(hEvent, INFINITE);
	
	if(WAIT_OBJECT_0 == dwRet)
		printf("thread2 signaled\n");
	
	printf("in thread2 --signaled\n");
	
	return 0;
}
int main()
{
	
	hEvent = CreateEvent(NULL, false, true, NULL);      //自动置位，初始触发 
	
	HANDLE handle[2];
	handle[0] = (HANDLE)_beginthreadex(NULL, 0, func1, NULL, 0, NULL);
	Sleep(200);
	
	handle[1] = (HANDLE)_beginthreadex(NULL, 0, func2, NULL, 0, NULL);
	Sleep(200);
	
	WaitForMultipleObjects(2, handle, true, INFINITE);
	
	
	return 0;
}
