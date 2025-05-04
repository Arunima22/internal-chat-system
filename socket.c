#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BACKLOG 10
#define BUFSIZE 1024
#define MAXCLIENTS 5

void get_addr(struct sockaddr_in * serverAddress, int port, char * add4){
	memset(serverAddress, 0, sizeof(struct sockaddr_in));
	serverAddress->sin_family = PF_INET;
	serverAddress->sin_port = htons(port);
	inet_aton(add4, &serverAddress->sin_addr);
}
 
int main(int argc, char * argv[]){

	int socketFD, clientFD;
	char message[BUFSIZE];

	if (argc != 3){
		printf("Usage: %s <IP> <port>\n", argv[0]);
		return 0;
	}

	socketFD = socket(PF_INET, SOCK_STREAM, 0);

	if (socketFD == -1){
		perror("Socket");
	}
	else {
		printf("Socket FD: %d\n", socketFD);
	}
	
	struct sockaddr_in serverAddress;
	get_addr(&serverAddress, atoi(argv[2]), argv[1]);

	int serverRes = bind(socketFD, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
	if (serverRes == -1){
		perror("Bind");
	} 
	else {
		printf("Bind was successful\n");
	}

	int listenRes = listen(socketFD, BACKLOG);
	if (listenRes == -1){
		perror("Listen");
	}
	else {
		printf("Socket now listening\n");
	}

	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen = sizeof(clientAddress);

	for (int i = 0; i < MAXCLIENTS; i++){
		clientFD = accept(socketFD, (struct sockaddr *) &clientAddress, &clientAddressLen);
		if (clientFD == -1){
			perror("Accept");
		} else {
			printf("Accepted connection\n");
		}
		int str_len;
		while(1){
			str_len = read(clientFD,message,BUFSIZE);
			if (str_len == 0){
				break;
			}
			printf("Message received form client\n");
			write(clientFD,message,str_len);
			printf("Message echoed to client\n");
		}
			
		close(clientFD);
	}

	printf("Closing connection...\n");
	close(socketFD);
	return 0;
 }
