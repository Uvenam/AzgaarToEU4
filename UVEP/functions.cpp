#include "../UVEP/functions.h"
void make_uppercase(std::string& data)
{

	std::transform(data.begin(), data.end(), data.begin(),
		[](unsigned char c) { return std::toupper(c); });



}
void make_lowercase(std::string& data)
{

	std::transform(data.begin(), data.end(), data.begin(),
		[](unsigned char c) { return std::tolower(c); });



}
int yn_isVowel(char possible_vowel)
{
	if (possible_vowel == 'a' ||
		possible_vowel == 'A' ||

		possible_vowel == 'e' ||
		possible_vowel == 'E' ||

		possible_vowel == 'i' ||
		possible_vowel == 'I' ||

		possible_vowel == 'o' ||
		possible_vowel == 'O' ||

		possible_vowel == 'u' ||
		possible_vowel == 'U' ||

		possible_vowel == 'y' ||
		possible_vowel == 'Y')
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
void make_lowercase_any(std::wstring& data)
{
	std::wstring UpperCase;
	for (auto&& ch : data)
	{
		UpperCase += towupper(ch);
	}

}

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

	mutex.unlock();

}// end of WriteToFile
void YELL(const std::string& message) {
	std::cout << '\n' << message << std::endl;
}//end of YELL
short RenderShortFromStringTimes100(const std::string& message) {
	float temp;
	short remp;
	temp = std::stof(message);
	remp = (temp * 100);
	return remp;
}// end of RenderShotFromStringTimes100
short StringToShort(const std::string& message) {
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


std::tuple<int,int,int,int> ParseStringUpdateCells(std::vector<cell_info>& all_cells, std::string& example_data) {

	std::cout << "\nParsing string, updating cells...";

	const std::string regex_cell_block
		= "\\{\"type\":\"Feature\",\"geometry\":\\{\"type\":\"Polygon\",\"coordinates\":.*?\\}\\}";	// should get ex:
	/*
	"coordinates":[[[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25]]]},"properties":{"id":0,"height":-109,"biome":0,"type":"ocean","population":0,"state":0,"province":0,"culture":0,"religion":0,"neighbors":[1,7,6]}}
	*/
	const std::string regex_cell_coordinates = "\\[\\[.*?\\]\\]\\}"; // of former, should get ex:
	/*
	[[																					// entire string as match[0]
	[-44.66,57.25],[-50.62,52.65],[-56.25,56.8],[-54,59.38],[-44.55,58.26],[-44.66,57.25] // as match[1]
	]]}
	*/
	const std::string regex_cell_vertex = "\-?\[0-9\]+\\.?\[0-9\]*"; // of former, should get
	/*
	-44.66
	57.25
	-50.62
	52.65
	-56.25
	56.8
	...and so on
	*/
	const std::string regex_cell_properties = "\"id\":\(\[0-9\]+\),\"height\":\(-?\[0-9\]+\),\"biome\":\(\[0-9\]+\),\"type\":\(\"\[^\"\]+\"\),\"population\":\(\[0-9\]+\),\"state\":\(\[0-9\]+\),\"province\":\(\[0-9\]+\),\"culture\":\(\[0-9\]+\),\"religion\":\(\[0-9\]+\),\(\"neighbors\"\:\\[\[^\\]\]+\\]\)";
	// Regex for regex101.com
	/*
	\"id\":([0-9]+),\"height\":(-?[0-9]+),\"biome\":([0-9]+),\"type\":(\"[^\"]+\"),\"population\":([0-9]+),\"state\":([0-9]+),\"province\":([0-9]+),\"culture\":([0-9]+),\"religion\":([0-9]+)
	*/

	std::smatch fetched_data;	// whenever regex returns results, they are a string and need converted
	short Xcoord = -1;
	short Ycoord = -1;

	long cell_index = -1;
	std::regex rex_chunk(regex_cell_block);
	//all_cells.push_back(cell_info()); // creates a new element
			// Divy up example_data into various matches
	std::sregex_iterator CellData_itr(example_data.cbegin(), example_data.cend(), rex_chunk);
	// Define regex for coords and verticies
	std::regex rex_coords(regex_cell_coordinates);
	std::regex rex_vertex(regex_cell_vertex);
	std::regex rex_properties(regex_cell_properties);
	std::regex rex_neighbor_id("\(\[0-9\]+\)");
	// For iterator
	std::sregex_iterator sreg_end;
	// For temp holding of string
	std::string CellData_str;
	std::string CellCoord_str;
	std::smatch CellData_matches;
	std::string CellNeighbor_str;

	int left_most = 0;
	int right_most = 0;
	int top_most = 0;
	int bottom_most = 0;


	while (CellData_itr != sreg_end) {		// Go through all cell_data matches (coordinates and properties)

		all_cells.push_back(cell_info()); cell_index++;		// Create new cell, pushback onto global vector of all cells, update how many cells there are
// TODO				// Should use size function on the array to find number of cells
		//std::cout << "\n[INFO]Cell data chunk for cell " << cell_index << ": " << std::endl;
		CellData_str = CellData_itr->str();
		//YELL(CellData_str);

		//Have cell_data chunk from above, need to sift out coordinates and properties
		// Searching chunk at a time, so the following will create verticies
		std::regex_search(CellData_str.cbegin(), CellData_str.cend(), CellData_matches, rex_coords);
		//YELL("\n[INFO]Cell coords fetched: ");
		CellCoord_str = CellData_matches[0];
		//YELL(CellCoord_str);
		//YELL("\n[INFO]Cell vertecies fetched:");
		std::sregex_iterator CellVertex_itr(CellCoord_str.cbegin(), CellCoord_str.cend(), rex_vertex);
		short vertex_itr = 0;


		// TAKING sifted coordinates AND PLACING THEM in corresponding cell
		while (CellVertex_itr != sreg_end) {

			Xcoord = RenderShortFromStringTimes100(CellVertex_itr->str(0));
			CellVertex_itr++;
			// Commenting out the next 3 lines will work (presumably an error with regex finding an odd number of verticies when it should be finding an even number

			Ycoord = RenderShortFromStringTimes100(CellVertex_itr->str(0));
			all_cells[cell_index].add_coord(Xcoord, Ycoord);
			CellVertex_itr++;

			if (Xcoord < left_most) { left_most = Xcoord; }
			if (Xcoord > right_most) { right_most = Xcoord; }
			if (Ycoord < bottom_most) { bottom_most = Ycoord; }
			if (Ycoord > top_most) { top_most = Ycoord; }




			//std::cout << "\nVertex " << (vertex_itr) << ": " << std::endl;
			//std::cout << std::get<0>(all_cells[cell_index].verticies[vertex_itr]) << std::endl;
			//std::cout << std::get<1>(all_cells[cell_index].verticies[vertex_itr]) << std::endl;
			vertex_itr++;

		}
		// TAKING sifted properties AND PLACING THEM in corresponding cell

		std::regex_search(CellData_str.cbegin(), CellData_str.cend(), CellData_matches, rex_properties);

		//std::cout << "ID: ";
		all_cells[cell_index].id = StringToShort(CellData_matches[1].str());
		//std::cout << "Height: ";
		all_cells[cell_index].height = StringToShort(CellData_matches[2].str());
		//std::cout << "Biome ID: " << std::endl;
		all_cells[cell_index].biome = StringToShort(CellData_matches[3].str());
		//std::cout << "Type str: " << std::endl;
		all_cells[cell_index].type = (CellData_matches[4].str());
		//std::cout << "Population: " << std::endl;
		all_cells[cell_index].pop = std::stoi(CellData_matches[5].str());
		//std::cout << "Country: " << std::endl;
		all_cells[cell_index].country = StringToShort(CellData_matches[6].str());
		//std::cout << "Sub-Country: " << std::endl;
		all_cells[cell_index].sub_country = StringToShort(CellData_matches[7].str());
		//std::cout << "Culture ID: " << std::endl;
		all_cells[cell_index].culture = StringToShort(CellData_matches[8].str());
		//std::cout << "Religion ID: " << std::endl;
		all_cells[cell_index].religion = StringToShort(CellData_matches[9].str());

		CellNeighbor_str = CellData_matches[10].str();
		std::sregex_iterator CellNeighbor_itr(CellNeighbor_str.cbegin(), CellNeighbor_str.cend(), rex_neighbor_id);

		//YELL("[INFO] Cell Neighbors fetched:");

		while (CellNeighbor_itr != sreg_end) {

			//YELL(CellNeighbor_itr->str(0));
			all_cells[cell_index].neighbors.push_back(StringToShort(CellNeighbor_itr->str(0)));
			CellNeighbor_itr++;
		}

		//YELL("\n[INFO]Cell properties fetched");


		// TAKING sifted neighbors AND PLACING THEM in corresponding neighbors vector


		CellData_itr++;
	}// end of while(CellData_itr != sreg_end){

	return std::make_tuple(left_most,right_most,top_most,bottom_most);



}

void ReadFromPlaceInto(std::string wanted_file, std::string& file_info) {
	std::stringstream buffer{};
	std::fstream fileStream;
	fileStream.open(wanted_file, std::ios::in);	// read contents (don't want to output to this file)
	if (fileStream) {
		std::cout << wanted_file << " opened" << std::endl;
		// File is open, Want to get line for future usage and save (IO expensive) / Copy file contents into string
		buffer << fileStream.rdbuf();	// read entire file content
		file_info = buffer.str();		// stringify it, put it into string variable
		YELL("\nFile info retrieved");
		//YELL(file_info);

	}//end of if for fileStream
	else {		// couldn't open file, some sort of error
		throw std::runtime_error("Cannot open cell_file");
	}//couldn't open fileStream else


}

void GenericOutput(std::vector<cell_info> all_cells, std::string output_file) {


	std::cout << "\nOutputting to log.txt...";
	std::ofstream outputLog(output_file);		// Whatever is written will be an overwrite eachtime program runs
	if (outputLog) {

		//YELL("\n[INFO]Cell Data: ");

		for (int proll = 0; proll < all_cells.size(); proll++) {
			outputLog << "\nCell: " << all_cells[proll].id << "\n";
			outputLog << "Height: " << all_cells[proll].height << "\n";
			outputLog << "Biome: " << all_cells[proll].biome << "\n";
			outputLog << "Type: " << all_cells[proll].type << "\n";
			outputLog << "Population: " << all_cells[proll].pop << "\n";
			outputLog << "State: " << all_cells[proll].country << "\n";
			outputLog << "Sub-state: " << all_cells[proll].sub_country << "\n";
			outputLog << "Culture: " << all_cells[proll].culture << "\n";
			outputLog << "Religion: " << all_cells[proll].religion << "\n";

			outputLog << "Verticies:\n";
			for (int pion = 0; pion < all_cells[proll].verticies.size(); pion++) {
				outputLog << std::get<0>(all_cells[proll].verticies[pion]);
				outputLog << " , ";
				outputLog << std::get<1>(all_cells[proll].verticies[pion]);
				outputLog << "\n";
			}

			outputLog << "Neighbors:\n";
			for (int plok = 0; plok < all_cells[proll].neighbors.size(); plok++) {
				outputLog << all_cells[proll].neighbors[plok];
				outputLog << " , ";
			}
		}


		// Cell info gotten, need to parse for specific info such as:
		// Verticies
		// CONVERT string ab.cd TO signed short abcd 
		// Properties
			// ID, height, biome, type, pop, country, sub_country, culture, religion, neighbors

		YELL("\nwrite complete");



	}//end of if for outputLog
	else {
		throw std::runtime_error("Cannot open log.txt");
	}//else if couldn't open file


}

void EnsureDirectory(std::string desired_dir) {
	if (std::filesystem::create_directory(desired_dir))	// returns false if it exists, true if it doesn't
	{
		std::cout << '\n' << desired_dir << " created successfully!" << std::endl;
	}
	std::cout << '\n' << desired_dir << " directory exists" << std::endl;
};