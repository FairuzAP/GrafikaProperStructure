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

int main() {

  	// Screen initializing
	screen.ClearScreen();
	screen.addLayer();
	screen.addLayer();
	screen.setBorder(Border(0,1280,0,1024));

	// Shape1 Initializing
	Shape s;
	s.addEdge(Point(100,100)); s.addEdge(Point(100,200)); s.addEdge(Point(200,100));
	s.setFillColor(Color(255,0,0)); s.setBorderColor(Color(0,255,0)); s.setFloodFillSeed(Point(110,110));
	
	// Adding shape1 to layer 1, and prepare it for filled drawing 
	screen.getLayer(1).addShape(s);
	s.setFillColor(Color(0,255,0)); screen.getLayer(0).addShape(s);
	screen.getLayer(1).prepareLayers();
	
	// Shape2 Initializing
	s.edges.clear();
	s.addEdge(Point(300,300)); s.addEdge(Point(300,100)); s.addEdge(Point(100,300));
	s.setFloodFillSeed(Point(289,289)); s.setFillColor(Color(0,0,255));
	
	// Adding shape2 to layer 0, and prepare it for filled drawing
	screen.getLayer(0).addShape(s);
	screen.getLayer(0).prepareLayers();
	
	// Draw all Layer's prepared matrix
	screen.drawAll();
	
	// Scale all shape in layer 1, prepare for drawing, and draw it to the screen
	screen.getLayer(1).scaleAll(1.5,Point(100,100));
	screen.getLayer(1).prepareLayers();
	screen.drawAll();
	
	// Move all shape in layer 1, prepare for drawing, and draw it to the screen
	screen.getLayer(1).moveAll(50,50);
	screen.getLayer(1).prepareLayers();
	screen.drawAll();
	
	// Rotate all shape in layer 1, prepare for drawing, and draw it to the screen
	while (1) {
		string opr;
		int layer, destLayer, object, arg1, arg2, arg3;
		if (cin >> opr) {
			if (!opr.compare("exit")){ /* Exit the program */
				break;
			} else if (!opr.compare("adds")) { /* Add an object to a layer */
				cin >> layer;
				Shape s;
				s.addEdge(Point(100,100)); s.addEdge(Point(100,200)); s.addEdge(Point(200,100));
				s.setFillColor(Color(255,255,0)); s.setBorderColor(Color(0,255,0)); s.setFloodFillSeed(Point(110,110));
				screen.getLayer(layer).addShape(s);
			} else if (!opr.compare("deletes")){ /* Delete an object */
				cin >> layer >> object;
				screen.getLayer(layer).deleteShape(object);
			} else if (!opr.compare("selects")) { /* Select an object */
				cin >> layer >> object;
				screen.getLayer(layer).getShape(object).setFillColor(Color(1, 1, 1));
			} else if (!opr.compare(("moves"))) { /* Move an object by arg1, arg2 */
				cin >> layer >> object >> arg1 >> arg2;
				screen.getLayer(layer).getShape(object).move(arg1, arg2);
			} else if (!opr.compare("changesite")) { /* Change site */

			} else if (!opr.compare("changelayer")){ /* Change layer */
				cin >> layer >> object >> destLayer;
				screen.getLayer(destLayer).addShape(screen.getLayer(layer).getShape(object));
				screen.getLayer(layer).deleteShape(object);
			} else if (!opr.compare("savelayers")){ /* save layer */
				string filename;
				cin >> filename;
				screen.saveLayers(filename);
			}
		}
		// Draw all layers
		for (int i = 0; i < screen.getLayerCount(); i++) {
			screen.getLayer(i).prepareLayers();
		}
		screen.drawAll();
	}
	
	return 0;
}
