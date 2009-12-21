/**
 * \file sockserv.h
 * \author Thiago Jose de Campos
 **/

#ifndef SIM_H
#define SIM_H

#include <sys/types.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <list>
#include <map>
#include <vector>

#include "point2d.h"

using namespace std;

class Sim {
	private:
		int sockfd;
		char buffer[255];
		char recvBuffer[255];
		string recvMsgs;
		int nextId;
		map<int, int> nextSensorsId;
	protected:
		int sendMsg(string s);
		string recvMsg();
	public:
		/*
		 * Conecta ao servidor especificado
		 */
		Sim (string ip = "localhost", int port = 6703);
		/*
		 * Cria o mundo, deve ser efetuado antes de qualquer outro comando
		 */
		void setEnv(int world_width = 2000, int world_height = 1500, int screen_width = 800, int screen_height = 600);

		/*
		 * Adiciona um novo robo
		 * Retorna o id
		 */
		int addRobot(int x, int y, int size = 30, int rot = 0, int color = 0x0000FFFF);
		/*
		 * Adiciona um novo obstaculo, os pontos devem ser passados em sentido horario
		 * Retorna o id
		 */
		int addObstacle(list<Point2d> p, int color = 0xFF000077);
		/* 
		 * Adiciona um novo sensor ao robo
		 * Retorna o id do sensor
		 */
		int addSensor(int rId, int pos = 0, int length = 100, int width = 50, int rot = 0);

		/*
		 * Deleta o robô ou obstaculo
		 */
		void delObject(int id);
		/*
		 * Deleta um sensor
		 */
		void delSensor(int rId, int sId);

		/*
		 * Muda a velocidade do robo
		 */
		void setRobotSpeed(int id, int re, int rd);
		/*
		 * Teletransporta o robo
		 */
		void setRobotPos(int id, Point2d p);
		/*
		 * Muda a orientacao do robo
		 */
		void setRobotRot(int id, int rot);
		/*
		 * Muda o tempo da simulacao em ms
		 */
		void setSimulationTime(int t);
		/*
		 * Acelera a simulacao
		 */
		void setSimulationFast(bool f);
		
		/*
		 * Recebe a velocidade das rodas do robo
		 */
		void getRobotSpeed(int id, int &re, int &rd);
		/*
		 * Recebe a posicao do robo
		 */
		Point2d getRobotPos(int id);
		/*
		 * Recebe a orientacao do robo
		 */
		int getRobotRot(int id);
		/*
		 * Verifica as deteccoes de cada sensor do robo
		 */
		vector<int> getRobotDetections(int id);
		/*
		 * Verifica se robo colidiu
		 */
		bool getRobotCollision(int id);
		/*
		 * Recebe o tempo da simulacao em ms
		 */
		int getSimulationTime();
};

#endif
