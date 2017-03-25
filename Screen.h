#ifndef __Screen__
#define __Screen__
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "Color.h"
#include "shape.h"
#include "Border.h"

class Screen{

public :
	Screen(); // Constructor
	Color getColor(Point p); // Mendapatkan warna yang sedang ditampilkan pada baris ke r kolom ke c
	void setColor(Point p, int pixelSize, Color C); //set warna layar pada koordinat r,c 
	void setBorder(Border newB);
	
	int getWidth(); // mendapatkan width dari resolusi layar
	int getHeight(); // mendapatkan height dari resolusi layar

	void ClearScreen(); //Membersihkan layar
	
	void drawLine(Point start, Point end, Color c);
	
private :
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
	int fb_fd;
	char *fbp;
	Border screenBorder;

};

extern Screen screen; //a Global variable screen for other class to use

#endif
