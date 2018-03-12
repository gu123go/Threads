/*
** Author 	   : Gzh
** Datetime    : 3/12 
** Description : Mutex.��������֮����ź������⡣1.2����һ��mutex��Ȼ�󴥷����ڴ���֮ǰ��1.1һֱ���ڵȴ�״̬ 
*/

#include <stdio.h>
#include <process.h>
#include <windows.h>

const char* mutex_name = "Mutex";

int main()
{
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, true, mutex_name);
	if(hMutex == NULL){
		printf("�򿪻�����ʧ��\n");
		exit(1);
	}
	
	printf("�ȴ�����������...\n");
	
	DWORD dwRet = WaitForSingleObject(hMutex, 20*1000);       //�ȴ�20��
	switch(dwRet){
	case WAIT_ABANDONED:
		printf("����������������ֹ!\n");
		break;
	case WAIT_OBJECT_0:
		printf("���ܵ��ź���!\n");
		break;
	case WAIT_TIMEOUT:
		printf("�ȴ���ʱ!\n");
		break;
	} 
	
	CloseHandle(hMutex);
	
	return 0;
} 
