#ifndef __ColorMatrix__
#define __ColorMatrix__
#include <vector>
#include "Color.h"
#include "Point.h"

using namespace std;

class ColorMatrix{

public:
	ColorMatrix(int width, int height);
	ColorMatrix(const json& object);
	
	void setColor(Point p, Color c); //set semua warna
	Color getColor(Point p);

	json getJSONObject();
	
private:
	vector<Color> map;
	int maxX;
	int maxY;
	
};

#endif
