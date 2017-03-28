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
#include <fstream>
#include <iomanip>

#include "Color.h"
#include "Layer.h"

class Screen{

public :
	Screen(); // Constructor
	Color getColor(Point p); // Mendapatkan warna yang sedang ditampilkan pada baris ke r kolom ke c
	void setColor(Point p, int pixelSize, Color C); //set warna layar pada koordinat r,c 
	void setBorder(Border newB);
	
	int getWidth(); // mendapatkan width dari resolusi layar
	int getHeight(); // mendapatkan height dari resolusi layar
	
	void ClearScreen(); //Membersihkan layar
	
	//Layer manipulation
	void addLayer();
	void deleteLayer(int i);
	Layer& getLayer(int i);
	int getLayerCount();
	
	void setLayerShow(int i, bool s);
	bool getLayerShowStatus(int i);
	
	void toBack(int i);
	void toFront(int i);
	
	void drawAll();

	json getJSONObject();
	
	void saveLayers(const string& filename);
	void loadLayers(const string& filename);
private :
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
	int fb_fd;
	char *fbp;
	vector<Layer> layers;
	vector<bool> showlayers;
	Border screenBorder;
};

extern Screen screen; //a Global variable screen for other class to use

#endif
