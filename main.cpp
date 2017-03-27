#include "Screen.h"
#include "Layer.h"
#include "shape.h"

#include <unistd.h>
#include <iostream>

#include <string.h>
#include <stdio.h>
#include <thread>

using namespace std;

Screen screen;

void initCaptureKeyboard(){
	int layer, object, arg1, arg2;
	string opr;
	Shape *temp;
	while (1) {
		if (cin >> layer >> object >> opr >> arg1 >> arg2) {
			if (!opr.compare("select")){
				screen.getLayer(layer).getShape(object).move(100, 100);
			}
		}
	}
}

void startKeystrokeThread(){
	// Constructs the new thread and runs it. Does not block execution.
	thread t1(initCaptureKeyboard);

	// Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
	t1.detach();
}

int main() {
	
	// Screen initializing
	screen.ClearScreen();
	screen.addLayer();
	screen.addLayer();
	screen.setBorder(Border(0,800,0,600));
	
	// Input initializing
	startKeystrokeThread();

	// Shape1 Initializing
	Shape s;
	s.addEdge(Point(100,100)); s.addEdge(Point(100,200)); s.addEdge(Point(200,100));
	s.setFillColor(Color(255,0,0)); s.setBorderColor(Color(0,255,0)); s.setFloodFillSeed(Point(110,110));
	
	// Adding shape1 to layer 1, and prepare it for filled drawing 
	screen.getLayer(1).addShape(s);
	s.setFillColor(Color(0,255,0)); screen.getLayer(0).addShape(s);
	screen.getLayer(1).drawFilledAllShape();
	
	// Shape2 Initializing
	s.edges.clear();
	s.addEdge(Point(300,300)); s.addEdge(Point(300,100)); s.addEdge(Point(100,300));
	s.setFloodFillSeed(Point(289,289)); s.setFillColor(Color(0,0,255));
	
	// Adding shape2 to layer 0, and prepare it for filled drawing
	screen.getLayer(0).addShape(s);
	screen.getLayer(0).drawFilledAllShape();
	
	// Draw all Layer's prepared matrix
	screen.drawAll();
	usleep(1000000);
	
	// Scale all shape in layer 1, prepare for drawing, and draw it to the screen
	screen.getLayer(1).scaleAll(1.5,Point(100,100));
	screen.getLayer(1).drawFilledAllShape();
	screen.drawAll();
	usleep(1000000);
	
	// Move all shape in layer 1, prepare for drawing, and draw it to the screen
	screen.getLayer(1).moveAll(50,50);
	screen.getLayer(1).drawFilledAllShape();
	screen.drawAll();
	usleep(1000000);
	
	// Rotate all shape in layer 1, prepare for drawing, and draw it to the screen
	for(int i=1; i<255; i++) {
		screen.getLayer(1).rotateAll(45,Point(150,150));
		screen.getLayer(1).drawFilledAllShape();
		screen.getLayer(0).rotateAll(30,Point(300,300));
		screen.getLayer(0).drawFilledAllShape();
		screen.drawAll();
		usleep(50000);
	}
	return 0;
}

