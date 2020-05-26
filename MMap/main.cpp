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

	//Abfangen ob Dateiname überhaupt angegeben wurde.
	if (argc < 2) {
		//perror macht nen Output an cerr
		perror("Fehler: Dateiname nicht angegeben");
		//exit 1 heißt fehler in main
		exit(1);
	}

	//Dateiname zum öffnen
	char *filename = argv[1];
	//filedescriptor ist der int unter dem die Datei später mal erreichbar ist
	int filedescriptor = 0;

	int fd_to_write = 0;
	//neuen stat-pointer file_metadata erzeugen. wird später gebraucht um die filesize in bytes zu ermitteln.
	//stat ist n format in dem metadaten einer datei eingefügt werden
	struct stat *file_metadata = (struct stat*) malloc(sizeof(struct stat));
	//filemap ist der pointer unter der die Datei im Programm-Speicher (RAM) die Datei später erreichbar ist
	void *filemap;

	//öffne die datei readonly (mehr braucht's nicht)
	filedescriptor = open(filename, O_RDONLY);
	fd_to_write = open("kopie.txt", O_WRONLY | O_CREAT);

	//wenn das fehlschlägt konnte die Datei nicht geöffnet werden
	//wenn user z.b. keine readrechte hat.
	if (filedescriptor == -1 || fd_to_write == -1) {
		perror("Fehler: Kann Datei nicht oeffnen");
		exit(1);
	}
	//fstat(fd,statptr) kopiert die Metadaten der Datei von fd auf statptr
	//wenn das failed (returned -1), dann schmeiß n error
	if (fstat(filedescriptor, file_metadata) < 0) {
		perror("Fehler: Konnte metadaten nicht lesen");
		close(filedescriptor);
		close(fd_to_write);
		free(file_metadata);
		exit(1);
	}
	//mmap lädt die Datei in den Hauptspeicher und returned nen void* auf die Stelle
	//Argumente von nem Beispiel abgeschaut.
	filemap = mmap(0, file_metadata->st_size, PROT_READ,
	MAP_SHARED, filedescriptor, 0);
	//wenn filemap auf Adresse -1 zeigt hat mmap nicht geklappt. Fehler abfangen.
	if (filemap == MAP_FAILED) {
		perror("Fehler beim erstellen des mappings");
		close(filedescriptor);
		close(fd_to_write);
		free(file_metadata);
		exit(1);
	}

	//Char* zeiger zeigt auf ersten buchstabe vom gecasteten void*.
	//man könnte hier for simplicity auch n array nehmen
	char *zeiger = (char*) filemap;
	//for-schleife gibt alle chars in der Datei im Haupspeicher aus
	for (int i = 0; i <= file_metadata->st_size; i++) {
		//gib char aus
		if (write(fd_to_write, zeiger, sizeof(char)) == -1) {
			perror("Fehler beim schreiben");
			close(filedescriptor);
			close(fd_to_write);
			free(file_metadata);
			exit(1);
		}
		//erhöhe zeier um einen char auf den nächsten char
		zeiger = zeiger + sizeof(char);
	}

	//schließe fd
	close(filedescriptor);
	close(fd_to_write);
	//free speicher vom stat*
	free(file_metadata);

	return 0;
}

