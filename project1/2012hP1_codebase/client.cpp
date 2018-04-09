#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <time.h>
#include "proj1.h"
/* TODO: define Client member functions */

void Client::error(const char *msg)
{
	perror(msg);
	exit(1);
}

Client::Client(char *arg, int portno){
	//connent the server
	server = gethostbyname(arg);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR connecting");
}

void Client::get_price() {
	//read information from the server
	bzero(buffer, 256);
	n = read(sockfd, buffer, 256);
	if (n <= 0) error("ERROR reading from socket");
	//check if it's the wrong information
	if (strlen(buffer) < 40) printf(buffer);
	sleep(1);
}

void Client::gen_buy_request() {
	//continue when press enter
	getchar();
	bzero(buffer2, 256);
	n = read(sockfd, buffer2, 256);
	if (n <= 0) error("ERROR reading from socket");
	printf(buffer2);
	//print the price_buy and time
	printf("from client: client buy at ");
	printf(buffer2);
	//send the information to the server
	n = write(sockfd, buffer2, 256);
	if (n < 0) error("ERROR writing to socket");
	//read and print the result
	bzero(buffer3, 256);
	n = read(sockfd, buffer3, 256);	
	if (n < 0) error("ERROR reading from socket");
	if (n > 0) {
		printf(buffer3);
	}
	n = 0;
}