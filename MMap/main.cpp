/*
 * main.c
 *
 *  Created on: 23.05.2020
 *      Author: marius
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	if (argc < 2) {
		perror("Fehler: Dateiname nicht angegeben");
		exit(1);
	}

	char *filename = argv[1];
	int filedescriptor;
	struct stat *file_metadata = (struct stat*) malloc(sizeof(struct stat)); //buffer für die filesize
	void *filemap;

	filedescriptor = open(filename, O_RDWR);
	if (filedescriptor == -1) {
		perror("Fehler: Kann Datei nicht oeffnen");
		exit(1);
	}
//	fstat(filedescriptor, file_metadata);
	if (fstat(filedescriptor, file_metadata) < 0) {
		perror("Fehler: Konnte metadaten nicht lesen");
		close(filedescriptor);
		free(file_metadata);
		exit(1);
	}

	filemap = mmap(0, file_metadata->st_size, PROT_READ | PROT_WRITE,
	MAP_SHARED, filedescriptor, 0);
	if(filemap == MAP_FAILED){
		perror("Fehler beim erstellen des mappings");
		close(filedescriptor);
		free(file_metadata);
		exit(1);
	}

	char *zeiger = (char*) filemap;
	for (int i = 0; i <= file_metadata->st_size; i++) {
		cout << *zeiger;
		zeiger = zeiger + sizeof(char);
	}

	close(filedescriptor);
	free(file_metadata);

	return 0;
}

