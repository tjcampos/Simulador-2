/**
 * \file sockserv.h
 * \author Thiago Jose de Campos - PIBITI
 **/

#ifndef SOCKSERV_H
#define SOCKSERV_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <netdb.h>
#include <netinet/tcp.h>
#include <list>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <strings.h>
#include <string>

using namespace std;

/**
 * Classe que gerencia os sockets conectados ao servidor
 */
class SockServ{
	private:
		int sock;
		list<int> clients;
		struct sockaddr_in serv_addr;
		list<int>::iterator recvClient;
		string recvbuffer;
	protected:
		/**
		 * Fecha um socket
		 * \param socket a ser finalizado
		 */
		void stop(int socket);
		/**
		 * Recebe dados de um socket
		 * \param socket cliente que recebera a mensagem
		 * \param msg mensagem a ser enviada
		 * \return numero de caracteres recebidos
		 */
		int receive(int socket, char msg[]);
		/**
		 * Verifica se um socket esta ativo
		 * \param client cliente a ser verificado
		 * \return true em caso do socket estiver ativo e false caso contrario
		 */
		bool isActive(int client);
	public:
		/**
		 * Construtor da classe SockServ
		 * \param port porta a ser utilizada pelo servidor
		 */
		SockServ(unsigned short port = 6703);
		/**
		 * Destrutor da classe SockServ
		 */
		~SockServ();
		/**
		 * Checa a porta padrao por novos clientes
		 * \return true em caso de novo cliente conectado ou false caso contrario
		 */
		bool acceptClient();
		/**
		 * Disconecta todos os clientes e finaliza a porta padrao
		 */
		void stopAll();
		/**
		 * Configura a lista de recebimentos para o primeiro cliente
		 */
		void recvStart();
		/**
		 * Recebe os dados do proximo cliente
		 * \param clientId parametro de saida, socket que enviou a mensagem atual
		 * \return mensagem recebida
		 */
		string recvNext(int *clientId = NULL);
		/**
		 * Verifica se ha mais sockets a serem verificados
		 * \return true em caso de mais clientes ou false se alista de clientes chegou ao fim
		 */
		bool hasNext();
		/**
		 * Envia uma mensagem ao cliente desejado
		 * \param msg mensagem a ser enviada pelo socket
		 * \param client cliente a ser enviada a mensagem
		 */ 
		void sends(string &msg, int client);
		/**
		 * Envia uma mensagem para todos os clientes
		 * \param s mensagem a ser enviada
		 */
		void sendAll(string &s);
};

#endif
