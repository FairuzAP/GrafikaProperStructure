#include "Screen.h"

Screen::Screen(){
	fb_fd = open("/dev/fb0",O_RDWR);

	//Get variable screen information
	ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);
	ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo);
	
	//set grayscale into color mode and set bits per pixel
	vinfo.grayscale=0;
	vinfo.bits_per_pixel=32;
	ioctl(fb_fd, FBIOPUT_VSCREENINFO, &vinfo);

	//setting up the buffer pointer
	int buffersize = vinfo.yres_virtual * finfo.line_length;
	fbp = (char *) mmap(0, buffersize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, (off_t)0);
	
	screenBorder.minX = 0;
	screenBorder.maxX = getWidth();
	screenBorder.minY = 0;
	screenBorder.maxY = getHeight();
}

Color Screen::getColor(Point p) {
	if(p.y < 0 || p.y > getHeight() || p.x < 0 || p.x > getWidth())
		return Color(0,0,0);
	
	long int location = (p.x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (p.y+vinfo.yoffset) * finfo.line_length;
	int red = *(unsigned char*)(fbp + location + 2);
	int green = *(unsigned char*)(fbp + location + 1);
	int blue = *(unsigned char*)(fbp + location );
	
	return Color(red,green,blue);
}

void Screen::setColor(Point p, int pixelSize, Color color){
	if(p.y < 0 || p.y > getHeight() || p.x < 0 || p.x > getWidth()) {
		return;
	
	} else {
        for (int i = p.x; i < (p.x+pixelSize); i++) {
            for (int j = p.y; j < (p.y+pixelSize); j++) {
                int location = (i+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (j+vinfo.yoffset) * finfo.line_length;
                *(fbp + location) = color.getBlue();
                *(fbp + location +1) = color.getGreen();
                *(fbp + location +2) = color.getRed();
                *(fbp + location +3) = 0;
            }
        }
		
    }
}

void Screen::setBorder(Border newB) {
	screenBorder = newB;
}

int Screen::getWidth(){
	return vinfo.xres;
}
int	Screen::getHeight(){
	return vinfo.yres;
}

void Screen::ClearScreen(){
	for (int r=0;r<vinfo.yres;r++) {
		for (int c=0;c<vinfo.xres;c++) {
			int location = (c+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (r+vinfo.yoffset) * finfo.line_length;
			*(fbp + location) = 0;
			*(fbp + location +1) = 0;
			*(fbp + location +2) = 0;
			*(fbp + location + 3) = 0;
		}
	}
}


void Screen::drawLine(Point start, Point end, Color c) {
	
	int x1 = start.x, y1 = start.y;
	int x2 = end.x, y2 = end.y;
	int xmin = screenBorder.minX, xmax = screenBorder.maxX;
	int ymin = screenBorder.maxY, ymax = screenBorder.maxY;
	int x, y;

	int code1 = screenBorder.getClipCode(start);
	int code2 = screenBorder.getClipCode(end);

	int accept = 0;
	int valid = 1;

	if(screenBorder.isOverflow(start) || screenBorder.isOverflow(end) {
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
			setColor(new Point(x,y),1,c);

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
			setColor(new Point(x,y),1,c);

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


