#pragma once
#include "head.h"
// https://www.learncpp.com/cpp-tutorial/class-code-and-header-files/

struct cell_info {
	std::vector<  std::tuple<short, short>  > verticies;
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
	void add_coord(short x_coord, short y_coord) {
		this->verticies.push_back(std::make_tuple(x_coord, y_coord));
	}
};