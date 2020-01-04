#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h> // sockaddr_in 
#include <arpa/inet.h>  // inet_addr
#include <sys/socket.h> // AF_UNIX
#include <unistd.h>     // sleep, close, unink
#include <string.h>     // strlen

int main() 
{ 
	char   buff[20];
	int                client_sockfd;  
	struct sockaddr_in server_address; 
	
	// (1) stworz socket
	client_sockfd = socket(AF_INET,    	// domain
						   SOCK_STREAM, // type
						   0);          // protocol
	
	// (2) polacz adres zdalny z desktryptorem gniazda, gniazdo aktywne
	server_address.sin_family      = AF_INET; 
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port        = htons(9734); // => network order needed
	connect(client_sockfd, (struct sockaddr *)&server_address, sizeof(server_address));

	//6) zapis
	sleep(5);
	write(client_sockfd, "hello world", strlen("hello world") + 1);
	
	//(5) odczyt, wywołanie blokujace
	read(client_sockfd, buff, 20);
	printf("Odczytano - %s\n", buff);
	
	 // (7) - zamknięcie
	close(client_sockfd); 
}
	