#ifndef __Border__
#define __Border__
#include "Point.h"

// Model Class to store a Border Value
class Border {

public:
	Border();
	Border(int _minX, int _maxX, int _minY, int _maxX);
	
	bool isOverflow(Point p);
	int getClipCode(Point p);
	
	int minX;
	int maxX;
	int minY;
	int maxY;
};

#endif