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
volatile long count;            //��Դ
 
unsigned __stdcall func(void *pPM)
{
	int num = *(int*)pPM;
	ReleaseSemaphore(thread_semaphore, 1, NULL);
	
	Sleep(200);
	
	EnterCriticalSection(&thread_cs_code);
	count++;
	Sleep(0);
	printf("�̱߳��Ϊ%d ȫ����ԴֵΪ%d\n", num, count);
	LeaveCriticalSection(&thread_cs_code);
	return 0;	
}

int main()
{
	printf("\tsemaphore\n");
	thread_semaphore = CreateSemaphore(NULL, 0, 1, NULL);          //0��Դ���������1��ͬʱ���ʵ������ź��� 
	InitializeCriticalSection(&thread_cs_code);
	
	HANDLE handle[THREAD_NUM];
	count = 0;
	int i = 0; 
	while(i < THREAD_NUM){
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, func, &i, 0, NULL);
		Sleep(10);  ++i;     //�����滻��38�� 
		WaitForSingleObject(thread_semaphore, INFINITE);
		//++i;		
	} 
	WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);         //���ȴ���64��
	
	DeleteCriticalSection(&thread_cs_code);
	CloseHandle(thread_semaphore);
	
	for(int i = 0; i < THREAD_NUM; ++i)
		CloseHandle(handle[i]);
	
	return 0;
}
