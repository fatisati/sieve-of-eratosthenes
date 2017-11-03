#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
#define NUM_THREADS 100

/* create thread argument struct for thr_func() */
typedef struct _thread_data_t {
  int tid;
  double stuff;
} thread_data_t;

int size;
int *arr;
int *check;
pthread_t *thr;
thread_data_t *thr_data;
 
/* thread function */
void *thr_func(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;
  int i = data->tid;
  printf("hello from thr_func, thread id: %d\n", i);

  long j;
  for(j= i*i; j<size; j= j+i){
  	arr[j] = 0;
  }
 
  pthread_exit(NULL);
}
 
int main(int argc, char **argv) {

  int i, rc;
  size = 1000000;
  arr = (int *)malloc(sizeof(int) * size);
  check = (int *)malloc(sizeof(int) * size);

  thr = (pthread_t *)malloc(sizeof(pthread_t) * size);
  thr_data = (thread_data_t *)malloc(sizeof(thread_data_t) * size);

  for(i=0; i<size; i++){
  	arr[i] = 1;
	check[i]=0;
  }

  //pthread_t thr[size];
  /* create a thread_data_t argument array */
  //thread_data_t thr_data[size];
 
  /* create threads */
  int flag= 1;
  for (i = 2; i < size; i++) {

    if(arr[i]==1){
	
	if(flag){
		
		if(i*i >size){
			flag = 0;
		}
		else{
    			thr_data[i].tid = i;
			check[i]=1;
    			if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
      				fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      				return EXIT_FAILURE;
    			}
		}
	}
			
    }
  }
  /* block until all threads complete */
  for (i = 0; i < size; ++i) {
	if(check[i]){
	pthread_join(thr[i], NULL);
	}
  }
  int count =0;

  for (i = 2; i < size; ++i) {
	if(arr[i]==1){
		printf("%d ",i);
		count++;
	}
  }
  printf("%d", count);
 
  return EXIT_SUCCESS;
}
