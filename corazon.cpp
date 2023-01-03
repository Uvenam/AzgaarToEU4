#include "../UVEP/head.h"
#include "../UVEP/functions.h"
#include "../UVEP/globals.h"
#include "../UVEP/classes.h"
#include "../UVEP/VUCO.h"
#include "../UVEP/ScreenImaging.h"
#include "../UVEP/RPoint.h"

#include <exception>
#include <stdexcept>

#include "ocv.h"

import opencv_personal;
import screens;
// commit all, then push
#define		VERSION_STAMP	"V 0.410"
// Most recent change: Moving files into ../UVEP/
// Most recent goal


/*
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
*/

// namespace alias (aka can type this instead of full namespace path)
namespace fs = std::filesystem; // possible to cutdown on the namespace extensions. using "fs" instead of "std::filesystme" works

// CRTL M CRTL H to collapse section

//static std::exception_ptr teptr = nullptr;
// FOR ESC EXIT
DWORD WINAPI CheckEscape(LPVOID lpParam) {
while (GetAsyncKeyState(VK_ESCAPE) == 0) {
	//sleep 
	Sleep(10);
}
exit(0);

}

inline std::string AZGAAR_DIR = "AZGAAR";
inline std::string EU4_DIR = "AZGAAR_CONVERTED";
inline std::string COUNTRIES_DIR = "/countries";

std::string dir_azgaar = "AZGAAR";
std::string dir_cells;// dir_azgaar + "/" + "cell_geojson";
std::string dir_states = dir_azgaar + "/" + "states_csv";
std::string dir_cultures = dir_azgaar + "/" + "culture_csv";
std::string dir_namebase = dir_azgaar + "/" + "namebase_txt";
std::string dir_rivers = dir_azgaar + "/" + "river_geojson";
/* Form
[NAME OF CONTINENT] [ITEM] [YYYY-MM-DD-HrmilitaryHrmilitary-MinuteMinute].[FILETYPE]
Ex:
Vania Cells 2022-10-09-13-05.geojson
*/
std::regex desired_cell_csv_path( "\[\\w\]+ Cells \[0-9^-\]+.geojson" );

std::string dir_EU4 = "EU4_AZGAAR";
std::string dir_countries = dir_EU4 + "/" + "countries";
/* Structure: EU4
common
	bookmarks
		a_new_world.txt
	colonial_regions
		00_colonial_regions.txt
	countries
	country_colors
		00_country_colors.txt
	country_tags
		00_countries.txt
	cultures
		00_cultures.txt
	government_names
		00_government_names.txt
		01_government_names.txt
		zz_default_government_names.txt
	province_names
	...
*/
/* Structure: ANBENNAR
*/

const std::string cell_file = "cell_map.geojson";
const std::string cell_file_t = "cell_map_t.geojson";
const std::string file_test = "file_test.txt"; // for testing if comparisons work

int main() {
CreateThread(NULL, 0, CheckEscape, NULL, 0, NULL);			// FOR ESC EXIT
/*################################################################################################*/
/*################################################################################################*/
try {
std::vector<cell_info>	all_cells;					// holds all cell info
std::string file_info;
std::string CellNeighbor_str;
std::fstream fileStream;
//std::cout << VERSION_STAMP << std::endl;

VUCO( "", VERSION_STAMP );
/*################################################################################################*/
/*################################################################################################*/
// First, want to ensure directories. Theres information to be gotten from AZGAAR, and there is information to be placed in EU4
//std::cout << "\nAffirming AZGAAR directory...";

	VUCO( "", "Loading settings..." );
	settings options;

	VUCO("", "Affirming AZGAAR directory..." );
	EnsureDirectory(dir_azgaar); // First, have to ensure top  folder directory
	//std::cout << "\Retrieving Cell path...";
	/*
	VUCO( "", "Retrieving Cell Path...");
	std::smatch cell_file_name;
	std::string temp;
	for (const auto& entry : fs::directory_iterator( dir_azgaar )) {
		temp = entry.path().string();
		std::regex_search( temp, cell_file_name, std::regex("\[\\w\]+ Cells \[0-9^-\]+.geojson") );
		if (cell_file_name.empty() == FALSE) {
			break;
		}
	}
	if (cell_file_name.empty() == TRUE) {
		throw std::runtime_error("Couldn't find needed file XXX Cells DDDD.geojson");				
	}	
	*/
	std::string cell_path = FindFileDirectory(dir_azgaar, std::regex( "\[\\w\]+ Cells \[0-9^-\]+.geojson" ) );
	std::string culture_path = FindFileDirectory( dir_azgaar, std::regex( "\[\\w\]+ Cultures \[0-9^-\]+.csv" ) );
	std::string namesbase_path = FindFileDirectory( dir_azgaar, std::regex( "\[\\w\]+ Namesbase \[0-9^-\]+.txt" ) );
	std::string religions_path = FindFileDirectory( dir_azgaar, std::regex( "\[\\w\]+ Religions \[0-9^-\]+.csv" ) );
	std::string state_path = FindFileDirectory( dir_azgaar, std::regex( "\[\\w\]+ States \[0-9^-\]+.csv" ) );
	std::string burg_path = FindFileDirectory( dir_azgaar, std::regex( "\[\\w\]+ Burgs \[0-9^-\]+.csv" ) );
	//VUCO( "", cell_path );
	//cell_path = OpenFileReturnString( dir_cells ); // Trying to read for specific file (end in .geojson) within the dir_cells AND that there is only one file in it																												
	EnsureDirectory( dir_EU4 ); // EU4 top  folder directory										
	// HAVE IT OUTPUT FILES THAT ARE NEEDED
			//(so first execution it will create all the directories it will grab from and output that it needs 
			//X_states.csv here and so on, next iteration it will continue successfully,  find and open

	// should do a search for a cell_file that would come from AZGAAR and be placed in the AZGAAR directory.
		// should also do this for every other possible file (e.g. States.csv, and so on. Issue is that their names will be long strings of info and end in states.csv or something similar)
	//std::string wanted_file = dir_azgaar + "/" + cell_file;
		// After ensuring directories exist, want to start with reading from AZGAAR cell info
/*########################		 INFO GATHERING		 		   ###################################*/
/*################################################################################################*/
	ReadFromPlaceInto(cell_path, file_info);
	//std::cout << "\nRead from " << cell_path;
	{std::string vuco_temp = "Read from" + cell_path;
	VUCO( "", vuco_temp );
	}

	// READ FROM CELL_MAP or string, EXTRACT VERTEX DATA, ID DATA, and so on
	std::tuple<int, int, int, int> extents; // should be: left, right, top, bottom
	extents = ParseStringUpdateCells(all_cells, file_info); // left, right, top, bottom



// Have all cell info, time to transform into EU4 shape/dimensions

/*######################	WORKING WITH THE MAP			######################################*/
/*################################################################################################*/

	std::vector<burg_info> all_burgs;	// all burgs X and Y point, need to convert two decimal float to int
	// Regex: [^,]*,
	// C++ regex: \[^,\]*,
	// note that all will have comma at end

	
	all_burgs = BurgParse( burg_path );
	//VUCO( "", all_burgs[0].capital );
	{
		std::string capital = "capital";
		VUCO ( "Capital?", all_burgs[0].capital, TRUE );
		int value = capital.compare ( all_burgs[0].capital );
		VUCO ( "COMPARE RESULTS", value, TRUE);
	
	
	}
	// get burgs, their population, then include/measure with cell_info

	// burgs have an ID, a name, a province, province full name, state, state full name, culture, religion, population, latittude, longitude, elevation, capital, port, citadel, walls, plaza, temple, shanty town, and city generator link

	TransformPoints( 5632, 2048, all_burgs, all_cells, extents );
	//TransformPoints_NoStretch ( all_burgs, all_cells, extents );
	//TransformPoints ( 5632, 2048, all_burgs, extents );
	
	// Create Map using ID of all_cell element and correspond it to the cell_info
	// New Array where the index matches ID of cell (done using map)
	std::unordered_map <int, cell_info> indexed_cells;
	int all_cells_size = all_cells.size();
	for (int t_itr = 0; t_itr < all_cells_size; t_itr++) {
		indexed_cells.emplace( all_cells[t_itr].id, all_cells[t_itr] );
	}

	std::unordered_map <int, burg_info> indexed_burgs;
	int all_burgs_size = all_burgs.size ();
	for (int t_itr = 0; t_itr < all_burgs_size; t_itr++) {
		indexed_burgs.emplace ( all_burgs[t_itr].id, all_burgs[t_itr] );
	}

	// Map each burg to a cell ID
	
//	auto all_burgs_copy = all_burgs;

	/*
	//################################################################################################//
										ISSUE
		Transform Points
		? What if map provided is an island? So the map could be like 5000 x 2000, but the cells only
		exist within (2500,1000), (2500,1500), (2000,1000), (2000,1500)

		? Is there a need for stretching? Or even, how do you know you should stretch the points?

	//################################################################################################//


	*/

	std::vector<int> index_list_of_cells_with_burgs = AssignBurgsToCells (all_burgs,all_cells);

	// burg ID corresponds to location within all_burgs -1 (so burg id of 1 is at all_burgs[0])

	std::vector<province_info> all_provinces = CreateProvinces ( all_cells );

/*##########################      WORKING WITH THE CULUTRES      #################################*/
/*################################################################################################*/

	// all cultures
	std::vector<culture> all_cultures;
	all_cultures = CultureParse( culture_path );
	std::unordered_map <int, culture> all_cultures_map;
	int all_cultures_size = all_cultures.size ();
	for (int t_itr = 0; t_itr < all_cultures_size; t_itr++) {
		all_cultures_map.emplace ( all_cultures[t_itr].id, all_cultures[t_itr] );
	}

/*####################		MAKING OF THE NAMEBASES		            ##############################*/
	VUCO( "", "Getting Namesbases..." );
	std::vector<culture_namebase> all_namebases;

	std::vector<std::string> namebase_file_lines;
	namebase_file_lines = ReadFromLineByLine( namesbase_path );
	NamebaseParse( namebase_file_lines, all_namebases );
	/*{
		std::string vuco_temp = all_namebases[0].fn_MakeWordAzgaar( 5, 12, "" );
		VUCO( "", vuco_temp );
	}*/





	// create unordered map of namebase using name as key, enables cultures to use namebase easily
	std::unordered_map <std::string, culture_namebase> all_namebase_map;
	int all_namebases_size = all_namebases.size();
	for (int t_itr = 0; t_itr < all_namebases_size; t_itr++) {
		all_namebase_map.emplace( all_namebases[t_itr].name, all_namebases[t_itr] );
	}

/*####################	CALCULATE RELATED CULTURES BASED ON ORIGINS ##############################*/

	if (options.CULTURE_BREAKDOWN_STATES == TRUE && options.CULTURE_BREAKDOWN_PROVINCES == TRUE) {
	
		// Take culture from all_cultures, make it the culture group
		std::unordered_map<int,culture_union> all_culture_unions;

		std::vector<culture> additional_cultures;
		int new_culture_ids = all_cultures.size ();	// start new culture id with size of all_cultures
		for (auto& each_culture : all_cultures) {
			culture_union new_culture_union;
			
			new_culture_union.id			=	each_culture.id;
			new_culture_union.color_rgb[0]	=	each_culture.color_rgb[0];
			new_culture_union.color_rgb[1]	=	each_culture.color_rgb[1];
			new_culture_union.color_rgb[2]	=	each_culture.color_rgb[2];
			new_culture_union.type			=	each_culture.type;
			new_culture_union.namesbase		=	each_culture.namesbase;
			new_culture_union.origins		=	each_culture.origins;
			new_culture_union.name			=	each_culture.name;
			//new_culture_union.primary		=	each_culture.primary;
		
			all_culture_unions.emplace ( each_culture.id, new_culture_union );
		}
		// Having made each culture group, make a new subculture based on each province/state pairing that the culture is present at
		// Construct a list of unique cell_info.country and cell_info.subcountry pairings and the culture 
		// country,subcountry,culture
		std::unordered_map<std::string, short>	unique_cultures;
		std::unordered_map<std::string, short> unique_state_province_and_new_culture;
		for (auto& each_cell : all_cells) {
			std::string string_country = std::to_string ( each_cell.country );
			std::string string_subcountry = std::to_string ( each_cell.sub_country );
			std::string temp_key = string_country + string_subcountry;

			if(		(unique_cultures.emplace ( temp_key, each_cell.culture ).second)	) { // if emplacement successful

				culture new_culture;

				new_culture = all_cultures_map[each_cell.culture];
				new_culture.id = new_culture_ids;
				unique_state_province_and_new_culture.emplace ( temp_key, new_culture.id );
				
				additional_cultures.push_back ( new_culture );
				all_culture_unions[each_cell.culture].subcultures.push_back ( new_culture );

				each_cell.culture = new_culture_ids;
				new_culture_ids++;
			}
			else {	// Can't emplace, thus exists already and cell culture needs updated
				each_cell.culture = unique_state_province_and_new_culture[temp_key];
			}
			
		}
		// Now all cells have cultures dependendent on state,province, and original culture
		// Update culture mapping to only include additional cultures (all_culture = additional_culture);
		all_cultures.clear ();
		all_cultures = additional_cultures;

		all_cultures_map.clear();
		all_cultures_size = all_cultures.size ();
		for (int t_itr = 0; t_itr < all_cultures_size; t_itr++) {
			all_cultures_map.emplace ( all_cultures[t_itr].id, all_cultures[t_itr] );
		}
		
		// Need to generate name lists for each unique culture (now all_cultures)
		for (auto& each_culture : all_cultures) {

			std::string doubles = all_namebase_map[each_culture.namesbase].doubled_letters;
			int letters_min = all_namebase_map[each_culture.namesbase].min_length;
			int letters_max = all_namebase_map[each_culture.namesbase].max_length;

			for (int x = 0; x <= 20;x++) {
			
				each_culture.male_names.push_back (		all_namebase_map[each_culture.namesbase].fn_MakeWordAzgaar ( letters_min, letters_max, doubles )	);
				each_culture.female_names.push_back (	all_namebase_map[each_culture.namesbase].fn_MakeWordAzgaar ( letters_min, letters_max, doubles )	);

			}
			for (int x = 0; x <= 15; x++) {
				
				each_culture.dynasty_names.push_back (	all_namebase_map[each_culture.namesbase].fn_MakeWordAzgaar ( letters_min, letters_max, doubles )	);
			
			
			}
		
		
		}
	
	
	}

/*####################	?? MAP TECH GROUPS BASED ON ORIGINS??		##############################*/

/*####################	CULTURE DIVISION BASED ON STATE+PROVINCE DIVISION			##############################*/
/*####################	?? MAP TECH GROUPS BASED ON CULTURE DIVISION, USING ROOT CULTURE AS DICTATING??		##############################*/

	// ex
/*###########################   WORKING WITH THE STATES   ########################################*/
/*################################################################################################*/
	// all states
	std::vector<state_info> all_states;
	all_states = StateParse( state_path );	// Copy operation?

/*###########################   Breakdown section??      ########################################*/
	
	// Get unique TAGS
	std::unordered_set<std::string> all_tags;
	all_tags = TAGParse( all_states ); // Tag resolution. States are also assigned state.TAG

	// Map state ID from AZGAAR to EU4 TAG
	std::unordered_map<short, std::string> ID_to_TAG;
	for (auto& state_itr : all_states) {
		ID_to_TAG.emplace ( state_itr.ID, state_itr.TAG );
	
	}


// RETRIEVE EMBLEMS
/*################################################################################################*/

	// https://armoria.herokuapp.com/?format=png&size=147&shield=square	// Need to trim transparent edge off
	//https://github.com/Azgaar/armoria-api#readme

	VUCO ( "FLAGS", "Flags should be generated in square format", TRUE );
	VUCO ( "FLAGS", "Unfortunately, retrieving and rendering .svg files is out of the scope of this application", TRUE );
		// either read it via program and batch/series of files
		// or ASK USER TO DOWNLOAD ALL STATE PNG AND RENAME TO STATE
		// or ASK USER TO ADD EXTENSION TO DO THE RETRIEVAL AND RENAMING automatic
		// Also ask user to get armoria and download flags from there
	
// CREATION OF FLAGS
/*################################################################################################*/

	VUCO ( "FLAGS", "Use external resource ARMORIA to generate flags", TRUE );
	VUCO ( "FLAGS", "Generate at least 700 flags of size 128x128", TRUE );
	VUCO ( "FLAGS", "Recommended settings: 1920x1080 screen, GIANT gallery, NO SIMPLE shield, NO gradient, black border of thickness 1, scale 1.6", TRUE );
	VUCO ( "FLAGS", "Export as PNG, place within flags folder. You should do this 3 or 4 times, and thus will have 3 or 4 .png files", TRUE );

// EU4 needs 128x128 TGA files with TAG.tga format
	// Armoria: on a 1920x1080 screen: GIANT gallery, NO SIMPLE shield,NO gradient,1 black border, 1.6 scale
	// Export24 as PNG (?JPEG?)

	// Europa Universalis IV / gfx / flags

	/*
	dontUseModulesInTheFuture();

	cv::Mat single_image = openAndRead();
	std::vector<cv::Mat>images = splitImage( single_image, 24, 12 );
	showAnImage( images[0] );
	showAnImage( images[1] );

	*/
// CREATION OF MAIN CULTURES
/*################################################################################################*/

	// Europa Universalis IV / commmon / cultures / 00_cultures.txt
	/*
	custom_culture_group = {
			graphical_culture = westerngfx
			custom_culture_1 = {			// This serves to provicde unique names for culture in gorup
				primary = CUT
				male_names = {
					MaleName1 MaleName2 MaleName3
					"Male Name 1" "Male Name 2" "Male Name 3"
				}
				female_names = {
					FemaleName1 FemaleName2 FemaleName3
					"Female Name 1" "Female Name 2" "Female Name 3"
				}
				dynasty_names = {
					DynastyName1 DynastyName2 DynastyName3
					"Dynasty Name 1" "Dynasty Name 2" "Dynasty Name 3"
				}
			}
			custom_culture_2 = {
				primary = CUC
				male_names = {
					MaleName4 MaleName5 MaleName6
					"Male Name 4" "Male Name 5" "Male Name 6"
				}
				female_names = {
					FemaleName4 FemaleName5 FemaleName6
					"Female Name 4" "Female Name 5" "Female Name 6"
				}
				dynasty_names = {
					DynastyName4 DynastyName5 DynastyName6
					"Dynasty Name 4" "Dynasty Name 5" "Dynasty Name 6"
				}
			}
			custom_culture_3 = {
				primary = CUL
				male_names = {
					MaleName4 MaleName5 MaleName6
					"Male Name 4" "Male Name 5" "Male Name 6"
				}
				female_names = {
					FemaleName4 FemaleName5 FemaleName6
					"Female Name 4" "Female Name 5" "Female Name 6"
				}
				dynasty_names = {
					DynastyName4 DynastyName5 DynastyName6
					"Dynasty Name 4" "Dynasty Name 5" "Dynasty Name 6"
				}
			}
		}
	}
	*/

// BURG LOCATION AND TYING TO PROVINCES
/*################################################################################################*/

// ASSIGN DEVELOPMENT TO PROVINCES
/*################################################################################################*/
	if (options.DEVELOPMENT_TRUE_POP_OR_FALSE_RANDOM == TRUE) 
	{ 
		// DEVELOPMENT will be based off pop-weights and population
		for (auto& each_province : all_provinces) {
			int total_population = 0;
			int burg_population = 0;
			int rural_population = 0;
			for (auto& each_cell : each_province.cell_ids) {
				total_population += indexed_cells[each_cell].pop;
				burg_population += indexed_burgs[indexed_cells[each_cell].burg_id].pop;
			}
			rural_population = total_population - burg_population;

			each_province.base_dev[0] = 1+static_cast<unsigned char>(total_population * options.DEVELOPMENT_POP_WEIGHTS[0]);
			each_province.base_dev[1] = 1+static_cast<unsigned char>(burg_population * options.DEVELOPMENT_POP_WEIGHTS[1]);
			each_province.base_dev[2] = 1+static_cast<unsigned char>(rural_population * options.DEVELOPMENT_POP_WEIGHTS[2]);
		
		
		
		
		}

	}
	else /* if DEVELOPMENT_TRUE_POP_OR_FALSE_RANDOM == FALSE */
	{
	
	}

	if (options.USE_BURGS_CSV_FOR_DEVELOPMENT == TRUE) {

		// ? Is it possible to just see if the variable is empty instead of comparing the strings?
		// ? Would it be possible to just do this for provinces that have cells that have cities? index_list_cells_with_burgs ?

		std::string capital = "capital";
		std::string port = "port";
		std::string citadel = "citadel";
		std::string walls = "walls";
		std::string plaza = "plaza";
		std::string temple = "temple";
		std::string shanty = "shanty";

		for (auto& each_province : all_provinces) {
			int adm = 0;
			int dip = 0;
			int mil= 0;

			for (auto& each_cell : each_province.cell_ids) {
			
				if (capital.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].capital ) == 0)	{	adm += options.DBV[0][0];	dip += options.DBV[0][1];	mil += options.DBV[0][2]; }
				if (port.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].port ) == 0)			{	adm += options.DBV[1][0];	dip += options.DBV[1][1];	mil += options.DBV[0][2]; }
				if (citadel.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].citadel ) == 0)	{	adm += options.DBV[2][0];	dip += options.DBV[2][1];	mil += options.DBV[0][2]; }
				if (walls.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].walls ) == 0)		{	adm += options.DBV[3][0];	dip += options.DBV[3][1];	mil += options.DBV[0][2]; }
				if (plaza.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].plaza ) == 0)		{	adm += options.DBV[4][0];	dip += options.DBV[4][1];	mil += options.DBV[0][2]; }
				if (temple.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].temple ) == 0)		{	adm += options.DBV[5][0];	dip += options.DBV[5][1];	mil += options.DBV[0][2]; }
				if (shanty.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].shanty ) == 0)		{	adm += options.DBV[6][0];	dip += options.DBV[6][1];	mil += options.DBV[0][2]; }

			}


			each_province.base_dev[0] += adm;
			each_province.base_dev[1] += dip;
			each_province.base_dev[2] += mil;
		}
	
	}

	if (options.USE_BURGS_CSV_FOR_BUILDINGS == TRUE) {
	
		std::string capital = "capital";
		std::string port = "port";
		std::string citadel = "citadel";
		std::string walls = "walls";
		std::string plaza = "plaza";
		std::string temple = "temple";
		std::string shanty = "shanty";

		for (auto& each_province : all_provinces) {
			int adm = 0;
			int dip = 0;
			int mil= 0;

			for (auto& each_cell : each_province.cell_ids) {
			
				//if (capital.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].capital ) == 0)	{	adm += 2;	dip += 2;	mil += 2;	}
				if (port.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].port ) == 0)			{ each_province.shipyard = TRUE; }
				if (citadel.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].citadel ) == 0)	{ each_province.fort_15th = TRUE; }
				if (walls.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].walls ) == 0)		{ each_province.fort_15th = TRUE; }
				if (plaza.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].plaza ) == 0)		{ each_province.center_of_trade = 1; }
				//if (temple.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].temple ) == 0)		{	adm += 2;							}
				//if (shanty.compare ( indexed_burgs[indexed_cells[each_cell].burg_id].shanty ) == 0)		{	adm += 1;	dip += 1;				}

			}
		}
	}

// ASSIGNMENT OF CULTURE(AND NAME)/STATE/RELIGION/CORES TO PROVINCES
/*################################################################################################*/

// ASSIGNMENT OF NAMES TO PROVINCES
/*################################################################################################*/

// CREATION OF PROVINCES / SEA REGIONS (AND UNIQUE COLOR FOR EACH)
/*################################################################################################*/


	// https://eu4.paradoxwikis.com/Geographical_list_of_provinces

	// Europa Universalis IV / history / provinces / [PROV_ID] - [PROVINCE_NAME].txt

	/*
	owner = SWE
	controller = SWE
	add_core = SWE
	add_core = FIN
	culture = finnish
	religion = catholic
	hre = no
	base_tax = 1
	base_production = 1
	trade_goods = fur
	base_manpower = 1
	capital = "Tavastehus"
	is_city = yes
	#fort_15th = yes
	discovered_by = western
	discovered_by = eastern
	*/

	/*
	for( auto &cell : all_cells){
	// Create file in directory
	std::string target;
	// target = MOD_PATH_DIR + FORMATTED_INFO + ".txt"	// should look like "Baierbia/history/provinces/50 - Spannor.txt"
	std::ofstream out(target);


	}






	*/
	
	
// CREATION OF COUNTRIES
/*################################################################################################*/

// check C:\Program Files (x86)\Steam\steamapps\workshop\content\236850\2325242514\

	//for (auto& each_state : all_states) {
		// Create file > / Europa Universalis IV / common / countries / [COUNTRY_FULLNAME].txt
		// Resolve graphical_culture
		// Resolve Color
		// Resolve historical_idea_groups
		// Resolve historical_units
		// Generate some Monarch Names
		// Generate some Leader names
		// Generate some ship names
		// Generate Army names
		// Generate Fleet names
	
	
		// Create File > / Europa Universalis IV / history / countries / [TAG] - [COUNTRY_FULLNAME].txt
		// Resolve Government
		// Resolve adding government reforms
		// Resolve government rank (is optional)
		// Resolve mercantilism (is optional)
		// Resolve technology_group
		// Resolve religion
		// Resolve primary culture
		// Resolve adding accepted cultures
		// Resolve capital province ID
	//}

	//Country File / Europa Universalis IV / common / countries / [COUNTRY_FULLNAME].txt
	/*
	graphical_culture = westerngfx
	color = { 157  51  167 }
	historical_idea_groups = {
	defensive_ideas
	offensive_ideas
	religious_ideas
	economic_ideas
	diplomatic_ideas
	innovativeness_ideas
	spy_ideas
	trade_ideas
	}
	historical_units = {
	western_medieval_infantry
	western_medieval_knights
	western_men_at_arms
	swiss_landsknechten
	dutch_maurician
	austrian_tercio
	austrian_grenzer
	austrian_hussar
	austrian_white_coat
	prussian_uhlan
	austrian_jaeger
	mixed_order_infantry
	open_order_cavalry
	napoleonic_square
	napoleonic_lancers
	}
	monarch_names = {
	"Leopold #1" = 100
	"Femalia #1" = -1
	}
	leader_names = {
	Leman
	}
	ship_names = {
	"Comte de Smet de Nayer"
	}
	army_names = {
	"Armee von $PROVINCE$"
	}
	fleet_names = {
	"Stadtflotte"
	}
	*/

	//Country History / Europa Universalis IV / history / countries / [TAG] - [COUNTRY_FULLNAME].txt
	/*
				government = absolute_monarchy	
				add_government_reform =			// Special reforms?
				government_rank =				// Empire? Kingdom? Duchy?
				mercantilism = 10
				technology_group = western
				religion = catholic
				primary_culture = flemish
				add_accepted_culture =
				capital = 90	# Antwerp
				// fixed_capital = 90 # Antwerp // can't move away from this province, no cost to move to this province

	*/


	// CHINA MECHANICS

		// add_government_reform = celestial_empire
		// government_rank = 3

		// EUIV / events / ChineseFactions.txt
		// EUIV / events / ChineseEmpire.txt

	// SHOGUN MECHANICS
	
		// EUIV / history / diplomacy / [Shogunate].txt
		// EUIV / events / Japan.txt
		// EUIV / events / flavorJAP.txt
		// EUIV / events / flavorDaimyo.txt

	// HRE MECHANICS
		
		// EUIV / history / diplomacy / [holy_roman_empire].txt


	// EUIV / common / country_tags / 00_countries.txt
	// EUIV / common / country_tags / [phrase_mod].txt
	// EUIV / common / country_colors / 00_country_colors.txt

	/* EX from ANBENNAR
	A01	= "countries/Lorent.txt"
	A02	= "countries/Deranne.txt"
	A03	= "countries/Redglades.txt"
	A04	= "countries/Wesdam.txt"
	[TAG] = "countries/[COUNTRY_NAME].txt"
	...
	*/


// DIPLOMACY
/*################################################################################################*/

	// EUIV / history / diplomacy / [A phrase, mainly for personal reference].txt
	
// CREAITON OF RELIGIONS https://eu4.paradoxwikis.com/Religion_modding
/*################################################################################################*/
	// EUIV / common / religious_conversions / 00_religious_conversions.txt
	// EUIV / common / religions / 00_religions.txt
	
// factions? https://eu4.paradoxwikis.com/Faction_modding
	
// government modding?
	
// CREATION OF TRADE ZONES
/*################################################################################################*/

	// EUIV / common / tradenodes / 00_tradenodes.txt
	// EUIV / common / trade_companies / 00_trade_companies.txt
	
// CREATION OF COLONIAL REGIONS
/*################################################################################################*/

	// EUIV / common / colonial_regions / 00_colonial_regions.txt

// FIXING
/*################################################################################################*/

	// EUIV / common / triggered_modifiers / 00_triggered_modifiers.txt
	// EUIV / common / scripted_triggers/	00_scripted_triggers.txt
	// EUIV / common / scripted_triggers/	00_scripted_triggers_startup_screen.txt
	// EUIV / common / scripted_triggers/	01_scripted_triggers_province_modifiers.txt
	// EUIV / common / scripted_effects/	01_scripted_effects_for_on_actions.txt
	// EUIV / common / revolt_triggers / 00_revolt_triggers.txt

	// EUIV / common / rebel_types
	// EUIV / common / province_triggered_modifiers / 00_modifiers.txt
	// ? province_names?
	// EUIV / common / on_actions / 00_on_actions.txt
	// EUIV / common / natives / 00_natives.txt
	// EUIV / common / mercenary_companies / 00_mercenaries.txt
	// EUIV / common / insults / 00_insults.txt
	// EUIV / common / institutions / 00_Core.txt
	// EUIV / common / holy_orders / 00_holy_orders.txt
	// EUIV / common / defender_of_faith / 00_defender_of_faith.txt
	// EUIV / common / ages / 00_default.txt

	// EUIV / events

	// EUIV / decisions

	// EUIV / history / wars

	// EUIV / missions

	// EUIV / localisation


// Information calculated, time to output into EU4 formats and such
	

//GenericOutput(all_cells, "log2.txt");

	// HAVE TO GENERATE SEABOARD (make grid of hexagons that span the world, write them first, have them "replace" the cells that they take up and their neighbors (so land cells that border ocean cells (i.e. have ocean cells as neighbors) will instead have this new cell as a neighbor (or not even a cell, maybe have it as a sea province)
	// could have centers equally spaced through the map and make a new DrawHexagonCenteredHere()
	// HAVE TO DRAW SEABOARD BEFORE NON-OCEAN PROVINCES
	// HAVE TO MERGE LAND CELLS INTO PROVINCES (most likely 2 or 3, average size straight out of AZGAAR and into rendering is ~100 px. Avg size in EU4 is ~200 Europe, ~350 elsewhere
	// prolly want to track the size of the various polygons that are rendered and centroids
	// DEAD SPACE (e.g. Greenland, Australia, etc.)
	// CREATING THE IMAGE
	// FOLLOWING IS FOR EXAMPLE PURPOSES! FIRSTLY: PROVINCE ID NEEDS TO BE UNIQUELY MAPPED TO COLOR_RGB TO ENUSRE THAT THERE ARE NO REPEATS
	// NOTE THAT THE VERTICIES CONTAIN A DUPLICATE VALUE OF THE FIRST COORD INITIALLY PUT INTO THEM (just the way it is output from AZGAAR). IT WILL NOT BE USED IN RASTERIZATION because the DrawPolygon ignores duplicates (effectively)

/*###########################      CREATING THE IMAGES          ##################################*/
/*################################################################################################*/
	//VUCO( "", "Creating image" );
	//std::random_device rd; // obtain random number from hardware
	//std::mt19937 gen( rd() ); // seed generator
	//std::uniform_int_distribution<> distrib( 0, 255 ); //define the range // distrib(gen)


// EUIV / map

// CREATE continent.txt

// CREATE default.map (text file)

// CREATE definition.csv

// CREATE positions.txt

// CREATE region.txt

// CREATE superregion.txt

// CREATE rivers.bmp

// CREATE terrain.bmp

// CREATE terrain.txt

// CREATE world_normal.bmp	// needs to be 1/2 of dimensions of full scale map [2816 x 1024]

// CREATE heightmap.bmp
// Issue: Heightmap is not working correctly
// Cause : You have an gradient that is too extreme.Don’t go from 100 to 200 without steps in between.

// CREATE province.bmp
// province colors HAVE TO BE UNIQUE! Just like TAGS

// CREATE area.txt

// .dds -> 8.8.8.8 ARGB 32bpp (or bit) profile with no mipmaps.
// or maybe 8.8.8.8 16 bit ARGB with mipmaps. according to https://www.reddit.com/r/hoi4modding/comments/bk8umn/proper_way_to_save_dds_files/, needs verified
// needs to be 1/2 of dimensions of full scale map [2816 x 1024]
// must use Nearest Neighbour to maintain pixel-perfect accuracy.

// CREATE colormap_water.dds	// land is like RGB 19,216,216; coast is 14,97,110; deep ocean is 5,18,36; ocean is 8,54,60
VUCO( "DDS", "FIND IMAGE colormap_water.bmp AND CONVERT TO DDS USING PAINT.NET" );

// CREATE climate.txt

// CREATE trees.bmp
VUCO( "DDS", "FIND IMAGE trees.bmp AND CONVERT TO DDS USING PAINT.NET" );
// CREATE colormap_[SEASON].dds in EUIV / map / terrain
VUCO( "DDS", "FIND IMAGES colormap_SEASON.bmp AND CONVERT TO DDS USING PAINT.NET" );
// CREATE colormap_[SEASON].dds in EUIV / map / random

// CREATE lakes.txt in EUIV / map / lakes / 00_lakes.txt

	ScreenRaster EU4_MAP( 5632, 2048 );

	//std::cout << "\nGenerating polygonmap from all_cells...";
	VUCO( "", "Generating polygonmap from all_cells..." );
	for (int dp_itr = 0; dp_itr < all_cells.size() - 1; dp_itr++) {
		int height_col = (3248+all_cells[dp_itr].height)/99;	// shift up by 3248 to be purely positive height, divide by 99 to be 0 to 255.6 (0.6 gets truncated off)
		IPixel color_rgb( height_col, height_col, height_col );

		//IPixel land( 0xFFFFFF );
		//IPixel water( 0x000FFF );

		RPoly temp_poly;
		//RPoly temp_poly2;									// TEMP
		temp_poly.points = all_cells[dp_itr].verticies;


		if (all_cells[dp_itr].biome == 0) {
			color_rgb.b = 255;
			color_rgb.g = 255;
		}
		else {
			color_rgb.b = 0;
			color_rgb.g = 125;
		}


		//temp_poly2.points = all_cells[dp_itr+1].verticies; // TEMP, ALSO CHANGE size()-1 to size()
		//temp_poly.MergePoly(temp_poly2);
		DrawPolygon( &temp_poly, &color_rgb, EU4_MAP );
	}

	// GenerateCoastalPolygons
	// GenerateSeaboardPolygons
	// If we draw a hexagon grid
	ScreenRaster heightmap_bmp = CreateHeightmap( all_cells );
	// Draw gradient on heightmap? Blur?
	// Add texture to heightmap? For land/mountain areas, then for ocean, then for coastal?
	heightmap_bmp.Export8( "heightmap.bmp" ,1);
	heightmap_bmp.grid_vector = VectorizeGrid ( heightmap_bmp.grid );
	AddHeightNoise (heightmap_bmp.grid_vector,0,95,0,95,1);
	AddHeightNoise ( heightmap_bmp.grid_vector, 95, 255, 95, 255, 1 );
	heightmap_bmp.RenderPixels ( heightmap_bmp.grid_vector );
	heightmap_bmp.Export8 ( "heightmap_randomized.bmp", 1 );

	ScreenRaster normal_bmp = CalculateNormal(heightmap_bmp);
	Image normal_export( normal_bmp.width, normal_bmp.height );
	normal_export.MapRaster( normal_bmp );
	normal_export.Export24("normal.bmp");
	
	Image EU4_MAP_BMP( 5632, 2048 );
	//std::cout << "\nMapping polygons to EU4 Map...";
	VUCO( "", "Mapping polygons to EU4 map...");
	EU4_MAP_BMP.MapRaster( EU4_MAP );
	//std::cout << "\nCreating bmp...";
	VUCO( "", "Creating bmp...");
	EU4_MAP_BMP.Export24( "eu4_map.bmp" );

/*###########################      BOOKMARK CREATION			##################################*/
/*################################################################################################*/

	// EUIV / common / bookmarks / [a_phrase].txt

	/*
	bookmark =
{
	name = "LILACWARS_NAME"
	desc = "LILACWARS_DESC"
	date = 1444.11.11
	
	center = 8
	default = yes
	
	country = A01	#Lorent
	country = A02	#Deranne
	
	country = A04	#Wesdam
	country = A11	#Pearlsedge
	
	country = A12	#Beepeck
	country = A13	#Gawed
	
	country = A46	#Arbaran
	country = A25	#Damescrown
	country = A62	#Telgeir
	
	country = A85	#Magisterium
	country = A45	#Istralore
	country = A30	#Wex
	country = A72	#Arannen
	
	country = A33	#Verne
	country = A29	#Busilar

	easy_country = A04	#Wesdam
	easy_country = A11	#Pearlsedge
	easy_country = A13	#Gawed
	easy_country = A45	#Istralore
	easy_country = A72	#Arannen
	easy_country = A33	#Verne

}
	*/

/*###########################      .mod FILE CREATION			##################################*/
/*################################################################################################*/

	/*
	replace_path = "common/bookmarks"
	replace_path="common/province_names"
	replace_path="common/government_names"
	replace_path="common/disasters"
	replace_path="common/rebel_types"
	replace_path="common/countries"
	replace_path="common/mercenary_companies"
	replace_path="events"
	replace_path="missions"
	replace_path="decisions"
	replace_path="history/diplomacy"
	replace_path="history/countries"
	replace_path="history/wars"
	replace_path="history/provinces"
	replace_path="history/advisors"
	replace_path="gfx/loadingscreens"
	*/


/*################################################################################################*/
/*################################################################################################*/
	// Anbennar map:
	// province.bmp is 5632 x 2048
	// land tile ranges from ~150 to ~400 typically
	// ocean tiles range from ~3,000 coastal to ~40,000 open ocean
	//

	// EU4 map:
	// 5632 x 2048
	// land tile ranges from ~200 in Germany, ~300 France, ~600 Eastern Europe, ~350 India, ~700 China, ~200 Mexico
	// land RGB typically floored at RGB 10,10,10 and range to 200,200,200
	// ocean tiles range from ~3,000 coastal to ~30,000 open ocean
	// ocean RGB typically floored at RGB 0,200,200. values range to 150,252,252
	//

	// AZGAAR
	// Map is constructed by means of XY coordinates and polygons
	// Population = 0, State ID of 0, Province ID of 0, Culture ID of 0, Religion ID of 0 -> uncolonizeable
	// Type of 1 = ocean tile
	// Biome = Marine -> Lake
	//

	// Want to:
	// Render a cell onto a province picture
	// province needs to have specific RGB, this has to be unique and tied to its ID
	// province id's need to be iterative (so grouping up cells to merge them into a single province, where would the id's go? couldn't use the cell id's as province ids)
	//
/*################################################################################################*/

}
catch (std::runtime_error runtime) {		// managing file opening error
	std::cerr << "Runtime Error:" << runtime.what() << std::endl;
	std::cerr << "\nEARLY END";
	system ( "pause>0" );
	return 0;
}//end of catch for runtime error

std::cout << "\n[ ] Program End. Enjoy!" << std::endl;
#ifdef _DEBUG
	system("pause>0");
#else
#endif
	return 0;
}	// End of main()

