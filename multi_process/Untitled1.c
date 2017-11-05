 // For WinXp

#define _WIN32_WINNT 0x0501

#include <windows.h>

#include <stdio.h>
#include<string.h>
int size;
int *arr;
int *check;
//int *val;

HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;

HANDLE g_hInputFile = NULL;
 
void CreateChildProcess(void); 
void WriteToPipe(void); 
void ReadFromPipe(void); 
void ErrorExit(PTSTR); 

STARTUPINFO *si;
PROCESS_INFORMATION *pi;

int main()

{

    //STARTUPINFO si[10];

    //PROCESS_INFORMATION pi[10];
    //int val[10];
    size = 100;
    arr = (int *)malloc(sizeof(int) * size);
	//val = (int *)malloc(sizeof(int) * size);
	check = (int *)malloc(sizeof(int) * size);
	si = (STARTUPINFO *)malloc(sizeof(STARTUPINFO) * size);
	pi = (PROCESS_INFORMATION *)malloc(sizeof(PROCESS_INFORMATION) * size);
	
	int i;
    for(i=0; i<size; i++){
		arr[i] = 1;
		check[i] = 0;
	}
	int flag= 1;
    
    
	for(i=0; i<size; i++){
		
		if(arr[i] == 1){
			if(flag){
				
				if(i*i > size){
					flag = 0;
				}
				
				else{
					ZeroMemory(&si[i], sizeof(si[i]));

    				si[i].cb = sizeof(si[i]);

    				ZeroMemory(&pi[i], sizeof(pi[i]));
    				char str[] = ".\a.exe ";
					char snum[10];
					char snum2[10];
					strcat(str, itoa(i, snum,10));
					strcat(str, " ");
					strcat(str, arr);
					printf("::%d\n", &arr);
    				// Start the child process. If not OK...
    				if(!CreateProcess("C:\\Users\\Fateme\\Desktop\\uni\\os\\mini_project1\\multi_process\\a.exe",	// module name.

        				str,    // Command line.

        				NULL,    // Process handle not inheritable.

        				NULL,    // Thread handle not inheritable.

        				FALSE,   // Set handle inheritance to FALSE.

        				0,       // No creation flags.

        				NULL,    // Use parent's environment block.

        				NULL,    // Use parent's starting directory.

        				&si[i],     // Pointer to STARTUPINFO structure.

        				&pi[i])     // Pointer to PROCESS_INFORMATION structure.

    				)

 

       					// Then, give some prompt...

       					printf("\nSorry! CreateProcess() failed.\n\n");

   				//else, give some prompt...

   					else

   					{

      			 	//printf("\nWell, CreateProcess() looks OK.\n");
		
       				//printf("exit after 5000 ms...\n\n");
       				check[i] = 1;
       				printf("called %d:\n", i);

  					}
				}
			}
		}
		
	}
    

    // Wait until child process exits after 5000 ms.
	for(i=0; i<size; i++){
		if(check[i]){
			WaitForSingleObject(pi[i].hProcess, 5000);
			printf("%d terminated\n", i);
		}

    	
	}
    
	
    // Close process and thread handles.
	for(i=0; i<size; i++){
		if(check[i]){
			CloseHandle(pi[i].hProcess);

    CloseHandle(pi[i].hThread);
		}
		

	}
    
    return 0;

}
