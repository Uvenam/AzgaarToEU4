#pragma once
#include "../UVEP/head.h"
#include "../UVEP/VUCO.h"
#include "../UVEP/RPoint.h"
#include "../UVEP/functions.h" // for definitions
//#include "../UVEP/RScreenImage.h"

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
	void add_coord(int x_coord, int y_coord);
};


class culture_namebase {	//##################################################################################

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
	void fn_makeWord(int length_ele, int depth_ele);

	void fn_makeWord_VCVC(int length_ele, int min_ele);


	std::string getName();

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


class symbol_data {
	//##################################################################################

public:
	std::string symbol = "";
	int	freq = 0;
	//##################################################################################
}; // end class				

// Extra functions working with classes
std::tuple<int, int, int, int> ParseStringUpdateCells(std::vector<cell_info>& all_cells, std::string& example_data);
void NamebaseParse( std::vector<std::string> read_list, std::vector<culture_namebase> &all_namebases );

void GenericOutput(std::vector<cell_info> all_cells, std::string output_file);

void TransformPoints( int desired_width, int desired_height, std::vector<cell_info>& all_cells, std::tuple<int,int,int,int>& extents );

// std::vector<int> NeighborBlockColor (all_cells, center_cell_id, distance)// function should be able to take a central cell ID, go through its neighbors, find distance to central cell, compare distance, and approve? or disapprove? return list of cell ID's that are good to color / within distance

// LinkRiverToMap
// CreateArea
// CreateRegion
// CreateContinent