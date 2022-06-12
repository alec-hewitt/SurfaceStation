#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>


#include "main.h"

#define MAX_BUFF 100
#define PORT 8080
#define SA struct sockaddr

void transact_telemetry(int conn){
	char buff[MAX_BUFF];
	int n;

	for(;;){
		bzero(buff, MAX_BUFF);
		printf("hi");
		//read message
		read(conn, buff, sizeof(buff));
		//print
		printf(buff);
		bzero(buff, MAX_BUFF);
		n = 0;
		//copy message
		while((buff[n++] = getchar()) != '\n')
			;
		//send
		write(conn, buff, sizeof(buff));

		//check for deliberate termination
		if(strncmp("exit", buff, 4) == 0){
			printf("exiting!!!\n");
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	//GPIO Test
	printf("UROV surface server\n");

	int sock, conn, len;
	struct sockaddr_in servaddr, cli;

	//create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1){
		printf("socket creation failed!\n");
		exit(0);
	} else {
		printf("socket created!\n");
	}
	bzero(&servaddr, sizeof(servaddr));

	//assign ip + port
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if ((bind(sock, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	} else {
		printf("Socket successfully binded..\n");
	}

	//now listen to client on socket
	if((listen(sock, 5)) != 0){
		printf("listen failed\n");
		exit(0);
	} else {
		printf("server listening...\n");
	}

	//listening done
	len = sizeof(cli);

	//accept packet
	conn = accept(sock, (SA*)&cli, &len);
	if(conn < 0){
		printf("server accept client failed\n");
		exit(0);
	} else {
		printf("accepted client\n");
	}

	//chat now
	transact_telemetry(conn);

	close(sock);

	return 0;
}
