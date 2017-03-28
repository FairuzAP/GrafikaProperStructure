#ifndef __Point__
#define __Point__

#include "json.hpp"
using json = nlohmann::json;

// Model Class to store 2 Dimentional Coordinates
class Point{

public:
	Point();					//constructor
	Point(int x, int y); 		//constructor with initial x and y

	void setPoint(int x, int y); //set x and y
	void setPoint(double x, double y); //set x and y , used for rotation
	int getX();
	int getY();
	
	void swapPoint(Point *P);
	void moveBy(int DetalX, int DeltaY);
	void moveTo(int x, int y);
	
	void rotatePoros(double theta, Point poros);
	void scaleBy(double ratio, Point anchor);

	json getJSONObject();

	double x;
	double y;
};

#endif

