#ifndef PROJ1_H 
#define PROJ1_H
#include <time.h>
using namespace std;

/* TODO: Server and Client classes */
const int PORTNO = 51818;
class Server {
	public:
	Server();
	int sock();
	void gen_price(int);
	void process_buy_request(int );
	
	private:
	int sockfd;
	int portno;
	char buffer[256];
	int *price;
	struct sockaddr_in serv_addr, cli_addr;
	void error(const char *msg);
	int *last_renew;
	int share_size;
	int segmentId;
	int *buy_attempts;
};

class Client {
	public:
	Client(char * ,int );
	int portno;
	void gen_buy_request();
	void get_price();
	
	private:
	int sockfd;
	int *price;
	int share_size;
	int segmentId;
	time_t get_time;
	time_t sent_time;
	void error(const char* msg);
	void print_results(bool,int,int,time_t,time_t);
	struct hostent *server;
	struct sockaddr_in serv_addr;
};

#endif
