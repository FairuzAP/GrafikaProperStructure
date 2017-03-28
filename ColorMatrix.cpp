#include "ColorMatrix.h"
#include <iostream>

using namespace std;

ColorMatrix::ColorMatrix(int width, int height) {
	for(int i=0; i<width*height; i++) {
		map.push_back(Color());
	}
	maxX = width;
	maxY = height;
}

void ColorMatrix::setColor(Point p, Color c) {
	map.at(p.x+p.y*maxX).setColor(c.getRed(), c.getGreen(), c.getBlue());
}

Color ColorMatrix::getColor(Point p) {
	return map.at(p.x+p.y*maxX);
}

json ColorMatrix::getJSONObject() {
	json object;

	json map_object;
	for (vector<Color>::iterator it = map.begin(); it != map.end(); ++it) {
		map_object.push_back(it->getJSONObject());
	}
	object["map"] = map_object;
	
	object["maxX"] = maxX;
	object["maxY"] = maxY;

	return object;
}