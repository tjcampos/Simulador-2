#include "simctrl.h"

SimCtrl::SimCtrl(bool fast, int speedMultiply, int fps){
	running = true;
	started = false;
	this->fps = fps;
	this->speedMultiply = speedMultiply;
	this->tick = speedMultiply*10000/fps;
	this->fast = fast;
	simTime = 0;
	limitFps = fps?true:false;
}

bool SimCtrl::isRunning() {
	return running;
}

bool SimCtrl::isStarted() {
	return started;
}

void SimCtrl::start() {
	started = true;
	SDL_initFramerate(&fpsm);
	SDL_setFramerate(&fpsm, fps);
}

void SimCtrl::stopSimulation(){
	running = false;
}

void SimCtrl::delay(int time){
	SDL_Delay(time);
}

bool SimCtrl::addObject(Object &o){
	if (findObject<Object>(o.getId()) == NULL){
		objects.push_back(&o);
		return true;
	}
	return false;
}

bool SimCtrl::delObject(int id){
	list<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
		if ((*it)->getId() == id){
			objects.erase(it);
			return true;
		}
	return false;

}

void SimCtrl::setFast(bool fast){
	this->fast = fast;
}

int SimCtrl::getFast(){
	return fast;
}

void SimCtrl::setSpeedMult(int sm){
	if (sm > 0){
		speedMultiply = sm;
		tick = speedMultiply*10000/fps;
		SDL_setFramerate(&fpsm, fps);
	}
}

int SimCtrl::getSpeedMult(){
	return speedMultiply;
}

void SimCtrl::setFps(int fps){
	if (fps > 0){
		this->fps = fps;
		tick = speedMultiply*10000/fps;
		SDL_setFramerate(&fpsm, fps);
	}
	limitFps = fps?true:false;
}

int SimCtrl::getFps(){
	return fps;
}

void SimCtrl::draw(Drawing &s){
	if (!fast){
		stringstream ss;
		string time;
		for (list<Object*>::iterator it = objects.begin() ; it != objects.end(); it++)
			(*it)->draw(s);
		if (limitFps)
			SDL_framerateDelay(&fpsm);
		ss << simTime/10000;
		ss >> time;
		time += " sec";
		Point2d p (10,10);
		s.drawText(time, p);
	}
}

void SimCtrl::runStep(Drawing &s){
	int tmpTick = tick;
	simTime += tmpTick;
	detections.clear();
	for (list<Object*>::iterator it = objects.begin() ; it != objects.end(); it++){
		(*it)->runStep(s,tmpTick, objects);
		if (typeid(**it) == typeid(Robot)){
			Robot *r = (Robot*) (*it);
			list<SLevel> s = r->checkSensors(objects);
			detections.splice(detections.begin(), s);
		}
	}
}

list<SLevel>* const SimCtrl::getDetections(){
	return &detections;
}

unsigned long int SimCtrl::getSimTime(){
	return simTime/10;
}

void SimCtrl::setSimTime(unsigned long int time){
	simTime = time*10;
}

list<Event> const SimCtrl::getNewEvents(){
	list<Event> evt;
	for (list<Object*>::iterator it = objects.begin() ; it != objects.end(); it++){
		if (typeid(**it) == typeid(Robot)){
			Event tmp;
			Robot *r = (Robot*) *it;
			tmp.id = r->getId();
			tmp.value = r->getNewEvents();
			if (tmp.value != 0)
				evt.push_back(tmp);
		}
	}
	return evt;
}

void SimCtrl::sendEvents(SockServ &sock){
	list<Event> const evt = getNewEvents();
	for (list<Interruption>::iterator i = interruptions.begin(); i != interruptions.end(); i++){
		for (list<Event>::const_iterator j = evt.begin(); j != evt.end(); j++){
			if (j->id == i->rid){
				string s, tmp;
				stringstream conv;
				s = "event robot id ";
				conv << i->rid;
				conv >> tmp;
				s += tmp;
				if ((j->value & 1) != 0)
					s += " sensor";
				if ((j->value & 2) != 0)
					s += " collision";
				sock.sends(s,i->socket);
			}
		}
	}
}

void SimCtrl::addInterrupt(int sock, int rId){
	Interruption i;
	i.socket = sock;
	i.rid = rId;
	interruptions.push_back(i);
}

void SimCtrl::delInterrupt(int sock, int rId){
	for (list<Interruption>::iterator i = interruptions.begin(); i != interruptions.end(); i++){
		if (i->rid == rId && i->socket == sock){
			list<Interruption>::iterator tmp = i;
			i++;
			interruptions.erase(tmp);
		}
	}
}

void SimCtrl::addTimeAlert(int sock, unsigned long int time){
	TimeInterruption t;
	t.socket = sock;
	t.time = time;
	timeir.push_back(t);
}

void SimCtrl::delTimeAlert(int sock, unsigned long int time){
	for (list<TimeInterruption>::iterator i = timeir.begin(); i != timeir.end(); i++){
		if (i->time == time && i->socket == sock){
			list<TimeInterruption>::iterator tmp = i;
			i++;
			timeir.erase(tmp);
		}
	}
}


void SimCtrl::sendTimeAlert(SockServ &sock){
	for (list<TimeInterruption>::iterator i = timeir.begin(); i != timeir.end(); i++){
		if (i->time <= this->getSimTime()){
			string s, tmp;
			stringstream conv;
			s = "timealert ";
			conv << i->time;
			conv >> tmp;
			s += tmp;
			sock.sends(s,i->socket);
			
			list<TimeInterruption>::iterator tmpi = i;
			i++;
			timeir.erase(tmpi);
		}
	}
}

void SimCtrl::restart(){
	objects.clear();
	detections.clear();
	interruptions.clear();
	timeir.clear();
	setSimTime(0);
}
