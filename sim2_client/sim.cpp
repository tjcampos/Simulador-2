#include <iostream>
#include <cstdio>
#include <cstring>

#include "sim.h"

Sim::Sim (string ip, int port){
	struct hostent *server = NULL;
	struct sockaddr_in serv_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) perror("Erro ao criar socket");

	server = gethostbyname(ip.c_str());
	if (!server) perror("Erro ao resolver o host");

	memset(&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	if (inet_aton(server->h_addr, (in_addr*) &(serv_addr.sin_addr.s_addr))) perror("Erro ao resolver o host");
	serv_addr.sin_port = htons(port);

	if (connect(sockfd,(sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) perror("Erro ao conectar ao servidor");
	cout << "Conectado a" << ip << ":" << port << endl;

//	setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));
	nextId =1;
}

void Sim::setEnv(int world_width, int world_height, int screen_width, int screen_height){
	list<Point2d> l;
	sprintf(buffer, "start worlddim %d %d screendim %d %d", world_width, world_height, screen_width, screen_height);
	if (sendMsg(buffer) == -1) perror("Erro ao enviar mensagem para criacao do ambiente");
	l.push_back(Point2d(0,0));
	l.push_back(Point2d(0,world_width));
	l.push_back(Point2d(world_height,world_width));
	l.push_back(Point2d(world_height,0));
	this->addObstacle(l, 0x00000000);
}

int Sim::sendMsg(string s){
	s += ";";
	return send(sockfd, s.c_str(), s.size(), 0);
}

string Sim::recvMsg(){
	int size;
	string s;

	size = recv(sockfd, recvBuffer, 255, 0);
	if (size > -1)
		recvBuffer[size] = 0;
	recvMsgs += recvBuffer;
	
	size = recvMsgs.find(';', 0) +1;
	s = recvMsgs.substr(0, size);
	recvMsgs.erase(0, size);
	return s;
}

int Sim::addRobot(int x, int y, int size, int rot, int color){
	sprintf(buffer, "add robot id %d pos %d %d size %d rot %d color %d", nextId, x, y, size, rot, color);
	sendMsg(buffer);
	nextSensorsId[nextId] = 1;
	return nextId++;
}

int Sim::addObstacle(list<Point2d> p, int color){
	string msg;

	sprintf(buffer, "add obstacle id %d", nextId);
	msg += buffer;

	for(list<Point2d>::iterator it = p.begin(); it != p.end(); it++){
		sprintf(buffer, " vert %d %d", (*it).x, (*it).y);
		msg += buffer;
	}

	sprintf(buffer, " color %d", color);
	msg += buffer;
	sendMsg(msg);

	return nextId++;
}

void Sim::delObject(int id){
	sprintf(buffer, "del object id %d", id);
	sendMsg(buffer);
}

int Sim::addSensor(int rId, int pos, int length, int width, int rot){
	sprintf(buffer, "add sensor rid %d sid %d pos %d length %d width %d rot %d", rId, nextSensorsId[rId], pos, length, width, rot);
	sendMsg(buffer);
	return nextSensorsId[rId]++;
}

void Sim::delSensor(int rId, int sId){
	sprintf(buffer, "del sensor rid %d sid %d", rId, sId);
	sendMsg(buffer);
}

void Sim::setRobotSpeed(int id, int re, int rd){
	sprintf(buffer, "set robot id %d speed %d %d", id, re, rd);
	sendMsg(buffer);
}

void Sim::setRobotPos(int id, Point2d pos){
	sprintf(buffer, "set robot id %d pos %d %d", id, pos.x, pos.y);
	sendMsg(buffer);
}

void Sim::setRobotRot(int id, int rot){
	sprintf(buffer, "set robot id %d rot %d", id, rot);
	sendMsg(buffer);
}

void Sim::setSimulationTime(int t){
	sprintf(buffer, "set simulation time %d", t);
	sendMsg(buffer);
}

void Sim::setSimulationFast(bool f){
	sprintf(buffer, "set simulation fast %d", f);
	sendMsg(buffer);
}

void Sim::getRobotSpeed(int id, int &re, int &rd){
	string resp;
	int pos = -1;

	sprintf(buffer, "get robot id %d speed", id);
	sendMsg(buffer);
	resp = recvMsg();
	for (int i=0; i < 4; i++)
		pos = resp.find(' ', ++pos);
	++pos;

	re = atoi(resp.substr(pos, resp.find(' ', pos) -pos).c_str());
	pos = resp.find(' ', pos) +1;
	rd = atoi(resp.substr(pos, resp.find(';', pos) -pos).c_str());
}

Point2d Sim::getRobotPos(int id){
	string resp;
	int pos = -1;
	Point2d p;

	sprintf(buffer, "get robot id %d pos", id);
	sendMsg(buffer);
	resp = recvMsg();
	for (int i=0; i < 4; i++)
		pos = resp.find(' ', ++pos);
	++pos;

	p.x = atoi(resp.substr(pos, resp.find(' ', pos) -pos).c_str());
	pos = resp.find(' ', pos) +1;
	p.y = atoi(resp.substr(pos, resp.find(';', pos) -pos).c_str());

	return p;
}

int Sim::getRobotRot(int id){
	string resp;
	int pos = -1;
	int rot;

	sprintf(buffer, "get robot id %d rot", id);
	sendMsg(buffer);
	resp = recvMsg();
	for (int i=0; i < 4; i++)
		pos = resp.find(' ', ++pos);
	++pos;

	rot = atoi(resp.substr(pos, resp.find(';', pos) -pos).c_str());

	return rot;
}

vector<int> Sim::getRobotDetections(int id){
	static vector<int> s(nextSensorsId[id], 0);

	int sId, level;
	int pos = -1;
	string resp;

	sprintf(buffer, "get detections id %d", id);
	sendMsg(buffer);
	resp = recvMsg();

	for (vector<int>::iterator it = s.begin(); it != s.end(); it++){
		*it = 0;
	}
	
	for (int i=0; i < 5; i++)
		pos = resp.find(' ', pos +1);
	++pos;
	
	while (pos != 0){	
		sId = atoi(resp.substr(pos, resp.find(' ', pos) -pos).c_str());
		pos = resp.find(' ', pos);
		pos = resp.find(' ', pos +1) +1;
		level = atoi(resp.substr(pos, resp.find(' ', pos) -pos).c_str());
		pos = resp.find(' ', pos) +1;
		if (pos != 0) pos = resp.find(' ', pos +1) +1;
		if (pos != 0) pos = resp.find(' ', pos +1) +1;
		s[sId] = level;
	}
	
	return s;
}

bool Sim::getRobotCollision(int id){
	string resp;
	int pos = -1;
	int col;

	sprintf(buffer, "get robot id %d collision", id);
	sendMsg(buffer);
	resp = recvMsg();

	for (int i=0; i < 4; i++)
		pos = resp.find(' ', ++pos);
	++pos;

	col = atoi(resp.substr(pos, resp.find(';', pos) -pos).c_str());

	return col;
}

int Sim::getSimulationTime(){
	string resp;
	int pos = -1;
	int time;

	sprintf(buffer, "get simulation time");
	sendMsg(buffer);
	resp = recvMsg();

	for (int i=0; i < 2; i++)
		pos = resp.find(' ', ++pos);
	++pos;

	time = atoi(resp.substr(pos, resp.find(';', pos) -pos).c_str());

	return time;
}

