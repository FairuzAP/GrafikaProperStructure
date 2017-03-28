#include "Border.h"

using namespace std;

Border::Border() {
	minX = 0; maxX = 0;
	minY = 0; maxY = 0;
}
Border::Border(int _minX, int _maxX, int _minY, int _maxY) {
	minX = _minX; maxX = _maxX;
	minY = _minY; maxY = _maxY;
}

bool Border::isOverflow(Point p) {
	return !((p.x >= minX)&&(p.x <= maxX)&&(p.y >= minY)&&(p.y <= maxY));
}
int Border::getClipCode(Point p) {
	int code = 0;

	if (p.x < minX) {           // to the left of clip window 0001
		code |= 1;
	} else if (p.x > maxX) {     // to the right of clip window 0010
		code |= 2;
	} 
	
	if (p.y < minY) {          // below the clip window 0100
		code |= 4;
	} else if (p.y > maxY) {     // above the clip window 1000
		code |= 8;
	}

	return code;
}
	
json Border::getJSONObject() {
	json object;
	object["minX"] = minX;
	object["maxX"] = maxX;
	object["minY"] = minY;
	object["maxY"] = maxY;
	return object;
}
