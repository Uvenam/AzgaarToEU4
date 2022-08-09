#pragma once
#include "../UVEP/head.h"

class progressBar {			//##################################################################################

public:
	int amountOfFiller = 0;
	int pBarLength = 50;

	int currentProgress = 0;
	int items = 100;

	char firstPartOfBar = '[';
	char lastPartOfBar = ']';
	char barFiller = '#';
	char barEmpty = '.';
	std::string task = "";
	void update(int newProgress);
	void updatePercent(double newPercent);
	void reuse(int items1);
	progressBar(std::string task_ele, int elements);
	progressBar(int elements);
	progressBar();



}; // end class				//##################################################################################


class stateMaker {

	//FORM for STATES from AZGAAR
	/*
	Id,State,Full Name,Form,RPixel,Capital,Culture,Type,Expansionism,Cells,Burgs,Area mi2,Total Population,Rural Population,Urban Population
	EX:
	52,Zubo,Zuban Empire,Empire,#db97e0,Zubo,Uruk,Nomadic,4.9,754,58,12232384,3226127,2895337,330790
	*/
	// FORM for COUNTRIES in EU4, directory: common/countries
	/*
		graphical_culture
		color = { X, Y, Z}
		historical_idea_groups
		historical_units
		monarch_names // optional
		leader_names //optional
		ship_names //optional
		army_names //optional
		fleet_names //optional

	*/
	// FORM for COUNTRIES in EU4, directory: history/countries
	/*
		setup_vision = yes
		government = monarchy
		add_government_reform = feudalism_reform
		government_rank = 1
		primary_culture = derannic
		religion = regent_court
		technology_group = tech_cannorian
		capital = 113 # Deranne
		fixed_capital = //optional // also # is for comments in paradox txt format

	*/
public:
	// from azgaar states.csv
	short ID;
	std::string name;
	std::string form;
	long color;
	std::string capital;
	std::string culture;
	std::string type;
	float expansionism;

	// eu4 to be made
	std::string country_tag;
	// flag as TGA
	// country idea groups
	// color, RGB values
	// government
	// technology_group
	// religion
	// primary_culture
	// capital as province ID
	// fixed_capital as province ID

	// Not sure if needed since these come with cell read in
	short burg_count;
	long area_mi2;
	long rural_population;
	long urban_population;

	void fnParseLine(std::string result_getLine_ele) {

		std::string regex_info = "[^\\,\]+";
		// Iterate over each match. Match 1 should be ID, Match 2 is State, 3 is full name and is discarded, 4 is form, 5 is color, 6 is capital, 7 is culture, 8 is type, 9 is expansionism, 10 is cell count and is discarded, 11 is burg count, 12 is area, 13 is total pop, 14 is rural pop, 15 is urban pop

	}

};


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
	void add_coord(short x_coord, short y_coord);
};