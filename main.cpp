#include "Screen.h"
#include "Layer.h"
#include "shape.h"
#include <unistd.h>


using namespace std;

Screen screen;
int main() {
	
	Shape s;
	s.addEdge(Point(100,100));
	s.addEdge(Point(100,200));
	s.addEdge(Point(200,100));
	s.setFillColor(Color(255,0,0));
	s.setBorderColor(Color(0,255,0));
	s.setFloodFillSeed(Point(101,101));
	
	screen.ClearScreen();
	screen.addLayer();
	screen.addLayer();
	screen.setBorder(Border(99,301,99,301));
	
	screen.getLayer(1).addShape(s);
	screen.getLayer(1).drawAllShapeOutline();
	screen.getLayer(1).fillAllShape();
	s.edges.clear();
	s.addEdge(Point(300,300));
	s.addEdge(Point(300,100));
	s.addEdge(Point(100,300));
	s.setFloodFillSeed(Point(289,289));
	s.setFillColor(Color(0,0,255));
	screen.getLayer(0).addShape(s);
	screen.getLayer(0).drawAllShapeOutline();
	screen.getLayer(0).fillAllShape();
	screen.drawAll();
	usleep(1000000);
	
	screen.getLayer(1).getShape(0).scale(1.5,Point(100,100));
	screen.getLayer(1).drawAllShapeOutline();
	screen.getLayer(1).fillAllShape();
	screen.drawAll();
	usleep(1000000);
	
	screen.getLayer(1).getShape(0).moveBy(50,50);
	screen.getLayer(1).drawAllShapeOutline();
	screen.getLayer(1).fillAllShape();
	screen.drawAll();
	usleep(1000000);
	
	screen.getLayer(1).getShape(0).Rotate(90,Point(150,150));
	screen.getLayer(1).drawAllShapeOutline();
	screen.getLayer(1).fillAllShape();
	screen.drawAll();
	
	return 0;
}

