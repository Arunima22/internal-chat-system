#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>

#define SV_SOCK_PATH "/tmp/usr_sock"
 
int main(){

	int socketFD = socket(PF_LOCAL, SOCK_STREAM, 0);

	if (socketFD == -1){
		printf("Socket Not Made\n");
	}
	else {
		printf("Socket Made\n");
		printf("Socket FD: %d\n", socketFD);
	}
	
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = PF_LOCAL;
	strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);
	
	unlink(SV_SOCK_PATH);
	int server_res = bind(socketFD, (struct sockaddr *) &addr, sizeof(addr));
	if (server_res == -1){
		perror("bind");
		printf("Bind was not successful\n");
	} 
	else {
		printf("Bind was successful\n");
	}

	return 0;
	
 }
