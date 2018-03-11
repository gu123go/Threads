/*
** Author 	   : Gzh
** Datetime    : 3/11
** Description : �¼�Event
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
	SetEvent(thread_event);           //event�¼�������for������ִ��
	 
	Sleep(100);
	
	EnterCriticalSection(&thread_code); 
	count++;
	printf("�̱߳��Ϊ%d ȫ����ԴΪ%d\n", thread_num, count);
	LeaveCriticalSection(&thread_code);
	
	return 0;
}

int main()
{
	printf("\t�߳�ͬ����Event\n");
	thread_event = CreateEvent(NULL, false, false, NULL);         //��ʼ��һ���Զ���λ����ʼ���źŵ������¼� 
	InitializeCriticalSection(&thread_code);
	HANDLE handle[THREAD_NUM];
	
	
	for(int i = i; i < THREAD_NUM; ++i){
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, func, &i, 0, NULL);
		WaitForSingleObject(handle[i], INFINITE);
	}
		 
	
	WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);
	CloseHandle(&thread_event);
	DeleteCriticalSection(&thread_code);
	
	return 0;
}
