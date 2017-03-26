#ifndef __Layer__
#define __Layer__
#include <vector>

#include "ColorMatrix.h"
#include "shape.h"
#include "Border.h"

using namespace std;

class Layer {

public :
	Layer(int width, int height); // Constructor
	Color getColor(Point p); // Mendapatkan warna yang sedang ditampilkan pada baris ke r kolom ke c
	void setColor(Point p, Color C); //set warna layar pada koordinat r,c 
	void setBorder(Border newB);
	
	void ClearScreen();
	void drawLine(Point start, Point end, Color c);
	
	void floodFill(Point fire, Color oldc, Color newc);
	void floodFillBorder(Point fire, Color borderc, Color newc);
	
	void addShape(Shape s);
	Shape& getShape(int index);
	
	void drawShapeOutline(int index);
	void drawAllShapeOutline();
	
	void fillShape(int index);
	void fillAllShape();
	
	
	int height;
	int width;
	ColorMatrix colorMap;
	Border screenBorder;
	
	vector<Shape> shapeList;
};

#endif

