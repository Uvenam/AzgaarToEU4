#include <iostream> // IO to console
#include <fstream>  // for manipulating files, IO to files. contains datatypes such as fstream
#include <sstream>	// for stringstream buffer
#include <string>   // for creating strings and using strings, treated as std::string type. Also includes string functions
#include <filesystem>   // opendir function enability
#include <regex>		//used for finding info in string
#include <tuple>		// for creating binded data
#include <vector>		// for storing varying data
#include <mutex>				// for protecting file access
#include <stdexcept>			// for exceptions
#include "OpenAndEdit.h"

#define VERSION_STAMP	"V 0.205"

namespace fs = std::filesystem; // possible to cutdown on the namespace extensions. using "fs" instead of "std::filesystme" works


void WriteToFile(const std::string& message, const std::string& file_path);
void YELL(const std::string& message);
short RenderShortFromStringTimes100(const std::string& message);
short StringToShort(const std::string& message);
int main() {

	std::string example_data =
		"{\"type\":\"FeatureCollection\",\"features\":[{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25]]]},\"properties\":{\"id\":0,\"height\":-109,\"biome\":12,\"type\":\"island\",\"population\":140,\"state\":2,\"province\":3,\"culture\":4,\"religion\":5,\"neighbors\":[1,7,6]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-40.16,51.19],[-42.53,52.2],[-44.21,54.22],[-44.66,57.25],[-44.55,58.26],[-44.1,58.6],[-41.17,58.26],[-36.56,52.65],[-38.14,51.53],[-40.16,51.19]]]},\"properties\":{\"id\":1,\"height\":-29,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[11,10,9,7,0,2,12]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-35.44,52.65],[-36.56,52.65],[-41.17,58.26],[-34.31,60.84],[-33.97,60.5],[-34.65,52.99],[-35.44,52.65]]]},\"properties\":{\"id\":2,\"height\":-70,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[13,12,1,3]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-30.6,51.76],[-34.65,52.99],[-33.97,60.5],[-27.45,58.04],[-28.57,52.43],[-28.8,52.2],[-30.6,51.76]]]},\"properties\":{\"id\":3,\"height\":-55,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[30,13,2,4,14]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-19.91,57.36],[-22.61,52.32],[-26.33,51.76],[-28.57,52.43],[-27.45,58.04],[-24.52,59.94],[-19.91,57.36]]]},\"properties\":{\"id\":4,\"height\":-88,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[16,15,14,3]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-55.12,47.94],[-65.7,49.29],[-67.5,52.99],[-63.79,56.02],[-56.92,56.35],[-54.9,48.17],[-55.12,47.94]]]},\"properties\":{\"id\":5,\"height\":-88,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[19,18,17,6]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-52.76,48.5],[-54.9,48.17],[-56.92,56.35],[-56.25,56.8],[-50.62,52.65],[-50.4,51.64],[-52.76,48.5]]]},\"properties\":{\"id\":6,\"height\":-70,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[8,19,5,0,7]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-47.25,49.85],[-50.4,51.64],[-50.62,52.65],[-44.66,57.25],[-44.21,54.22],[-47.25,49.85]]]},\"properties\":{\"id\":7,\"height\":-55,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[9,8,6,0,1]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-48.26,47.38],[-50.06,46.93],[-52.76,48.5],[-50.4,51.64],[-47.25,49.85],[-47.14,48.84],[-48.26,47.38]]]},\"properties\":{\"id\":8,\"height\":-70,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[22,21,19,6,7,9]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-45.56,48.17],[-47.14,48.84],[-47.25,49.85],[-44.21,54.22],[-42.53,52.2],[-43.42,48.62],[-45.56,48.17]]]},\"properties\":{\"id\":9,\"height\":-9,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[24,22,8,7,1,10]}},{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-40.16,51.19],[-41.17,47.27],[-43.42,48.62],[-42.53,52.2],[-40.16,51.19]]]},\"properties\":{\"id\":10,\"height\":-9,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[1,11,24,9]}}]}";
	//Copy
	/*
	{"type":"FeatureCollection","features":[{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25]]]},"properties":{"id":0,"height":-109,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[1,7,6]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-40.16,51.19],[-42.53,52.2],[-44.21,54.22],[-44.66,57.25],[-44.55,58.26],[-44.1,58.6],[-41.17,58.26],[-36.56,52.65],[-38.14,51.53],[-40.16,51.19]]]},"properties":{"id":1,"height":-29,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[11,10,9,7,0,2,12]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-35.44,52.65],[-36.56,52.65],[-41.17,58.26],[-34.31,60.84],[-33.97,60.5],[-34.65,52.99],[-35.44,52.65]]]},"properties":{"id":2,"height":-70,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[13,12,1,3]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-30.6,51.76],[-34.65,52.99],[-33.97,60.5],[-27.45,58.04],[-28.57,52.43],[-28.8,52.2],[-30.6,51.76]]]},"properties":{"id":3,"height":-55,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[30,13,2,4,14]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-19.91,57.36],[-22.61,52.32],[-26.33,51.76],[-28.57,52.43],[-27.45,58.04],[-24.52,59.94],[-19.91,57.36]]]},"properties":{"id":4,"height":-88,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[16,15,14,3]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-55.12,47.94],[-65.7,49.29],[-67.5,52.99],[-63.79,56.02],[-56.92,56.35],[-54.9,48.17],[-55.12,47.94]]]},"properties":{"id":5,"height":-88,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[19,18,17,6]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-52.76,48.5],[-54.9,48.17],[-56.92,56.35],[-56.25,56.8],[-50.62,52.65],[-50.4,51.64],[-52.76,48.5]]]},"properties":{"id":6,"height":-70,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[8,19,5,0,7]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-47.25,49.85],[-50.4,51.64],[-50.62,52.65],[-44.66,57.25],[-44.21,54.22],[-47.25,49.85]]]},"properties":{"id":7,"height":-55,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[9,8,6,0,1]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-48.26,47.38],[-50.06,46.93],[-52.76,48.5],[-50.4,51.64],[-47.25,49.85],[-47.14,48.84],[-48.26,47.38]]]},"properties":{"id":8,"height":-70,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[22,21,19,6,7,9]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-45.56,48.17],[-47.14,48.84],[-47.25,49.85],[-44.21,54.22],[-42.53,52.2],[-43.42,48.62],[-45.56,48.17]]]},"properties":{"id":9,"height":-9,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[24,22,8,7,1,10]}},{"type":"Feature","geometry":{"type":"Polygon","coordinates":[[[-40.16,51.19],[-41.17,47.27],[-43.42,48.62],[-42.53,52.2],[-40.16,51.19]]]},"properties":{"id":10,"height":-9,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[1,11,24,9]}}]}
	*/
	const std::string example_snippet =
		"{\"type\":\"Feature\",\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25]]]},\"properties\":{\"id\":0,\"height\":-109,\"biome\":0,\"type\":\"ocean\",\"population\":0,\"state\":0,\"province\":0,\"culture\":0,\"religion\":0,\"neighbors\":[1,7,6]}}";

	//Searching for
	/*
	Need to search for
		{"type":"Feature","geometry":{"type":"Polygon","coordinates":
	Extract the data from
		[	[
		[-16.76,42.56],[-17.21,42.67],[-20.25,45.48],[-19.58,48.95],[-9.23,51.87],[-4.95,49.74],[-4.5,49.4],[-9.34,45.92],[-16.76,42.56]
		]	]
	and
		,"properties":{"id":1,"height":-29,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[11,10,9,7,0,2,12]}}
	Put into
	*/

	// storage of verticies and properties of a cell from .geojson file
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
		std::vector<short> neighbors;
		void add_coord(short x_coord, short y_coord) {
			this->verticies.push_back(std::make_tuple(x_coord, y_coord));
		}
	};
	// to create an item
	cell_info C1;
	// the main holder of all the cells:
	std::vector<cell_info>	all_cells;
	//	all_cells[0].id = 0;					// can only modify that vector element when its been created
	//	C1.verticies.push_back(std::tuple<short, short>(-16.6, 17.7));	// how to add verticies
	//	C1.add_coord(5, 5);

		// C++ doesn't support lookbehind, need to update those with (?<=)

		//Regex semi-defines
		/*
		 Regex for capturing entire section
					((?<="coordinates":).*?(?=\}\}))
			 Rgex for capturing entire section with ending }}
					((?<="coordinates":).*?(\}\}))
			 Regex for capturing Verticies, but also captures neighbors
					((?<=\[)[0-9,\.-]+(?=\]))
		 Regex for capturing X and Y as two separate groups for between []
				\[([\-0-9\.]+)(?:,)([\-0-9\.]+)(?=\])
			 Rgex for capturing all verticies, though they are not separated
					((?<=\[\[)[0-9\]\[,\.-]+(?=\]\]))
			 Regex for matching the properties unseparated
					((?<=\{)[a-zA-Z0-9\,\"\:\[\]-]+(?=\}))
		*/

	std::smatch fetched_data;	// whenever regex returns results, they are a string and need converted
	short Xcoord;
	short Ycoord;

	// fetched_data[0] will be the entire match, fetched_data[1] will be the first subsection
	// will be returned as str (prolly) that needs converted to int/float

#if 0
	// In order to examine all matches within the target sequence, std::regex_search may be called in a loop, restarting each time from m[0].second of the previous call. std::regex_iterator offers an easy interface to this iteration.
	// 
	// Example regex ( https://stackoverflow.com/questions/29321249/regex-grouping-matches-with-c-11-regex-library )
	std::string s{ R"(
t?B:Username!Username@Username.tcc.domain.com Connected
t?B:Username!Username@Username.tcc.domain.com WEBMSG #Username :this is a message
t?B:Username!Username@Username.tcc.domain.com Status: visible
)" };

	std::regex rgx("WEBMSG #([a-zA-Z0-9]+) :(.*)");
	std::smatch matches;

	if (std::regex_search(s, matches, rgx)) {
		std::cout << "Match found\n";

		for (size_t i = 0; i < matches.size(); ++i) {
			std::cout << i << ": '" << matches[i].str() << "'\n";
		}
	}
	else {
		std::cout << "Match not found\n";
	}
#endif



	const std::string regex_cell_block = "\"coordinates\":.*?\\}\\}";	// should get ex:
	/*
	"coordinates":[[[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25]]]},"properties":{"id":0,"height":-109,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[1,7,6]}}
	*/
	const std::string regex_cell_coordinates = "\\[\\[(.*?)\\]\\]\\}"; // of former, should get ex:
	/*
	[[																					// entire string as match[0]
	[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25] // as match[1]
	]]}
	*/
	const std::string regex_cell_vertex = "\-?\[0-9\]+\\.?\[0-9\]+"; // of former, should get
	/*
	-44.66
	57.25
	-50.62
	52.65
	-56.25
	56.8
	...and so on
	*/
	const std::string regex_cell_properties = "\"id\":\(\[0-9\]+\),\"height\":\(-?\[0-9\]+\),\"biome\":\(\[0-9\]+\),\"type\":\(\"\[^\"\]+\"\),\"population\":\(\[0-9\]+\),\"state\":\(\[0-9\]+\),\"province\":\(\[0-9\]+\),\"culture\":\(\[0-9\]+\),\"religion\":\(\[0-9\]+\)";
	// Regex for regex101.com
	/*
	\"id\":([0-9]+),\"height\":(-?[0-9]+),\"biome\":([0-9]+),\"type\":(\"[^\"]+\"),\"population\":([0-9]+),\"state\":([0-9]+),\"province\":([0-9]+),\"culture\":([0-9]+),\"religion\":([0-9]+)
	*/


	//const std::string wanted_file = "C:/Desktop/AZGAAR_to_EU4/OpenAndEdit/infohere/expa.txt"; // works for explicit
	// Create a directory
	const std::string dir_base = "base";
	const std::string dir_azgaar = "AZGAAR";
	const std::string cell_file = "cell_map.geojson";
	const std::string cell_file_t = "cell_map_t.geojson";
	const std::string file_test = "file_test.txt"; // for testing if comparisons work

	std::string file_info;
	std::stringstream buffer{};

	std::fstream fileStream;

	// The .exe will create a subdirectory to its hosting folder, putting this file named file_name in there
	// This process is relative

	std::cout << VERSION_STAMP << std::endl;

// MAIN TRY SECTION
//====================================================================================================================//
//====================================================================================================================//

	try {
		if (fs::create_directory(dir_azgaar))	// returns false if it exists, true if it doesn't
		{
			std::cout << dir_azgaar << " created successfully!" << std::endl;
		}
		std::cout << dir_azgaar << " as directory exists" << std::endl;

		std::string wanted_file = dir_azgaar + "/" + cell_file;

		fileStream.open(wanted_file, std::ios::in);	// read contents (don't want to output to this file)
		std::cout << wanted_file << " opened" << std::endl;
		if (fileStream) {

			// File is open, Want to get line for future usage and save (IO expensive) / Copy file contents into string
			buffer << fileStream.rdbuf();	// read entire file content
			file_info = buffer.str();		// stringify it, put it into string variable
			YELL("File info retrieved:\n");
			YELL(file_info);
			YELL("\n");




		}//end of if for fileStream
		else {		// couldn't open file, some sort of error
			throw std::runtime_error("Cannot open cell_file");
		}//couldn't open fileStream else

		std::ofstream outputLog("log.txt");		// Whatever is written will be an overwrite eachtime program runs
		if (outputLog) {


			// Want to iteratively search string for individual cell info


			std::regex rgx("[0-9]+", std::regex_constants::extended | std::regex_constants::icase);
			std::smatch matches;
			std::smatch fetched_unstringed;
			// following only does it once, makes one match and the following are submatches.
			if (std::regex_search(example_data, matches, rgx)) {
				std::cout << "Match found\n";

				for (size_t i = 0; i < matches.size(); ++i) {
					std::cout << i << ": '" << matches[i].str() << "'\n";
				}
			}
			else {
				std::cout << "Match not found\n";
			}


			// https://www.youtube.com/watch?v=_79j_-2xMrQ&ab_channel=BoQian
			std::regex exp(regex_cell_block);
			std::sregex_iterator pos(example_data.cbegin(), example_data.cend(), exp);
			std::sregex_iterator end;	// Default constructor defines past-the-end iterator
			while (pos != end) {
				for (size_t b = 0; b < pos->size(); b++)
					std::cout << "Matched " << b << pos->str(b) << std::endl;

				pos++;
			}
			std::sregex_token_iterator pos2(example_data.cbegin(), example_data.cend(), exp, 0);
			std::sregex_token_iterator end2;
			while (pos2 != end2) {
				std::cout << "FF SubMatched: " << pos2->str() << std::endl;
				pos2++;
			}


			// READ FROM CELL_MAP or string, EXTRACT VERTEX DATA, ID DATA, and so on
			//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

			example_data = file_info;









			// big error: when using file_info copied into example_data, regex_iterator not dereferenceable. this happens at cell id 345



















			long cell_counter = -1;
			//all_cells.push_back(cell_info()); // creates a new element
					// Divy up example_data into various matches
			std::sregex_iterator CellData_itr(example_data.cbegin(), example_data.cend(), exp);
			// Define regex for coords and verticies
			std::regex rex_coords(regex_cell_coordinates);
			std::regex rex_vertex(regex_cell_vertex);
			std::regex rex_properties(regex_cell_properties);
			// For iterator
			std::sregex_iterator sreg_end;
			// For temp holding of string
			std::string CellData_str;
			std::string CellCoord_str;
			std::smatch CellData_matches;
			while (CellData_itr != sreg_end) {

				while (CellData_itr != sreg_end) {		// Go through all cell_data matches (coordinates and properties)

					all_cells.push_back(cell_info()); cell_counter++;		// Create new cell, pushback onto global vector of all cells, update how many cells there are
	// TODO			// Should use size function on the array to find number of cells
					std::cout << "\nCell data chunk for cell " << cell_counter << ": " << std::endl;
					CellData_str = CellData_itr->str();
					YELL(CellData_str);

					//Have cell_data chunk from above, need to sift out coordinates and properties
					// Searching chunk at a time, so the following will create verticies
					std::regex_search(CellData_str.cbegin(), CellData_str.cend(), CellData_matches, rex_coords);
					YELL("\nCell coords fetched: ");
					CellCoord_str = CellData_matches[1];
					YELL(CellCoord_str);
					YELL("Cell vertecies fetched:\n");
					std::sregex_iterator CellVertex_itr(CellCoord_str.cbegin(), CellCoord_str.cend(), rex_vertex);
					short vertex_itr = 0;


					// TAKING sifted coordinates AND PLACING THEM in corresponding cell
					while ((CellVertex_itr != sreg_end)) {

						Xcoord = RenderShortFromStringTimes100(CellVertex_itr->str(0));
						CellVertex_itr++;
						Ycoord = RenderShortFromStringTimes100(CellVertex_itr->str(0));
						all_cells[cell_counter].add_coord(Xcoord, Ycoord);
						CellVertex_itr++;
						std::cout << "Vertex " << (vertex_itr) << ": " << std::endl;
						std::cout << std::get<0>(all_cells[cell_counter].verticies[vertex_itr]) << std::endl;
						std::cout << std::get<1>(all_cells[cell_counter].verticies[vertex_itr]) << std::endl;
						vertex_itr++;

					}


					// TAKING sifted properties AND PLACING THEM in corresponding cell
					YELL("Cell properties fetched:\n");
					std::regex_search(CellData_str.cbegin(), CellData_str.cend(), CellData_matches, rex_properties);

					//std::cout << "ID: ";
					all_cells[cell_counter].id = StringToShort(CellData_matches[1].str());
					//std::cout << "Height: ";
					all_cells[cell_counter].height = StringToShort(CellData_matches[2].str());
					//std::cout << "Biome ID: " << std::endl;
					all_cells[cell_counter].biome = StringToShort(CellData_matches[3].str());
					//std::cout << "Type str: " << std::endl;
					all_cells[cell_counter].type = (CellData_matches[4].str());
					//std::cout << "Population: " << std::endl;
					all_cells[cell_counter].pop = std::stoi(CellData_matches[5].str());
					//std::cout << "Country: " << std::endl;
					all_cells[cell_counter].country = StringToShort(CellData_matches[6].str());
					//std::cout << "Sub-Country: " << std::endl;
					all_cells[cell_counter].sub_country = StringToShort(CellData_matches[7].str());
					//std::cout << "Culture ID: " << std::endl;
					all_cells[cell_counter].culture = StringToShort(CellData_matches[8].str());
					//std::cout << "Religion ID: " << std::endl;
					all_cells[cell_counter].religion = StringToShort(CellData_matches[9].str());


					// TAKING sifted neighbors AND PLACING THEM in corresponding neighbors vector







					CellData_itr++;
				}


				// CONFIRMATION of obtaining cell info and correctly parsing
				std::cout << "\nThere are " << all_cells.size() << " many cells";
				std::cout << "\nCell counter is " << cell_counter;
				YELL("\nCell Data: ");
				for (int proll = 0; proll < all_cells.size(); proll++) {
					std::cout << "Cell: " << all_cells[proll].id << "\n";
					std::cout << "Height: " << all_cells[proll].height << "\n";
					std::cout << "Biome: " << all_cells[proll].biome << "\n";
					std::cout << "Type: " << all_cells[proll].type << "\n";
					std::cout << "Population: " << all_cells[proll].pop << "\n";
					std::cout << "State: " << all_cells[proll].country << "\n";
					std::cout << "Sub-state: " << all_cells[proll].sub_country << "\n";
					std::cout << "Culture: " << all_cells[proll].culture << "\n";
					std::cout << "Religion: " << all_cells[proll].religion << "\n";

					std::cout << "Verticies:\n";
					for (int pion = 0; pion < all_cells[proll].verticies.size(); pion++) {
						std::cout << std::get<0>(all_cells[proll].verticies[pion]);
						std::cout << " , ";
						std::cout << std::get<1>(all_cells[proll].verticies[pion]);
						std::cout << "\n";
					}
				}


				// Cell info gotten, need to parse for specific info such as:
				// Verticies
				// CONVERT string ab.cd TO signed short abcd 
				// Properties
					// ID, height, biome, type, pop, country, sub_country, culture, religion, neighbors

				YELL("\nwrite complete");


			}
		}//end of if for outputLog
		else {
			throw std::runtime_error("Cannot open log.txt");
		}//else if couldn't open file

		}//end of try
		catch (std::runtime_error runtime) {		// managing file opening error
			std::cout << "Caught runtime error:" << runtime.what() << std::endl;
		}//end of catch for runtime error
		catch (...) {								// managing all other errors
			std::cout << "Unknown exception\n";
		}//end of any catch






		std::cout << "\nEnd of Program";
		system("pause>0"); // gets ride of the console extra text by pausing program execution at the very end
}	// End of main()


void WriteToFile(const std::string  message, const std::string& file_path) {
		// |mutex| is to protect access to |file| (which is shared across threads).
		static std::mutex mutex;

		// Lock |mutex| before accessing |file|.
		std::lock_guard<std::mutex> lock(mutex);

		// Try to open file.
		std::ofstream file(file_path);
		if (!file.is_open()) {
			throw std::runtime_error("[runtime error] Cannot Open");
		}

		// Write |message| to |file|.
		file << message << std::endl;

}// end of WriteToFile
void YELL(const std::string & message) {
	std::cout << message << std::endl;
}//end of YELL
short RenderShortFromStringTimes100(const std::string & message) {
	float temp;
	short remp;
	temp = std::stof(message);
	remp = (temp * 100);
	return remp;
}// end of RenderShotFromStringTimes100
short StringToShort(const std::string & message) {
	short remp = -1;
	int temp = -1;
	temp = std::stoi(message);
	if (temp >= SHRT_MAX || temp <= SHRT_MIN) {
		throw(std::range_error("Trying to convert too large of a number!"));
}
	else {
		remp = temp;
}
	return remp;
}// end of StringToShort