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
	
	void setFloodFillSeed(Point p);
	void setFillColor(Color C);
	void setBorderColor(Color c);
	
	void move(int deltaX, int deltaY);
	void rotate(int theta, Point poros);
	void scale(double x, Point poros);

	json getJSONObject();


	Point floodfill_seed;
	vector<Point> edges;
	Color Border;
	Color Fill;
};

#endif                                                   

