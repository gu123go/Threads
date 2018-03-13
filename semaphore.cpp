/*
** Author 	   : Gzh
** Datetime    : 3/12
** Description : semaphore
*/ 

#include <stdio.h>
#include <process.h>
#include <windows.h>

enum{ THREAD_NUM = 10 };
HANDLE thread_semaphore;
CRITICAL_SECTION thread_cs_code;
volatile long count;            //资源
 
unsigned __stdcall func(void *pPM)
{
	int num = *(int*)pPM;
	ReleaseSemaphore(thread_semaphore, 1, NULL);
	
	Sleep(200);
	
	EnterCriticalSection(&thread_cs_code);
	count++;
	Sleep(0);
	printf("线程编号为%d 全局资源值为%d\n", num, count);
	LeaveCriticalSection(&thread_cs_code);
	return 0;	
}

int main()
{
	printf("\tsemaphore\n");
	thread_semaphore = CreateSemaphore(NULL, 0, 1, NULL);          //0资源，最大允许1个同时访问的匿名信号量 
	InitializeCriticalSection(&thread_cs_code);
	
	HANDLE handle[THREAD_NUM];
	count = 0;
	int i = 0; 
	while(i < THREAD_NUM){
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, func, &i, 0, NULL);
		Sleep(10);  ++i;     //可以替换成38行 
		WaitForSingleObject(thread_semaphore, INFINITE);
		//++i;		
	} 
	WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);         //最大等待数64个
	
	DeleteCriticalSection(&thread_cs_code);
	CloseHandle(thread_semaphore);
	
	for(int i = 0; i < THREAD_NUM; ++i)
		CloseHandle(handle[i]);
	
	return 0;
}
