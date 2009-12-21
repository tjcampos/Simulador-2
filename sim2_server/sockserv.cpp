#include "sockserv.h"

SockServ::SockServ(unsigned short port){
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("ERROR opening socket");
		return;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	int on = 1;
	fcntl(sock, F_SETFL, O_NONBLOCK);

	struct protoent *p;
	p = getprotobyname("tcp");
//	if (setsockopt(sock, p->p_proto, SO_REUSEADDR | TCP_NODELAY, &on, sizeof(on)) < 0){
//		perror("ERROR setting up socket options");
//	}
	
	if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){ 
		perror("ERROR on binding");
		return;
	}
	if (listen(sock, 1) < 0){
		perror("ERROR listening");
	}
	else{
		cout << "Servidor escutando na porta " << port << endl;
	}
}

SockServ::~SockServ(){
	stopAll();
}

bool SockServ::acceptClient(){
	int usrSock;
	unsigned int clilen;
	struct sockaddr_in cli_addr;
	clilen = sizeof(cli_addr);
	if ((usrSock = accept(sock, (struct sockaddr *) &cli_addr, &clilen)) >= 0) {
		cout << "Conexao iniciada em: " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << endl;

		int on = 1;
		fcntl(usrSock, F_SETFL, O_NONBLOCK);

		struct protoent *p;
		p = getprotobyname("tcp");
//		if (setsockopt(usrSock, p->p_proto, SO_REUSEADDR | TCP_NODELAY, &on, sizeof(on)) < 0){
//			perror("ERROR setting up socket options");
//		}
		clients.push_front(usrSock);
		return true;
	}
	return false;
}

void SockServ::stopAll(){
	for(list<int>::iterator it = clients.begin(); it != clients.end(); it++){
		stop(*it);
	}
	close(sock);
	clients.clear();
	fcntl(sock, F_SETFL, O_NONBLOCK);
}

void SockServ::stop(int socket){
	sockaddr_in addr;
	unsigned int addr_len = sizeof(addr);
	getsockname(socket, (sockaddr *) &addr, (socklen_t *) &addr_len);
	close(socket);
	fcntl(socket, F_SETFL, O_NONBLOCK);
	cout << "Conexao finalizada em: " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << endl;
}

int SockServ::receive(int socket, char buffer[]){
	int r;
	r = recv(socket, buffer, 1024, 0);
	if (r>0)
		buffer[r] = '\0';
	return r;
}

void SockServ::recvStart(){
	recvClient = clients.begin();
}

string SockServ::recvNext(int *clientId){
	char tmp[1024] = "";
	int r;
	int pos;
	string msg;
	if (recvClient != clients.end()){
		if ((r = receive(*recvClient, tmp)) > 0){
			recvbuffer += tmp;
			if (clientId != NULL)
				*clientId = *recvClient;
		}
		else if (r == 0){
			stop(*recvClient);
			recvClient = clients.erase(recvClient);
		}
		else 
			recvClient++;
	}
	pos = recvbuffer.find_first_of(';');
	if (pos != string::npos) {
		msg = recvbuffer.substr(0, pos);
		recvbuffer.erase(0, pos +1);
	}
	return msg;
}

bool SockServ::hasNext(){
	if (recvClient != clients.end())
		return true;
	else
		return false;
}

void SockServ::sends(string &msg, int client){
        char buffer;
	msg += ";\n";
	if (isActive(client))
		send(client, msg.c_str(), msg.size(), 0);
}

void SockServ::sendAll(string &s){
	for(list<int>::iterator it = clients.begin(); it != clients.end(); it++){
		sends(s,*it);
	}
}

bool SockServ::isActive(int client){
        char buffer;
	if (recv(client, &buffer, 1, MSG_PEEK) != 0)
		return true;
	return false;
}
