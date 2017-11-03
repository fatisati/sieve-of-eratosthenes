#include<stdio.h>
#include <stdlib.h>


int main(){
	int size = 10000000;
	int *arr;
	arr = (int *)malloc(sizeof(int) * size);
	for(int i=0; i<size; i++){
		arr[i] = 0;
	}
	int flag= 1;
	for(int i=2; i<size; i++){
		
		arr[i]++;
		if(arr[i] == 1){
			
			printf("%d ", i);
			
			if(flag){
				if(i*i > size){
					flag = 0;
				}
				
				for(long j= i*i; j<size; j= j+i){
					arr[j]++;
				}
			}
			
		}
	}
	
}
