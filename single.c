#include<stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<stdio.h>   
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
int main(){
	int size = 1000000;
	int *arr;
	arr = (int *)malloc(sizeof(int) * size);
	int i;
	for(i=0; i<size; i++){
		arr[i] = 0;
	}
	int flag= 1;
	for(i=2; i<size; i++){
		
		arr[i]++;
		if(arr[i] == 1){
			
			//printf("%d ", i);
			
			if(flag){
				if(i*i > size){
					flag = 0;
				}
				long j;
				for(j= i*i; j<size; j= j+i){
					arr[j]++;
				}
			}
			
		}
	}
	
	int count =0;
	for(i=2; i<size; i++){
		if(arr[i] == 1){
			printf("%d ", i);
			count++;
		}
	}
	printf("\n%d", count);
	return 0;
}
