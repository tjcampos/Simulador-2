#include "object.h"

Object::Object(int id, Uint32 color, bool enable){
	this->id = id;
	this->color = color;
	this->enable = enable;
}

void Object::setColor(Uint32 color){
	this->color = color;
}

Uint32 Object::getColor(){
	return color;
}

int Object::getId(){
	return id;
}

void Object::setEnable(bool enable){
	this->enable = enable;
}

bool Object::getEnable(){
	return enable;
}
