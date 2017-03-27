#include "Screen.h"
#include <iostream>

using namespace std;

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
	
	layers.clear();
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
                if(vinfo.bits_per_pixel == 32) {
					*(fbp + location +3) = 0;
				}
            }
        }
		
    }
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
			setColor(Point(c,r),1,Color(0,0,0));
		}
	}
}

void Screen::setBorder(Border newB) {
	if(newB.minX < 0) newB.minX = 0;
	if(newB.maxX > getWidth()) newB.maxX = getWidth();
	if(newB.minY < 0) newB.minY = 0;
	if(newB.maxY > getHeight()) newB.maxY = getHeight();
	
	screenBorder = newB;
	for(int i=0; i<layers.size(); i++) 
		layers.at(i).setBorder(newB);
}

void Screen::addLayer() {
	layers.push_back(Layer(getWidth(), getHeight()));
	showlayers.push_back(true);
}
void Screen::deleteLayer(int idx) {
	layers.erase(layers.begin() + idx);
	showlayers.erase(showlayers.begin() + idx);
}
int Screen::getLayerCount() {
	return layers.size();
}
	
void Screen::setLayerShow(int i, bool s) {
	showlayers.at(i) = s;
}
bool Screen::getLayerShowStatus(int i) {
	return showlayers.at(i);
}
	
void Screen::toBack(int i) {
	iter_swap(layers.begin() + i, layers.begin() + 0);
	iter_swap(showlayers.begin() + i, showlayers.begin() + 0);
}
void Screen::toFront(int i) {
	iter_swap(layers.begin() + i, layers.begin() + layers.size() - 1);
	iter_swap(showlayers.begin() + i, showlayers.begin() + showlayers.size() - 1);
}

Layer& Screen::getLayer(int i) {
	return layers.at(i);
}
int Screen::getLayerCount(){
	return layers.size();
}

void Screen::drawAll() {
	Color background(0,0,0);
	ClearScreen();
	
	for(int y=screenBorder.minY; y<screenBorder.maxY; y++) {
		for(int x=screenBorder.minX; x<screenBorder.maxX; x++) {
			
			for(int l=layers.size()-1; l>=0; l--) {	
				if(showlayers.at(l)) {	
					
					if(!background.isSame(layers.at(l).getColor(Point(x,y)))) {
						
						setColor(Point(x,y), 1, layers.at(l).getColor(Point(x,y)));
						break;
						
					}
					
				}
			}
			
		}
	}
}

