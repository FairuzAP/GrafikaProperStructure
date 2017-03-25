#ifndef __SHAPE__
#define __SHAPE__
#include "Point.h"
#include "Color.h"
#include <vector>
#include <cmath>

using namespace std;

// Model Class to store Eclosed Polyline Data
class Shape {

public:

	// Constructor, 
	Shape();
	Shape(vector<Point>& starting_edge, Color borderc, Color fillc);
	Shape& operator=(const Shape &obj);
	Shape(const Shape &obj);
	
	// Destructor
	~Shape();
	
	void addEdge(Point p);
	
	//set floodfill color
	void setFillColor(Color C);
	//set Border Color to color c
	void setBorderColor(Color c);
	
	//Move the object by delta
	//deltaX : move the object in X axis by delta X
	//deltaY : move the object in Y axis by delta Y
	void moveBy(int deltaX, int deltaY);

	//rotate the object by theta degree clockwise with 
	//cePoint center as  center of rotation
	void Rotate(int theta, Point poros);

	void scale(double x, Point poros);

	Point floodfill_seed;
	vector<Point> edges;
	Color Border;
	Color Fill;

};

#endif                                                   

