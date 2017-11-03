#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include<tchar.h>
#include <psapi.h>

// Use to convert bytes to MB
#define DIV 1048576

// Use to convert bytes to MB
//#define DIV 1024

// Specify the width of the field in which to print the numbers. 
// The asterisk in the format specifier "%*I64d" takes an integer 
// argument and uses it to pad and right justify the number.

#define WIDTH 7

// Secound Thread function
void ThreadProc(void *param);
int size;
int *arr;

// First thread 
int main()
{	
	

	int n;
	int i;
	int val = 0;
	HANDLE handle;
	
	printf("\t Thread Demo\n");

//	printf("Enter the number of threads : ");
//	scanf("%d",&n);
	

//	for(i=0;i<n;i++)
//	{
//		val = i+1;
//		handle = (HANDLE) _beginthread( ThreadProc,0,&val); // create thread
//		WaitForSingleObject(handle,INFINITE);
//		
//		
//	}
	size = 10000000;
	arr = (int *)malloc(sizeof(int) * size);
	for(i=0; i<size; i++){
		arr[i] = 0;
	}
	int flag= 1;
	for(i=2; i<size; i++){
		
		arr[i]++;
		if(arr[i] == 1){
						
			if(flag){
				if(i*i > size){
					flag = 0;
				}
				
				else{
					val = i;
					handle = (HANDLE) _beginthread(ThreadProc,0,&val); // create thread
					WaitForSingleObject(handle,INFINITE);
				}
				
			}
			
		}
	}
	
//	for(i=2; i<size; i++){
//		if(arr[i] == 1){
//			printf("%d ",i);
//		}
//	}
MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
	DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
	printf("%d", virtualMemUsed);
	return 0;
}


void ThreadProc(void *param)
{
	
	int i=*((int*)param);
	//printf("%d Thread is Running!\n",i);
	long j;
	for(j= i*i; j<size; j= j+i){
					arr[j]++;
	}
	_endthread();

}

