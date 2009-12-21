#define NBOTS 10
#define GEN_TIME 30000 //tempo (aprox.) de cada geracao em ms
#include <iostream>
#include <list>
#include <unistd.h>
#include <cassert>
#include <cstring>

#include "point2d.h"
#include "sim.h"
#include "ag.h"

using namespace std;

void buildWorld(Sim &s);

int main (){
	Sim s;
	Ag ag(NBOTS);
	Point2d p;
	vector<int> sensors;
	int rId[NBOTS];
	int last[NBOTS];
	int action;
	int gen = 1;

	s.setEnv();
	memset(last, -1, NBOTS*sizeof(int));
	buildWorld(s);
	ag.randomize();

	//robo zero sempre verde (melhor pela implementacao do ag)
	rId[0] = s.addRobot(500, 150, 30, 0, 0x00FF00FF);
	s.addSensor(rId[0], -45);
	s.addSensor(rId[0]);
	s.addSensor(rId[0], 45);
	for( int i = 1; i < NBOTS; i++){
		rId[i] = s.addRobot(500 +75*i, 150);
		s.addSensor(rId[i], -45);
		s.addSensor(rId[i]);
		s.addSensor(rId[i], 45);
	}

	while (1){
		while (s.getSimulationTime() < GEN_TIME){
			for( int i = 0; i < NBOTS; i++){
				sensors = s.getRobotDetections(rId[i]);
				action = ag.getAction(i, vector<int>(++(sensors.begin()), sensors.end()));

				if (action != last[i]){
					switch (action) {
						case 0:
							s.setRobotSpeed(rId[i], 50, -50);
						break;
						case 1:
							s.setRobotSpeed(rId[i], -50, 50);
						break;
						case 2:
							s.setRobotSpeed(rId[i], 50, 50);
						break;
					}
					last[i] = action;
				}
				
				if (action == 2)
					ag.updateFitness(i, 1);
				if (s.getRobotCollision(rId[i])){
					s.setRobotRot(rId[i], s.getRobotRot(rId[i]) + 1800);
					ag.updateFitness(i, -30);
				}
			}
			usleep(1);
		}
		cout << "Gerecao: " << gen++ << " ";
		ag.newPop();
		ag.resetFitness();
		s.setSimulationTime(0);
	}

	sleep(1);
	return 0;
}

void buildWorld(Sim &s){
	list<Point2d> obj;
	obj.push_back(Point2d (500,800));
	obj.push_back(Point2d (500,1200));
	obj.push_back(Point2d (800,1400));
	obj.push_back(Point2d (1000,1000));
	obj.push_back(Point2d (800,600));
	s.addObstacle(obj);
	obj.clear();
	obj.push_back(Point2d (200,400));
	obj.push_back(Point2d (200,600));
	obj.push_back(Point2d (400,400));
	s.addObstacle(obj);
	obj.clear();
	obj.push_back(Point2d (1100,1500));
	obj.push_back(Point2d (1100,2000));
	obj.push_back(Point2d (1500,2000));
	obj.push_back(Point2d (1500,1500));
	s.addObstacle(obj);
	obj.clear();
	obj.push_back(Point2d (1100,400));
	obj.push_back(Point2d (1100,800));
	obj.push_back(Point2d (1500,800));
	obj.push_back(Point2d (1500,400));
	s.addObstacle(obj);
}
