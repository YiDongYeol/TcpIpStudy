#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

int main(int argc, char *argv[])
{
	int sock;
	pid_t pid;
	sock = socket(PF_INET, SOCK_STREAM, 0);

	printf("Origin Descriptor = %d\n", sock);

	pid = fork();

	if(pid==0)
		printf("Child Descriptor = %d\n", sock);
	else
		printf("Parent Descriptor = %d\n", sock);

	close(sock);
	return 0;
}
