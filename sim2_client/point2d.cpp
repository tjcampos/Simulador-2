#include "point2d.h"

Point2d::Point2d(int x, int y){
	this->x = x;
	this->y = y;
}

Point2d &Point2d::operator= (const Point2d &p){
	if (this == &p)      
		return *this;
	this->x = p.x;
	this->y = p.y;
	return *this;
}

Point2d &Point2d::operator+= (const Point2d &p){
	this->x += p.x;
	this->y += p.y;
	return *this;
}

const Point2d Point2d::operator+ (const Point2d &p) const{
	Point2d result = *this;
	result += p;
	return result;
}

Point2d &Point2d::operator*= (const int &p){
	this->x *= p;
	this->y *= p;
	return *this;
}

const Point2d Point2d::operator* (const int &p) const{
	Point2d result = *this;
	result *= p;
	return result;
}

Point2d &Point2d::operator/= (const int &p){
	this->x /= p;
	this->y /= p;
	return *this;
}

const Point2d Point2d::operator/ (const int &p) const{
	Point2d result = *this;
	result /= p;
	return result;
}
