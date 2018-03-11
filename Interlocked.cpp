/*
** Author 	   : Gzh
** Datetime    : 3/11
** Description : 没有使用 Interlocked
*/ 

#include <stdio.h>
#include <windows.h>
#include <process.h>        //_beginthreadex

enum { THREAD_NUM = 10 };
volatile long g_nLongCount;
unsigned int __stdcall func(void* pM)
{
	Sleep(100);
	g_nLongCount++;
	Sleep(50);
	
	return 0;
}

int main()
{
	printf("\t原子操作\n");
	int num = 50;     // 
	int day = 0;
	while(++day <= num){
		g_nLongCount = 0;
		int i;
		HANDLE handle[THREAD_NUM];
		for(int i = 0; i < THREAD_NUM; ++i){
			handle[i] = (HANDLE)_beginthreadex(NULL, 0, func, NULL, 0, NULL);
		} 
		WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);
		printf("第%d 天有%d个用户登陆后记录结果是%d\n",day, THREAD_NUM, g_nLongCount);
	}
		
	return 0;
}
 
