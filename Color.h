#ifndef __Color__
#define __Color__

#include "json.hpp"
using json = nlohmann::json;

// Model Class to store RGB Color Value
class Color{

public:
	Color();					//constructor
	Color(int r, int g, int b); //constructor with initial color
	Color(const json& object);

	void setColor(int r, int g, int b); //set semua warna
	int getRed();
	int getGreen();
	int getBlue();
	bool isSame(Color C);
	json getJSONObject();

private:
	int Red;
	int Green;
	int Blue;
};

#endif