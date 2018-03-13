/*
** Author 	   : Gzh
** Datetime    : 3/13
** Description : consumer and producer.��������ֻ������������һ����Ʒ������������һ����Ʒ���� 
*/

#include <stdio.h>
#include <windows.h>
#include <process.h>

volatile int buffer;
const int END_PRODUCE_NUMBER = 10;
CRITICAL_SECTION thread_cs;
HANDLE thread_event_empty, thread_event_full;

unsigned __stdcall consumerThread(void *pM)
{
	volatile bool flag = true;
	while(flag){
		WaitForSingleObject(thread_event_full, INFINITE);
		
		EnterCriticalSection(&thread_cs);
		--buffer;
		printf("����������һ����Ʒ��Ŀǰ��%d ��\n", buffer);
		LeaveCriticalSection(&thread_cs);
		
		SetEvent(thread_event_empty); 
		
		Sleep(1000/(buffer+1));
	}
	return 0;
}

unsigned __stdcall producerThread(void *pM)
{
	bool flag = true;
	while(flag){
		WaitForSingleObject(thread_event_empty, INFINITE);
		
		EnterCriticalSection(&thread_cs);
		++buffer;
		printf("����������һ����Ʒ��ǰ��%d��\n", buffer);

		LeaveCriticalSection(&thread_cs);
		
		SetEvent(thread_event_full);
		Sleep(1000/(buffer+1));
	}
	
	return 0;
}

int main()
{
	InitializeCriticalSection(&thread_cs);
	thread_event_empty = CreateEvent(NULL, false, true, NULL);            //��������ʼ��Ϊ�գ��Զ���λ 
	thread_event_full = CreateEvent(NULL, false, false, NULL);            //
	
	HANDLE handle[2];
	handle[1] = (HANDLE)_beginthreadex(NULL, 0, producerThread, NULL, 0, NULL);
	//Sleep(0);
	handle[0] = (HANDLE)_beginthreadex(NULL, 0, consumerThread, NULL, 0, NULL);
	//Sleep(1);

	
	WaitForMultipleObjects(2, handle, true, INFINITE);
	
	for(int i = 0; i < 2; ++i) CloseHandle(handle[i]);
	CloseHandle(thread_event_full);
	CloseHandle(thread_event_empty);
	DeleteCriticalSection(&thread_cs);
	
	return 0;
} 
