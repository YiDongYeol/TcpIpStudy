#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

void* request_handler(void* arg);
void send_data(int clnt_sock);
void send_image(int clnt_sock);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_size;
	char req_line[1024];
	if(argc!=2){
		exit(1);
	}

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		exit(1);
	if(listen(serv_sock, 20)==-1)
		exit(1);

	while(1)
	{
		clnt_adr_size=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size);
		printf("Conection Request : %s:%d\n",
			inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));
		read(clnt_sock,req_line,1024);
		printf("%s\n",req_line);
		if(!strncmp(req_line,"GET /peng.jpg",13))
			send_image(clnt_sock);
		else
			send_data(clnt_sock);
		close(clnt_sock);

	}
	close(serv_sock);
	return 0;
}

void send_data(int clnt_sock)
{

	char buf[]="HTTP/1.1 200 OK\r\n"
		"Server:Linux Web Server \r\n"
		"Content-Type: text/html; charset=UTF-8\r\n\r\n"
		"<!DOCTYPE html>\r\n"
		"<html><head><title> My Web Page </title>\r\n"
		"<style>body {background-color: #FFFF00 }</style></head>\r\n"
		"<body><center><hl>Hello world!!</hl><br>\r\n"
		"<img src=\"peng.jpg\"></center></body></html>\r\n";

	write(clnt_sock,buf,sizeof(buf)-1);
}
void send_image(int clnt_sock)
{
	char img_buf[800000];
	int img;
	img=open("peng.jpg", O_RDONLY);
	read(img,img_buf,sizeof(img_buf));
	write(clnt_sock, img_buf, sizeof(img_buf));

	close(img);
}
