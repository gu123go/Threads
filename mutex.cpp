/* 
** Author 	 	: Gzh
** Datetime     : 3/12
** Description  : 互斥量Mutex
*/ 

#include <stdio.h>
#include <process.h>
#include <windows.h>

enum{THREAD_NUM = 10};
volatile long count;
HANDLE thread_mutex;
CRITICAL_SECTION thread_cs;
unsigned __stdcall func(void *pM)
{
	int num = *(int*)pM;
	ReleaseMutex(thread_mutex);
	
	Sleep(200);
	
	EnterCriticalSection(&thread_cs);
	Sleep(10);
	++count;
	printf("第%d用户拥有%d个资源\n", num, count);
	LeaveCriticalSection(&thread_cs);
	
	return 0;
}


int main()
{
	thread_mutex = CreateMutex(NULL, false, NULL);
	InitializeCriticalSection(&thread_cs);
	
	HANDLE handle[THREAD_NUM];
	for(int i = 0; i < THREAD_NUM; ++i){
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, func, &i, 0, NULL);
		WaitForSingleObject(thread_mutex, INFINITE);
	}
	
	WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);
	return 0;
}

