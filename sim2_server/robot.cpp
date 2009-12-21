#include "robot.h"

Robot::Robot(int id, Uint32 color, int posx, int posy, int size, int rot, int vl, int vr, bool enable):Object(id,color,enable){
	pos.x = posx*1000;
	pos.y = posy*1000;
	this->setSpeed(vl,vr);
	this->size = size;
	setRot(rot);
	newEvent = 0;
	lastCollision = false;
}

void Robot::setPos(Point2d pos){
	Robot::pos = pos*1000;
}

Point2d Robot::getPos(){
	return pos/1000;
}

void Robot::setSize(int size){
	this->size = size;
}

int Robot::getSize(){
	return size;
}

void Robot::setSpeed(int vl, int vr){
	this->vl = vl;
	this->vr = vr;
}

void Robot::getSpeed(int &vl, int &vr){
	vl = this->vl;
	vr = this->vr;
}

void Robot::setRot(int rot){
	rot *= 100;
	if (rot < 360000 && rot >= 0)
		this->rot = rot;
	else{
		if (rot > 0){
			rot = rot%360000;
		}
		else{
			rot = 360000 + rot%360000;
		}
		this->rot = rot;
	}
}

void Robot::setFineRot(int rot){
	if (rot < 360000 && rot >= 0)
		this->rot = rot;
	else{
		if (rot > 0){
			rot = rot%360000;
		}
		else{
			rot = 360000 + rot%360000;
		}
		this->rot = rot;
	}
}

int Robot::getRot(){
	return rot/100;
}

void Robot::draw(Drawing &s){
	s.drawCircle(pos/1000,size,getColor());
	Point2d tmp;
	tmp.x = (int) (Trigtable::tcos(rot/100)*size);
	tmp.y = (int) (Trigtable::tsin(rot/100)*size);
	tmp += pos/1000;
	s.drawLine(pos/1000,tmp,getColor() ^ 0xFFFFFF77);
	drawSensor(s);
}

void Robot::runStep(Drawing &s, int tick, list<Object*> &objects){
	float vCenter;
	Point2d npos = pos;
	if ((vl - vr) == 0){ 
		vCenter = vl;
	}
	else {
		vCenter = (vl + vr) / 2.0;
		float teta = 2.864788975654116044 * tick * ((float) (vl - vr) / size);
		setFineRot((int) (rot + teta));
	}
	npos.x += (int) (0.1 * Trigtable::tcos(rot/100) * vCenter * tick);
	npos.y += (int) (0.1 * Trigtable::tsin(rot/100) * vCenter * tick);
	if (isValidPosition(objects.begin(), objects.end(), npos/1000, size)){
		pos = npos;
		collision = false;
	}
	else
		collision = true;
	if (collision != lastCollision)
		newEvent |= 2;
	lastCollision = collision;
}

bool Robot::addSensor(int id, int pos , int length, int width, int rot){
	if (findSensor(id) == sensors.end()){
		sensors.push_back(*(new RSensor(id,pos,length,width,rot)));
		return true;
	}
	return false;
}

void Robot::drawSensor(Drawing &s){
	for ( list<RSensor>::iterator it = sensors.begin() ; it != sensors.end(); it++ )
		(*it).draw(s);
}

list<RSensor>::iterator Robot::findSensor(int id){
	list<RSensor>::iterator it;
	for ( it = sensors.begin() ; it != sensors.end(); it++ )
		if (it->getId() == id)
			return it;
	return it;
}

bool Robot::delSensor(int id){
	list<RSensor>::iterator it = findSensor(id);
	if (it != sensors.end()){
		sensors.erase(it);
		return true;
	}
	return false;
}

bool Robot::getSensor(int id, int &pos , int &length, int &width, int &rot){
	list<RSensor>::iterator it = findSensor(id);
	if (it != sensors.end()){
		pos = it->getPos();
		length = it->getLength();
		width = it->getWidth();
		rot = it->getRot();
		return true;
	}
	return false;
}

bool Robot::setSensor(int id, int pos , int length, int width, int rot){
	list<RSensor>::iterator it = findSensor(id);
	if (it != sensors.end()){
		it->setPos(pos);
		it->setLength(length);
		it->setWidth(width);
		it->setRot(rot);
		return true;
	}
	return false;
}

bool Robot::isValidPosition(list<Object*>::iterator begin, list<Object*>::iterator end, Point2d pos, int size){
	for (list<Object*>::iterator it = begin; it != end; it++){
		if (typeid(**it) == typeid(Robot) && (*it != this)){
			Robot *r = (Robot*) *it;
			int sizex = (pos.x - (r->getPos()).x);
			int sizey = (pos.y - (r->getPos()).y);
			if (sizex*sizex + sizey*sizey <= (size + r->getSize())*(size + r->getSize()))
				return false;
		}
		else if (typeid(**it) == typeid(Obstacle)){
			Obstacle *o = (Obstacle*) *it;
			Point2d trash[2];
			Point2d const *vertices;
			for (int i = 0; i < o->getNVertices(); i++){
				vertices = o->getVertices();
				if (CheckIntersect::getIntersect(pos, size, vertices[i], vertices[(i+1)%o->getNVertices()], trash))
					return false;
			}
		}
	}
	return true;
}

list<SLevel> const Robot::checkSensors(list<Object*> &objects, int max, int min){
	list<SLevel> detections;
	int svalue;
	list<SLevel>::iterator last = lastDetections.begin();
	for (list<RSensor>::iterator it = sensors.begin();  it != sensors.end(); it++){
		if ((svalue = it->scan(objects, this, max, min)) != min){
			SLevel s;
			s.rId = this->getId();
			s.sId = it->getId();
			s.sLevel = svalue;
			detections.push_back(s);
			if ((s.sId != last->sId) || (s.sLevel != last->sLevel))
				newEvent |= 1;
			last++;
		}
	}
	lastDetections = detections;
	return lastDetections;
}

bool Robot::getCollision(){
	lastCollision = collision;
	return collision;
}

int Robot::getNewEvents(){
	int tmp = newEvent;
	newEvent = 0;
	return tmp;
}

void Robot::clearEvents(){
	newEvent = 0;
}

