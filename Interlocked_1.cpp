/*
** Author 	   : Gzh
** Datetime    : 3/11
** Description : 使用Interlocked
*/ 

#include <stdio.h>
#include <process.h>
#include <windows.h>

enum { THREAD_NUM = 50 };
volatile long g_nLongCount;
unsigned __stdcall func(void *pM)
{
	Sleep(100);
	InterlockedIncrement((long*)&g_nLongCount);          //原子操作
	Sleep(50);
	
	return 0; 
}

int main()
{
	int num = 50;
	int day = 0;
	while(++day <= num){
		g_nLongCount = 0;
		HANDLE handle[THREAD_NUM];
		
		for(int i = 0; i < THREAD_NUM; ++i)
			handle[i] = (HANDLE)_beginthreadex(NULL, 0, func, NULL, 0, NULL);
		WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);
		printf("第%d天%d个用户登陆后记录结果是%d\n", day, THREAD_NUM, g_nLongCount);
	}
	
	return 0;
}
