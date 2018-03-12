/*
** Author 	   : Gzh
** Datetime    : 3/12 
** Description : Mutex.两个进程之间的信号量互斥。1.2创建一个mutex，然后触发，在触发之前，1.1一直处于等待状态 
*/

#include <stdio.h>
#include <process.h>
#include <windows.h>

const char* mutex_name = "Mutex";

int main()
{
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, true, mutex_name);
	if(hMutex == NULL){
		printf("打开互斥量失败\n");
		exit(1);
	}
	
	printf("等待互斥量触发...\n");
	
	DWORD dwRet = WaitForSingleObject(hMutex, 20*1000);       //等待20秒
	switch(dwRet){
	case WAIT_ABANDONED:
		printf("互斥量进程意外终止!\n");
		break;
	case WAIT_OBJECT_0:
		printf("接受到信号量!\n");
		break;
	case WAIT_TIMEOUT:
		printf("等待超时!\n");
		break;
	} 
	
	CloseHandle(hMutex);
	
	return 0;
} 
