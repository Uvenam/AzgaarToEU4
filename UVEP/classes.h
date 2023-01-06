#pragma once
#include "../UVEP/head.h"
#include "../UVEP/VUCO.h"
#include "../UVEP/RPoint.h"
#include "../UVEP/functions.h" // for definitions
//#include "../UVEP/RScreenImage.h"

struct settings {
	// variables and default values
	bool LARGE_WORLD = FALSE;
	bool ONLY_REPLACE_NEW_WORLD = FALSE;
	bool USE_RNW = FALSE;
	bool UNINHABITED_NEW_WORLD = FALSE;

	bool GOVERNMENT_UNIQUE_USAGE = TRUE;		// Will try to start countries with unique government or allow it (ex: random area on border of "catholic" religion area, if its "protestant" then it can form "prussia") (ex: russia)
	bool GOVERNMENT_STRICT_CONDITIONS = FALSE;	// Will either try and assign as many unique governments as possible at game start if false. If true, will adhere to conditions of original (ex: gond kingdom, you have to have indian tech and gondi culture)		
												// Also GOVERNMENT_STRICT_CONDITION will OVERWRITE government conditions

	bool CULTURE_BREAKDOWN_STATES_AS_UNIONS = FALSE;	// Mutually exclusive with CULTURE_BREAKDOWN_STATES // Also not sure if should only apply to large states
	bool CULTURE_BREAKDOWN_STATES = TRUE;
	bool CULTURE_BREAKDOWN_PROVINCES = TRUE;

	// Azgaar stores info of landmasses as continent (3) and islands (seemingly random #, probably based on generation order). EX: Af-Eur-Asia : Continent (3), NA : Island (9), SA : Island (34), Aus : Island (43), Jap : Island (28)
	std::vector<std::string> TECH_EUROPEAN;
	std::vector<std::string> TECH_ASIAN;
	std::vector<std::string> TECH_AMERICAN;
	// ...

	bool RELIGION_MAPPING_ACTION = TRUE;				// FALSE is EXPERIMENTAL, UNTESTED, NOT GUARANTEED TO WORK. This is a placeholder currently. TRUE is azgaar religions will be (roughly) mapped to EU4 religions

	std::vector<std::string> HRE_EQUIVALENT;
	bool HRE_CREATION = TRUE;
	bool HRE_BREAKDOWN = FALSE; // If given 1 for HRE_EQUIVALENT, assume given multiple

	std::string MANDATE_OF_HEAVEN_EQUIVALENT;
	bool MANDATE_OF_HEAVEN_CREATION = TRUE;

	std::string SHOGUN_EQUIVALENT;	// This country will be considered the shogun (should have government Shogunate
	bool SHOGUN_CREATION = TRUE;	// Use SHOGUN_EQUIVALENT or find largest state (population wise) with Shogunate government in Azgaar_states and make them SHOGUN_EQUIVALENT. They will be the shogun. 
	bool SHOGUN_ONE_AZGAAR_SHOGUNATE = TRUE;	// All other states with shogunate government will be independent daimyos if false or vassal daimyos if true
	bool SHOGUN_BREAKDOWN = TRUE; // SHOGUN_EQUIVALENT will be broken down into single province
	bool SHOGUN_OVERRIDE_SHOGUNS_RELIGION_TO_SHINTO = FALSE;	// Whatever religion the azgaar state is becomes equivalent to Shinto, OVERRIDES other religion
	bool SHOGUN_CONVERT_SHOGUN_TO_SHINTO = FALSE;	// all provinces within SHOGUN_EQUIVALENT will be converted to Shinto, no religion correlation if OVERRIDE_SHOGUNS_RELIGION_TO_SHINTO is false. Otherwise will convert all provinces to be the overridden religion (enforces uniformity)
	bool SHOGUN_CONVERT_JAPAN_TO_SHINTO = TRUE;		// all provinces within JAPAN region will be converted to Shinto, no religion correlation if OVERRIDE_SHOGUNS_RELIGION_TO_SHINTO is false. Otherwise will convert all provinces to be the overriden religion (enforces uniformity)
	// For gameplay purposes, the culture of the largest state with Shogunate government will be considered Japanese. all provinces of states with shogunate azgaar government form will be a part of the Japan region
	// Capital of SHOGUN_EQUIVALENT will be considered Kyoto


	std::vector<std::string> SPECIFIC_BREAKDOWNS;  // Provide list of countries you want specifically broken down 
	bool GLOBAL_BREAKDOWN = FALSE;
	bool GLOBAL_BREAKDOWN_TRUE_ORDERED_OR_FALSE_RANDOM = TRUE; // Either go from largest to smallest or randomly pick nations that have more than 1 province
	int  GLOBAL_BREAKDOWN_TO = 639;	// How many countries would you like to see at game start? Default is # EU4 has at game start. GLOBAL BREAKDOWN continues until this number is surpassed.

	bool BREAKDOWN_KEEP_CLAIMS = TRUE;
	bool BREAKDOWN_KEEP_CORES = FALSE; // Supersedes claims
	bool BREAKDOWN_SUCCESSOR_STATES = FALSE; // All breakdown calculations occur, then remnant country is replaced. Disables vassalization-release methods if TRUE.
	bool BREAKDOWN_FORMABLE = TRUE;	// Successor states will be able to form the initial state
	bool BREAKDOWN_TAG_TO_DUCHY_VASSAL = TRUE;
	bool BREAKDOWN_DUCHY_TO_PROVINCE_VASSAL = TRUE;
	bool BREAKDOWN_VASSAL_TIERED = TRUE;

	int START_TIME = 1444;
	int END_TIME = 1821;
	bool SCALE_TIME = FALSE;

	bool DEVELOPMENT_TRUE_POP_OR_FALSE_RANDOM = TRUE;
	int DEVELOPMENT_POP_CAP[3] = { 5,5,5 };
	bool DEVELOPMENT_ADD_RANDOM = TRUE;				
	int	 DEVELOPMENT_RANDOM_RANGE[2] = { 3,30 };	
	float DEVELOPMENT_POP_WEIGHTS[3] = { 0.5, 0.5, 0.5 };
	// DEVELOPMENT_BUILDING_VALUES
	int DBV[7][3] =					
	{
		{2,2,2},	// Capital
		{0,2,0},	// Port
		{0,0,2},	// Citadel
		{0,0,1},	// Walls
		{0,1,0},	// Plaza
		{2,0,0},	// Temple
		{1,1,0}		// Shanty
	};

	std::vector<std::string[2]> RELIGION_MAPPING;	// std::vector<std::pair<std::string,std::string>> ?

	bool USE_DIPLOMACY_CSV = FALSE;
	bool USE_MILITARY_CSV = FALSE;
	bool MILITARY_TRUE_NONE_OR_FALSE_ECONOMY = TRUE;
	bool USE_BURGS_CSV_FOR_DEVELOPMENT = FALSE;	
	bool USE_BURGS_CSV_FOR_BUILDINGS = FALSE;		/// ? What if its mid-game? So there would realistically be chapels and workshops built?

	

};

class progressBar {			//##################################################################################
	// https://www.youtube.com/watch?v=ayfCxgVStdQ&ab_channel=JacobSorber
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

struct state_info {

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
	// Used for...Azgaar prolly
	short ID;
	// Proper name of state
	std::string name;
	// things
	std::string form;
//	int color;
	std::string capital;
	std::string culture;
	std::string type;
	float expansionism;

	// EU4 name
	std::string TAG;
	// flag as TGA
	// country idea groups
	// color, RGB values
	unsigned char color_rgb[3];
	// government
	// std::vecotr<std::string> add_government_reform
	// int government_rank
	// technology_group
	// religion
	// primary_culture
	// capital as province ID
	// fixed_capital as province ID

	// Not sure if needed since these come with cell read in
	//short burg_count;
	//long area_mi2;
	//long rural_population;
	//long urban_population;

	void fnParseLine(std::string result_getLine_ele) {

		std::string regex_info = "[^\\,\]+";
		// Iterate over each match. Match 1 should be ID, Match 2 is State, 3 is full name and is discarded, 4 is form, 5 is color, 6 is capital, 7 is culture, 8 is type, 9 is expansionism, 10 is cell count and is discarded, 11 is burg count, 12 is area, 13 is total pop, 14 is rural pop, 15 is urban pop

	}

};
struct cell_info {
	//cells have 2 decimal precision for floats
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

	short burg_id;	// 1 burg per cell

	void add_coord(int x_coord, int y_coord);
};
struct river_info {
	// Rivers have 4 decimal precision for floats
	std::vector<FPoint> points;

	unsigned char rgb[3];

	int i;		// id
	int source;	// cell ID
	int mouth;	// cell ID
	// int discharge;
	// float length;
	// float width;
	// float width_factor;
	// float source_width;
	int parent;	// id of the parent river, whichever it "directly" "connects" to 
	std::vector<int> cells;
	// int basin;	// What "Main" river is this a part of? 
	std::string name;
	// std::string type;
	// std::string id_string;	// 


};
struct burg_info {
	// ID
	int id;
	// BURG
	std::string name;
	// PROVINCE FULL NAME
	
	// STATE
	
	// STATE FULL NAME
	
	// CULTURE
	std::string culture;
	// RELIGION
	std::string religion;
	// POPULATION
	int pop;
	// LATITUDE
	int y_latitude;
	// LONGITUDE
	int x_longitude;
	// ELEVATION(ft)
	
	// CAPITAL
	std::string capital;
	// PORT
	std::string port;
	// CITADEL
	std::string citadel;
	// WALLS
	std::string walls;
	// PLAZA
	std::string plaza;
	// TEMPLE
	std::string temple;
	// SHANTY TOWN
	std::string shanty;






};
struct province_info {
public:
	std::vector<int> cell_ids;
	// for complex borders and land fragmentation as seen on coasts
	std::vector<RPoint> pixels;
	short prov_id;
	std::string name;
	unsigned char color_rgb[3];
	std::vector<std::string> cores;
	std::string owner;
	//std::string controller;
	//0 is base_tax, 1 is base_production, 2 is base_manpower
	unsigned char base_dev[3]; 
	// Ranges from -3248ft to 22061ft (or 0 to 100 where ~20 is sealevel, but its saved as -3248 to 22061)
	// Lowest is [0,0,0], sea level IS [94,94,94] (so values at 94 and below are "sea"), and [255,255,255] is highest. The heightmap.bmp file should be in Greyscale mode and saved as a 8-bit bitmap image file (.BMP).
	// Normal: RGB, B is always 255. G for vertical changes (Max increase top to bottom:0, max decrease top to bottom: 255). R for horizontal changes (Max incease left to right: 0, max decrease left to right: 255). Increase: black to white, decrease: white to black
	short height;
	short biome;
	std::string type;
	bool hre;
	bool is_city;
	std::string culture;
	std::string religion;
	std::string trade_good;
	std::string capital; // essentially name of province
	std::vector <std::string> discovered_by;
	short center_of_trade;
	bool fort_15th; //theres fort
	bool shipyard;
	// Specific culture names?


};
struct culture {
public:
	int id;
	unsigned char color_rgb[3];
	// cell count
	// expansionism
	std::string type;
	std::string namesbase;
	std::vector<std::string> origins;




	std::string name;
	std::string primary;
	std::vector<std::string> male_names;
	std::vector<std::string> female_names;
	std::vector<std::string> dynasty_names;
	// country = { has_banners = 1}
	// province = { local_has_banners = 1}

};
struct culture_union : public culture {
public:
	std::vector<culture> subcultures;
	std::string graphical_culture;
};
// NOTE: Deities MUST HAVE TITLES! "Name, title"
struct religion {

	std::string EU4_equivalent;

	int id;
	std::string name;
	int color;
	std::string type;
	std::string form;
	std::string supreme_deity;
	//Area mi2	
	//Believers	
	std::vector<std::string> origins;
};

struct culture_namebase {	//##################################################################################

// NAMEBASE FORMAT
/*
EX NAME BASe
//		NAME	MIN LENGTH	MAX LENGTH	LETTERS TO BE DOUBLED	HOW MANY MULTI-WORD NAMES ALLOWED IN 0-1 RANGE
	{name: "English", i: 1, min: 6, max: 11, d: "", m: .1, b: "Abingdon,Albrighton,Alcester,Almondbury,Altrincham,Amersham,Andover,Appleby,Ashboume,Atherstone,Aveton,Axbridge,Aylesbury,Baldock,Bamburgh,Barton,Basingstoke,Berden,Bere,Berkeley,Berwick,Betley,Bideford,Bingley,Birmingham,Blandford,Blechingley,Bodmin,Bolton,Bootham,Boroughbridge,Boscastle,Bossinney,Bramber,Brampton,Brasted,Bretford,Bridgetown,Bridlington,Bromyard,Bruton,Buckingham,Bungay,Burton,Calne,Cambridge,Canterbury,Carlisle,Castleton,Caus,Charmouth,Chawleigh,Chichester,Chillington,Chinnor,Chipping,Chisbury,Cleobury,Clifford,Clifton,Clitheroe,Cockermouth,Coleshill,Combe,Congleton,Crafthole,Crediton,Cuddenbeck,Dalton,Darlington,Dodbrooke,Drax,Dudley,Dunstable,Dunster,Dunwich,Durham,Dymock,Exeter,Exning,Faringdon,Felton,Fenny,Finedon,Flookburgh,Fowey,Frampton,Gateshead,Gatton,Godmanchester,Grampound,Grantham,Guildford,Halesowen,Halton,Harbottle,Harlow,Hatfield,Hatherleigh,Haydon,Helston,Henley,Hertford,Heytesbury,Hinckley,Hitchin,Holme,Hornby,Horsham,Kendal,Kenilworth,Kilkhampton,Kineton,Kington,Kinver,Kirby,Knaresborough,Knutsford,Launceston,Leighton,Lewes,Linton,Louth,Luton,Lyme,Lympstone,Macclesfield,Madeley,Malborough,Maldon,Manchester,Manningtree,Marazion,Marlborough,Marshfield,Mere,Merryfield,Middlewich,Midhurst,Milborne,Mitford,Modbury,Montacute,Mousehole,Newbiggin,Newborough,Newbury,Newenden,Newent,Norham,Northleach,Noss,Oakham,Olney,Orford,Ormskirk,Oswestry,Padstow,Paignton,Penkneth,Penrith,Penzance,Pershore,Petersfield,Pevensey,Pickering,Pilton,Pontefract,Portsmouth,Preston,Quatford,Reading,Redcliff,Retford,Rockingham,Romney,Rothbury,Rothwell,Salisbury,Saltash,Seaford,Seasalter,Sherston,Shifnal,Shoreham,Sidmouth,Skipsea,Skipton,Solihull,Somerton,Southam,Southwark,Standon,Stansted,Stapleton,Stottesdon,Sudbury,Swavesey,Tamerton,Tarporley,Tetbury,Thatcham,Thaxted,Thetford,Thornbury,Tintagel,Tiverton,Torksey,Totnes,Towcester,Tregoney,Trematon,Tutbury,Uxbridge,Wallingford,Wareham,Warenmouth,Wargrave,Warton,Watchet,Watford,Wendover,Westbury,Westcheap,Weymouth,Whitford,Wickwar,Wigan,Wigmore,Winchelsea,Winkleigh,Wiscombe,Witham,Witheridge,Wiveliscombe,Woodbury,Yeovil"}

	FROM NAMEBASE.txt

	German|5|12|lt|0|Achern,Aichhalden,Aitern,Albbruck,Alpirsbach,Altensteig,Althengstett,Appenweier,Auggen,Wildbad,Badenen,Badenweiler,Baiersbronn,Ballrechten,Bellingen,Berghaupten,Bernau,Biberach,Biederbach,Binzen,Birkendorf,Birkenfeld,Bischweier,Blumberg,Bollen,Bollschweil,Bonndorf,Bosingen,Braunlingen,Breisach,Breisgau,Breitnau,Brigachtal,Buchenbach,Buggingen,Buhl,Buhlertal,Calw,Dachsberg,Dobel,Donaueschingen,Dornhan,Dornstetten,Dottingen,Dunningen,Durbach,Durrheim,Ebhausen,Ebringen,Efringen,Egenhausen,Ehrenkirchen,Ehrsberg,Eimeldingen,Eisenbach,Elzach,Elztal,Emmendingen,Endingen,Engelsbrand,Enz,Enzklosterle,Eschbronn,Ettenheim,Ettlingen,Feldberg,Fischerbach,Fischingen,Fluorn,Forbach,Freiamt,Freiburg,Freudenstadt,Friedenweiler,Friesenheim,Frohnd,Furtwangen,Gaggenau,Geisingen,Gengenbach,Gernsbach,Glatt,Glatten,Glottertal,Gorwihl,Gottenheim,Grafenhausen,Grenzach,Griesbach,Gutach,Gutenbach,Hag,Haiterbach,Hardt,Harmersbach,Hasel,Haslach,Hausach,Hausen,Hausern,Heitersheim,Herbolzheim,Herrenalb,Herrischried,Hinterzarten,Hochenschwand,Hofen,Hofstetten,Hohberg,Horb,Horben,Hornberg,Hufingen,Ibach,Ihringen,Inzlingen,Kandern,Kappel,Kappelrodeck,Karlsbad,Karlsruhe,Kehl,Keltern,Kippenheim,Kirchzarten,Konigsfeld,Krozingen,Kuppenheim,Kussaberg,Lahr,Lauchringen,Lauf,Laufenburg,Lautenbach,Lauterbach,Lenzkirch,Liebenzell,Loffenau,Loffingen,Lorrach,Lossburg,Mahlberg,Malsburg,Malsch,March,Marxzell,Marzell,Maulburg,Monchweiler,Muhlenbach,Mullheim,Munstertal,Murg,Nagold,Neubulach,Neuenburg,Neuhausen,Neuried,Neuweiler,Niedereschach,Nordrach,Oberharmersbach,Oberkirch,Oberndorf,Oberbach,Oberried,Oberwolfach,Offenburg,Ohlsbach,Oppenau,Ortenberg,otigheim,Ottenhofen,Ottersweier,Peterstal,Pfaffenweiler,Pfalzgrafenweiler,Pforzheim,Rastatt,Renchen,Rheinau,Rheinfelden,Rheinmunster,Rickenbach,Rippoldsau,Rohrdorf,Rottweil,Rummingen,Rust,Sackingen,Sasbach,Sasbachwalden,Schallbach,Schallstadt,Schapbach,Schenkenzell,Schiltach,Schliengen,Schluchsee,Schomberg,Schonach,Schonau,Schonenberg,Schonwald,Schopfheim,Schopfloch,Schramberg,Schuttertal,Schwenningen,Schworstadt,Seebach,Seelbach,Seewald,Sexau,Simmersfeld,Simonswald,Sinzheim,Solden,Staufen,Stegen,Steinach,Steinen,Steinmauern,Straubenhardt,Stuhlingen,Sulz,Sulzburg,Teinach,Tiefenbronn,Tiengen,Titisee,Todtmoos,Todtnau,Todtnauberg,Triberg,Tunau,Tuningen,uhlingen,Unterkirnach,Reichenbach,Utzenfeld,Villingen,Villingendorf,Vogtsburg,Vohrenbach,Waldachtal,Waldbronn,Waldkirch,Waldshut,Wehr,Weil,Weilheim,Weisenbach,Wembach,Wieden,Wiesental,Wildberg,Winzeln,Wittlingen,Wittnau,Wolfach,Wutach,Wutoschingen,Wyhlen,Zavelstein



*/

// CULTURE FORMAT
/*
FORM for CULTURE
Id,Name,Color,Cells,Expansionism,Type,Area mi2,Population,Namesbase,Emblems Shape,Origins
// Origins is the Parent cultures

EX:
10,Mercian,#6e40aa,2071,4.2,Nomadic,35060224,19355483,English,heater,""


*/

public:


	/* ######################################################
					BEHAVIOR TO EMULATE
	LENGTH: 5, 12					DOUBLED: 
	One, Ono, ona, Onan
	=> Onone, Onono, Onone, Onan, Ona, Onona, Onone, 
	
	One, Ono, Onen
	=> Onen, Onono, Onone, Ononen, Ononononononen
	
	
	###################################################### */


	std::string name;
	int min_length;
	int max_length;
	std::string doubled_letters;
	float multi_word_names;
	std::vector<std::string> source_list;

	std::vector<std::string> onsets;
	std::vector<std::string> generic_coda;
	std::unordered_map<std::string, std::vector<char>> coda_map;
	std::unordered_map<std::string, std::vector<std::string>> dia_map;
	std::unordered_map<char, std::vector<std::string>> five_letter_syllable_map;

	std::unordered_set<std::string> unique_names;
	std::vector<std::string> vec_names;

	std::unordered_set<std::string> unique_vowels;
	std::unordered_set<std::string> unique_consonants;

	std::vector<std::string> unique_consonants_saved;
	std::vector<std::string> unique_vowels_saved;

	std::unordered_set<std::string> unique_vowels_start;
	std::unordered_set<std::string> unique_consonants_start;
	std::unordered_set<std::string> unique_vowels_mid;
	std::unordered_set<std::string> unique_consonants_mid;
	std::unordered_set<std::string> unique_vowels_end;
	std::unordered_set<std::string> unique_consonants_end;


	std::unordered_set<std::string> unique_syllables;


	std::unordered_map<char, std::vector<char>> char_map;

	// Syllable, tracks previous "phoneme" and frequency
	//DEPRECATED
	void fn_makeWord(int length_ele, int depth_ele);
	//DEPRECATED
	void fn_makeWord_VCVC(int length_ele, int min_ele);

	//DEPRECATED
	std::string getName();
	//DEPRECATED
	void fn_make_vector_of_unique_names();

	// old and deprecated
	/*
	void makeNamebase ( std::vector<std::string> original_list )
	{
		// Update so it doesn't get as easily stuck!!
		std::string onset_building;
		for ( int eachword = 0; eachword < original_list.size () - 1; eachword++ )
		{
			for ( int eachchar = 0; eachchar < original_list[eachword].length () - 1; eachchar++ )
			{
				try
				{
					// get 3 characters
					onset_building = original_list[eachword].substr ( eachchar, 3 );	// from original list element (i.e. a word), get the first two characters, copy them and place them into onsets
					// check if 3 characters were retrieved
					if ( onset_building.length () == 3 )
					{
						// keep the first two characters
						this->onsets.push_back ( onset_building.substr ( 0, 2 ) );
						//std::cout<< '\r';
						//std::cout << this->onsets.size ();
						//std::cout << std::flush;

						// add the 3rd character to the coda map, uses the new onsets element
						this->coda_map[onsets[onsets.size () - 1]].push_back ( onset_building[2] );

					}
					else
					{
						if ( onset_building.length () == 2 )
						{
							this->generic_coda.push_back ( onset_building.substr ( 1, 2 ) );

						}

						continue;
					}


				}
				catch ( std::out_of_range& oor )
				{
					std::cerr << "[ERROR] Out of range error: " << oor.what () << '\n';

				}


			}

		}

	}
	*/
	/*
void generateWord ( int length )
{
	// start word
	//YELL "[gw] Word Building Start";

	std::string word_building = "";
	if ( this->onsets.size () == 0 )
	{

		std::cerr << "[ERROR] INSUFFICIENT TRAINING DATA!";
		//throw "ERROR! ONSET_SIZE == 0!";
		return;
	}

	// make random seed
	//YELL "[gw] Seed";

	srand ( ( previous_random ) );

	// make random number
	//YELL "[gw] Random Number";
	std::random_device rd;
	std::mt19937 gen ( rd () );
	std::uniform_int_distribution<> distrib ( 0, 2000 );
	std::string wordsmith = "";

	// replace with std::uniform_int_distribution<int> or http://en.cppreference.com/w/cpp/numeric/random
	//https://stackoverflow.com/questions/28656004/c-random-doesnt-workreturns-same-value-always







	int rando = distrib ( gen );

						//rand ();

	//YELL rando;
	int randaa = distrib ( gen );
	//YELL randaa;
	int indexo = 0;
	// find the size of the onset vector, assign to variable
	//YELL "[gw] Get Onset Size";

	int onset_size = onsets.size ();
	if ( onset_size == 1 )
	{
		//std::cout << "\n" << "[gw] ONSET_SIZE FOUND TO BE 1";
		indexo = 0;

	}
	// randomly pick an onset
	else
	{
		//std::cout << "\n" << "[gw] ONSET_SIZE != 1";
		if ( onset_size == 0 )
		{
			std::cerr << "[ERROR] EXPECTED ONSET_SIZE > 0";
			throw "ERROR! ONSET_SIZE IS 0!";

		}

		//std::cout << "\n" << "[gw] GETTING RANDOM NUMBER FROM 0 TO ONSET_SIZE - 1";
		indexo = distrib ( gen ) % ( onset_size );
		//std::cout << "\n" << indexo;
	}


	//std::cout << "\n" << "[gw] FOUND RANDOM ONSET";
	std::string temporary_onset = this->onsets[indexo];
	//std::cout << "\n" << temporary_onset;


	word_building += temporary_onset;

	//YELL "[gw] word start: ";
	//YELL word_building;


	// find the size of the coda_map vector that corresponds to that specific onset
	int temporary_size = coda_map[temporary_onset].size ();
	// IF the size = 0, either treat it as the end of the word or add something from generic_coda
	if ( temporary_size == 0 )
	{
		//std::cout << "\n" << "[ISSUE] TEMPORARY SIZE = 0";
		indexo = 0;

	}
	else
	{
		//std::cout << "\n" << "[gw] GETTING RANDOM CODA FROM 0 TO " << temporary_size << " - 1";
		indexo = distrib ( gen ) % ( temporary_size );
		//std::cout << "\n" << indexo;
	}
	// randomly pick a coda
	word_building += coda_map[temporary_onset][indexo];
	//YELL "[gw] update to word_building";
	//YELL word_building;


	// continue word to finish
	//std::cout << "\n" << "[gw] WORD BUILDING START: " << word_building << " with length " << word_building.length();

	while ( length > word_building.length () )
	{
		// get last one characters
		wordsmith = word_building.substr ( word_building.length () - 1 );

		//std::cout << "\n" << "[gw]" << wordsmith;

		temporary_size = coda_map[wordsmith].size ();
		//std::cout << "\n" << "[gw] THIS-> CODA_MAP SIZE " << this->coda_map[wordsmith].size ();
		//std::cout << "\n" << "[gw] CODA_MAP SIZE " << coda_map[wordsmith].size ();
		if ( temporary_size == 0 )
		{
			//std::cout << "\n" << "[gw] NO CODA FOUND!";
			temporary_size = 1;

		}
		//std::cout << "\n" << "[gw] GETTING RANDOM CODA FROM 0 TO " << temporary_size << " - 1";
		indexo = distrib(gen) % temporary_size;
		//std::cout << "\n" << indexo;
		if ( indexo == 0 )
		{
			// want to end the string prematurely
			//std::cout << "\n" << "[gw] Using Generic Coda";
			word_building += this->generic_coda[0];
			break;
		}
		else // indexo != 0
		{
			word_building += coda_map[wordsmith][indexo];

		}
		//std::cout << "\n" << word_building;




	}
	//std::cout << "\n" << "[gw] Final name: " << word_building;
	this->unique_names.insert ( word_building );

}
*/
/*
void fn_makeMarkov_VariableDepth ( std::vector<std::string> original_list, int depth_ele )
{
	// Update so it doesn't get as easily stuck!!
	//progressBar TRACK( "Build Markov", original_list.size () - 1);

	std::string onset_building;
	for ( int eachword = 0; eachword < original_list.size () - 1; eachword++ )
	{
		for ( int eachchar = 0; eachchar < original_list[eachword].length () - 1; eachchar++ )
		{
			try
			{
				// get 2 characters
				onset_building = original_list[eachword].substr ( eachchar, 2 );	// from original list element (i.e. a word), get the first two characters, copy them and place them into onsets
				//std::cout << "\n" << "[mMC] BUILT ONSET " << onset_building;
				if ( onset_building.length () == 2 )
				{
					// push char one into onsets
					this->onsets.push_back ( onset_building.substr ( 0, 1 ) );
					this->generic_coda.push_back ( onset_building.substr ( 1, 2 ) );


					// add the 3rd character to the coda map, uses the new onsets element
					this->coda_map[onsets[onsets.size () - 1]].push_back ( onset_building[1] );
					//std::cout << "\n" << onsets[onsets.size () - 1];
					//std::cout << "\n" << coda_map[onsets[onsets.size () - 1]][0];

				}
				else
				{
					if ( onset_building.length () == 1 )
					{
						std::cout << "\n" << "[ISSUE] ONSET_BUILDING ONLY LENGTH 1, SOMEHOW REACHED FURTHER THAN INTENDED";
						this->generic_coda.push_back ( onset_building.substr ( 1, 2 ) );

					}

					continue;
				}


			}
			catch ( std::out_of_range& oor )
			{
				std::cerr << "[ERROR] Out of range error: " << oor.what () << '\n';

			}


		}
		//TRACK.update ( 1 );

	}
}
*/
	void fn_makeMarkov(std::vector<std::string> original_list);

	void fn_getDias(std::vector<std::string> original_list);
	void fn_AzgaarNamebaseGeneration( std::vector<std::string> original_list );
	std::string fn_MakeWordAzgaar( int min, int max, std::string dupl );
	// The way AZGAAR does it:
	// Here is an array of words. Break up each word into syllables (5 letters
	//

		// function for creating a Namebase via Pseudo-syllable, azgaar style
		 //and the necessary members for that

		// Another posibility:
		/*
		static char vowel[] = {
			"a",
			"e",
			"i",
			"o",
			"u",
		};

		static char consonant[] = {
			"b", "ch", "d", "f", "g", "j", "k", "l", "m", "n", "p", "r", "s",
			"t", "v", "x", "z", "ph", "sh", "th", "sp", "st",
		};

		static char pattern[] = {
			"vcvc",
			"cvcvc",
			"cvcv",
			"vcv",
			"cvc",
			"cvv",
			"cvcvv",
		};

		*/

		// Read WORD
		// all letters between two vowels gets put into temp_array_consonant_pair
		// all letters between two consonants gets put into temp_array_vowel_pair


}; // end class				//##################################################################################
struct symbol_data {
	//##################################################################################

public:
	std::string symbol = "";
	int	freq = 0;
	//##################################################################################
}; // end class				

// Extra functions working with classes
std::tuple<int, int, int, int> ParseStringUpdateCells(std::vector<cell_info>& all_cells, std::string& example_data);
void						   ParseStringUpdateRivers ( std::vector<river_info>& all_rivers, std::string& example_data );
// Also calls namebase generation function
void NamebaseParse( std::vector<std::string> read_list, std::vector<culture_namebase> &all_namebases );
// Takes file path, returns vector of states with info filled in
std::vector<state_info> StateParse( std::string state_path );
std::unordered_set<std::string> TAGParse( std::vector<state_info>& all_states );
std::vector<culture> CultureParse(std::string culture_path);
std::vector<burg_info> BurgParse( std::string burg_path );
std::vector<religion> ReligionParse ( std::string religion_path );
void GenericOutput(std::vector<cell_info> all_cells, std::string output_file);

void TransformPoints( int desired_width, int desired_height, std::vector<burg_info>& all_burgs, std::vector<cell_info>& all_cells, std::tuple<int,int,int,int>& extents );
void TransformPoints_NoStretch ( std::vector<burg_info>& all_burgs, std::vector<cell_info>& all_cells, std::tuple<int, int, int, int>& extents );
std::vector<int> AssignBurgsToCells ( std::vector<burg_info>all_burgs, std::vector<cell_info> & all_cells );
std::vector<province_info> CreateProvinces (std::vector<cell_info> all_cells);

// std::vector<int> NeighborBlockColor (all_cells, center_cell_id, distance)// function should be able to take a central cell ID, go through its neighbors, find distance to central cell, compare distance, and approve? or disapprove? return list of cell ID's that are good to color / within distance

// LinkRiverToMap

// CreateArea

// CreateRegion

// CreateContinent
// 0 is for generic, 1 is for state -> province
std::vector<state_info> Breakdown(state_info parent, int option); 
