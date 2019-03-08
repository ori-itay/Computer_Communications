#include <stdio.h>
#include "winsock2.h" 

int main(int argc, char** argv) {

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Error at WSAStartup()\n");


	if (argc != 4) {
		fprintf(stderr, "Error: not enough arguments were provided\n");
		exit(1);
	}
	char* ip = argv[1]; char* port = argv[2]; char* file_name = argv[3];


	serv_port = (unsigned int)strtoul(port, NULL, 10); 
	struct sockaddr_in serv_addr;




	return 0;
}