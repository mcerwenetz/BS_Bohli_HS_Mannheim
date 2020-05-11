#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int i =0;

void* function(void *arg) {
	while(i < 100000){
		pthread_mutex_lock(&mutex);
		++i;
		pthread_mutex_unlock(&mutex);
		printf("i=%d\n", i);
	}
	return NULL;

}

void thread_mutex(void) {
	const int size = 2;
	pthread_t *threadgroup = new pthread_t[size];
	for (int i = 0; i < size; ++i) {
		pthread_create(&threadgroup[i], NULL, function, NULL);
	}

	for (int i = 0; i < size; ++i) {
		pthread_join(threadgroup[i], NULL);
	}



}
