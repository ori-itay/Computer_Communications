#include <stdio.h>
#include "winsock2.h"
#include <stdlib.h>

void Init_Winsock();

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Error: not enough arguments were provided!\n");
		exit(1);
	}
	Init_Winsock();






	return 0;
}

void Init_Winsock() {
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Error at WSAStartup()\n");
	exit(1);
}