/**
 * \file eventmanager.h
 * \author Thiago Jose de Campos - PIBITI
 **/
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "simctrl.h"
#include "robot.h"
#include "point2d.h"

using namespace std;

/**
 * Classe que trata as mensagens recebidas pelo simulador, decodificando-as e executando a operacao desejada
 */
class EventManager {
	protected:
		/**
		 * Remove todos os objetos, interrupcoes e interrupções e configura o tempo para zero
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void restart(stringstream &evt, SimCtrl &sc);
		/**
		 * Adiciona um robo na simulacao
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void addRobot(stringstream &evt, SimCtrl &sc);
		/**
		 * Adiciona um sensor a um robo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void addSensor(stringstream &evt, SimCtrl &sc);
		/**
		 * Adiciona um obstaculo na simulacao
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void addObstacle(stringstream &evt, SimCtrl &sc);
		/**
		 * Adiciona o cliente na lista de interrupcoes de um robo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \param client cliente que enviou a mensagem
		 */
		static void addInterrupt(stringstream &evt, SimCtrl &sc, int client);
		/**
		 * Aciona um alerta quando o tempo especificado chegar
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \param client cliente que enviou a mensagem
		 */
		static void addTimeAlert(stringstream &evt, SimCtrl &sc, int client);
		/**
		 * Exclui um objeto da simulacao, pode ser um robo, obstaculo ou demais objetos
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void delObject(stringstream &evt, SimCtrl &sc);
		/**
		 * Exclui um sensor de um robo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void delSensor(stringstream &evt, SimCtrl &sc);
		/**
		 * Exclui um cliente da lista de avisos de um robo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \param client cliente que enviou a mensagem
		 */
		static void delInterrupt(stringstream &evt, SimCtrl &sc, int client);
		/**
		 * Exclui um alerta de tempo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \param client cliente que enviou a mensagem
		 */
		static void delTimeAlert(stringstream &evt, SimCtrl &sc, int client);
		/**
		 * Checa parametros de um robo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \return string a ser enviada pelo socket
		 */
		static string getRobot(stringstream &evt, SimCtrl &sc);
		/**
		 * Checa parametros de um obstaculo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \return string a ser enviada pelo socket
		 */
		static string getObstacle(stringstream &evt, SimCtrl &sc);
		/**
		 * Recebe a lista de deteccoes efetuada pelo simulador no frame atual
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \return string a ser enviada pelo socket
		 */
		static string getDetections(stringstream &evt, SimCtrl &sc);
		/**
		 * Recebe informacoes de um sensor
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \return string a ser enviada pelo socket
		 */
		static string getSensor(stringstream &evt, SimCtrl &sc);
		/**
		 * Recebe informacoes da simulacao
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 * \return string a ser enviada pelo socket
		 */
		static string getSimulation(stringstream &evt, SimCtrl &sc);
		/**
		 * Altera configuracoes de um robo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void setRobot(stringstream &evt, SimCtrl &sc);
		/**
		 * Altera especificacoes de um obstaculo
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void setObstacle(stringstream &evt, SimCtrl &sc);
		/**
		 * Altera especificacoes de um sensor
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void setSensor(stringstream &evt, SimCtrl &sc);
		/**
		 * Altera configuracoes globais da simulacao
		 * \param evt mensagem recebida pelo simulador
		 * \param sc controlador de simulacao, onde serao aplicados os comandos desejados
		 */
		static void setSimulation(stringstream &evt, SimCtrl &sc);

	public:
		/**
		 * interpreta a string evt e executa a operacao desejada em sc
		 * \param evt mensagem decodificada do evento
		 * \param sc controle da simulacao, para efetuar as acoes desejadas
		 * \param client cliente que enviou a mensagem
		 */
		static string runEvent(stringstream &evt, SimCtrl &sc, int client = 0);
		/**
		 * comando que inicializa o simulador, apos receber um stringstream
		 * \param evt mensagem decodificada do evento
		 * \param sc controle da simulacao, para efetuar as acoes desejadas
		 */
		static Drawing* startSim(stringstream &evt, SimCtrl &sc);
};
#endif
