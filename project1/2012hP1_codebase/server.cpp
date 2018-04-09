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
	//set up the server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	//initialize the shared memories and variables 
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
	//generate random price in[0,1]
	srand(time(NULL));
	float price_current= (rand() % 101 )/ 100.0;
	//update the price every 10 seconds
	int time_current = (int) time(NULL);
	if ((time_current - *time_start) > 9) {
		*price = price_current;
		*time_start = time_current;
	}
	//print price and time into the buffer
	time_t mytime = time(NULL);
	bzero(buffer, 256);
	snprintf(buffer, 255, "$%.2f at %s", *price, ctime(&mytime));
	printf(buffer);
	//send to the client
	n = write(sock, buffer, 256);
	if (n < 0) error("ERROR writing to socket");
	//add 1 second
	sleep(1);
}

void Server::process_buy_request(int sock) {
	//read the price_buy from the client
	bzero(buffer2, 256);
	n = read(sock, buffer2, 256);
	sleep(1);
	if (n < 0) error("ERROR reading from socket");
	//check if the client press enter instead of Ctrl+c
	if (n > 0) {
		(*attempts)++;
		printf("num buy attempts = %d\n", *attempts);
		//extract the price_buy from the buffer2
		for (int i = 1; i <= 4; i++) {
			 buffer3[i-1] = buffer2[i];
		}
		//compare the price_buy and current price
		//and send information back to the client
		float price_buy = atof(buffer3);
		float price_sell = *price;
		time_t time_r = time(NULL);
		if (price_sell == price_buy) {
			bzero(buffer3, 256);
			snprintf(buffer3, 255, "client buy at %sserver sell at $%.2f at %sall times approx\nbuy SUCCSEEFUL from the server!\n\n", buffer2, price_sell, ctime(&time_r));
		}
		else{
			bzero(buffer3, 256);
			snprintf(buffer3, 255, "client but at %sserver sell at $%.2f at %sall times approx\nbuy FAILED from the server!\n\n", buffer2, price_sell, ctime(&time_r));
		}
		n = write(sock, buffer3, 256);
		if (n < 0) error("ERROR writing to socket");
	}
}