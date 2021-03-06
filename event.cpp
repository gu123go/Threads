/*
** Author 	   : Gzh
** Datetime    : 3/11
** Description : 事件Event
*/ 

#include <stdio.h>
#include <process.h>
#include <windows.h>

enum { THREAD_NUM = 10 };
volatile long count;
HANDLE thread_event;
CRITICAL_SECTION thread_code;
unsigned __stdcall func(void *pM)
{
	int thread_num = *(int*)pM;
	SetEvent(thread_event);           //event事件触发，for语句继续执行
	//PulseEvent(thread_event);         /*SetEvent(thread_event); ResetEvent(thread_event);*/
	Sleep(100);
	
	EnterCriticalSection(&thread_code); 
	count++;
	printf("线程编号为%d 全局资源为%d\n", thread_num, count);
	LeaveCriticalSection(&thread_code);
	
	return 0;
}

int main()
{
	printf("\t线程同步：Event\n");
	thread_event = CreateEvent(NULL, false, false, NULL);         //初始化一个自动置位，初始无信号的匿名事件 
	InitializeCriticalSection(&thread_code);
	HANDLE handle[THREAD_NUM];
	
	
	for(int i = i; i < THREAD_NUM; ++i){
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, func, &i, 0, NULL);
		WaitForSingleObject(thread_event, INFINITE);
	}
		 
	
	WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);
	CloseHandle(&thread_event);
	DeleteCriticalSection(&thread_code);
	
	return 0;
}
