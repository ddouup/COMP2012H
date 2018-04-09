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

	price = (float*)mmap(NULL, sizeof(price), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (price == MAP_FAILED)
		error("ERROR in mmap");
	*price = 0;
}
	
void Client::get_price() {
	
	n = read(sockfd, buffer, 256);
	if (n <= 0) error("ERROR reading from socket");

	float a = atof(buffer);
	*price = a;
	time_t mytime = time(NULL);
	printf("$%.2f ", a);
	printf(ctime(&mytime));

	sleep(1);
}

void Client::gen_buy_request() {
	//
	getchar();
	
	n = read(sockfd, buffer2, 256);
	if (n <= 0) error("ERROR reading from socket");
	float price_buy = atof(buffer2);

	n = write(sockfd, buffer2, 256);
	time_t time_s = time(NULL);
	if (n < 0) error("ERROR writing to socket");

	printf("from client: client buy at ");
	printf("$%.2f at ", price_buy);
	printf(ctime(&time_s));
	/*
	bzero(buffer2, 256);
	n = read(sockfd, buffer2, 256);	
	*/
	sleep(1);
	time_t time_r = time(NULL);
	if (n < 0) error("ERROR reading from socket");

	float price_sell = atof(buffer2);
	
	printf("client buy at $%.2f at %s", price_buy, ctime(&time_s));
	printf("server sell at $%.2f at %s", *price, ctime(&time_r));
	printf("all times approx\n");

	if (price_sell == price_buy)
		printf("buy SUCCESSFUL from the server!\n\n");
	else
		printf("buy FAILED from the server!\n\n");

	sleep(1);
}