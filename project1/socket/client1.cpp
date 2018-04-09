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
#include <iostream>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <limits>

/* TODO: define Client member functions */
using namespace std;

void Client::error(const char *msg){
	perror(msg);
	exit(0);
}

Client::Client(char *arg, int portno):server(gethostbyname(arg)), portno(PORTNO), 
			share_size(sizeof(int)){
	//connect the server
	int skfd = socket(AF_INET, SOCK_STREAM, 0);
	if(skfd < 0)
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server -> h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server -> h_length);
	serv_addr.sin_port = htons(portno);
	if(connect(skfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0)
		error("ERROR connecting");
	sockfd = skfd;
  
	//create shared memory to store common data for processes
	segmentId = shmget(IPC_PRIVATE, share_size, S_IRUSR | S_IWUSR);
	price = (int *) shmat(segmentId, NULL, 0);
	*price = 0;
}

void Client::get_price(){
	char buffer[256]; //store contents from socket
	//read from socket
	int n = read(sockfd, buffer, 256);
	if(n < 0)
    error("ERROR reading from socket");
	int server_gen_price = atoi(buffer);
	
	int pr = server_gen_price%100;//the actual price
	//if it's not from Server::gen_price
	//re-get_price
	int server_gen_filter = server_gen_price/100;
	if (server_gen_filter != 2) {
		cerr << "error reading from server_gen socket"
			<< endl;
		return;
	}
	*price = pr; //change the shm price after successfully get_price
	//print the price with time
	time_t mytime;
	mytime = time(NULL);
	cout << "$" << pr << "  |  "
	<< ctime(&mytime);
	
	//add 1 sec
	sleep(1);
}

//print information according to the feedback
void Client::print_results(bool cond, int buy_pr, int pr, time_t sent_time, time_t get_time) {
	string buy_cond = 
		(cond) ? "SUCCESSFUL" : "FAILED";
	cout << "client buy  at $" << buy_pr 
		<< " at " << ctime(&sent_time);
	cout << "server sell at $" << pr 
		<< " at " << ctime(&get_time);
	cout << "all time approx" << endl;
	cout << "buy " << buy_cond << " from server" << endl;
}

void Client::gen_buy_request() {
	int buy_pr; //the price sent to the server
	char buffer[256]; //store socket contents
	cin.clear();//clear error flag
	
	//press enter to continue
	cin.ignore(numeric_limits<streamsize>::max(), '\n' );
	
	buy_pr = *price;//the price in request
	//to differentiate from others
	int client_sent_price = buy_pr + 100;
	//to send the price to the server
	bzero(buffer,256);
	snprintf(buffer, 255, "%d", client_sent_price);
	int n = write(sockfd,buffer,256);
	sent_time = time(NULL);
	if (n < 0)
		error("ERROR writing to the socket");
	
	//and get the feedback from server	
	char buf[256]; //store socket contents
	int server_proc_price; //the actual price
	int server_proc_filter = 0; // the content filter
	//read from socket, if content doesn't match
	//send error message, and re-read
	while (server_proc_filter != 3) {
		int nn = read(sockfd, buf, 256);
		if(nn < 0)
			error("ERROR reading from socket");
		server_proc_price = atoi(buf);
		server_proc_filter = server_proc_price/100;
		if (server_proc_filter != 3)
			cerr << "error reading from server_proc socket" << endl;
	}
	
	//record time after successfully read from socket
	get_time = time(NULL);
	//price returned from server
	//which indicate whether request succeed
	int pr = server_proc_price%100;
	//print information acoording to the feedback
	print_results((pr <= buy_pr), buy_pr, pr, sent_time, get_time);
	
	//add 1 sec
	sleep(1);
}
