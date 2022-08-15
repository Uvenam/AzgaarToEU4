#pragma once
#include "../UVEP/head.h"
#include "../UVEP/RPoint.h"

class IPixel;

class Province {
public:
	// info for provinces.bmp
		//RPoly shape;
	
	// info for adjacencies.csv

	// info for positions.txt
	double positions[2];	// item 0 will be X, item 1 will be Y

	/* If you are manually adding positions, then the mappings for each co-ordinate on the provinces.bmp (or any of the standard sized images) are as follows:
	X – Maps 1:1. i.e. In CS4 the X co-ordinate will match the co-ordinate you put in the positions.tt
	Y – From the width of your map, take the position within your image editor and subtract it from the width (i.e. 2048 – 755). This will give you the value you need to add to the positions.txt (1293). Essentially the y co-ordinate is flipped. */

	// info for definition.csv
	int id;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	std::string province_name;
	// info for continent.txt
	
	// info for area.txt	
	
	// info for history
		// int id
	std::string owner;
	std::string controller;
	std::vector<std::string> cores;

	std::string culture;
	std::string religion;


	// info for terrain.bmp and terrain.txt and trees.bmp
		// short biome; (RGB value) and std::string type; (string)
	// info for rivers.bmp (?)

	// info for heightmap.bmp and world_normal.bmp
		// short height;
	// info for colormap_autumn.dds, colormap_spring.dds, colormap_summer.dds, colormap_winter.dds
	
	// Development info ?
		//int pop;
};
/*
struct cell_info {
	std::vector<RPoint> verticies;
	int id;
	short height;
	short biome;
	std::string type;
	int pop;
	short country;
	short sub_country;
	short culture;
	short religion;
	std::vector<int> neighbors;
	void add_coord( int x_coord, int y_coord );
};
*/