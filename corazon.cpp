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
#define		VERSION_STAMP	"V 0.390"
// Most recent change: Moving files into ../UVEP/
// Most recent goal
#define		DEBUG	// for VUCO logging and for ending pause

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

	// ISSUE!!! WITH BURGPARSE
	// all_burgs = BurgParse( burg_path );
	// VUCO( "", all_burgs[0].capital );

	// get burgs, their population, then include/measure with cell_info

	// burgs have an ID, a name, a province, province full name, state, state full name, culture, religion, population, latittude, longitude, elevation, capital, port, citadel, walls, plaza, temple, shanty town, and city generator link

	TransformPoints( 5632, 2048, all_cells, extents );
	
	// Create Map using ID of all_cell element and correspond it to the cell_info
	// New Array where the index matches ID of cell (done using map)
	std::unordered_map <int, cell_info> indexed_cells;
	int all_cells_size = all_cells.size();
	for (int t_itr = 0; t_itr < all_cells_size; t_itr++) {
		indexed_cells.emplace( all_cells[t_itr].id, all_cells[t_itr] );
	}

/*##########################      WORKING WITH THE CULUTRES      #################################*/
/*################################################################################################*/

	// all cultures
	std::vector<culture> all_cultures;
	all_cultures = CultureParse( culture_path );

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

	// ex
/*###########################   WORKING WITH THE STATES   ########################################*/
/*################################################################################################*/
	// all states
	std::vector<state_info> all_states;
	all_states = StateParse( state_path );	// Copy operation?

/*###########################   Breakdown section??      ########################################*/
	
	std::unordered_set<std::string> all_tags;
	all_tags = TAGParse( all_states ); // Tag resolution

/*################################################################################################*/
/*################################################################################################*/
// RETRIEVE EMBLEMS
		// either read it via program and batch/series of files
		// or ASK USER TO DOWNLOAD ALL STATE PNG AND RENAME TO STATE
		// or ASK USER TO ADD EXTENSION TO DO THE RETRIEVAL AND RENAMING automatic
		// Also ask user to get armoria and download flags from there
	
// CREATION OF FLAGS
	// EU4 needs 128x128 TGA files with TAG.tga format
	// Armoria: on a 1920x1080 screen: GIANT gallery, NO SIMPLE shield,NO gradient,1 black border, 1.6 scale
	// Export as PNG (?JPEG?)

	/*
	dontUseModulesInTheFuture();

	cv::Mat single_image = openAndRead();
	std::vector<cv::Mat>images = splitImage( single_image, 24, 12 );
	showAnImage( images[0] );
	showAnImage( images[1] );

	*/

	
// CREATION OF COUNTRIES
	
// CREATION OF MAIN CULTURES
	
// CREAITON OF RELIGIONS https://eu4.paradoxwikis.com/Religion_modding
	
// CREATION OF PROVINCES / SEA REGIONS (AND UNIQUE COLOR FOR EACH)
	
// ASSIGN DEVELOPMENT TO PROVINCES
	
// CHINA MECHANICS
	
// SHOGUN MECHANICS
	
// HRE MECHANICS
	
// factions? https://eu4.paradoxwikis.com/Faction_modding
	
// government modding?
	
// ASSIGNMENT OF CULTURE(AND NAME)/STATE/RELIGION/CORES TO PROVINCES
	
// CREATION OF TRADE ZONES
	
// CREATION OF COLONIAL REGIONS

// Information calculated, time to output into EU4 formats and such
	GenericOutput(all_cells, "log2.txt");

	// HAVE TO GENERATE SEABOARD (make grid of hexagons that span the world, write them first, have them "replace" the cells that they take up and their neighbors (so land cells that border ocean cells (i.e. have ocean cells as neighbors) will instead have this new cell as a neighbor (or not even a cell, maybe have it as a sea province)
	// could have centers equally spaced through the map and make a new DrawHexagonCenteredHere()
	// HAVE TO DRAW SEABOARD BEFORE NON-OCEAN PROVINCES
	// HAVE TO MERGE LAND CELLS INTO PROVINCES (most likely 2 or 3, average size straight out of AZGAAR and into rendering is ~100 px. Avg size in EU4 is ~200 Europe, ~350 elsewhere
	// prolly want to track the size of the various polygons that are rendered and centroids
	// DEAD SPACE (e.g. Greenland, Australia, etc.)
	// CREATING THE IMAGE
	// FOLLOWING IS FOR EXAMPLE PURPOSES! FIRSTLY: PROVINCE ID NEEDS TO BE UNIQUELY MAPPED TO COLOR_RGB TO ENUSRE THAT THERE ARE NO REPEATS
	// NOTE THAT THE VERTICIES CONTAIN A DUPLICATE VALUE OF THE FIRST COORD INITIALLY PUT INTO THEM (just the way it is output from AZGAAR). IT WILL NOT BE USED IN RASTERIZATION because the DrawPolygon ignores duplicates (effectively)

/*###########################      CREATING THE IMAGE           ##################################*/
/*################################################################################################*/
	VUCO( "", "Creating image" );
	std::random_device rd; // obtain random number from hardware
	std::mt19937 gen( rd() ); // seed generator
	std::uniform_int_distribution<> distrib( 0, 255 ); //define the range // distrib(gen)
	
	ScreenRaster EU4_MAP( 5632, 2048 );

	

	//std::cout << "\nGenerating polygonmap from all_cells...";
	VUCO( "", "Generating polygonmap from all_cells..." );
	for (int dp_itr = 0; dp_itr < all_cells.size() - 1; dp_itr++) {
		IPixel color_rgb( distrib( gen ), distrib( gen ), distrib( gen ) );

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
	heightmap_bmp.Export( "heightmap.bmp" ,1);
	ScreenRaster normal_bmp = CalculateNormal(heightmap_bmp);
	Image normal_export( normal_bmp.width, normal_bmp.height );
	normal_export.MapRaster( normal_bmp );
	normal_export.Export("normal.bmp");
	
	Image EU4_MAP_BMP( 5632, 2048 );
	//std::cout << "\nMapping polygons to EU4 Map...";
	VUCO( "", "Mapping polygons to EU4 map...");
	EU4_MAP_BMP.MapRaster( EU4_MAP );
	//std::cout << "\nCreating bmp...";
	VUCO( "", "Creating bmp...");
	EU4_MAP_BMP.Export( "eu4_map.bmp" );




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
	return 0;
}//end of catch for runtime error

	std::cout << "\nEnd of Program";
#ifdef DEBUG
	system("pause>0");
#else
#endif
	return 0;
}	// End of main()

