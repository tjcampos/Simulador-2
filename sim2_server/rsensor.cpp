#include "rsensor.h"

RSensor::RSensor(int id, int pos , int length, int width, int rot){
	this->id = id;
	setRot(rot);
	setPos(pos);
	this->length = length;
	this->width = width;
}

int RSensor::getId(){
	return id;
}

void RSensor::setRot(int rot){
		if (rot < 3600 && rot >= 0)
			this->rot = rot;
		else{
			if (rot > 0){
				rot = rot%3600;
			}
			else{
				rot = 3600 + rot%3600;
			}
			this->rot = rot;
		}
}

int RSensor::getPos(){
	return pos;
}

void RSensor::setPos(int pos){
		if (pos < 3600 && pos >= 0)
			this->pos = pos;
		else{
			if (pos > 0){
				pos = pos%3600;
			}
			else{
				pos = 3600 + pos%3600;
			}
			this->pos = pos;
		}
}

int RSensor::getRot(){
	return rot;
}

void RSensor::setLength(int length){
	this->length = length;
}

int RSensor::getLength(){
	return length;
}

void RSensor::setWidth(int width){
	this->width = width;
}

int RSensor::getWidth(){
	return width;
}

void RSensor::draw(Drawing &s){
	s.drawLine(vertices[0], vertices[1], 0xFF0000FF); //linha da esquerda
	s.drawLine(vertices[1], vertices[2], 0xFF0000FF); //linha final
	s.drawLine(vertices[2], vertices[3], 0xFF0000FF); //linha da direita
	s.drawLine(vertices[3], vertices[0], 0xFF0000FF); //linha inicial
	while(!detections.empty()){
		s.drawCircle(detections.front(), 3, 0x0000ffff);
		detections.pop_front();
	}
}

int RSensor::scan(list<Object*> &objects, Robot *r, int max, int min, int maxBufferSize){

	//calculo da posicao atual do sensor
	float xRSensor, yRSensor;
	float sensorSin, sensorCos;

	xRSensor = (r->getPos()).x + (r->getSize() * Trigtable::tcos(pos + r->getRot()));
	yRSensor = (r->getPos()).y + (r->getSize() * Trigtable::tsin(pos + r->getRot()));
	sensorSin = Trigtable::tsin(r->getRot() + rot + pos);
	sensorCos = Trigtable::tcos(r->getRot() + rot + pos);
	vertices[0].x = (int) (xRSensor + 0.5 * width * sensorSin);
	vertices[0].y = (int) (yRSensor - 0.5 * width * sensorCos);
	vertices[3].x = (int) (xRSensor - 0.5 * width * sensorSin);
	vertices[3].y = (int) (yRSensor + 0.5 * width * sensorCos);
	vertices[1].x = (int) (vertices[0].x + length * sensorCos);
	vertices[1].y = (int) (vertices[0].y + length * sensorSin);
	vertices[2].x = (int) (vertices[3].x + length * sensorCos);
	vertices[2].y = (int) (vertices[3].y + length * sensorSin);

	//se o tamanho da lista ultrapassar o tamnho maximo ela eh limpa
	if (detections.size() > maxBufferSize)
		detections.clear();

	//calculo da deteccao de objetos
	int menor = max;
        for (list<Object*>::iterator it = objects.begin(); it != objects.end(); it++){
		if (typeid(**it) == typeid(Robot) && *it != r ){
			Point2d intersect[2];
			Robot *r = (Robot*) *it;
			float dist;
			for (int i = 0; i < 4; i++){
				int nint = CheckIntersect::getIntersect(r->getPos(), r->getSize(), vertices[i], vertices[(i+1)%4], intersect);
				for (int k = 0; k < nint; k++){
					detections.push_back(intersect[k]);
					dist = (intersect[k].x - xRSensor) * (intersect[k].x - xRSensor) + (intersect[k].y - yRSensor) * (intersect[k].y - yRSensor);
					dist = dist*((max-min-1)*(max-min-1))/(length*length) + min;
					if ((int) dist < menor*menor)
						menor = (int) sqrt(dist);
				}
			}
		}
		else if (typeid(**it) == typeid(Obstacle)){
			Point2d intersect;
			Obstacle *o = (Obstacle*) *it;
			float dist;
			for (int i = 0; i < 4; i++){
				for (int j = 0; j < o->getNVertices(); j++){
					Point2d const *vert = o->getVertices();
					bool nint = CheckIntersect::getIntersect(vert[j], vert[(j+1)%o->getNVertices()], vertices[i], vertices[(i+1)%4], intersect);
					if (nint){
						detections.push_back(intersect);
						dist = (intersect.x - xRSensor) * (intersect.x - xRSensor) + (intersect.y - yRSensor) * (intersect.y - yRSensor);
						dist = dist*((max-min-1)*(max-min-1))/(length*length) + min;
						if ((int) dist < menor*menor)
							menor = (int) sqrt(dist);
					}
				}
			}
		}
	}
	return max - menor;
}
