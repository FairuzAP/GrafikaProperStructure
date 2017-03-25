#include "Layer.h"

#include <iostream>
using namespace std;

Layer::Layer(int _width, int _height) : colorMap(_width, _height) {
	//shapeList.clear();
	width = _width;
	height = _height;
	screenBorder.minX = 0;
	screenBorder.maxX = width-1;
	screenBorder.minY = 0;
	screenBorder.maxY = height-1;
}

Color Layer::getColor(Point p) {
	if(p.y < 0 || p.y > height || p.x < 0 || p.x > width)
		return Color(0,0,0);
		
	return colorMap.getColor(p);
}

void Layer::setColor(Point p, Color color) {
	if(p.y < 0 || p.y > height || p.x < 0 || p.x > width)
		return;
	
	colorMap.setColor(p, color);
}

void Layer::setBorder(Border newB) {
	screenBorder = newB;
}

void Layer::ClearScreen() {
	for (int r=0;r<height;r++) {
		for (int c=0;c<width;c++) {
			setColor(Point(c,r),Color(0,0,0));
		}
	}
}


void Layer::drawLine(Point start, Point end, Color c) {
	
	cout << "Drawing from " << start.x << "," << start.y << " to " << end.x << "," << end.y << endl;
	
	int x1 = start.x, y1 = start.y;
	int x2 = end.x, y2 = end.y;
	int xmin = screenBorder.minY, xmax = screenBorder.maxY;
	int ymin = screenBorder.minX, ymax = screenBorder.maxX;
	int x, y;

	int code1 = screenBorder.getClipCode(start);
	int code2 = screenBorder.getClipCode(end);

	int accept = 0;
	int valid = 1;

	if(screenBorder.isOverflow(start) || screenBorder.isOverflow(end)) {
		while(1) {
			if (!(code1 | code2)) { // Kedua endpoint di dalam batas, keluar loop & print
				accept = 1;
				break;
			} else if (code1 & code2) { // Kedua endpoint di region yang sama diluar batas
				break;
			} else {

				//Salah satu endpoint ada di luar batas
				int code = code1 ? code1 : code2;

				//Cara perpotongan menggunakan persamaan garis
				if (code & 8) {           // endpoint di atas area clip
					x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
					y = ymax;
				} else if (code & 4) { // endpoint di bawah area clip
					x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
					y = ymin;
				} else if (code & 2) {  // endpoint di sebelah kanan area clip
					y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
					x = xmax;
				} else if (code & 1) {   // endpoint di sebelah kiri area clip
					y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
					x = xmin;
				}

				//Pindahkan point yang ada di luar area ke dalam
				if (code == code1) {
					start.x = x;
					start.y = y;
					code1 = screenBorder.getClipCode(start);
				} else {
					end.x = x;
					end.y = y;
					code2 = screenBorder.getClipCode(end);
				}
			}
		}

		if(accept) {
			return drawLine(start, end, c);
		}
	}

	
	int col = 0;
	
	// Coord. of the next point to be displayed
	x = start.x;
	y = start.y;

	// Calculate initial error factor
	int dx = abs(end.x - start.x);
	int dy = abs(end.y - start.y);
	int p = 0;

	// If the absolute gradien is less than 1
	if(dx >= dy) {

		// Memastikan x1 < x2
		if(start.x > end.x) {
			start.x = end.x;
			start.y = end.y;
			end.x = x;
			end.y = y;
			x = start.x;
			y = start.y;
		}

		// Repeat printing the next pixel until the line is painted
		while (x <= end.x) {

			// Draw the next pixel
			setColor(Point(x,y),c);

			// Calculate the next pixel
			if(p < 0) {
				p = p + 2*dy;
			} else {
				p = p + 2*(dy-dx);
				if (end.y - start.y > 0) {
					++y;
				} else {
					--y;
				}
			}
			++x;
		}

	// If the absolute gradien is more than 1
	} else {

		// Memastikan y1 < y2
		if(start.y > end.y) {
			start.x = end.x;
			start.y = end.y;
			end.x = x;
			end.y = y;
			x = start.x;
			y = start.y;
		}

		// Repeat printing the next pixel until the line is painted
		while(y <= end.y) {

			// Draw the next pixel
		setColor( Point(x,y),c);

			// Calculate the next pixel
			if(p < 0) {
				p = p + 2*dx;
			} else {
				p = p + 2*(dx-dy);
				if (end.x - start.x > 0) {
					++x;
				} else {
					--x;
				}
			}
			++y;
		}
	}
	
}

void Layer::floodFill(Point fire, Color oldc, Color newc) {
	if((!screenBorder.isOverflow(fire)) ) {
		if(oldc.isSame(getColor(fire))) {
			
			setColor(fire, newc);				
			floodFillBorder(Point(fire.x,(fire.y+1)),oldc,newc);
			floodFillBorder(Point(fire.x,(fire.y-1)),oldc,newc);
			floodFillBorder(Point((fire.x+1),fire.y),oldc,newc);
			floodFillBorder(Point((fire.x-1),fire.y),oldc,newc);
				
		}
	}
}
void Layer::floodFillBorder(Point fire, Color borderc, Color newc) {
	if((!screenBorder.isOverflow(fire)) ) {
		if(!borderc.isSame(getColor(fire))) {
			if(!borderc.isSame(getColor(fire))) {
				
				setColor(fire, newc);				
				floodFillBorder(Point(fire.x,(fire.y+1)),borderc,newc);
				floodFillBorder(Point(fire.x,(fire.y-1)),borderc,newc);
				floodFillBorder(Point((fire.x+1),fire.y),borderc,newc);
				floodFillBorder(Point((fire.x-1),fire.y),borderc,newc);
				
			}
		}
	}
}

//void Layer::addShape(shape s) {}
//shape& Layer::getShape(int index) {}

//void Layer::drawAllShape() {}
