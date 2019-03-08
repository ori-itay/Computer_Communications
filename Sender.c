#include <stdio.h>

int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Error: not enough arguments were provided\n");
		exit(1);
	}
	char* ip = argv[1]; char* port = argv[2]; char* file_name = argv[3];






	return 0;
}