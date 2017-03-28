#include "Point.h"
#include <cmath>

Point::Point() {
	setPoint(0.00,0.00);
}

Point::Point(int x, int y) {
	setPoint(x/1.00,y/1.00);
} 	

void Point::setPoint(int x, int y) {
	this->x = x/1.00;
	this->y = y/1.00;
} 

void Point::setPoint(double x, double y) {
	this->x = x;
	this->y = y;
} 


int Point::getX() {
	return round(x);
}

int Point::getY() {
	return round(y);
}

void swap (double *a, double *b) {
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void Point::swapPoint(Point *P) {
	swap(&x, &P->x);
	swap(&y, &P->y);
}

void Point::moveBy(int DeltaX, int DeltaY){
	x += DeltaX;
	y += DeltaY;
}
void Point::moveTo(int nx, int ny){
	x = nx/1.0;
	y = ny/1.0;
}

void Point::rotatePoros(double theta, Point poros){
	double cosr = cos((22*theta)/(180*7));
	double sinr = sin((22*theta)/(180*7));
	double tempx = poros.x + ((x - poros.x) * cosr) - ((y - poros.y) * sinr);
	double tempy = poros.y + ((x - poros.x) * sinr) + ((y - poros.y) * cosr);
	x = round(tempx);
	y = round(tempy);
}

void Point::scaleBy(double ratio, Point anchor) {
	double tempx = anchor.x + ((x - anchor.x) * ratio);
	double tempy = anchor.y + ((y - anchor.y) * ratio);
	x = round(tempx);
	y = round(tempy);
}

json Point::getJSONObject() {
	json object;
	object.push_back(x);
	object.push_back(y);
	return object;
}