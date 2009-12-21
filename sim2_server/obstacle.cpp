#include "obstacle.h"

Obstacle::Obstacle(int id, Uint32 color, int nvertices, Point2d *vertices, bool enable):Object(id,color,enable){
	this->nvertices = nvertices;
	this->vertices = vertices;
}

int Obstacle::getNVertices(){
	return nvertices;
}

Point2d const *Obstacle::getVertices(){
	return vertices;
}

void Obstacle::setVertices(int nvertices, Point2d *vertices){
	this->nvertices = nvertices;
	this->vertices = vertices;
}

void Obstacle::runStep(Drawing &s, int tick, list<Object*> &objects) { }

void Obstacle::draw(Drawing &s){
	s.drawPolygon(vertices, nvertices, Object::getColor());
}
