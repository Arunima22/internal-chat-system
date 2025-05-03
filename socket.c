#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BACKLOG 10

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
	
	//unlink(SV_SOCK_PATH);

	int server_res = bind(socketFD, (struct sockaddr *) &addr, sizeof(addr));
	if (server_res == -1){
		perror("Bind");
	} 
	else {
		printf("Bind was successful\n");
	}

	int listen_res = listen(socketFD, BACKLOG);
	if (listen_res == -1){
		perror("Listen");
	}
	else {
		printf("Socket now listening\n");
	}

	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	int accept_res = accept(socketFD, (struct sockaddr *) &client_addr, &client_addr_len);
	if (accept_res == -1){
		perror("Accept");
	} else {
		printf("Accepted connection\n");
	}

	char * message = "I received a message\n";
	write(accept_res, message, strlen(message));
	printf("Sent a message\n");

	close(accept_res);
	close(socketFD);
	
	return 0;
	
 }
