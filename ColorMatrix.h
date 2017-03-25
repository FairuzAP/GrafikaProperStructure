#ifndef __ColorMatrix__
#define __ColorMatrix__
#include <vector>
#include "Color.h"
#include "Point.h"

using namespace std;

class ColorMatrix{

public:
	ColorMatrix(int width, int height);
	
	void setColor(Point p, Color c); //set semua warna
	Color getColor(Point p);
	
private:
	vector<Color> map;
	int maxX;
	int maxY;
	
};

#endif
