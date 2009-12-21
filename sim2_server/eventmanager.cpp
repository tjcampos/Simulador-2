#include "eventmanager.h"

string EventManager::runEvent(stringstream &evt, SimCtrl &sc, int client) {
	string tmpEvt;
	string response;
	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "quit"){
			tmpEvt.clear();
			evt >> tmpEvt;
			sc.stopSimulation();
		}

		else if (tmpEvt == "restart"){
			restart(evt,sc);
		}

		if (tmpEvt == "add"){
			tmpEvt.clear();
			evt >> tmpEvt;
			if (tmpEvt == "robot")
				addRobot(evt,sc);
			else if (tmpEvt == "sensor")
				addSensor(evt,sc);
			else if (tmpEvt == "obstacle")
				addObstacle(evt,sc);
			else if (tmpEvt == "evtinterruption")
				addInterrupt(evt,sc,client);
			else if (tmpEvt == "timealert")
				addTimeAlert(evt,sc,client);
		}

		else if (tmpEvt == "del"){
			tmpEvt.clear();
			evt >> tmpEvt;
			if (tmpEvt == "robot" || tmpEvt == "obstacle" || tmpEvt == "object")
				delObject(evt,sc);
			else if (tmpEvt == "sensor")
				delSensor(evt,sc);
			else if (tmpEvt == "evtinterruption")
				delInterrupt(evt,sc,client);
			else if (tmpEvt == "timealert")
				delTimeAlert(evt,sc,client);
		}

		else if (tmpEvt == "set"){
			tmpEvt.clear();
			evt >> tmpEvt;
			if (tmpEvt == "robot")
				setRobot(evt,sc);
			else if (tmpEvt == "obstacle")
				setObstacle(evt,sc);
			else if (tmpEvt == "sensor")
				setSensor(evt,sc);
			else if (tmpEvt == "simulation")
				setSimulation(evt,sc);
		}

		else if (tmpEvt == "get"){
			tmpEvt.clear();
			evt >> tmpEvt;
			if (tmpEvt == "robot")
				response += getRobot(evt,sc);
			else if (tmpEvt == "obstacle")
				response += getObstacle(evt,sc);
			else if (tmpEvt == "detections")
				response += getDetections(evt,sc);
			else if (tmpEvt == "sensor")
				response += getSensor(evt,sc);
			else if (tmpEvt == "simulation")
				response += getSimulation(evt,sc);
		}
		else {
			evt.clear();
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	return response;
}

string EventManager::getSensor(stringstream &evt, SimCtrl &sc){
	int rid = 0, sid = 0;
	int rot = 0, length = 100, width = 50, pos = 0; 
	int ctrl = 0;
	Robot *r;
	string tmpEvt, resp = "sensor", temp;
	stringstream conv;
	
	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		//cout << tmpEvt << " = " << length << endl;
		if (ctrl == 3){
			r = sc.getObject<Robot>(rid);
			if (r->getSensor(sid, pos, length, width, rot))
				ctrl += 4;
		}

		if (tmpEvt == "rid"){
			evt >> rid;
			ctrl += 1;
			resp += " rid ";
			conv << rid;
			conv >> temp;
			resp += temp;
		}
		else if (tmpEvt == "sid"){
			evt >> sid;
			ctrl += 2;
			resp += " sid ";
			conv << sid;
			conv >> temp;
			resp += temp;
		}
		else if (ctrl >= 7 and r != NULL){
			if (tmpEvt == "rot"){
				resp += " rot ";
				conv << rot;
				conv >> temp;
				resp += temp;
				ctrl += 1;
			}
			else if (tmpEvt == "length"){
				resp += " length ";
				conv << length;
				conv >> temp;
				resp += temp;
				ctrl += 1;
			}
			else if (tmpEvt == "width"){
				resp += " width ";
				conv << width;
				conv >> temp;
				resp += temp;
				ctrl += 1;
			}
			else if (tmpEvt == "pos"){
				resp += " pos ";
				conv << pos;
				conv >> temp;
				resp += temp;
				ctrl += 1;
			}
			else{
				break;
			}
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
		conv.clear();
	}

	if (ctrl < 8) {
		return "";
	}
	else {
		return resp;
	}	
}

string EventManager::getDetections(stringstream &evt, SimCtrl &sc){
	int id = 0, opr = 0, infos = 0;
	Robot *r;
	string tmpEvt, resp = "detections id ", temp;
	stringstream conv;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
			r = sc.getObject<Robot>(id);
			conv << id;
			conv >> temp;
			resp += temp;
			opr += 1;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}

	if (opr != 1) {
		return "";
	}
	else {
		list<SLevel> const *s = sc.getDetections();
		for (list<SLevel>::const_iterator it = s->begin(); it != s->end(); it++){
			if (it->rId == id){
				resp += " sensor id ";
				conv.clear();
				conv << it->sId;
				conv >> temp;
				resp += temp;
				resp += " level ";
				conv.clear();
				conv << it->sLevel;
				conv >> temp;
				resp += temp;
			}
		}
		return resp;
	}	
}

string EventManager::getObstacle(stringstream &evt, SimCtrl &sc){
	int id = 0, opr = 0, infos = 0;
	Obstacle *o;
	string tmpEvt, resp = "obstacle id ", temp;
	stringstream conv;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
			o = sc.getObject<Obstacle>(id);
			conv << id;
			conv >> temp;
			resp += temp;
			opr += 1;
		}
		else if (opr > 0) {
			conv.clear();
			if (tmpEvt == "color"){
				conv << o->getColor();
				resp += " color ";
				conv >> temp;
				resp += temp;
			}
			else if (tmpEvt == "nvertices"){
				conv << o->getNVertices();
				resp += " nvertices ";
				conv >> temp;
				resp += temp;
			}
			else if (tmpEvt == "vertices"){
				int nvert;
				Point2d const *vert;
				nvert = o->getNVertices();
				
				vert = o->getVertices();
				for (int i=0; i < nvert; i++){
					resp += " vert ";
					conv.clear();
					conv << vert[i].x;
					conv >> temp;
					resp += temp;

					resp += " ";
					conv.clear();
					conv << vert[i].y;
					conv >> temp;
					resp += temp;
				}
			}
			else{
				break;
			}
			opr++;
		}

		tmpEvt.clear();
		evt >> tmpEvt;
		conv.clear();
	}

	if (opr < 2) {
		return "";
	}
	else {
		return resp;
	}	
}

string EventManager::getRobot(stringstream &evt, SimCtrl &sc){
	int id = 0, opr = 0, infos = 0;
	Robot *r;
	string tmpEvt, resp = "robot id ", temp;
	stringstream conv;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
			r = sc.getObject<Robot>(id);
			conv << id;
			conv >> temp;
			resp += temp;
			opr += 1;
		}
		else if (opr > 0 && r != NULL) {
			conv.clear();
			if (tmpEvt == "color"){
				conv << r->getColor();
				resp += " color ";
				conv >> temp;
				resp += temp;
			}
			else if (tmpEvt == "pos"){
				Point2d p = r->getPos();
				conv << p.x;
				resp += " pos ";
				conv >> temp;
				resp += temp;
				resp += " ";
				conv.clear();
				conv << p.y;
				conv >> temp;
				resp += temp;
			}
			else if (tmpEvt == "size"){
				conv << r->getSize();
				resp += " size ";
				conv >> temp;
				resp += temp;
			}
			else if (tmpEvt == "rot"){
				conv << r->getRot();
				resp += " rot ";
				conv >> temp;
				resp += temp;
			}
			else if (tmpEvt == "speed"){
				int vl, vr;
				r->getSpeed(vl, vr);
				conv << vl;
				resp += " speed ";
				conv >> temp;
				resp += temp;
				conv << vr;
				resp += " ";
				conv.clear();
				conv >> temp;
				resp += temp;
			}
			else if (tmpEvt == "collision"){
				if (r->getCollision())
					resp += " collision 1";
				else
					resp += " collision 0";

			}
			else{
				break;
			}
			opr++;
		}

		tmpEvt.clear();
		evt >> tmpEvt;
	}

	if (opr < 2) {
		return "";
	}
	else {
		return resp;
	}	
}

void EventManager::delObject(stringstream &evt, SimCtrl &sc){
	int id = 0;
	string tmpEvt;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (id > 0)
		sc.delObject(id);
}

void EventManager::addObstacle(stringstream &evt, SimCtrl &sc){
	string tmpEvt;
	int id = 0;
	Uint32 color = 0xFF000077;
	vector<Point2d> vertices;
	Point2d *vert, pos;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
		}
		else if (tmpEvt == "vert"){
			evt >> pos.y;
			evt >> pos.x;
			vertices.push_back(pos);
		}
		else if (tmpEvt == "color"){
			evt >> color;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	
	if (vertices.size() < 3)
		return;

	//transforma a lista em um vetor
	vert = new Point2d[vertices.size()];
	for (int i = 0; i < vertices.size(); i++)
		vert[i] = vertices[i];
	
	if (id > 0)
		sc.addObject(*(new Obstacle(id, color, vertices.size(), vert))); 
}
	
void EventManager::delSensor(stringstream &evt, SimCtrl &sc){
	int rid = 0, sid = 0;
	string tmpEvt;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "rid"){
			evt >> rid;
		}
		else if (tmpEvt == "sid"){
			evt >> sid;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (rid > 0 and sid > 0){
		Robot *r = sc.getObject<Robot>(rid);
		r->delSensor(sid);
	}
}

void EventManager::addSensor(stringstream &evt, SimCtrl &sc){
	string tmpEvt;
	int rid = 0, sid = 0;
	int rot = 0, length = 100, width = 50, pos = 0; 
	int ctrl = 0;
	
	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "rid"){
			evt >> rid;
			ctrl += 1;
		}
		else if (tmpEvt == "sid"){
			evt >> sid;
			ctrl += 2;
		}
		else if (tmpEvt == "rot"){
			evt >> rot;
		}
		else if (tmpEvt == "length"){
			evt >> length;
		}
		else if (tmpEvt == "width"){
			evt >> width;
		}
		else if (tmpEvt == "pos"){
			evt >> pos;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (ctrl == 3 && rid > 0 && sid > 0){
		Robot *r;
		r = sc.getObject<Robot>(rid);
		r->addSensor(sid, pos * 10, length, width, rot * 10);
	}
}

void EventManager::addRobot(stringstream &evt, SimCtrl &sc){
	int id = 1;
	Uint32 color = 0x0000FFFF;
	int posx = 0, posy = 0, size = 30, rot = 0, vl = 0, vr = 0;
	string tmpEvt;
	int ctrl = 0;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
			ctrl += 1;
		}
		else if (tmpEvt == "pos"){
			evt >> posy;
			evt >> posx;
			ctrl += 2;
		}
		else if (tmpEvt == "size"){
			evt >> size;
		}
		else if (tmpEvt == "rot"){
			evt >> rot;
		}
		else if (tmpEvt == "color"){
			evt >> color;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (ctrl == 3 && id > 0){
		sc.addObject(*(new Robot(id, color, posx, posy, size, rot*10)));
	}
}


void EventManager::setRobot(stringstream &evt, SimCtrl &sc){
	int id = 1;
	Uint32 color;
	int size, rot, vl, vr;
	Point2d pos, speed;
	string tmpEvt;
	int ctrl = 0;
	Robot *r = NULL;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
			ctrl += 1;
			r = sc.getObject<Robot>(id);
		}
		else if (ctrl >= 1 && r != NULL){
			if (tmpEvt == "pos"){
				evt >> pos.y;
				evt >> pos.x;
				r->setPos(pos);
			}
			else if (tmpEvt == "size"){
				evt >> size;
				r->setSize(size);
			}
			else if (tmpEvt == "rot"){
				evt >> rot;
				r->setRot(rot);
			}
			else if (tmpEvt == "color"){
				evt >> color;
				r->setColor(color);
			}
			else if (tmpEvt == "speed"){
				evt >> speed.x;
				evt >> speed.y;
				r->setSpeed(speed.x, speed.y);
			}
			else{
				break;
			}
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
}

void EventManager::setObstacle(stringstream &evt, SimCtrl &sc){
	int id = 1;
	Uint32 color;
	string tmpEvt;
	int ctrl = 0;
	Obstacle *o = NULL;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
			ctrl += 1;
			o = sc.getObject<Obstacle>(id);
		}
		else if (ctrl >= 1 && o != NULL){
			if (tmpEvt == "color"){
				evt >> color;
				o->setColor(color);
			}
			else{
				break;
			}
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
}

void EventManager::setSensor(stringstream &evt, SimCtrl &sc){
	string tmpEvt;
	int rid = 0, sid = 0;
	int rot = 0, length = 100, width = 50, pos = 0; 
	int ctrl = 0;
	Robot *r;
	
	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (ctrl == 3){
			r = sc.getObject<Robot>(rid);
			if (r->getSensor(sid, pos, length, width, rot))
				ctrl += 4;
		}

		if (tmpEvt == "rid"){
			evt >> rid;
			ctrl += 1;
		}
		else if (tmpEvt == "sid"){
			evt >> sid;
			ctrl += 2;
		}
		else if (ctrl == 7 and r != NULL){
			if (tmpEvt == "rot"){
				evt >> rot;
				r->setSensor(sid, pos, length, width, rot);
			}
			else if (tmpEvt == "length"){
				evt >> length;
				r->setSensor(sid, pos, length, width, rot);
			}
			else if (tmpEvt == "width"){
				evt >> width;
				r->setSensor(sid, pos, length, width, rot);
			}
			else if (tmpEvt == "pos"){
				evt >> pos;
				r->setSensor(sid, pos, length, width, rot);
			}
			else{
				break;
			}
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
}

string EventManager::getSimulation(stringstream &evt, SimCtrl &sc){
	int opr = 0;
	string tmpEvt, resp = "simulation", temp;
	stringstream conv;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "time"){
			conv << sc.getSimTime();
			conv >> temp;
			resp += " time ";
			resp += temp;
			opr++;
		}
		else if (tmpEvt == "fast"){
			if (sc.getFast())
				resp += " fast 1";
			else
				resp += " fast 0";
			opr++;
		}
		else if (tmpEvt == "fps"){
			resp += " fps ";
			conv << sc.getFps();
			conv >> temp;
			resp += temp;
			opr++;
		}
		else if (tmpEvt == "speedmult"){
			resp += " speedmult ";
			conv << sc.getSpeedMult();
			conv >> temp;
			resp += temp;
			opr++;
		}
		else{
			break;
		}

		tmpEvt.clear();
		evt >> tmpEvt;
		conv.clear();
	}

	if (opr < 1) {
		return "";
	}
	else {
		return resp;
	}	
}

void EventManager::setSimulation(stringstream &evt, SimCtrl &sc){
	string tmpEvt;
	stringstream conv;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "time"){
			unsigned long int time;
			evt >> time;
			sc.setSimTime(time);
		}
		else if (tmpEvt == "fast"){
			int fast;
			evt >> fast;
			if (fast)
				sc.setFast(true);
			else
				sc.setFast(false);

		}
		else if (tmpEvt == "fps"){
			int fps;
			evt >> fps;
			sc.setFps(fps);
		}
		else if (tmpEvt == "speedmult"){
			int mult;
			evt >> mult;
			sc.setSpeedMult(mult);
		}
		else{
			break;
		}

		tmpEvt.clear();
		evt >> tmpEvt;
	}
}

void EventManager::addInterrupt(stringstream &evt, SimCtrl &sc, int client){
	int id = 1;
	string tmpEvt;
	int ctrl = 0;

	if (client == 0)
		return;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
			ctrl += 1;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (ctrl > 0){
		sc.addInterrupt(client, id);
	}
}

void EventManager::delInterrupt(stringstream &evt, SimCtrl &sc, int client){
	int id = 0;
	string tmpEvt;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "id"){
			evt >> id;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (id > 0)
		sc.delInterrupt(client, id);
}

void EventManager::addTimeAlert(stringstream &evt, SimCtrl &sc, int client){
	int time = 0;
	string tmpEvt;
	int ctrl = 0;

	if (client == 0)
		return;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "time"){
			evt >> time;
			ctrl += 1;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (ctrl > 0){
		sc.addTimeAlert(client, time);
	}
}

void EventManager::delTimeAlert(stringstream &evt, SimCtrl &sc, int client){
	int time = 0;
	string tmpEvt;
	int ctrl = 0;

	if (client == 0)
		return;

	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "time"){
			evt >> time;
			ctrl += 1;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (ctrl > 0){
		sc.delTimeAlert(client, time);
	}
}

void EventManager::restart(stringstream &evt, SimCtrl &sc){
	int id = 0;
	string tmpEvt;
	
	sc.restart();
}

Drawing* EventManager::startSim(stringstream &evt, SimCtrl &sc){
	string tmpEvt;
	int ww, wh, sw, sh;
	int ctrl = 0;

	evt >> tmpEvt;
	if (tmpEvt != "start")
		return NULL;

	tmpEvt.clear();
	evt >> tmpEvt;
	while (tmpEvt.size() != 0){
		if (tmpEvt == "worlddim"){
			evt >> ww;
			evt >> wh;

			ctrl += 1;
		}
		else if (tmpEvt == "screendim"){
			evt >> sw;
			evt >> sh;

			ctrl += 2;
		}
		else{
			break;
		}
		tmpEvt.clear();
		evt >> tmpEvt;
	}
	if (ctrl == 3){
		Drawing *s = new Drawing(ww, wh, sw, sh);
		sc.start();
		return s;
	}
}
