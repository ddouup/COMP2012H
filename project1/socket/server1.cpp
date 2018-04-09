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
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

/* TODO: define Server member functions here */

using namespace std;

void Server::error(const char* msg) {
	perror(msg);
	exit(1);
}

Server::Server() : portno(PORTNO), share_size(sizeof(int) * 3) {
	
	//initialize server and store the socketfd for binding serv_addr
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	int skfd = socket(AF_INET, SOCK_STREAM, 0);
	if (skfd < 0)
		error("ERROR opening socket");
	if (bind (skfd, (struct sockaddr *) &serv_addr,
		  sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	sockfd = skfd;
	
	//create shared memory to store common data for processes
	segmentId = shmget(IPC_PRIVATE, share_size, S_IRUSR | S_IWUSR);
	last_renew = (int *) shmat(segmentId, NULL, 0);
	*last_renew = 0;
	price = last_renew + 1;
	*price = 10;
	buy_attempts = last_renew + 2;
	*buy_attempts = 0;
	
}

//return socketfd binded with server address
int Server::sock(){
	return sockfd;
}

void Server::process_buy_request(int sockfd){
	char buffer[256]; // store contents from socket
	//read the request
	int n = read(sockfd, buffer, 256);
	if(n < 0)
		error("ERROR reading from socket");
	//if it's not from Client::gen_buy_request
	//re-read
	int client_buy_filter = atoi(buffer)/100;
	if (client_buy_filter != 1) {
		cerr << "error reading from client_buy socket"
			<< endl;
		sleep(1);
		return;
	}

	//add and print buy_attempts after successfully read 
	(*buy_attempts)++;
	cout << "num buy attempts: " << *buy_attempts <<endl;
	
	//compare with and return to client the current price
	bzero(buffer,256);
	int server_proc_price = *price +300;
	snprintf(buffer, 255, "%d", server_proc_price);
	int nn = write(sockfd,buffer,256);
	if (nn < 0)
		error("ERROR writing to the socket");

	//add 1 sec
	sleep(1);
}
void Server::gen_price(int sockfd) {
	/*NEED TO RENEW*/
	//generate the price
	int rPrice;
	srand (time(NULL));
	rPrice = rand() % 9 + 1;
	/*NEED TO RENEW*/
	
	//get how many 10-secs have passed in UNIX time
	int cur_time = (int) time(NULL);;
	//if price hasn't been renewed in this 10-sec
	//renew it and increase the renewed time
	if(cur_time > *last_renew + 9) {
		*last_renew = cur_time;
		*price = rPrice;
		
		time_t mytime;
		mytime = time(NULL);
		cout << "$" << rPrice << "  |  " << ctime(&mytime);
	}

	//send the price to the client every sec
    bzero(buffer,256);
	int server_gen_price = *price + 200;
	snprintf(buffer, 255, "%d", server_gen_price);
	int n = write(sockfd,buffer,256);
	if (n < 0)
		error("ERROR writing to the socket");
	
	//add 1 sec
	sleep(1);
}