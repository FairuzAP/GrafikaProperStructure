#include "shape.h"

#define PI  3.14159265
#define EPS 0.00001

using namespace std;

Shape::Shape() : Border(0,0,0), Fill(0,0,0) {
	edges.clear();
}
Shape::Shape(vector<Point>& starting_edge, Color borderc, Color fillc) {
	edges.clear();
	edges = starting_edge;
	Border = borderc;
	Fill = fillc;
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

void Shape::setFloodFillSeed(Point p) {
	floodfill_seed = p;
}
void Shape::setFillColor(Color C) {
	Fill = C;
}
void Shape::setBorderColor(Color c) {
	Border = c;
}

void Shape::move(int deltaX, int deltaY){
	for(int i=0; i<edges.size(); i++){
		edges[i].moveBy(deltaX, deltaY);
	}
	floodfill_seed.moveBy(deltaX,deltaY);
}
void Shape::rotate(int theta, Point poros){
	for(int i=0; i<edges.size(); i++){
		edges[i].rotatePoros(theta, poros);
	}
	floodfill_seed.rotatePoros(theta, poros);
}
void Shape::scale(double x, Point poros){
	for(int i=0; i<edges.size(); i++){
		edges[i].scaleBy(x, poros);
	}
	floodfill_seed.scaleBy(x, poros);
}

json Shape::getJSONObject() {
	json object;
	object["floodfill_seed"] = floodfill_seed.getJSONObject();
	json edges_object;
	for (vector<Point>::iterator edge = edges.begin(); edge != edges.end(); ++edge) {
		edges_object.push_back(edge->getJSONObject());
	}
	object["edges"] = edges_object;
	object["Border"] = Border.getJSONObject();
	object["Fill"] = Fill.getJSONObject();
	return object;
}