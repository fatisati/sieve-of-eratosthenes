#include <windows.h>

#include <stdio.h>

void work(int i, int *arr){
	printf("working %d arr %d\n", i, arr[i]);
}
//int argc, char *argv[]
int main(int argc, char *argv[]){
	
	//printf("%d", *argv[1] - 48);
	int a;
	a = (argv[2]-48);
	work(*argv[1] - 48, a);
	//work();
	return 0;
}
