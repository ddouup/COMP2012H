#ifndef PROJ1_H 
#define PROJ1_H

/* TODO: Server and Client classes */

const int Portno = 9999;

class Server {
private:
	int n, sockfd, portno, newsockfd, size, *attempts, *time_start;
	float *price;
	struct sockaddr_in serv_addr;
	char buffer[256], buffer2[256];
	void error(const char *msg);

public:
	Server();
	int sock();
	void gen_price(int sock);
	void process_buy_request(int sock);
};

class Client {
private:
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int n, sockfd, size;
	float *price;
	char buffer[256], buffer2[256];
	void error(const char *msg);

public:
	Client(char *arg, int portno);
	void get_price();
	void gen_buy_request();
};
#endif
