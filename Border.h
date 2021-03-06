#ifndef __Border__
#define __Border__
#include "Point.h"

// Model Class to store a Border Value
class Border {

public:
	Border();
	Border(int _minX, int _maxX, int _minY, int _maxY);
	Border(const json& object);
	
	bool isOverflow(Point p);
	int getClipCode(Point p);
	
	json getJSONObject();
	
	int minX;
	int maxX;
	int minY;
	int maxY;
};

#endif
