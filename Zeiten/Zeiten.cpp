#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

int main(int argc, char **argv) {
	string command;
	if (argc > 2) {
		command = argv[1];
		command += " ";
		command += argv[2];
	} else {
		command = argv[1];
	}

	timeval starttime;
	timeval endtime;
	rusage usage;

	gettimeofday(&starttime, 0);
	system(command.c_str());
	gettimeofday(&endtime, 0);
	long took_usec = endtime.tv_usec - starttime.tv_usec;
	time_t took_sec = endtime.tv_sec - starttime.tv_sec;
	getrusage(RUSAGE_SELF, &usage);

	cout << "Kommando: " << command << endl;
	cout << "Laufzeit: "<< took_sec << "." << took_usec << "s" << endl;
	cout <<"User-Zeit: "<< usage.ru_utime.tv_sec <<"."<<usage.ru_utime.tv_usec<<"s" << endl;
	cout <<"System-Zeit: "<< usage.ru_stime.tv_sec <<"."<<usage.ru_stime.tv_usec<<"s" << endl;

}
