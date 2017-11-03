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
int *check;
int *val;
HANDLE *handle;

// First thread 
int main()
{	
	

	int n;
	int i;
	
	size = 1000000;
	//HANDLE handle[size];
	
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
	arr = (int *)malloc(sizeof(int) * size);
	val = (int *)malloc(sizeof(int) * size);
	check = (int *)malloc(sizeof(int) * size);
	handle = (HANDLE *)malloc(sizeof(HANDLE) * size);
	
	//handle[0] = (HANDLE) _beginthread(ThreadProc,0,&val);
	//handle[1] = (HANDLE) _beginthread(ThreadProc,0,&val);


	for(i=0; i<size; i++){
		arr[i] = 1;
		check[i] = 0;
	}
	int flag= 1;
	for(i=2; i<size; i++){
		
		//arr[i] = 1;
		if(arr[i] == 1){
						
			if(flag){
				if(i*i > size){
					flag = 0;
				}
				
				else{
					val[i] = i;
					printf("called %d:\n", val[i]);
					handle[i] = (HANDLE) _beginthread(ThreadProc,0,&val[i]); // create thread
					check[i] = 1;
				}
				
			}
			
		}
	}
	
	for(i=2; i<size; i++){
		if(check[i] == 1){
			WaitForSingleObject(handle[i],INFINITE);
		}
	}
	int count =0;
	for(i=2; i<size; i++){
		if(arr[i] == 1){
			printf("%d ", i);
			count++;
		}
	}
	printf("%d", count);
	return 0;
}


void ThreadProc(void *param)
{
	
	int i = *((int*)param);
	//printf("Thread %d is Running!\n",i);
	long j;
	for(j= i*i; j<size; j= j+i){
					arr[j] = 0;
	}
	_endthread();
}

