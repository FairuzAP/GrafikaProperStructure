#include "shape.h"

#define PI  3.14159265
#define EPS 0.00001
using namespace std;

Shape::Shape() {
	edges.clear();
	Border = Color(0,0,0);
	Fill = Color(0,0,0);
}
Shape::Shape(vector<Point>& starting_edge, Color borderc, Color fillc) {
	edges.clear();
	edges = starting_edge;
	Border = borderc;
	Fill = fillc;
	Fill = Color(0,0,0);
}
Shape::~Shape(){
	edges.clear();
}
Shape::Shape(const Shape &obj){
	this->floodfill_seed = obj.floodfill_seed;
	this->edges = obj.edges;
	this->Border = obj.Border;
	this->Fill = obj.Fill;
}
Shape& Shape::operator=(const Shape &obj){
	this->floodfill_seed = obj.floodfill_seed;
	this->edges = obj.edges;
	this->Border=obj.Border;
	this->Fill = obj.Fill;
	return *this;
}

void Shape::addEdge(Point p) {
	edges.push_back(p);
}

void Shape::setFillColor(Color C) {
	Fill = C;
}
void Shape::setBorderColor(Color c) {
	Border = c;
}

void Shape::moveBy(int deltaX, int deltaY){
	for(int i=0; i<edges.size(); i++){
		edges[i].moveBy(deltaX, deltaY);
	}
	floodfill_seed.moveBy(deltaX,deltaY);
}
void Shape::Rotate(int theta, Point poros){
	for(int i=0; i<edges.size(); i++){
		edges[i].rotatePoros(theta, poros);

	}
	floodfill_seed.rotatePoros(theta, poros);
}
void Shape::scale(double x, Point poros){
	for(int i=0; i<edges.size();i++){
		edges[i].x *=x;
		edges[i].y *=x;
	}
}

