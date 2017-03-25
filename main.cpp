#include "Screen.h"
#include "Layer.h"

using namespace std;

Screen screen;
int main() {
	
	screen.ClearScreen();
	screen.addLayer();
	screen.addLayer();
	screen.setBorder(Border(100,300,100,300));
	screen.getLayer(0).drawLine(Point(0,200), Point(1000,200), Color(255,0,0));
	screen.getLayer(1).drawLine(Point(200,0), Point(200,1000), Color(0,255,0));
	screen.drawAll();

	return 0;
}

