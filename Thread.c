#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include<tchar.h>
#include "psapi.h"

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
	int ii;
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
	for(ii=0; ii<size; ii++){
		arr[ii] = 0;
	}
	int flag= 1;
	for(ii=2; ii<size; ii++){
		
		arr[ii]++;
		if(arr[ii] == 1){
						
			if(flag){
				if(ii*ii > size){
					flag = 0;
				}
				
				else{
					val = ii;
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

// Get the list of process identifiers.

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return 1;
    }

    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the memory usage for each process

    for ( i = 0; i < cProcesses; i++ )
    {
        PrintMemoryInfo( aProcesses[i] );
    }

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

void PrintMemoryInfo( DWORD processID )
{
    HANDLE hProcess;
    PROCESS_MEMORY_COUNTERS pmc;

    // Print the process identifier.

    printf( "\nProcess ID: %u\n", processID );

    // Print information about the memory usage of the process.

    hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ,
                                    FALSE, processID );
    if (NULL == hProcess)
        return;

    if ( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
    {
        printf( "\tPageFaultCount: 0x%08X\n", pmc.PageFaultCount );
        printf( "\tPeakWorkingSetSize: 0x%08X\n", 
                  pmc.PeakWorkingSetSize );
        printf( "\tWorkingSetSize: 0x%08X\n", pmc.WorkingSetSize );
        printf( "\tQuotaPeakPagedPoolUsage: 0x%08X\n", 
                  pmc.QuotaPeakPagedPoolUsage );
        printf( "\tQuotaPagedPoolUsage: 0x%08X\n", 
                  pmc.QuotaPagedPoolUsage );
        printf( "\tQuotaPeakNonPagedPoolUsage: 0x%08X\n", 
                  pmc.QuotaPeakNonPagedPoolUsage );
        printf( "\tQuotaNonPagedPoolUsage: 0x%08X\n", 
                  pmc.QuotaNonPagedPoolUsage );
        printf( "\tPagefileUsage: 0x%08X\n", pmc.PagefileUsage ); 
        printf( "\tPeakPagefileUsage: 0x%08X\n", 
                  pmc.PeakPagefileUsage );
    }

    CloseHandle( hProcess );
}

