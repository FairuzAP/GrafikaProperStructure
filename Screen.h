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
#include <vector>

#include "Color.h"
#include "Layer.h"

using namespace std;

class Screen{

public :
	Screen(); // Constructor
	Color getColor(Point p); // Mendapatkan warna yang sedang ditampilkan pada baris ke r kolom ke c
	void setColor(Point p, int pixelSize, Color C); //set warna layar pada koordinat r,c 
	void setBorder(Border newB);
	
	int getWidth(); // mendapatkan width dari resolusi layar
	int getHeight(); // mendapatkan height dari resolusi layar
	
	void ClearScreen(); //Membersihkan layar
	
	void addLayer();
	Layer& getLayer(int i);
	void drawAll();
	
private :
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
	int fb_fd;
	char *fbp;
	vector<Layer> layers;
	Border screenBorder;
};

extern Screen screen; //a Global variable screen for other class to use

#endif
