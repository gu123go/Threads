/*
** Author 	   : Gzh
** Datetime    : 3/11
** Description : 关键段CS 
*/ 

#include <stdio.h>
#include <process.h>
#include <windows.h>

enum { THREAD_NUM = 10 };                              //线程数 
volatile long count;                                   //全局资源 
CRITICAL_SECTION thread_parameter, thread_code;        //关键段变量声明
 
unsigned __stdcall Func(void *pM)
{
	int thread_num = *(int*)pM;
	LeaveCriticalSection(&thread_parameter);
	Sleep(50);
	
	EnterCriticalSection(&thread_code);
	count++;
	printf("线程编号%d, 全局资源值%d\n", thread_num, count);
	LeaveCriticalSection(&thread_code);
	
	return 0;
}

int main()
{
	HANDLE handle[THREAD_NUM];
	InitializeCriticalSection(&thread_parameter);         //初始化 
	InitializeCriticalSection(&thread_code);              //初始化 
	
	for(int i = 0; i < THREAD_NUM; ){
		EnterCriticalSection(&thread_parameter);
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, Func, &i, 0, NULL);
		++i;
	}
	
	WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);
	DeleteCriticalSection(&thread_parameter);
	DeleteCriticalSection(&thread_code);
	
	return 0;
}

