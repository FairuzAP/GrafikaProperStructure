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
	
	// Basic Getter Setter
	Color getColor(Point p);
	void setColor(Point p, Color C);
	void setBorder(Border newB);
	
	// Matrix drawing method
	void ClearScreen();
	void drawLine(Point start, Point end, Color c);
	void floodFill(Point fire, Color oldc, Color newc);
	void floodFillBorder(Point fire, Color borderc, Color newc);
	
	void drawShapeOutline(int index);
	
	// Shape Model Manipulation Method
	void addShape(Shape s);
	void deleteShape(int i);
	Shape& getShape(int index);
	int getShapeCount();
	
	void moveAll(int deltaX, int deltaY);
	void rotateAll(int theta, Point poros);
	void scaleAll(double x, Point poros);
	
	void toggleOutline(int i, bool b);
	void toggleFill(int i, bool b);
	void prepareLayers();

	json getJSONObject();
	
private :
	int height;
	int width;
	ColorMatrix colorMap;
	Border screenBorder;
	
	vector<Shape> shapeList;
	vector<bool> isOutline;
	vector<bool> isFill;
	
};

#endif

