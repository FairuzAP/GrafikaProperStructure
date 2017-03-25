#ifndef __ColorMatrix__
#define __ColorMatrix__
#include "Color.h"

class ColorMatrix{

public:
	ColorMatrix(int maxY, int maxY);

	void setColor(int x, int y, Color c); //set semua warna
	Color getColor(int x, int y);
	
private:
	Color* map;
	int maxX;
	int maxY;
	
};

#endif