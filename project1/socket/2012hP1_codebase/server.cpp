#include <stdio.h>
#include <math.h>
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

/* TODO: define Server member functions here */

void Server::error(const char *msg){
	perror(msg);
	exit(1);
}

Server::Server():portno(Portno){

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	
	price = (float*)mmap(NULL, sizeof(price), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (price == MAP_FAILED)
		error("ERROR in mmap");
	srand(time(NULL));
	*price = (rand() % 101) / 100.0;
	time_start = (int*)price + 1;
	*time_start = (int) time(NULL);
	attempts = time_start + 1;
	*attempts = 0;
}
	
int Server::sock() {
	return sockfd;
}

void Server::gen_price(int sock) {
	srand(time(NULL));
	float price_current= (rand() % 101 )/ 100.0;
	
	int time_current = (int) time(NULL);
	
	//update the price every 10 seconds
	if ((time_current - *time_start) > 9) {
		*price = price_current;
		*time_start = time_current;
	}
	
	time_t mytime = time(NULL);

	bzero(buffer, 256);
	printf("$%.2f ", *price);
	printf(ctime(&mytime));
	
	snprintf(buffer, 255, "%f", *price);
	n = write(sock, buffer, 256);
	if (n < 0) error("ERROR writing to socket");

	sleep(1);
}

void Server::process_buy_request(int sock) {
	n = read(sock, buffer2, 256);
	if (n < 0) error("ERROR reading from socket");

	(*attempts)++;

	printf("num buy attempts = %d\n", *attempts);

	bzero(buffer2, 256);
	snprintf(buffer2, 255, "%f", *price);
	n = write(sock, buffer2, 256);
	if (n < 0) error("ERROR writing to socket");

	sleep(1);
}