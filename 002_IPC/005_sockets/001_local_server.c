#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>     // sockaddr_un 
#include <sys/socket.h> // AF_UNIX
#include <unistd.h>     // sleep, close, unink

#define SERVER_PATH     "/tmp/server"
#define BUFFER_LENGTH    250

int main() 
{ 
	int    socket_server, socket_client;
	int    rc, length;
    char   buffer[BUFFER_LENGTH];
    struct sockaddr_un serveraddr;

// (1) - stworz socket
	socket_server = socket(AF_UNIX,    	// domain
						   SOCK_STREAM, // type
						   0);          // protocol
    if (socket_server < 0) {
		printf("socket() failed");
		exit(-1);
    }
	
// (2) połącz adres lokalny z desktryptorem gniazda	
	memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path, SERVER_PATH);	

	rc = bind(socket_server, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if (rc < 0) {
		printf("bind() failed");
		exit(-1);
    }

// (3) ustaw gniazdo jako pasywne - mozliwosc akceptacji polaczen
	rc = listen(socket_server, 10);
    if (rc < 0) {
		printf("listen() failed");
		exit(-1);
    }

// (4) zaakceptuj polaczenie na gniezdzie, blokujace wywolanie
	printf("Server gotowy do akceptacji polaczen - czekamy...\n");
	socket_client = accept(socket_server, NULL, NULL);
	if (socket_client < 0) {
		printf("accept() failed");
		exit(-1);
    }

// (5) zapis / odczyt	
	printf("Klient polaczyl sie, odczytujemy dane\n");	
	read(socket_client, buffer, 20);
	printf("Odczytano - %s\n", buffer);
	
	write(socket_client, "hello back", strlen("hello back") + 1);
	sleep(5);
	
	close(socket_client);
	close(socket_server);
    unlink(SERVER_PATH);
}
	