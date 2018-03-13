/*
** 
** Datetime    : 3/13
** Description : 
*/


#include <stdio.h>
#include <process.h>
#include <windows.h>

const int BUFFER_SIZE = 4;
int buffer[BUFFER_SIZE];       //缓冲区 
int buffer_i, buffer_j; 
const int END_PRODUCE_NUMBER = 6;
HANDLE thread_semaphore_full, thread_semaphore_empty;
CRITICAL_SECTION thread_cs;
unsigned __stdcall producerThread(void *pM)
{
	for(int i = 1; i <= END_PRODUCE_NUMBER; ++i){
		WaitForSingleObject(thread_semaphore_empty, INFINITE);
		
		EnterCriticalSection(&thread_cs);
		buffer[buffer_i] = i;
		printf("\t生产者%d 在缓冲池第%d个缓冲区中投放数据%d\n\n", GetCurrentThreadId(), buffer_i, buffer[buffer_i]);
		buffer_i = (buffer_i + 1) % BUFFER_SIZE;
		LeaveCriticalSection(&thread_cs);
			
		ReleaseSemaphore(thread_semaphore_full, 1, NULL);

	}
	
	printf("\tproducerThread %d thread over\n\n", GetCurrentThreadId());
	return 0;	
}

unsigned __stdcall consumerThread(void *pM)
{
	bool flag = true;
	while(flag){
		WaitForSingleObject(thread_semaphore_full, INFINITE);
		
		EnterCriticalSection(&thread_cs);
		printf("编号为%d的消费者从缓冲池中第%d个缓冲区取出数据%d\n", GetCurrentThreadId(), buffer_j, buffer[buffer_j]);
		if(buffer[buffer_j] == END_PRODUCE_NUMBER){
			LeaveCriticalSection(&thread_cs);
			ReleaseSemaphore(thread_semaphore_full, 1, NULL);
			break;
		}
		buffer_j = (buffer_j + 1) % BUFFER_SIZE;
		LeaveCriticalSection(&thread_cs);
		
		Sleep(50);
		
		ReleaseSemaphore(thread_semaphore_empty, 1, NULL);
	}
	printf("consumerThread %d thread over\n", GetCurrentThreadId());
	return 0;
}

int main()
{
	InitializeCriticalSection(&thread_cs);
	thread_semaphore_full = CreateSemaphore(NULL, 0, 4, NULL);      //4个缓冲区，记录有数据缓冲区个数 
	thread_semaphore_empty = CreateSemaphore(NULL, 4, 4, NULL);      //记录空缓冲区个数 
	
	const int THREAD_NUM = 4;              //2 consumer; 2 producer 
	HANDLE handle[THREAD_NUM];
	buffer_i = buffer_i = 0;
	memset(buffer, 0, sizeof(buffer));
	handle[0] = (HANDLE)_beginthreadex(NULL, 0, producerThread, NULL, 0, NULL);
	handle[1] = (HANDLE)_beginthreadex(NULL, 0, producerThread, NULL, 0, NULL);
	handle[2] = (HANDLE)_beginthreadex(NULL, 0, consumerThread, NULL, 0, NULL);
	handle[3] = (HANDLE)_beginthreadex(NULL, 0, consumerThread, NULL, 0, NULL);
	
	WaitForMultipleObjects(THREAD_NUM, handle, true, INFINITE);
	
	DeleteCriticalSection(&thread_cs);
	CloseHandle(thread_semaphore_full);
	CloseHandle(thread_semaphore_empty);
	
	for(int i = 0; i < THREAD_NUM; ++i)
		CloseHandle(handle[i]);
	 
	return 0;
}


 
