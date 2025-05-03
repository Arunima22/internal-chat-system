#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
void get_addr(struct sockaddr_in * addr, int port, char * add4){
	memset(addr, 0, sizeof(struct sockaddr_in));
	addr->sin_family = PF_INET;
	addr->sin_port = htons(port);
	inet_aton(add4, &addr->sin_addr);
}

int main(){

	int socketFD = socket(PF_INET, SOCK_STREAM, 0);

	if (socketFD == -1){
		perror("Socket");
	}
	else {
		printf("Socket FD: %d\n", socketFD);
	}
	
	struct sockaddr_in addr;
	get_addr(&addr, 8080, "127.0.0.1");


	int client_res = connect(socketFD, (struct sockaddr *) &addr, sizeof(addr));	
	if (client_res == -1) {
		perror("Connect");
	}
	else {
		printf("Connection to socket successful\n");
	}	
	
	char buf[500];
	read(socketFD, buf, 500);
	printf("Received: %s\n", buf);
	
	return 0;
	
 }
