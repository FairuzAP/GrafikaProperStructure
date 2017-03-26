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

