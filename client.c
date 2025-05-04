#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 1024
 
void get_addr(struct sockaddr_in * addr, int port, char * add4){
	memset(addr, 0, sizeof(struct sockaddr_in));
	addr->sin_family = PF_INET;
	addr->sin_port = htons(port);
	inet_aton(add4, &addr->sin_addr);
}

int main(int argc, char * argv[]){

	if (argc != 3){
		printf("Usage: %s <IP> <port>\n", argv[0]);
		return 0;
	}

	int clientFD = socket(PF_INET, SOCK_STREAM, 0);
	if (clientFD == -1){
		perror("Socket");
		return 0;
	}
	else {
		printf("Socket FD: %d\n", clientFD);
	}
	
	struct sockaddr_in addr;
	get_addr(&addr, atoi(argv[2]), argv[1]);

	printf("Here\n");

	int connectRes = connect(clientFD, (struct sockaddr *) &addr, sizeof(addr));	
	if (connectRes == -1) {
		perror("Connect");
	}
	else {
		printf("Connection to socket successful\n");
	}	
	
	char buf[BUFSIZE];
	while(1){
		fputs("Input message (q to quit): ", stdout);
		fgets(buf, BUFSIZE, stdin);
		if(!strcmp(buf,"q\n")||!strcmp(buf,"Q\n"))
			break;
		write(clientFD, buf, strlen(buf));
		int str_len = read(clientFD, buf, BUFSIZE-1);
		buf[str_len] = 0;
		printf("Message from the server: %s", buf);

	}
	printf("Closing connection...\n");
	close(clientFD);
	return 0;
	
 }
