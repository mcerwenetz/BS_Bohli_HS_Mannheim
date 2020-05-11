#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <array>
#include <pthread.h>

using namespace std;

int  main(){
	const int LEN = 10;
	int* array = new int[LEN];
	srand(time(NULL));
	for(int i =0; i < LEN; i++){
		array[i]=rand()%100;
	}

	pthread_t thread_id;
	pthread_create(&thread_id, NULL, NULL, NULL);
	pthread_join(thread_id, NULL);

	delete[] array;
	return 0;
}

