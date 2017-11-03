#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
#define NUM_THREADS 100
int size;
int *arr;
/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid;
  double stuff;
} thread_data_t;
 
/* thread function */
void *thr_func(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;
  int i = data->tid;
  printf("hello from thr_func, thread id: %d\n", i);

  long j;
  for(j= i*i; j<size; j= j+i){
  	arr[j]++;
  }
 
  pthread_exit(NULL);
}
 
int main(int argc, char **argv) {

  int i, rc;
  size = 100;
  arr = (int *)malloc(sizeof(int) * size);
  for(i=0; i<size; i++){
  	arr[i] = 0;
  }

  pthread_t thr[size];
  /* create a thread_data_t argument array */
  thread_data_t thr_data[size];
 
  /* create threads */
  int flag= 1;
  for (i = 2; i < size; i++) {

    arr[i]++;
    if(arr[i]==1){
	
	if(flag){
		
		if(i*i >size){
			flag = 0;
		}
		else{
    			thr_data[i].tid = i;
    			if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
      				fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      				return EXIT_FAILURE;
    			}
			pthread_join(thr[i], NULL);
		}
	}
			
    }
  }
  /* block until all threads complete */
  /*for (i = 0; i < size; ++i) {
	pthread_join(thr[i], NULL);
  }*/

  for (i = 0; i < size; ++i) {
	if(arr[i]==1){
		printf("%d ",i);
	}
  }
 
  return EXIT_SUCCESS;
}
