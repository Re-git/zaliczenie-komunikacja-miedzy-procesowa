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
	int    server_sockfd;
	int	   client_sockfd; 
	int    server_len; 
	int    client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	
	// (1) stworz socket
	server_sockfd = socket(AF_INET,    	// domain
						   SOCK_STREAM, // type
						   0);          // protocol
	
	// (2) połącz adres lokalny z desktryptorem gniazda
	server_address.sin_family      = AF_INET; 
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	server_address.sin_port        = htons(9734); // => network order needed
	bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)); 
	
	// (3) ustaw gniazdo jako pasywne
	listen(server_sockfd, 
	       1); // The backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow   
	
	client_len = sizeof(client_address); 
	
	// (4) zaakceptuj polaczenie na gniezdzie, blokujace wywolanie
	printf("Czekamy aż klient się polaczy...\n");
	client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len); 
	printf("Czekamy aż klient polaczyl sie\n");
	
	//(5) odczyt, wywolanie blokujace
	printf("Czekamy na dane od klienta...\n");
	read(client_sockfd, buff, 20);
	printf("Odczytano - %s\n", buff);
	
	//6) zapis
	write(client_sockfd, "hello back", strlen("hello back") + 1);
	
	sleep(5);
	
	// (7) - zamknięcie
	close(client_sockfd);
}
	