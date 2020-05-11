/*
 * thread.c
 *
 *  Created on: 11.05.2020
 *      Author: marius
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* callback(void *vargb) {
	sleep(1);
	printf("Callback aus dem Thread\n");
	return NULL;
}

int main(int argc, char **argv) {
	pthread_t thread_id;
	printf("Before Thread\n");
	pthread_create(&thread_id, NULL, callback, NULL);
	pthread_join(thread_id, NULL);
	printf("After Thread");
	exit(0);
}

