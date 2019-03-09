#include <stdio.h>
#include "winsock2.h" 

#define SEND_BUFF 57
#define READ_BUFF 49

int main(int argc, char** argv) {

	Init_Winsock();
	//test
	char send_buff[SEND_BUFF];
	char read_buff[READ_BUFF];
	unsigned int serv_port = -1, totalsent = -1, num_sent = -1, num_read = -1, notwritten = -1, not_been_read = -1;
	int sockfd = -1, input_file_size = 0;
	FILE *fp;

	if (argc != 4) {
		fprintf(stderr, "Error: not enough arguments were provided\n");
		exit(1);
	}
	char* ip = argv[1]; char* port = argv[2]; char* file_name = argv[3];

	if ((fp = fopen(file_name, "r")) == NULL) {
		fprintf(stderr, "Error: not able to open file. \n");
		exit(1);
	}
	input_file_size = get_file_size(file_name);


	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(1);
	}

	serv_port = (unsigned int)strtoul(port, NULL, 10); //get server's port number
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port); // htons for endiannes
	serv_addr.sin_addr.s_addr = inet_addr(ip);

	not_been_read = input_file_size;
	while (not_been_read > 0) {
		memset(read_buff, 0, READ_BUFF);
		num_read = read(fp, read_buff, MIN(READ_BUFF, not_been_read));
		if (num_read <= 0) {
			fprintf(stderr, "Error reading fron file. exiting...\n");
			exit(1);
		}
		not_been_read -= num_read;
		compute_block(read_buff, send_buff);

		notwritten = num_read; //curr num of bytes to write
		totalsent = 0;
		// keep looping until nothing left to write for this BUFF size block
		while (notwritten > 0) {
			// notwritten = how much left to write ; totalsent = how much written so far ; num_sent = how much written in last write() call
			num_sent = sendto(sockfd, send_buff + totalsent, notwritten, 0, &serv_addr, sizeof(serv_addr));
			if (num_sent == -1) {// check if error occured (server closed connection?)
				fprintf(stderr, "%s\n", strerror(errno));
				exit(1);
			}
			totalsent += num_sent;
			notwritten -= num_sent;
		}
	}

	if (fclose(fp) != 0) {
		fprintf(stderr, "%s\n", strerror(errno));
	}
	if (closesocket(sockfd) != 0) {
		fprintf(stderr, "%s\n", strerror(errno));
	}
	return 0;
}




void Init_Winsock() {
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Error at WSAStartup()\n");
	exit(1);
}



//based on code from https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
int get_file_size(FILE *fp) {
	int size = 0;

	fseek(fp, 0, SEEK_END); // seek to end of file
	size = ftell(fp); // get current file pointer
	rewind(fp); // seek back to beginning of file

	return size;
}

void compute_block(char read_buff[READ_BUFF], char send_buff[SEND_BUFF]) {



	return;
}