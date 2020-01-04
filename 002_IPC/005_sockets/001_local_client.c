#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>     // sockaddr_un 
#include <sys/socket.h> // AF_UNIX
#include <unistd.h>     // sleep, close, unink

#define SERVER_PATH     "/tmp/server"
#define BUFFER_LENGTH    250

int main() 
{ 
	char   buff[BUFFER_LENGTH];
	int    client_sockfd, rc; 
	struct sockaddr_un server_address; 
	
// (1) stworz socket
	client_sockfd = socket(AF_UNIX,    	// domain
						   SOCK_STREAM, // type
						   0);          // protocol
	if (client_sockfd < 0) {
		printf("socket() failed");
		exit(-1);
    }
	
// (2) polacz adres zdalny z desktryptorem gniazda, gniazdo aktywne
	memset(&server_address, 0, sizeof(server_address));
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, SERVER_PATH);
	rc = connect(client_sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
	if (rc < 0) {
		printf("bind() failed");
		exit(-1);
    }

// (5) zapis / odczyt	
	sleep(5);
	write(client_sockfd, "hello world", strlen("hello world") + 1);
	
	read(client_sockfd, buff, BUFFER_LENGTH);
	printf("Odczytano - %s\n", buff);	

	close(client_sockfd); 
}
	