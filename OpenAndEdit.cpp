﻿#include <iostream> // IO to console
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
#include <thread>		// for making sure esc ends program in the middle

#include <memory>

#include <unordered_map>
#include <unordered_set>

#include <ctime>
#include <iomanip>
#include <random>

#include <io.h>
#include <fcntl.h>

#include <Windows.h>

#include <algorithm>
#include <cctype>

#include <clocale>
#include <codecvt>

// commit all, then push
#define VERSION_STAMP_	"V 0.352"
#define  DEBUG	// for VUCO logging

template <class ST>
void VUCO(std::string const& where_ele, ST& message)
{
#ifdef DEBUG
	// write message to std::cerr
	std::cout << '\n' << '[' << where_ele << ']' << message;
#else
	// write message to log file
#endif
}
template <class ST>
void VUCO(bool act, std::string const& where_ele, ST& message)
{
#ifdef DEBUG
	// write message to std::cerr
	if (act == TRUE)
	{
		std::cout << '\n' << '[' << where_ele << "] " << message;
	}

#else
	// write message to log file
#endif
}


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
	void update(int newProgress)
	{
		currentProgress += newProgress;
		if (currentProgress > items)
		{

			return;
		}
		amountOfFiller = pBarLength * (currentProgress / items);

		std::cout << std::fixed << std::setprecision(0) << "\r" // bring cursor to start of line
			<< task << " "
			<< firstPartOfBar
			<< currentProgress << "/" << items << lastPartOfBar;
		std::cout << firstPartOfBar
			<< std::fixed << std::setprecision(1) << 100 * currentProgress / items << "%";

		for (int a = 0; a < amountOfFiller; a++)
		{ //Print out current progress
			std::cout << barFiller;
		}

		for (int b = 0; b < pBarLength - amountOfFiller; b++)
		{
			std::cout << barEmpty;
		}
		std::cout << lastPartOfBar;
		std::cout << std::flush;


	}
	void updatePercent(double newPercent)
	{
		int increaseBy = newPercent * (items / 100);
		if ((increaseBy + currentProgress) > items)
		{
			return;
		}
		update(increaseBy);
	}
	void reuse(int items1)
	{
		this->amountOfFiller = 0;

		this->currentProgress = 0;

		this->items = items1;

	}
	progressBar(std::string task_ele, int elements)
	{
		task = task_ele;
		items = elements;
	}
	progressBar() { };



}; // end class				//##################################################################################
class symbol_data {			//##################################################################################

public:
	std::string symbol = "";
	int	freq = 0;
}; // end class				//##################################################################################

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

	std::string name;

	std::vector<std::string> onsets;
	std::vector<std::string> generic_coda;
	std::unordered_map<std::string, std::vector<char>> coda_map;
	std::unordered_map<std::string, std::vector<std::string>> dia_map;

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
	void fn_makeWord(int length_ele, int depth_ele)
	{
		std::string word_str = "";
		if (this->onsets.size() == 0)
		{

			std::cerr << "[ERROR] INSUFFICIENT TRAINING DATA!";
			throw "ERROR! ONSET_SIZE == 0!";
			return;
		}

		//setting up randomness
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, 2000);
		int rand1 = distrib(gen);
		int rand2 = distrib(gen);
		int rand3 = distrib(gen);

		int index_of_onset = 0;
		int onset_size = onsets.size();
		if (onset_size == 1)
		{
			//std::cout << "\n" << "[gw] ONSET_SIZE FOUND TO BE 1";
			index_of_onset = 0;

		}
		// randomly pick an onset
		else
		{
			//std::cout << "\n" << "[gw] ONSET_SIZE = " << onset_size;
			if (onset_size == 0)
			{
				std::cerr << "[ERROR] EXPECTED ONSET_SIZE > 0";
				throw "ERROR! ONSET_SIZE IS 0!";

			}

			//std::cout << "\n" << "[gw] GETTING RANDOM NUMBER FROM 0 TO " << onset_size-1;
			index_of_onset = rand1 % (onset_size);
			//std::cout << "\n" << index_of_onset;
		}

		//std::cout << "\n" << "[gw] FOUND RANDOM ONSET";
		std::string temporary_onset = this->onsets[index_of_onset];
		//std::cout << "\n" << temporary_onset;

		// Update the word with the temporary onset
		word_str += temporary_onset;
		// Find the number of coda's for that onset
		int temporary_size = coda_map[temporary_onset].size();
		int index_of_codas = 0;
		// IF the size = 0, either treat it as the end of the word or add something from generic_coda
		if (temporary_size == 0)
		{
			//std::cout << "\n" << "[ISSUE] TEMPORARY SIZE = 0";
			index_of_codas = 0;

		}
		else
		{
			//std::cout << "\n" << "[gw] GETTING RANDOM CODA FROM 0 TO " << temporary_size-1;
			index_of_codas = rand2 % (temporary_size);
			//std::cout << "\n" << index_of_codas;
		}
		// randomly pick a coda
		word_str += coda_map[temporary_onset][index_of_codas];
		//YELL "[gw] update to word_building";
		//YELL word_building;


		// continue word to finish
		//std::cout << "\n" << "[gw] WORD BUILDING START: " << word_str << " with length " << word_str.length ();

		while (length_ele > word_str.length())
		{
			// get last one characters
			std::string wordsmith = word_str.substr(word_str.length() - depth_ele);

			//std::cout << "\n" << "[gw]" << wordsmith;

			temporary_size = coda_map[wordsmith].size();
			//std::cout << "\n" << "[gw] THIS-> CODA_MAP SIZE " << this->coda_map[wordsmith].size ();
			//std::cout << "\n" << "[gw] CODA_MAP SIZE " << coda_map[wordsmith].size ();
			if (temporary_size == 0)
			{
				//std::cout << "\n" << "[gw] NO CODA FOUND!";
				temporary_size = 1;

			}
			//std::cout << "\n" << "[gw] GETTING RANDOM CODA FROM 0 TO " << temporary_size << " - 1";
			if (temporary_size == 0)
			{
				//std::cout << "\n" << "[gw] Using Generic Coda";
				word_str += this->generic_coda[0];
				break;
			}
			index_of_codas = distrib(gen) % temporary_size;
			//std::cout << "\n" << index_of_codas;

			word_str += coda_map[wordsmith][index_of_codas];


			//std::cout << "\n" << word_str;




		}
		//std::cout << "\n" << "[gw] Final name: " << word_str;
		this->unique_names.insert(word_str);




	}

	void fn_makeWord_VCVC(int length_ele, int min_ele)
	{
		bool act = TRUE;
		std::string nm = "makeWord_CVCV";

		std::string word_str = "";
		__int8 vowel_consonant = 0;

		if (this->unique_consonants_saved.size() == 0 || this->unique_vowels_saved.size() == 0)
		{

			std::cerr << "[ERROR] INSUFFICIENT TRAINING DATA!";
			//		throw "ERROR! ONSET_SIZE == 0!";
			return;
		}

		//setting up randomness
		// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
		std::random_device rd; // obtain random number from hardware
		std::mt19937 gen(rd()); // seed generator
		std::uniform_int_distribution<> distrib(0, 2000); //define the range
		int rand1 = distrib(gen);
		int rand2 = distrib(gen);
		int rand3 = distrib(gen);


		// Start, end, and tracking item in set
	//	auto set_start = unique_consonants.begin ();
	//	auto set_end = unique_consonants.end ();
	//	auto set_randomized_item = unique_consonants.begin ();

		// Size of set, want a random item in that set, modulo random number by size to get value of random element number
	//	int set_size = unique_consonants.size ();
	//	int desired_item_in_set = (rand1 % set_size); // int between 0 and set_size-1

		// Want to get item N, but can't do integer addition on iterator for unordered_set
		// Increase iterator until item N reached
		// desired_item_in_set serves as pseudo-index
	//	while ( desired_item_in_set > 0 )
	//	{
	//		set_randomized_item++;
	//		desired_item_in_set--;
	//	}


		// Randomly pick Cons or Vowel start (have to be careful which is more common, should have array/vector that has the starting dia and another for ending dia)
		// Going with consonant first for testing
		int index_of_dia_cons = 0;

		index_of_dia_cons = rand1 % unique_consonants_saved.size();

		int index_of_dia_vowel = 0;
		index_of_dia_vowel = rand2 % unique_vowels_saved.size();


		int word_length = 0;

		word_length = rand3 % (length_ele + 1);
		if (word_length < min_ele)
		{
			word_length += rand1 % min_ele;
		}


		// Randomly pick any available dia for vowel and for consonant
		while (word_str.length() < word_length)
		{
			// Alternate between adding vowels and adding consonants
			if (++vowel_consonant % 2 == 0)
			{
				//VUCO ( "CVCV INDEX CONS", index_of_dia_cons );
				//LOGG "[CVCV SIZE CONS] " << unique_consonants_saved.size ();

				word_str += unique_consonants_saved[index_of_dia_cons];
				index_of_dia_cons = distrib(gen) % unique_consonants_saved.size();

			}
			else
			{
				//VUCO ( "CVCV INDEX VOWEL", index_of_dia_vowel );
				//LOGG "[CVCV SIZE VOWEL] " << unique_vowels_saved.size ();

				word_str += unique_vowels_saved[index_of_dia_vowel];
				index_of_dia_vowel = distrib(gen) % unique_vowels_saved.size();
			}


		}





		// Add to word_str

		// Get size of dia_map using dia as key (dia as key => get vector of varying size)
		// Randomly pick number between 0 and dia_map[dia] . size() - 1; (do modulus operation);
		// Put into std::string next_addition
		// Pick next type (if consonant, pick vowel and vice versa) for succeeding 
		//









		VUCO(act, nm, word_str);
		this->unique_names.insert(word_str);




	}


	std::string getName()
	{
		std::unordered_set<std::string> ::iterator going_through = this->unique_names.begin();
		return *going_through;
	}

	void fn_make_vector_of_unique_names()
	{
		std::unordered_set<std::string> ::iterator ending = this->unique_names.end();

		for (std::unordered_set<std::string> ::iterator going_through = this->unique_names.begin();
			going_through != ending;
			going_through++)
		{
			this->vec_names.push_back(*going_through);

		}
	}

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
	void fn_makeMarkov(std::vector<std::string> original_list)
	{
		bool act = FALSE;
		// Update so it doesn't get as easily stuck!! 
		//progressBar TRACK( "Build Markov", original_list.size () - 1);

		std::string onset_building;
		for (int eachword = 0; eachword <= original_list.size() - 1; eachword++)
		{
			VUCO(act, "fnMM Word", eachword);
			for (int eachchar = 0; eachchar <= original_list[eachword].length() - 2; eachchar++)
			{
				VUCO(act, "fnMM Characters", eachchar);
				try
				{
					// get 2 characters
					onset_building = original_list[eachword].substr(eachchar, 2);	// from original list element (i.e. a word), get the first two characters, copy them and place them into onsets
					//std::cout << "\n" << "[mMC] BUILT ONSET " << onset_building;
					VUCO(act, "fnMM Get Onset", onset_building);

					if (onset_building.length() == 2)
					{
						// push char one into onsets
						this->onsets.push_back(onset_building.substr(0, 1));
						this->generic_coda.push_back(onset_building.substr(1, 2));


						// add the 3rd character to the coda map, uses the new onsets element
						this->coda_map[onsets[onsets.size() - 1]].push_back(onset_building[1]);
						//std::cout << "\n" << onsets[onsets.size () - 1];
						//std::cout << "\n" << coda_map[onsets[onsets.size () - 1]][0];

					}
					else
					{
						if (onset_building.length() == 1)
						{
							std::cout << "\n" << "[ISSUE] ONSET_BUILDING ONLY LENGTH 1, SOMEHOW REACHED FURTHER THAN INTENDED";
							this->generic_coda.push_back(onset_building.substr(1, 2));

						}

						continue;
					}


				}
				catch (std::out_of_range& oor)
				{
					std::cerr << "[ERROR] Out of range error: " << oor.what() << '\n';

				}


			}
			//TRACK.update ( 1 );

		}
	}

	void fn_getDias(std::vector<std::string> original_list)
	{
		//The following is done assuming non-accented latin characters (i.e. keys on a US keyboard)
		//Following also assumes lowercase
	   // for VUCO function (just helps with debugging and having a console output log
		bool act = TRUE;
		std::string nm = "makeMarkov_Dia";

		//Thinking:
	   /*
	   So a namebase will consist of strings / names
	   There can be up to 6 chars in a syllable: CC V V CC, where CC are diagraph and V V could be a dipthong or simple connection
	   Reading a name, it should read the first letter
	   Reading a character increases char_general_frequency for that char
	   Reading the next char increases char_following_frequency for that char using previous char as hash key
		   char_following_frequency for same-type (consonant then consonant, vowel then vowel) is initially 0

	   Should read entire word as C1C2V1C3C4 or something similar
		   EX: TLARK, read as TL - A - RK, 1 syllable so C1 C2 V1 C3 C4 -> C1 and C2 as diagraph, C3 and C4 as diagraph
			   TLARKA, read as TL - A - RK | KA, 2 syllable,
			   ATLARKA, read as A - TL | TL - A - RK | KA, 3 syllable
			   ?? but what if AT - LAR - KA
	   # of vowel = # of syllable
	   syllable ending = next syllable beginning if diagraph

	   Fuzesgyarmat

	   FU as syllable, FUZ as syllable, ZE as syllable
	   */
	   // Thinking 2:
	   /*
	   Syllable: ONSET - NUCLEUS - CODA
	   each portion CAN BE 2 chars
	   ex: STRING
	   C1 C2 C3 -> 3 chars, what do?
	   Start of word will get special treatment


	   */
		std::string syl_building = "";
		std::string dia_building = "";
		std::string prev_dia_building = "";

		int loop_ctr = 0;

		//std::string vowels_dia = "ÀÁÂÃÄÅÆÈÉÊËÌÍÎÏÒÓÔÕÖØÙÚÛÜÝàáâãäåæèéêëìíîïòóôõöøùúûüýÿ";
		std::string vowels = "aeiouy";
		std::string consonant = "qwrtplkjhgfdszxcvbnm";
		//std::regex rexgex_vowels ( "\(\[0-9\]+\)" );
		//std::regex regex_consonants;
		//int eachchar= 0;
		//int wordsize = 0;
		int c_or_v = 0;
		int c_or_v_next = 0;
		int eachchar = 0;

		for (int eachword = 0; eachword <= original_list.size() - 1; eachword++)
		{
			loop_ctr = 0;

			//std::cout << "\n" << "[mSL] New Word################################";

		//	wordsize = original_list[eachword].length ();
		//	eachchar = 0;
		//	while (eachchar < wordsize)
			//for ( int eachchar = 0; eachchar < original_list[eachword].length () - 1; eachchar++ )
			//VUCO ( "mSL START", eachword );
			eachchar = 0;
			while (eachchar <= original_list[eachword].length() - 1)
			{
				// Get char
				// Probe what type (cons or vowel)
				// Add to dia_building
				// probe type of next char
				// if same, add to dia_building and repeat
				//VUCO (act, "mSL", "####### START #############" );
				//std::cout << "\n" << "[mSL] New dia_building";
				dia_building = "";
				dia_building += original_list[eachword][eachchar];
				//VUCO ( act, "mSL", dia_building );
				//std::cout << "\n" << "[mSL] " << dia_building;

				c_or_v = yn_isVowel(original_list[eachword][eachchar]);
				c_or_v_next = 0;
				// If the word has at least 1 more char
				if ((original_list[eachword].length() - 1) - eachchar >= 1)
				{
					//	std::cout << "\n" << "[mSL] Check if Next Char exists and is vowel ";
					c_or_v_next = yn_isVowel(original_list[eachword][eachchar + 1]);
					//	std::cout << "\n" << c_or_v;
					//	std::cout << "\n" << c_or_v_next;

				}
				else // Word doesn't have more characters
				{
					//	std::cout << "\n" << "[mSL] Word End reached ";
						//eachchar = original_list[eachword].length (); //reached end of word
						//VUCO ( act, "mSL", "Word End Reached" );
					break; // exit while for eachchar
				}


				while (c_or_v == c_or_v_next) {
					//	std::cout << "\n" << "[mSL] while loop of checking likeness";
						// next_char checked before first while loop
						// within while, next_char is checked again
					//	std::cout << "\n" << "[mSL] dia update";
					dia_building += original_list[eachword][++eachchar];
					//	std::cout << "\n" << "[mSL] " << dia_building;
						// if there is another character in the string
					if ((original_list[eachword].length() - 1) - eachchar >= 1)
					{
						//	std::cout << "\n" << "[mSL] Checking next char in while loop";
						c_or_v_next = yn_isVowel(original_list[eachword][eachchar + 1]);
					}
					else
					{
						//	std::cout << "\n" << "[mSL] while exit due to word end reached";
						break; // exit while
					}

				}
				// dia_building is now string of same vowel/consonants

				// before adding to data, purify by making lowercase
				//std::cout << "\n" << "[mSL] Make dia lowercase";
				make_lowercase(dia_building);
				//std::cout << "\n" << "[mSL] " << dia_building;
				if (c_or_v == 1) // if vowel string
				{
					//	std::cout << "\n" << "[mSL] All Vowels emplaced";
					this->unique_vowels.emplace(dia_building);
				}
				else // if consonant string
				{
					//	std::cout << "\n" << "[mSL] All Consonants emplaced ";
					this->unique_consonants.emplace(dia_building);
				}


				if (loop_ctr == 0)
				{
					//std::cout << "\n" << "[mSL] Prev_dia updated using current";
					prev_dia_building = dia_building;
				}
				else
				{
					//	std::cout << "\n" << "[mSL] Prev_dia as key, new dia is pushed back onto vector. Dia then replaced prev_dia";
					dia_map[prev_dia_building].push_back(dia_building);
					prev_dia_building = dia_building;
				}
				//VUCO ( "mSL", "######## END ############" );
				loop_ctr++;


				// What char is this?
				 //For same type (vowel or consonant)
					 //Read this until other type. Add to dia_building



					 //attempt to insert current syllable into unique syllable set
					 //pair of iterator and boolean returned  https://cplusplus.com/reference/unordered_set///unordered_set/emplace/
					// if unique, value is TRUE. If not, or other issue, it is FALSE
					//this->unique_syllables.emplace ( syl_building );







				eachchar++;

			}

		}

		// want to place the hash_mapped dia's into a vector so that they can be easily accessed
		for (auto itr_cons = unique_consonants.begin(); itr_cons != unique_consonants.end(); itr_cons++)
		{
			this->unique_consonants_saved.push_back(*itr_cons);
		}

		for (auto itr_vowel = unique_vowels.begin(); itr_vowel != unique_vowels.end(); itr_vowel++)
		{
			this->unique_vowels_saved.push_back(*itr_vowel);
		}

		// can also do range constructor, but since vector element already exists it is not doable
		//https://www.techiedelight.com/convert-set-vector-cpp/

		VUCO(act, nm, "END OF FUNCTION");
	} // end funct

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

class stateMaker {

	//FORM for STATES from AZGAAR
	/*
	Id,State,Full Name,Form,Color,Capital,Culture,Type,Expansionism,Cells,Burgs,Area mi2,Total Population,Rural Population,Urban Population
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


// namespace alias (aka can type this instead of full namespace path)
namespace fs = std::filesystem; // possible to cutdown on the namespace extensions. using "fs" instead of "std::filesystme" works

const std::vector<std::string> AZGAAR_Government_Forms_Monarchy = {
	"Beylik",
	"Despotate",
	"Dominion",
	"Duchy",
	"Emirate",
	"Empire",
	"Horde",
	"Grand Duchy",
	"Heptarchy",
	"Khaganate",
	"Khanate",
	"Kingdom",
	"Marches",
	"Principality",
	"Satrapy",
	"Shogunate",
	"Sultanate",
	"Tsardom",
	"Ulus",
	"Viceroyalty",

};
const std::vector<std::string> AZGAAR_Government_Forms_Republic = {

	"Chancellery",
	"City-state",
	"Diarchy",
	"Federation",
	"Free City",
	"Most Serene Republic",
	"Oligarchy",
	"Protectorate",
	"Republic",
	"Tetrarchy",
	"Trade Company",
	"Triumvirate",

};
const std::vector<std::string> AZGAAR_Government_Forms_Union = {
	"Confederacy",
	"Confederation",
	"Conglomerate",
	"Commonwealth",
	"League",
	"Union",
	"United Hordes",
	"United Kingdom",
	"United Provinces",
	"United Republic",
	"United States",
	"United Tribes",


};
const std::vector<std::string> AZGAAR_Government_Forms_Theocracy = {
	"Bishopric",
	"Brotherhood",
	"Caliphate",
	"Diocese",
	"Divine Duchy",
	"Divine Grand Duchy",
	"Divine Principality",
	"Divine Kingdom",
	"Divine Empire",
	"Eparchy",
	"Exarchate",
	"Holy State",
	"Imamah",
	"Patriarchate",
	"Theocracy",
};
const std::vector<std::string> AZGAAR_Government_Forms_Anarchy = {

	"Commune",
	"Community",
	"Council",
	"Free Territory",
	"Tribes",



};

const std::vector<std::string> EU4_Government_Forms = {
		"monarchy",
		"republic",
		"tribal",
		"native",
		"theocracy",


};
// Could make this an unordered map
const std::vector<std::string> EU4_Government_Forms_Monarchy = {



};
// Monarchy -> Level 1 
// government = monarchy
// add_government_reform = ___________
/*

				feudalism_reform
				autocracy_reform
				plutocratic_reform
				# indian_sultanate_reform
				# nayankara_reform
				# misl_confederacy_reform
				# rajput_kingdom
				#negusa_nagast
				#solomonic_empire
				#Specific:
				# grand_duchy_reform
				# daimyo
				# indep_daimyo
				# elective_monarchy
				# iqta
				# ottoman_government
				# prussian_monarchy
				# austrian_dual_monarchy
				# principality
				# tsardom
				# mamluk_government
				# feudal_theocracy
				# celestial_empire
				# shogunate
				# english_monarchy
				# mandala_reform
				# revolutionary_empire_reform
				# holy_state_reform
				# austrian_archduchy_reform
				# siamese_absolutism
				# confucian_bureaucracy
				#musa_rule
				#mossi_federal_kingdom
*/
const std::vector<std::string> EU4_Government_Forms_Republic = {



};
// Republic -> Level 1
// government = republic
// add_government_reform = ___________
/*


				oligarchy_reform
				merchants_reform
				# venice_merchants_reform
				pirate_republic_reform
				noble_elite_reform
				free_city
				trading_city
				ambrosian_republic
				veche_republic
				# american_republic
				# federal_republic
				colonial_government
				crown_colony_government
				private_enterprise_colony_government
				self_governing_colony_government
				# dutch_republic
				peasants_republic
				revolutionary_republic_reform
				junior_revolutionary_republic_reform
				presidential_despot_reform
				cossacks_reform
				military_dictatorship_reform
				signoria_reform
				protectorate_parliament_reform
				# prussian_republic_reform
				# united_cantons_reform
				# kongsi_federation
				# millenarian_theocracy_reform



*/
const std::vector<std::string> EU4_Government_Forms_Tribal = {



};
// Tribal -> Level 1
// government = tribal
// add_government_reform = ___________
/*

				steppe_horde
				tribal_federation
				tribal_despotism
				tribal_kingdom
				siberian_tribe
				# gond_kingdom
				great_mongol_state_reform
				stateless_society
				polynesian_kingdom
				polynesian_tribe




*/
const std::vector<std::string> EU4_Government_Forms_Native = {



};
// Native -> Level 1
// government = native
// add_government_reform = ___________
/*
				native_chiefdom_reform
				native_federation_reform
				native_clan_council_reform
				native_hereditary_reform

*/
const std::vector<std::string> EU4_Government_Forms_Theocracy = {



};
// Theocracy -> Level 1
// government = theocracy
// add_government_reform = ___________
/*
				leading_clergy_reform
				monastic_order_reform
				papacy_reform
				holy_state_reform
				# united_cantons_reform

*/



void WriteToFile(const std::string& message, const std::string& file_path);
void YELL(const std::string& message);
short RenderShortFromStringTimes100(const std::string& message);
short StringToShort(const std::string& message);

// CRTL M CRTL H to collapse section

//static std::exception_ptr teptr = nullptr;

int main() {

	// Example Info
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
		std::vector<int> neighbors;
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
	short Xcoord = -1;
	short Ycoord = -1;

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


	//const std::string wanted_file = "C:/Desktop/AZGAAR_to_EU4/OpenAndEdit/infohere/expa.txt"; // works for explicit
	// Create a directory
	const std::string dir_base = "base";
	const std::string dir_azgaar = "AZGAAR";
	const std::string cell_file = "cell_map.geojson";
	const std::string cell_file_t = "cell_map_t.geojson";
	const std::string file_test = "file_test.txt"; // for testing if comparisons work

	std::string file_info;
	std::stringstream buffer{};

	std::string CellNeighbor_str;
	std::fstream fileStream;

	// The .exe will create a subdirectory to its hosting folder, putting this file named file_name in there
	// This process is relative

	std::cout << VERSION_STAMP << std::endl;

// MAIN TRY SECTION
//====================================================================================================================//
//====================================================================================================================//

	try {

		//std::thread EscCheck_obj(WaitForEscape);

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
			// Examples
			/*
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
			*/
			/*
			// https://www.youtube.com/watch?v=_79j_-2xMrQ&ab_channel=BoQian
			std::sregex_iterator pos(example_data.cbegin(), example_data.cend(), exp);
			std::sregex_iterator end;	// Default constructor defines past-the-end iterator
			while (pos != end) {
				for (size_t b = 0; b < pos->size(); b++)
					std::cout << "Matched " << b << pos->str(b) << std::endl;

				pos++;
			}
			*/
			/*
			std::sregex_token_iterator pos2(example_data.cbegin(), example_data.cend(), exp, 0);
			std::sregex_token_iterator end2;
			while (pos2 != end2) {
				std::cout << "FF SubMatched: " << pos2->str() << std::endl;
				pos2++;
			}
			*/

			// READ FROM CELL_MAP or string, EXTRACT VERTEX DATA, ID DATA, and so on
			//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //

			example_data = file_info;
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

			while (CellData_itr != sreg_end) {

				while (CellData_itr != sreg_end) {		// Go through all cell_data matches (coordinates and properties)

					all_cells.push_back(cell_info()); cell_index++;		// Create new cell, pushback onto global vector of all cells, update how many cells there are
// TODO				// Should use size function on the array to find number of cells
					std::cout << "\n[INFO]Cell data chunk for cell " << cell_index << ": " << std::endl;
					CellData_str = CellData_itr->str();
					YELL(CellData_str);

					//Have cell_data chunk from above, need to sift out coordinates and properties
					// Searching chunk at a time, so the following will create verticies
					std::regex_search(CellData_str.cbegin(), CellData_str.cend(), CellData_matches, rex_coords);
					YELL("\n[INFO]Cell coords fetched: ");
					CellCoord_str = CellData_matches[0];
					YELL(CellCoord_str);
					YELL("\n[INFO]Cell vertecies fetched:");
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
						std::cout << "\nVertex " << (vertex_itr) << ": " << std::endl;
						std::cout << std::get<0>(all_cells[cell_index].verticies[vertex_itr]) << std::endl;
						std::cout << std::get<1>(all_cells[cell_index].verticies[vertex_itr]) << std::endl;
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
					
					YELL("[INFO] Cell Neighbors fetched:");
					
					while (CellNeighbor_itr != sreg_end) {

						YELL(CellNeighbor_itr->str(0));
						all_cells[cell_index].neighbors.push_back( StringToShort(	CellNeighbor_itr->str(0) ) );
						CellNeighbor_itr++;
					}


					YELL("\n[INFO]Cell properties fetched");

					
// DO STUFF HERE
// ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛ //
// ⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛ //
					
					// TAKING sifted neighbors AND PLACING THEM in corresponding neighbors vector


					CellData_itr++;
				}// end of while(CellData_itr != sreg_end){


				// CONFIRMATION of obtaining cell info and correctly parsing
				std::cout << "\n[INFO]There are " << all_cells.size() << " many cells";
				std::cout << "\n[INFO]As such, cell index is " << cell_index;

			
				YELL("\n[INFO]Cell Data: ");
				for (int proll = 0; proll < all_cells.size(); proll++) {
					std::cout << "\nCell: " << all_cells[proll].id << "\n";
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

					std::cout << "Neighbors:\n";
					for (int plok = 0; plok < all_cells[proll].neighbors.size(); plok++) {
						std::cout << all_cells[proll].neighbors[plok];
						std::cout << " , ";
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

		//EscCheck_obj.join();

		}//end of try
		catch (std::runtime_error runtime) {		// managing file opening error
			std::cout << "Caught runtime error:" << runtime.what() << std::endl;
		}//end of catch for runtime error
		catch (...) {								// managing all other errors
			std::cout << "Unknown exception\n";
		}//end of any catch

// CREATING THE IMAGE

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
/*
void WaitForEscape() {
	char ch;
	while ((ch = std::cin.get()) != 27) {
		if (ch == 27) {
			teptr = std::current_exception();
		}
	};

}*/

// JS code for Markov Chain pseudo-syllables
/* 

"use strict";

window.Names = (function () {
  let chains = [];

  // calculate Markov chain for a namesbase
  const calculateChain = function (string) {
	const chain = [];
	const array = string.split(",");

	for (const n of array) {
	  let name = n.trim().toLowerCase();
	  const basic = !/[^\u0000-\u007f]/.test(name); // basic chars and English rules can be applied

	  // split word into pseudo-syllables
	  for (let i = -1, syllable = ""; i < name.length; i += syllable.length || 1, syllable = "") {
		let prev = name[i] || ""; // pre-onset letter
		let v = 0; // 0 if no vowels in syllable

		for (let c = i + 1; name[c] && syllable.length < 5; c++) {
		  const that = name[c],
			next = name[c + 1]; // next char
		  syllable += that;
		  if (syllable === " " || syllable === "-") break; // syllable starts with space or hyphen
		  if (!next || next === " " || next === "-") break; // no need to check

		  if (vowel(that)) v = 1; // check if letter is vowel

		  // do not split some diphthongs
		  if (that === "y" && next === "e") continue; // 'ye'
		  if (basic) {
			// English-like
			if (that === "o" && next === "o") continue; // 'oo'
			if (that === "e" && next === "e") continue; // 'ee'
			if (that === "a" && next === "e") continue; // 'ae'
			if (that === "c" && next === "h") continue; // 'ch'
		  }

		  if (vowel(that) === next) break; // two same vowels in a row
		  if (v && vowel(name[c + 2])) break; // syllable has vowel and additional vowel is expected soon
		}

		if (chain[prev] === undefined) chain[prev] = [];
		chain[prev].push(syllable);
	  }
	}

	return chain;
  };

  // update chain for specific base
  const updateChain = i => (chains[i] = nameBases[i] || nameBases[i].b ? calculateChain(nameBases[i].b) : null);

  // update chains for all used bases
  const clearChains = () => (chains = []);

  // generate name using Markov's chain
  const getBase = function (base, min, max, dupl) {
	if (base === undefined) {
	  ERROR && console.error("Please define a base");
	  return;
	}
	if (!chains[base]) updateChain(base);

	const data = chains[base];
	if (!data || data[""] === undefined) {
	  tip("Namesbase " + base + " is incorrect. Please check in namesbase editor", false, "error");
	  ERROR && console.error("Namebase " + base + " is incorrect!");
	  return "ERROR";
	}

	if (!min) min = nameBases[base].min;
	if (!max) max = nameBases[base].max;
	if (dupl !== "") dupl = nameBases[base].d;

	let v = data[""],
	  cur = ra(v),
	  w = "";
	for (let i = 0; i < 20; i++) {
	  if (cur === "") {
		// end of word
		if (w.length < min) {
		  cur = "";
		  w = "";
		  v = data[""];
		} else break;
	  } else {
		if (w.length + cur.length > max) {
		  // word too long
		  if (w.length < min) w += cur;
		  break;
		} else v = data[last(cur)] || data[""];
	  }

	  w += cur;
	  cur = ra(v);
	}

	// parse word to get a final name
	const l = last(w); // last letter
	if (l === "'" || l === " " || l === "-") w = w.slice(0, -1); // not allow some characters at the end

	let name = [...w].reduce(function (r, c, i, d) {
	  if (c === d[i + 1] && !dupl.includes(c)) return r; // duplication is not allowed
	  if (!r.length) return c.toUpperCase();
	  if (r.slice(-1) === "-" && c === " ") return r; // remove space after hyphen
	  if (r.slice(-1) === " ") return r + c.toUpperCase(); // capitalize letter after space
	  if (r.slice(-1) === "-") return r + c.toUpperCase(); // capitalize letter after hyphen
	  if (c === "a" && d[i + 1] === "e") return r; // "ae" => "e"
	  if (i + 2 < d.length && c === d[i + 1] && c === d[i + 2]) return r; // remove three same letters in a row
	  return r + c;
	}, "");

	// join the word if any part has only 1 letter
	if (name.split(" ").some(part => part.length < 2))
	  name = name
		.split(" ")
		.map((p, i) => (i ? p.toLowerCase() : p))
		.join("");

	if (name.length < 2) {
	  ERROR && console.error("Name is too short! Random name will be selected");
	  name = ra(nameBases[base].b.split(","));
	}

	return name;
  };

  // generate name for culture
  const getCulture = function (culture, min, max, dupl) {
	if (culture === undefined) return ERROR && console.error("Please define a culture");
	const base = pack.cultures[culture].base;
	return getBase(base, min, max, dupl);
  };

  // generate short name for culture
  const getCultureShort = function (culture) {
	if (culture === undefined) return ERROR && console.error("Please define a culture");
	return getBaseShort(pack.cultures[culture].base);
  };

  // generate short name for base
  const getBaseShort = function (base) {
	if (nameBases[base] === undefined) {
	  tip(`Namebase ${base} does not exist. Please upload custom namebases of change the base in Cultures Editor`, false, "error");
	  base = 1;
	}
	const min = nameBases[base].min - 1;
	const max = Math.max(nameBases[base].max - 2, min);
	return getBase(base, min, max, "", 0);
  };

  // generate state name based on capital or random name and culture-specific suffix
  const getState = function (name, culture, base) {
	if (name === undefined) return ERROR && console.error("Please define a base name");
	if (culture === undefined && base === undefined) return ERROR && console.error("Please define a culture");
	if (base === undefined) base = pack.cultures[culture].base;

	// exclude endings inappropriate for states name
	if (name.includes(" ")) name = capitalize(name.replace(/ /g, "").toLowerCase()); // don't allow multiword state names
	if (name.length > 6 && name.slice(-4) === "berg") name = name.slice(0, -4); // remove -berg for any
	if (name.length > 5 && name.slice(-3) === "ton") name = name.slice(0, -3); // remove -ton for any

	if (base === 5 && ["sk", "ev", "ov"].includes(name.slice(-2))) name = name.slice(0, -2);
	// remove -sk/-ev/-ov for Ruthenian
	else if (base === 12) return vowel(name.slice(-1)) ? name : name + "u";
	// Japanese ends on any vowel or -u
	else if (base === 18 && P(0.4)) name = vowel(name.slice(0, 1).toLowerCase()) ? "Al" + name.toLowerCase() : "Al " + name; // Arabic starts with -Al

	// no suffix for fantasy bases
	if (base > 32 && base < 42) return name;

	// define if suffix should be used
	if (name.length > 3 && vowel(name.slice(-1))) {
	  if (vowel(name.slice(-2, -1)) && P(0.85)) name = name.slice(0, -2);
	  // 85% for vv
	  else if (P(0.7)) name = name.slice(0, -1);
	  // ~60% for cv
	  else return name;
	} else if (P(0.4)) return name; // 60% for cc and vc

	// define suffix
	let suffix = "ia"; // standard suffix

	const rnd = Math.random(),
	  l = name.length;
	if (base === 3 && rnd < 0.03 && l < 7) suffix = "terra";
	// Italian
	else if (base === 4 && rnd < 0.03 && l < 7) suffix = "terra";
	// Spanish
	else if (base === 13 && rnd < 0.03 && l < 7) suffix = "terra";
	// Portuguese
	else if (base === 2 && rnd < 0.03 && l < 7) suffix = "terre";
	// French
	else if (base === 0 && rnd < 0.5 && l < 7) suffix = "land";
	// German
	else if (base === 1 && rnd < 0.4 && l < 7) suffix = "land";
	// English
	else if (base === 6 && rnd < 0.3 && l < 7) suffix = "land";
	// Nordic
	else if (base === 32 && rnd < 0.1 && l < 7) suffix = "land";
	// generic Human
	else if (base === 7 && rnd < 0.1) suffix = "eia";
	// Greek
	else if (base === 9 && rnd < 0.35) suffix = "maa";
	// Finnic
	else if (base === 15 && rnd < 0.4 && l < 6) suffix = "orszag";
	// Hungarian
	else if (base === 16) suffix = rnd < 0.6 ? "stan" : "ya";
	// Turkish
	else if (base === 10) suffix = "guk";
	// Korean
	else if (base === 11) suffix = " Guo";
	// Chinese
	else if (base === 14) suffix = rnd < 0.5 && l < 6 ? "tlan" : "co";
	// Nahuatl
	else if (base === 17 && rnd < 0.8) suffix = "a";
	// Berber
	else if (base === 18 && rnd < 0.8) suffix = "a"; // Arabic

	return validateSuffix(name, suffix);
  };

  function validateSuffix(name, suffix) {
	if (name.slice(-1 * suffix.length) === suffix) return name; // no suffix if name already ends with it
	const s1 = suffix.charAt(0);
	if (name.slice(-1) === s1) name = name.slice(0, -1); // remove name last letter if it's a suffix first letter
	if (vowel(s1) === vowel(name.slice(-1)) && vowel(s1) === vowel(name.slice(-2, -1))) name = name.slice(0, -1); // remove name last char if 2 last chars are the same type as suffix's 1st
	if (name.slice(-1) === s1) name = name.slice(0, -1); // remove name last letter if it's a suffix first letter
	return name + suffix;
  }

  // generato name for the map
  const getMapName = function (force) {
	if (!force && locked("mapName")) return;
	if (force && locked("mapName")) unlock("mapName");
	const base = P(0.7) ? 2 : P(0.5) ? rand(0, 6) : rand(0, 31);
	if (!nameBases[base]) {
	  tip("Namebase is not found", false, "error");
	  return "";
	}
	const min = nameBases[base].min - 1;
	const max = Math.max(nameBases[base].max - 3, min);
	const baseName = getBase(base, min, max, "", 0);
	const name = P(0.7) ? addSuffix(baseName) : baseName;
	mapName.value = name;
  };

  function addSuffix(name) {
	const suffix = P(0.8) ? "ia" : "land";
	if (suffix === "ia" && name.length > 6) name = name.slice(0, -(name.length - 3));
	else if (suffix === "land" && name.length > 6) name = name.slice(0, -(name.length - 5));
	return validateSuffix(name, suffix);
  }

  const getNameBases = function () {
	// name, min length, max length, letters to allow duplication, multi-word name rate [deprecated]
	// prettier-ignore
	return [
	  // real-world bases by Azgaar:
	  {name: "German", i: 0, min: 5, max: 12, d: "lt", m: 0, b: "Achern,Aichhalden,Aitern,Albbruck,Alpirsbach,Altensteig,Althengstett,Appenweier,Auggen,Wildbad,Badenen,Badenweiler,Baiersbronn,Ballrechten,Bellingen,Berghaupten,Bernau,Biberach,Biederbach,Binzen,Birkendorf,Birkenfeld,Bischweier,Blumberg,Bollen,Bollschweil,Bonndorf,Bosingen,Braunlingen,Breisach,Breisgau,Breitnau,Brigachtal,Buchenbach,Buggingen,Buhl,Buhlertal,Calw,Dachsberg,Dobel,Donaueschingen,Dornhan,Dornstetten,Dottingen,Dunningen,Durbach,Durrheim,Ebhausen,Ebringen,Efringen,Egenhausen,Ehrenkirchen,Ehrsberg,Eimeldingen,Eisenbach,Elzach,Elztal,Emmendingen,Endingen,Engelsbrand,Enz,Enzklosterle,Eschbronn,Ettenheim,Ettlingen,Feldberg,Fischerbach,Fischingen,Fluorn,Forbach,Freiamt,Freiburg,Freudenstadt,Friedenweiler,Friesenheim,Frohnd,Furtwangen,Gaggenau,Geisingen,Gengenbach,Gernsbach,Glatt,Glatten,Glottertal,Gorwihl,Gottenheim,Grafenhausen,Grenzach,Griesbach,Gutach,Gutenbach,Hag,Haiterbach,Hardt,Harmersbach,Hasel,Haslach,Hausach,Hausen,Hausern,Heitersheim,Herbolzheim,Herrenalb,Herrischried,Hinterzarten,Hochenschwand,Hofen,Hofstetten,Hohberg,Horb,Horben,Hornberg,Hufingen,Ibach,Ihringen,Inzlingen,Kandern,Kappel,Kappelrodeck,Karlsbad,Karlsruhe,Kehl,Keltern,Kippenheim,Kirchzarten,Konigsfeld,Krozingen,Kuppenheim,Kussaberg,Lahr,Lauchringen,Lauf,Laufenburg,Lautenbach,Lauterbach,Lenzkirch,Liebenzell,Loffenau,Loffingen,Lorrach,Lossburg,Mahlberg,Malsburg,Malsch,March,Marxzell,Marzell,Maulburg,Monchweiler,Muhlenbach,Mullheim,Munstertal,Murg,Nagold,Neubulach,Neuenburg,Neuhausen,Neuried,Neuweiler,Niedereschach,Nordrach,Oberharmersbach,Oberkirch,Oberndorf,Oberbach,Oberried,Oberwolfach,Offenburg,Ohlsbach,Oppenau,Ortenberg,otigheim,Ottenhofen,Ottersweier,Peterstal,Pfaffenweiler,Pfalzgrafenweiler,Pforzheim,Rastatt,Renchen,Rheinau,Rheinfelden,Rheinmunster,Rickenbach,Rippoldsau,Rohrdorf,Rottweil,Rummingen,Rust,Sackingen,Sasbach,Sasbachwalden,Schallbach,Schallstadt,Schapbach,Schenkenzell,Schiltach,Schliengen,Schluchsee,Schomberg,Schonach,Schonau,Schonenberg,Schonwald,Schopfheim,Schopfloch,Schramberg,Schuttertal,Schwenningen,Schworstadt,Seebach,Seelbach,Seewald,Sexau,Simmersfeld,Simonswald,Sinzheim,Solden,Staufen,Stegen,Steinach,Steinen,Steinmauern,Straubenhardt,Stuhlingen,Sulz,Sulzburg,Teinach,Tiefenbronn,Tiengen,Titisee,Todtmoos,Todtnau,Todtnauberg,Triberg,Tunau,Tuningen,uhlingen,Unterkirnach,Reichenbach,Utzenfeld,Villingen,Villingendorf,Vogtsburg,Vohrenbach,Waldachtal,Waldbronn,Waldkirch,Waldshut,Wehr,Weil,Weilheim,Weisenbach,Wembach,Wieden,Wiesental,Wildberg,Winzeln,Wittlingen,Wittnau,Wolfach,Wutach,Wutoschingen,Wyhlen,Zavelstein"},
	  {name: "English", i: 1, min: 6, max: 11, d: "", m: .1, b: "Abingdon,Albrighton,Alcester,Almondbury,Altrincham,Amersham,Andover,Appleby,Ashboume,Atherstone,Aveton,Axbridge,Aylesbury,Baldock,Bamburgh,Barton,Basingstoke,Berden,Bere,Berkeley,Berwick,Betley,Bideford,Bingley,Birmingham,Blandford,Blechingley,Bodmin,Bolton,Bootham,Boroughbridge,Boscastle,Bossinney,Bramber,Brampton,Brasted,Bretford,Bridgetown,Bridlington,Bromyard,Bruton,Buckingham,Bungay,Burton,Calne,Cambridge,Canterbury,Carlisle,Castleton,Caus,Charmouth,Chawleigh,Chichester,Chillington,Chinnor,Chipping,Chisbury,Cleobury,Clifford,Clifton,Clitheroe,Cockermouth,Coleshill,Combe,Congleton,Crafthole,Crediton,Cuddenbeck,Dalton,Darlington,Dodbrooke,Drax,Dudley,Dunstable,Dunster,Dunwich,Durham,Dymock,Exeter,Exning,Faringdon,Felton,Fenny,Finedon,Flookburgh,Fowey,Frampton,Gateshead,Gatton,Godmanchester,Grampound,Grantham,Guildford,Halesowen,Halton,Harbottle,Harlow,Hatfield,Hatherleigh,Haydon,Helston,Henley,Hertford,Heytesbury,Hinckley,Hitchin,Holme,Hornby,Horsham,Kendal,Kenilworth,Kilkhampton,Kineton,Kington,Kinver,Kirby,Knaresborough,Knutsford,Launceston,Leighton,Lewes,Linton,Louth,Luton,Lyme,Lympstone,Macclesfield,Madeley,Malborough,Maldon,Manchester,Manningtree,Marazion,Marlborough,Marshfield,Mere,Merryfield,Middlewich,Midhurst,Milborne,Mitford,Modbury,Montacute,Mousehole,Newbiggin,Newborough,Newbury,Newenden,Newent,Norham,Northleach,Noss,Oakham,Olney,Orford,Ormskirk,Oswestry,Padstow,Paignton,Penkneth,Penrith,Penzance,Pershore,Petersfield,Pevensey,Pickering,Pilton,Pontefract,Portsmouth,Preston,Quatford,Reading,Redcliff,Retford,Rockingham,Romney,Rothbury,Rothwell,Salisbury,Saltash,Seaford,Seasalter,Sherston,Shifnal,Shoreham,Sidmouth,Skipsea,Skipton,Solihull,Somerton,Southam,Southwark,Standon,Stansted,Stapleton,Stottesdon,Sudbury,Swavesey,Tamerton,Tarporley,Tetbury,Thatcham,Thaxted,Thetford,Thornbury,Tintagel,Tiverton,Torksey,Totnes,Towcester,Tregoney,Trematon,Tutbury,Uxbridge,Wallingford,Wareham,Warenmouth,Wargrave,Warton,Watchet,Watford,Wendover,Westbury,Westcheap,Weymouth,Whitford,Wickwar,Wigan,Wigmore,Winchelsea,Winkleigh,Wiscombe,Witham,Witheridge,Wiveliscombe,Woodbury,Yeovil"},
	  {name: "French", i: 2, min: 5, max: 13, d: "nlrs", m: .1, b: "Adon,Aillant,Amilly,Andonville,Ardon,Artenay,Ascheres,Ascoux,Attray,Aubin,Audeville,Aulnay,Autruy,Auvilliers,Auxy,Aveyron,Baccon,Bardon,Barville,Batilly,Baule,Bazoches,Beauchamps,Beaugency,Beaulieu,Beaune,Bellegarde,Boesses,Boigny,Boiscommun,Boismorand,Boisseaux,Bondaroy,Bonnee,Bonny,Bordes,Bou,Bougy,Bouilly,Boulay,Bouzonville,Bouzy,Boynes,Bray,Breteau,Briare,Briarres,Bricy,Bromeilles,Bucy,Cepoy,Cercottes,Cerdon,Cernoy,Cesarville,Chailly,Chaingy,Chalette,Chambon,Champoulet,Chanteau,Chantecoq,Chapell,Charme,Charmont,Charsonville,Chateau,Chateauneuf,Chatel,Chatenoy,Chatillon,Chaussy,Checy,Chevannes,Chevillon,Chevilly,Chevry,Chilleurs,Choux,Chuelles,Clery,Coinces,Coligny,Combleux,Combreux,Conflans,Corbeilles,Corquilleroy,Cortrat,Coudroy,Coullons,Coulmiers,Courcelles,Courcy,Courtemaux,Courtempierre,Courtenay,Cravant,Crottes,Dadonville,Dammarie,Dampierre,Darvoy,Desmonts,Dimancheville,Donnery,Dordives,Dossainville,Douchy,Dry,Echilleuses,Egry,Engenville,Epieds,Erceville,Ervauville,Escrennes,Escrignelles,Estouy,Faverelles,Fay,Feins,Ferolles,Ferrieres,Fleury,Fontenay,Foret,Foucherolles,Freville,Gatinais,Gaubertin,Gemigny,Germigny,Gidy,Gien,Girolles,Givraines,Gondreville,Grangermont,Greneville,Griselles,Guigneville,Guilly,Gyleslonains,Huetre,Huisseau,Ingrannes,Ingre,Intville,Isdes,Jargeau,Jouy,Juranville,Bussiere,Laas,Ladon,Lailly,Langesse,Leouville,Ligny,Lombreuil,Lorcy,Lorris,Loury,Louzouer,Malesherbois,Marcilly,Mardie,Mareau,Marigny,Marsainvilliers,Melleroy,Menestreau,Merinville,Messas,Meung,Mezieres,Migneres,Mignerette,Mirabeau,Montargis,Montbarrois,Montbouy,Montcresson,Montereau,Montigny,Montliard,Mormant,Morville,Moulinet,Moulon,Nancray,Nargis,Nesploy,Neuville,Neuvy,Nevoy,Nibelle,Nogent,Noyers,Ocre,Oison,Olivet,Ondreville,Onzerain,Orleans,Ormes,Orville,Oussoy,Outarville,Ouzouer,Pannecieres,Pannes,Patay,Paucourt,Pers,Pierrefitte,Pithiverais,Pithiviers,Poilly,Potier,Prefontaines,Presnoy,Pressigny,Puiseaux,Quiers,Ramoulu,Rebrechien,Rouvray,Rozieres,Rozoy,Ruan,Sandillon,Santeau,Saran,Sceaux,Seichebrieres,Semoy,Sennely,Sermaises,Sigloy,Solterre,Sougy,Sully,Sury,Tavers,Thignonville,Thimory,Thorailles,Thou,Tigy,Tivernon,Tournoisis,Trainou,Treilles,Trigueres,Trinay,Vannes,Varennes,Vennecy,Vieilles,Vienne,Viglain,Vignes,Villamblain,Villemandeur,Villemoutiers,Villemurlin,Villeneuve,Villereau,Villevoques,Villorceau,Vimory,Vitry,Vrigny,Ivre"},
	  {name: "Italian", i: 3, min: 5, max: 12, d: "cltr", m: .1, b: "Accumoli,Acquafondata,Acquapendente,Acuto,Affile,Agosta,Alatri,Albano,Allumiere,Alvito,Amaseno,Amatrice,Anagni,Anguillara,Anticoli,Antrodoco,Anzio,Aprilia,Aquino,Arce,Arcinazzo,Ardea,Ariccia,Arlena,Arnara,Arpino,Arsoli,Artena,Ascrea,Atina,Ausonia,Bagnoregio,Barbarano,Bassano,Bassiano,Bellegra,Belmonte,Blera,Bolsena,Bomarzo,Borbona,Borgo,Borgorose,Boville,Bracciano,Broccostella,Calcata,Camerata,Campagnano,Campodimele,Campoli,Canale,Canepina,Canino,Cantalice,Cantalupo,Canterano,Capena,Capodimonte,Capranica,Caprarola,Carbognano,Casalattico,Casalvieri,Casape,Casaprota,Casperia,Cassino,Castelforte,Castelliri,Castello,Castelnuovo,Castiglione,Castro,Castrocielo,Cave,Ceccano,Celleno,Cellere,Ceprano,Cerreto,Cervara,Cervaro,Cerveteri,Ciampino,Ciciliano,Cineto,Cisterna,Cittaducale,Cittareale,Civita,Civitavecchia,Civitella,Colfelice,Collalto,Colle,Colleferro,Collegiove,Collepardo,Collevecchio,Colli,Colonna,Concerviano,Configni,Contigliano,Corchiano,Coreno,Cori,Cottanello,Esperia,Fabrica,Faleria,Fara,Farnese,Ferentino,Fiamignano,Fiano,Filacciano,Filettino,Fiuggi,Fiumicino,Fondi,Fontana,Fonte,Fontechiari,Forano,Formello,Formia,Frascati,Frasso,Frosinone,Fumone,Gaeta,Gallese,Gallicano,Gallinaro,Gavignano,Genazzano,Genzano,Gerano,Giuliano,Gorga,Gradoli,Graffignano,Greccio,Grottaferrata,Grotte,Guarcino,Guidonia,Ischia,Isola,Itri,Jenne,Labico,Labro,Ladispoli,Lanuvio,Lariano,Latera,Lenola,Leonessa,Licenza,Longone,Lubriano,Maenza,Magliano,Mandela,Manziana,Marano,Marcellina,Marcetelli,Marino,Marta,Mazzano,Mentana,Micigliano,Minturno,Mompeo,Montalto,Montasola,Monte,Montebuono,Montefiascone,Monteflavio,Montelanico,Monteleone,Montelibretti,Montenero,Monterosi,Monterotondo,Montopoli,Montorio,Moricone,Morlupo,Morolo,Morro,Nazzano,Nemi,Nepi,Nerola,Nespolo,Nettuno,Norma,Olevano,Onano,Oriolo,Orte,Orvinio,Paganico,Palestrina,Paliano,Palombara,Pastena,Patrica,Percile,Pescorocchiano,Pescosolido,Petrella,Piansano,Picinisco,Pico,Piedimonte,Piglio,Pignataro,Pisoniano,Pofi,Poggio,Poli,Pomezia,Pontecorvo,Pontinia,Ponza,Ponzano,Posta,Pozzaglia,Priverno,Proceno,Prossedi,Riano,Rieti,Rignano,Riofreddo,Ripi,Rivodutri,Rocca,Roccagiovine,Roccagorga,Roccantica,Roccasecca,Roiate,Ronciglione,Roviano,Sabaudia,Sacrofano,Salisano,Sambuci,Santa,Santi,Santopadre,Saracinesco,Scandriglia,Segni,Selci,Sermoneta,Serrone,Settefrati,Sezze,Sgurgola,Sonnino,Sora,Soriano,Sperlonga,Spigno,Stimigliano,Strangolagalli,Subiaco,Supino,Sutri,Tarano,Tarquinia,Terelle,Terracina,Tessennano,Tivoli,Toffia,Tolfa,Torre,Torri,Torrice,Torricella,Torrita,Trevi,Trevignano,Trivigliano,Turania,Tuscania,Vacone,Valentano,Vallecorsa,Vallemaio,Vallepietra,Vallerano,Vallerotonda,Vallinfreda,Valmontone,Varco,Vasanello,Vejano,Velletri,Ventotene,Veroli,Vetralla,Vicalvi,Vico,Vicovaro,Vignanello,Viterbo,Viticuso,Vitorchiano,Vivaro,Zagarolo"},
	  {name: "Castillian", i: 4, min: 5, max: 11, d: "lr", m: 0, b: "Abanades,Ablanque,Adobes,Ajofrin,Alameda,Alaminos,Alarilla,Albalate,Albares,Albarreal,Albendiego,Alcabon,Alcanizo,Alcaudete,Alcocer,Alcolea,Alcoroches,Aldea,Aldeanueva,Algar,Algora,Alhondiga,Alique,Almadrones,Almendral,Almoguera,Almonacid,Almorox,Alocen,Alovera,Alustante,Angon,Anguita,Anover,Anquela,Arbancon,Arbeteta,Arcicollar,Argecilla,Arges,Armallones,Armuna,Arroyo,Atanzon,Atienza,Aunon,Azuqueca,Azutan,Baides,Banos,Banuelos,Barcience,Bargas,Barriopedro,Belvis,Berninches,Borox,Brihuega,Budia,Buenaventura,Bujalaro,Burguillos,Burujon,Bustares,Cabanas,Cabanillas,Calera,Caleruela,Calzada,Camarena,Campillo,Camunas,Canizar,Canredondo,Cantalojas,Cardiel,Carmena,Carranque,Carriches,Casa,Casarrubios,Casas,Casasbuenas,Caspuenas,Castejon,Castellar,Castilforte,Castillo,Castilnuevo,Cazalegas,Cebolla,Cedillo,Cendejas,Centenera,Cervera,Checa,Chequilla,Chillaron,Chiloeches,Chozas,Chueca,Cifuentes,Cincovillas,Ciruelas,Ciruelos,Cobeja,Cobeta,Cobisa,Cogollor,Cogolludo,Condemios,Congostrina,Consuegra,Copernal,Corduente,Corral,Cuerva,Domingo,Dosbarrios,Driebes,Duron,El,Embid,Erustes,Escalona,Escalonilla,Escamilla,Escariche,Escopete,Espinosa,Espinoso,Esplegares,Esquivias,Estables,Estriegana,Fontanar,Fuembellida,Fuensalida,Fuentelsaz,Gajanejos,Galve,Galvez,Garciotum,Gascuena,Gerindote,Guadamur,Henche,Heras,Herreria,Herreruela,Hijes,Hinojosa,Hita,Hombrados,Hontanar,Hontoba,Horche,Hormigos,Huecas,Huermeces,Huerta,Hueva,Humanes,Illan,Illana,Illescas,Iniestola,Irueste,Jadraque,Jirueque,Lagartera,Las,Layos,Ledanca,Lillo,Lominchar,Loranca,Los,Lucillos,Lupiana,Luzaga,Luzon,Madridejos,Magan,Majaelrayo,Malaga,Malaguilla,Malpica,Mandayona,Mantiel,Manzaneque,Maqueda,Maranchon,Marchamalo,Marjaliza,Marrupe,Mascaraque,Masegoso,Matarrubia,Matillas,Mazarete,Mazuecos,Medranda,Megina,Mejorada,Mentrida,Mesegar,Miedes,Miguel,Millana,Milmarcos,Mirabueno,Miralrio,Mocejon,Mochales,Mohedas,Molina,Monasterio,Mondejar,Montarron,Mora,Moratilla,Morenilla,Muduex,Nambroca,Navalcan,Negredo,Noblejas,Noez,Nombela,Noves,Numancia,Nuno,Ocana,Ocentejo,Olias,Olmeda,Ontigola,Orea,Orgaz,Oropesa,Otero,Palmaces,Palomeque,Pantoja,Pardos,Paredes,Pareja,Parrillas,Pastrana,Pelahustan,Penalen,Penalver,Pepino,Peralejos,Peralveche,Pinilla,Pioz,Piqueras,Polan,Portillo,Poveda,Pozo,Pradena,Prados,Puebla,Puerto,Pulgar,Quer,Quero,Quintanar,Quismondo,Rebollosa,Recas,Renera,Retamoso,Retiendas,Riba,Rielves,Rillo,Riofrio,Robledillo,Robledo,Romanillos,Romanones,Rueda,Sacecorbo,Sacedon,Saelices,Salmeron,San,Santa,Santiuste,Santo,Sartajada,Sauca,Sayaton,Segurilla,Selas,Semillas,Sesena,Setiles,Sevilleja,Sienes,Siguenza,Solanillos,Somolinos,Sonseca,Sotillo,Sotodasos,Talavera,Tamajon,Taragudo,Taravilla,Tartanedo,Tembleque,Tendilla,Terzaga,Tierzo,Tordellego,Tordelrabano,Tordesilos,Torija,Torralba,Torre,Torrecilla,Torrecuadrada,Torrejon,Torremocha,Torrico,Torrijos,Torrubia,Tortola,Tortuera,Tortuero,Totanes,Traid,Trijueque,Trillo,Turleque,Uceda,Ugena,Ujados,Urda,Utande,Valdarachas,Valdesotos,Valhermoso,Valtablado,Valverde,Velada,Viana,Vinuelas,Yebes,Yebra,Yelamos,Yeles,Yepes,Yuncler,Yunclillos,Yuncos,Yunquera,Zaorejas,Zarzuela,Zorita"},
	  {name: "Ruthenian", i: 5, min: 5, max: 10, d: "", m: 0, b: "Belgorod,Beloberezhye,Belyi,Belz,Berestiy,Berezhets,Berezovets,Berezutsk,Bobruisk,Bolonets,Borisov,Borovsk,Bozhesk,Bratslav,Bryansk,Brynsk,Buryn,Byhov,Chechersk,Chemesov,Cheremosh,Cherlen,Chern,Chernigov,Chernitsa,Chernobyl,Chernogorod,Chertoryesk,Chetvertnia,Demyansk,Derevesk,Devyagoresk,Dichin,Dmitrov,Dorogobuch,Dorogobuzh,Drestvin,Drokov,Drutsk,Dubechin,Dubichi,Dubki,Dubkov,Dveren,Galich,Glebovo,Glinsk,Goloty,Gomiy,Gorodets,Gorodische,Gorodno,Gorohovets,Goroshin,Gorval,Goryshon,Holm,Horobor,Hoten,Hotin,Hotmyzhsk,Ilovech,Ivan,Izborsk,Izheslavl,Kamenets,Kanev,Karachev,Karna,Kavarna,Klechesk,Klyapech,Kolomyya,Kolyvan,Kopyl,Korec,Kornik,Korochunov,Korshev,Korsun,Koshkin,Kotelno,Kovyla,Kozelsk,Kozelsk,Kremenets,Krichev,Krylatsk,Ksniatin,Kulatsk,Kursk,Kursk,Lebedev,Lida,Logosko,Lomihvost,Loshesk,Loshichi,Lubech,Lubno,Lubutsk,Lutsk,Luchin,Luki,Lukoml,Luzha,Lvov,Mtsensk,Mdin,Medniki,Melecha,Merech,Meretsk,Mescherskoe,Meshkovsk,Metlitsk,Mezetsk,Mglin,Mihailov,Mikitin,Mikulino,Miloslavichi,Mogilev,Mologa,Moreva,Mosalsk,Moschiny,Mozyr,Mstislav,Mstislavets,Muravin,Nemech,Nemiza,Nerinsk,Nichan,Novgorod,Novogorodok,Obolichi,Obolensk,Obolensk,Oleshsk,Olgov,Omelnik,Opoka,Opoki,Oreshek,Orlets,Osechen,Oster,Ostrog,Ostrov,Perelai,Peremil,Peremyshl,Pererov,Peresechen,Perevitsk,Pereyaslav,Pinsk,Ples,Polotsk,Pronsk,Proposhesk,Punia,Putivl,Rechitsa,Rodno,Rogachev,Romanov,Romny,Roslavl,Rostislavl,Rostovets,Rsha,Ruza,Rybchesk,Rylsk,Rzhavesk,Rzhev,Rzhischev,Sambor,Serensk,Serensk,Serpeysk,Shilov,Shuya,Sinech,Sizhka,Skala,Slovensk,Slutsk,Smedin,Sneporod,Snitin,Snovsk,Sochevo,Sokolec,Starica,Starodub,Stepan,Sterzh,Streshin,Sutesk,Svinetsk,Svisloch,Terebovl,Ternov,Teshilov,Teterin,Tiversk,Torchevsk,Toropets,Torzhok,Tripolye,Trubchevsk,Tur,Turov,Usvyaty,Uteshkov,Vasilkov,Velil,Velye,Venev,Venicha,Verderev,Vereya,Veveresk,Viazma,Vidbesk,Vidychev,Voino,Volodimer,Volok,Volyn,Vorobesk,Voronich,Voronok,Vorotynsk,Vrev,Vruchiy,Vselug,Vyatichsk,Vyatka,Vyshegorod,Vyshgorod,Vysokoe,Yagniatin,Yaropolch,Yasenets,Yuryev,Yuryevets,Zaraysk,Zhitomel,Zholvazh,Zizhech,Zubkov,Zudechev,Zvenigorod"},
	  {name: "Nordic", i: 6, min: 6, max: 10, d: "kln", m: .1, b: "Akureyri,Aldra,Alftanes,Andenes,Austbo,Auvog,Bakkafjordur,Ballangen,Bardal,Beisfjord,Bifrost,Bildudalur,Bjerka,Bjerkvik,Bjorkosen,Bliksvaer,Blokken,Blonduos,Bolga,Bolungarvik,Borg,Borgarnes,Bosmoen,Bostad,Bostrand,Botsvika,Brautarholt,Breiddalsvik,Bringsli,Brunahlid,Budardalur,Byggdakjarni,Dalvik,Djupivogur,Donnes,Drageid,Drangsnes,Egilsstadir,Eiteroga,Elvenes,Engavogen,Ertenvog,Eskifjordur,Evenes,Eyrarbakki,Fagernes,Fallmoen,Fellabaer,Fenes,Finnoya,Fjaer,Fjelldal,Flakstad,Flateyri,Flostrand,Fludir,Gardaber,Gardur,Gimstad,Givaer,Gjeroy,Gladstad,Godoya,Godoynes,Granmoen,Gravdal,Grenivik,Grimsey,Grindavik,Grytting,Hafnir,Halsa,Hauganes,Haugland,Hauknes,Hella,Helland,Hellissandur,Hestad,Higrav,Hnifsdalur,Hofn,Hofsos,Holand,Holar,Holen,Holkestad,Holmavik,Hopen,Hovden,Hrafnagil,Hrisey,Husavik,Husvik,Hvammstangi,Hvanneyri,Hveragerdi,Hvolsvollur,Igeroy,Indre,Inndyr,Innhavet,Innes,Isafjordur,Jarklaustur,Jarnsreykir,Junkerdal,Kaldvog,Kanstad,Karlsoy,Kavosen,Keflavik,Kjelde,Kjerstad,Klakk,Kopasker,Kopavogur,Korgen,Kristnes,Krutoga,Krystad,Kvina,Lande,Laugar,Laugaras,Laugarbakki,Laugarvatn,Laupstad,Leines,Leira,Leiren,Leland,Lenvika,Loding,Lodingen,Lonsbakki,Lopsmarka,Lovund,Luroy,Maela,Melahverfi,Meloy,Mevik,Misvaer,Mornes,Mosfellsber,Moskenes,Myken,Naurstad,Nesberg,Nesjahverfi,Nesset,Nevernes,Obygda,Ofoten,Ogskardet,Okervika,Oknes,Olafsfjordur,Oldervika,Olstad,Onstad,Oppeid,Oresvika,Orsnes,Orsvog,Osmyra,Overdal,Prestoya,Raudalaekur,Raufarhofn,Reipo,Reykholar,Reykholt,Reykjahlid,Rif,Rinoya,Rodoy,Rognan,Rosvika,Rovika,Salhus,Sanden,Sandgerdi,Sandoker,Sandset,Sandvika,Saudarkrokur,Selfoss,Selsoya,Sennesvik,Setso,Siglufjordur,Silvalen,Skagastrond,Skjerstad,Skonland,Skorvogen,Skrova,Sleneset,Snubba,Softing,Solheim,Solheimar,Sorarnoy,Sorfugloy,Sorland,Sormela,Sorvaer,Sovika,Stamsund,Stamsvika,Stave,Stokka,Stokkseyri,Storjord,Storo,Storvika,Strand,Straumen,Strendene,Sudavik,Sudureyri,Sundoya,Sydalen,Thingeyri,Thorlakshofn,Thorshofn,Tjarnabyggd,Tjotta,Tosbotn,Traelnes,Trofors,Trones,Tverro,Ulvsvog,Unnstad,Utskor,Valla,Vandved,Varmahlid,Vassos,Vevelstad,Vidrek,Vik,Vikholmen,Vogar,Vogehamn,Vopnafjordur"},
	  {name: "Greek", i: 7, min: 5, max: 11, d: "s", m: .1, b: "Abdera,Abila,Abydos,Acanthus,Acharnae,Actium,Adramyttium,Aegae,Aegina,Aegium,Aenus,Agrinion,Aigosthena,Akragas,Akrai,Akrillai,Akroinon,Akrotiri,Alalia,Alexandreia,Alexandretta,Alexandria,Alinda,Amarynthos,Amaseia,Ambracia,Amida,Amisos,Amnisos,Amphicaea,Amphigeneia,Amphipolis,Amphissa,Ankon,Antigona,Antipatrea,Antioch,Antioch,Antiochia,Andros,Apamea,Aphidnae,Apollonia,Argos,Arsuf,Artanes,Artemita,Argyroupoli,Asine,Asklepios,Aspendos,Assus,Astacus,Athenai,Athmonia,Aytos,Ancient,Baris,Bhrytos,Borysthenes,Berge,Boura,Bouthroton,Brauron,Byblos,Byllis,Byzantium,Bythinion,Callipolis,Cebrene,Chalcedon,Calydon,Carystus,Chamaizi,Chalcis,Chersonesos,Chios,Chytri,Clazomenae,Cleonae,Cnidus,Colosse,Corcyra,Croton,Cyme,Cyrene,Cythera,Decelea,Delos,Delphi,Demetrias,Dicaearchia,Dimale,Didyma,Dion,Dioscurias,Dodona,Dorylaion,Dyme,Edessa,Elateia,Eleusis,Eleutherna,Emporion,Ephesus,Ephyra,Epidamnos,Epidauros,Eresos,Eretria,Erythrae,Eubea,Gangra,Gaza,Gela,Golgi,Gonnos,Gorgippia,Gournia,Gortyn,Gythium,Hagios,Hagia,Halicarnassus,Halieis,Helike,Heliopolis,Hellespontos,Helorus,Hemeroskopeion,Heraclea,Hermione,Hermonassa,Hierapetra,Hierapolis,Himera,Histria,Hubla,Hyele,Ialysos,Iasus,Idalium,Imbros,Iolcus,Itanos,Ithaca,Juktas,Kallipolis,Kamares,Kameiros,Kannia,Kamarina,Kasmenai,Katane,Kerkinitida,Kepoi,Kimmerikon,Kios,Klazomenai,Knidos,Knossos,Korinthos,Kos,Kourion,Kume,Kydonia,Kynos,Kyrenia,Lamia,Lampsacus,Laodicea,Lapithos,Larissa,Lato,Laus,Lebena,Lefkada,Lekhaion,Leibethra,Leontinoi,Lepreum,Lessa,Lilaea,Lindus,Lissus,Epizephyrian,Madytos,Magnesia,Mallia,Mantineia,Marathon,Marmara,Maroneia,Masis,Massalia,Megalopolis,Megara,Mesembria,Messene,Metapontum,Methana,Methone,Methumna,Miletos,Misenum,Mochlos,Monastiraki,Morgantina,Mulai,Mukenai,Mylasa,Myndus,Myonia,Myra,Myrmekion,Mutilene,Myos,Nauplios,Naucratis,Naupactus,Naxos,Neapoli,Neapolis,Nemea,Nicaea,Nicopolis,Nirou,Nymphaion,Nysa,Oenoe,Oenus,Odessos,Olbia,Olous,Olympia,Olynthus,Opus,Orchomenus,Oricos,Orestias,Oreus,Oropus,Onchesmos,Pactye,Pagasae,Palaikastro,Pandosia,Panticapaeum,Paphos,Parium,Paros,Parthenope,Patrae,Pavlopetri,Pegai,Pelion,Peiraies,Pella,Percote,Pergamum,Petsofa,Phaistos,Phaleron,Phanagoria,Pharae,Pharnacia,Pharos,Phaselis,Philippi,Pithekussa,Philippopolis,Platanos,Phlius,Pherae,Phocaea,Pinara,Pisa,Pitane,Pitiunt,Pixous,Plataea,Poseidonia,Potidaea,Priapus,Priene,Prousa,Pseira,Psychro,Pteleum,Pydna,Pylos,Pyrgos,Rhamnus,Rhegion,Rhithymna,Rhodes,Rhypes,Rizinia,Salamis,Same,Samos,Scyllaeum,Selinus,Seleucia,Semasus,Sestos,Scidrus,Sicyon,Side,Sidon,Siteia,Sinope,Siris,Sklavokampos,Smyrna,Soli,Sozopolis,Sparta,Stagirus,Stratos,Stymphalos,Sybaris,Surakousai,Taras,Tanagra,Tanais,Tauromenion,Tegea,Temnos,Tenedos,Tenea,Teos,Thapsos,Thassos,Thebai,Theodosia,Therma,Thespiae,Thronion,Thoricus,Thurii,Thyreum,Thyria,Tiruns,Tithoraea,Tomis,Tragurion,Trapeze,Trapezus,Tripolis,Troizen,Troliton,Troy,Tylissos,Tyras,Tyros,Tyritake,Vasiliki,Vathypetros,Zakynthos,Zakros,Zankle"},
	  {name: "Roman", i: 8, min: 6, max: 11, d: "ln", m: .1, b: "Abila,Adflexum,Adnicrem,Aelia,Aelius,Aeminium,Aequum,Agrippina,Agrippinae,Ala,Albanianis,Ambianum,Andautonia,Apulum,Aquae,Aquaegranni,Aquensis,Aquileia,Aquincum,Arae,Argentoratum,Ariminum,Ascrivium,Atrebatum,Atuatuca,Augusta,Aurelia,Aurelianorum,Batavar,Batavorum,Belum,Biriciana,Blestium,Bonames,Bonna,Bononia,Borbetomagus,Bovium,Bracara,Brigantium,Burgodunum,Caesaraugusta,Caesarea,Caesaromagus,Calleva,Camulodunum,Cannstatt,Cantiacorum,Capitolina,Castellum,Castra,Castrum,Cibalae,Clausentum,Colonia,Concangis,Condate,Confluentes,Conimbriga,Corduba,Coria,Corieltauvorum,Corinium,Coriovallum,Cornoviorum,Danum,Deva,Divodurum,Dobunnorum,Drusi,Dubris,Dumnoniorum,Durnovaria,Durocobrivis,Durocornovium,Duroliponte,Durovernum,Durovigutum,Eboracum,Edetanorum,Emerita,Emona,Euracini,Faventia,Flaviae,Florentia,Forum,Gerulata,Gerunda,Glevensium,Hadriani,Herculanea,Isca,Italica,Iulia,Iuliobrigensium,Iuvavum,Lactodurum,Lagentium,Lauri,Legionis,Lemanis,Lentia,Lepidi,Letocetum,Lindinis,Lindum,Londinium,Lopodunum,Lousonna,Lucus,Lugdunum,Luguvalium,Lutetia,Mancunium,Marsonia,Martius,Massa,Matilo,Mattiacorum,Mediolanum,Mod,Mogontiacum,Moridunum,Mursa,Naissus,Nervia,Nida,Nigrum,Novaesium,Noviomagus,Olicana,Ovilava,Parisiorum,Partiscum,Paterna,Pistoria,Placentia,Pollentia,Pomaria,Pons,Portus,Praetoria,Praetorium,Pullum,Ragusium,Ratae,Raurica,Regina,Regium,Regulbium,Rigomagus,Roma,Romula,Rutupiae,Salassorum,Salernum,Salona,Scalabis,Segovia,Silurum,Sirmium,Siscia,Sorviodurum,Sumelocenna,Tarraco,Taurinorum,Theranda,Traiectum,Treverorum,Tungrorum,Turicum,Ulpia,Valentia,Venetiae,Venta,Verulamium,Vesontio,Vetera,Victoriae,Victrix,Villa,Viminacium,Vindelicorum,Vindobona,Vinovia,Viroconium"},
	  {name: "Finnic", i: 9, min: 5, max: 11, d: "akiut", m: 0, b: "Aanekoski,Abjapaluoja,Ahlainen,Aholanvaara,Ahtari,Aijala,Aimala,Akaa,Alajarvi,Alatornio,Alavus,Antsla,Aspo,Bennas,Bjorkoby,Elva,Emasalo,Espoo,Esse,Evitskog,Forssa,Haapajarvi,Haapamaki,Haapavesi,Haapsalu,Haavisto,Hameenlinna,Hameenmaki,Hamina,Hanko,Harjavalta,Hattuvaara,Haukipudas,Hautajarvi,Havumaki,Heinola,Hetta,Hinkabole,Hirmula,Hossa,Huittinen,Husula,Hyryla,Hyvinkaa,Iisalmi,Ikaalinen,Ilmola,Imatra,Inari,Iskmo,Itakoski,Jamsa,Jarvenpaa,Jeppo,Jioesuu,Jiogeva,Joensuu,Jokela,Jokikyla,Jokisuu,Jormua,Juankoski,Jungsund,Jyvaskyla,Kaamasmukka,Kaarina,Kajaani,Kalajoki,Kallaste,Kankaanpaa,Kannus,Kardla,Karesuvanto,Karigasniemi,Karkkila,Karkku,Karksinuia,Karpankyla,Kaskinen,Kasnas,Kauhajoki,Kauhava,Kauniainen,Kauvatsa,Kehra,Keila,Kellokoski,Kelottijarvi,Kemi,Kemijarvi,Kerava,Keuruu,Kiikka,Kiipu,Kilinginiomme,Kiljava,Kilpisjarvi,Kitee,Kiuruvesi,Kivesjarvi,Kiviioli,Kivisuo,Klaukkala,Klovskog,Kohtlajarve,Kokemaki,Kokkola,Kolho,Koria,Koskue,Kotka,Kouva,Kouvola,Kristiina,Kaupunki,Kuhmo,Kunda,Kuopio,Kuressaare,Kurikka,Kusans,Kuusamo,Kylmalankyla,Lahti,Laitila,Lankipohja,Lansikyla,Lappeenranta,Lapua,Laurila,Lautiosaari,Lepsama,Liedakkala,Lieksa,Lihula,Littoinen,Lohja,Loimaa,Loksa,Loviisa,Luohuanylipaa,Lusi,Maardu,Maarianhamina,Malmi,Mantta,Masaby,Masala,Matasvaara,Maula,Miiluranta,Mikkeli,Mioisakula,Munapirtti,Mustvee,Muurahainen,Naantali,Nappa,Narpio,Nickby,Niinimaa,Niinisalo,Nikkila,Nilsia,Nivala,Nokia,Nummela,Nuorgam,Nurmes,Nuvvus,Obbnas,Oitti,Ojakkala,Ollola,onningeby,Orimattila,Orivesi,Otanmaki,Otava,Otepaa,Oulainen,Oulu,Outokumpu,Paavola,Paide,Paimio,Pakankyla,Paldiski,Parainen,Parkano,Parkumaki,Parola,Perttula,Pieksamaki,Pietarsaari,Pioltsamaa,Piolva,Pohjavaara,Porhola,Pori,Porrasa,Porvoo,Pudasjarvi,Purmo,Pussi,Pyhajarvi,Raahe,Raasepori,Raisio,Rajamaki,Rakvere,Rapina,Rapla,Rauma,Rautio,Reposaari,Riihimaki,Rovaniemi,Roykka,Ruonala,Ruottala,Rutalahti,Saarijarvi,Salo,Sastamala,Saue,Savonlinna,Seinajoki,Sillamae,Sindi,Siuntio,Somero,Sompujarvi,Suonenjoki,Suurejaani,Syrjantaka,Tampere,Tamsalu,Tapa,Temmes,Tiorva,Tormasenvaara,Tornio,Tottijarvi,Tulppio,Turenki,Turi,Tuukkala,Tuurala,Tuuri,Tuuski,Ulvila,Unari,Upinniemi,Utti,Uusikaarlepyy,Uusikaupunki,Vaaksy,Vaalimaa,Vaarinmaja,Vaasa,Vainikkala,Valga,Valkeakoski,Vantaa,Varkaus,Vehkapera,Vehmasmaki,Vieki,Vierumaki,Viitasaari,Viljandi,Vilppula,Viohma,Vioru,Virrat,Ylike,Ylivieska,Ylojarvi"},
	  {name: "Korean", i: 10, min: 5, max: 11, d: "", m: 0, b: "Aewor,Andong,Angang,Anjung,Anmyeon,Ansan,Anseong,Anyang,Aphae,Apo,Asan,Baebang,Baekseok,Baeksu,Beobwon,Beolgyo,Beomseo,Boeun,Bongdam,Bongdong,Bonghwa,Bongyang,Boryeong,Boseong,Buan,Bubal,Bucheon,Buksam,Busan,Busan,Busan,Buyeo,Changnyeong,Changwon,Cheonan,Cheongdo,Cheongjin,Cheongju,Cheongju,Cheongsong,Cheongyang,Cheorwon,Chirwon,Chowol,Chuncheon,Chuncheon,Chungju,Chungmu,Daecheon,Daedeok,Daegaya,Daegu,Daegu,Daegu,Daejeon,Daejeon,Daejeon,Daejeong,Daesan,Damyang,Dangjin,Danyang,Dasa,Dogye,Dolsan,Dong,Dongducheon,Donggwangyang,Donghae,Dongsong,Doyang,Eonyang,Eumseong,Gaeseong,Galmal,Gampo,Ganam,Ganggyeong,Ganghwa,Gangjin,Gangneung,Ganseong,Gapyeong,Gaun,Gaya,Geochang,Geoje,Geojin,Geoncheon,Geumho,Geumil,Geumsan,Geumseong,Geumwang,Gijang,Gimcheon,Gimhae,Gimhwa,Gimje,Gimpo,Goa,Gochang,Gochon,Goesan,Gohan,Goheung,Gokseong,Gongdo,Gongju,Gonjiam,Goseong,Goyang,Gujwa,Gumi,Gungnae,Gunpo,Gunsan,Gunsan,Gunwi,Guri,Gurye,Guryongpo,Gwacheon,Gwangcheon,Gwangju,Gwangju,Gwangju,Gwangju,Gwangmyeong,Gwangyang,Gwansan,Gyeongju,Gyeongsan,Gyeongseong,Gyeongseong,Gyeryong,Hadong,Haeju,Haenam,Hamchang,Hamheung,Hampyeong,Hamyang,Hamyeol,Hanam,Hanrim,Hapcheon,Hapdeok,Hayang,Heunghae,Heungnam,Hoengseong,Hongcheon,Hongnong,Hongseong,Hwacheon,Hwado,Hwando,Hwaseong,Hwasun,Hwawon,Hyangnam,Icheon,Iksan,Illo,Imsil,Incheon,Incheon,Incheon,Inje,Iri,Iri,Jangan,Janghang,Jangheung,Janghowon,Jangseong,Jangseungpo,Jangsu,Jecheon,Jeju,Jeomchon,Jeongeup,Jeonggwan,Jeongju,Jeongok,Jeongseon,Jeonju,Jeonju,Jeungpyeong,Jido,Jiksan,Jillyang,Jinan,Jincheon,Jindo,Jingeon,Jinhae,Jinjeop,Jinju,Jinju,Jinnampo,Jinyeong,Jocheon,Jochiwon,Jori,Judeok,Jumunjin,Maepo,Mangyeong,Masan,Masan,Migeum,Miryang,Mokcheon,Mokpo,Mokpo,Muan,Muju,Mungyeong,Munmak,Munsan,Munsan,Naeseo,Naesu,Najin,Naju,Namhae,Namji,Nampyeong,Namwon,Namyang,Namyangju,Nohwa,Nongong,Nonsan,Ochang,Ocheon,Oedong,Okcheon,Okgu,Onam,Onsan,Onyang,Opo,Osan,Osong,Paengseong,Paju,Pocheon,Pogok,Pohang,Poseung,Punggi,Pungsan,Pyeongchang,Pyeonghae,Pyeongtaek,Pyeongyang,Sabi,Sabuk,Sacheon,Samcheok,Samcheonpo,Samho,Samhyang,Samnangjin,Samrye,Sancheong,Sangdong,Sangju,Sanyang,Sapgyo,Sariwon,Sejong,Seocheon,Seogwipo,Seokjeok,Seonggeo,Seonghwan,Seongjin,Seongju,Seongnam,Seongsan,Seonsan,Seosan,Seoul,Seungju,Siheung,Sinbuk,Sindong,Sineuiju,Sintaein,Soheul,Sokcho,Songak,Songjeong,Songnim,Songtan,Sunchang,Suncheon,Suwon,Taean,Taebaek,Tongjin,Tongyeong,Uijeongbu,Uiryeong,Uiseong,Uiwang,Ujeong,Uljin,Ulleung,Ulsan,Ulsan,Unbong,Ungcheon,Ungjin,Wabu,Waegwan,Wando,Wanggeomseong,Wiryeseong,Wondeok,Wonju,Wonsan,Yangchon,Yanggu,Yangju,Yangpyeong,Yangsan,Yangyang,Yecheon,Yeocheon,Yeoju,Yeomchi,Yeoncheon,Yeongam,Yeongcheon,Yeongdeok,Yeongdong,Yeonggwang,Yeongju,Yeongwol,Yeongyang,Yeonil,Yeonmu,Yeosu,Yesan,Yongin,Yongjin,Yugu,Wayang"},
	  {name: "Chinese", i: 11, min: 5, max: 10, d: "", m: 0, b: "Anding,Anlu,Anqing,Anshun,Baan,Baixing,Banyang,Baoding,Baoqing,Binzhou,Caozhou,Changbai,Changchun,Changde,Changling,Changsha,Changtu,Changzhou,Chaozhou,Cheli,Chengde,Chengdu,Chenzhou,Chizhou,Chongqing,Chuxiong,Chuzhou,Dading,Dali,Daming,Datong,Daxing,Dean,Dengke,Dengzhou,Deqing,Dexing,Dihua,Dingli,Dongan,Dongchang,Dongchuan,Dongping,Duyun,Fengtian,Fengxiang,Fengyang,Fenzhou,Funing,Fuzhou,Ganzhou,Gaoyao,Gaozhou,Gongchang,Guangnan,Guangning,Guangping,Guangxin,Guangzhou,Guide,Guilin,Guiyang,Hailong,Hailun,Hangzhou,Hanyang,Hanzhong,Heihe,Hejian,Henan,Hengzhou,Hezhong,Huaian,Huaide,Huaiqing,Huanglong,Huangzhou,Huining,Huizhou,Hulan,Huzhou,Jiading,Jian,Jianchang,Jiande,Jiangning,Jiankang,Jianning,Jiaxing,Jiayang,Jilin,Jinan,Jingjiang,Jingzhao,Jingzhou,Jinhua,Jinzhou,Jiujiang,Kaifeng,Kaihua,Kangding,Kuizhou,Laizhou,Lanzhou,Leizhou,Liangzhou,Lianzhou,Liaoyang,Lijiang,Linan,Linhuang,Linjiang,Lintao,Liping,Liuzhou,Longan,Longjiang,Longqing,Longxing,Luan,Lubin,Lubin,Luzhou,Mishan,Nanan,Nanchang,Nandian,Nankang,Nanning,Nanyang,Nenjiang,Ningan,Ningbo,Ningguo,Ninguo,Ningwu,Ningxia,Ningyuan,Pingjiang,Pingle,Pingliang,Pingyang,Puer,Puzhou,Qianzhou,Qingyang,Qingyuan,Qingzhou,Qiongzhou,Qujing,Quzhou,Raozhou,Rende,Ruian,Ruizhou,Runing,Shafeng,Shajing,Shaoqing,Shaowu,Shaoxing,Shaozhou,Shinan,Shiqian,Shouchun,Shuangcheng,Shulei,Shunde,Shunqing,Shuntian,Shuoping,Sicheng,Sien,Sinan,Sizhou,Songjiang,Suiding,Suihua,Suining,Suzhou,Taian,Taibei,Tainan,Taiping,Taiwan,Taiyuan,Taizhou,Taonan,Tengchong,Tieli,Tingzhou,Tongchuan,Tongqing,Tongren,Tongzhou,Weihui,Wensu,Wenzhou,Wuchang,Wuding,Wuzhou,Xian,Xianchun,Xianping,Xijin,Xiliang,Xincheng,Xingan,Xingde,Xinghua,Xingjing,Xingqing,Xingyi,Xingyuan,Xingzhong,Xining,Xinmen,Xiping,Xuanhua,Xunzhou,Xuzhou,Yanan,Yangzhou,Yanji,Yanping,Yanqi,Yanzhou,Yazhou,Yichang,Yidu,Yilan,Yili,Yingchang,Yingde,Yingtian,Yingzhou,Yizhou,Yongchang,Yongping,Yongshun,Yongzhou,Yuanzhou,Yuezhou,Yulin,Yunnan,Yunyang,Zezhou,Zhangde,Zhangzhou,Zhaoqing,Zhaotong,Zhenan,Zhending,Zhengding,Zhenhai,Zhenjiang,Zhenxi,Zhenyun,Zhongshan,Zunyi"},
	  {name: "Japanese", i: 12, min: 4, max: 10, d: "", m: 0, b: "Abira,Aga,Aikawa,Aizumisato,Ajigasawa,Akkeshi,Amagi,Ami,Anan,Ando,Asakawa,Ashikita,Bandai,Biratori,China,Chonan,Esashi,Fuchu,Fujimi,Funagata,Genkai,Godo,Goka,Gonohe,Gyokuto,Haboro,Hamatonbetsu,Happo,Harima,Hashikami,Hayashima,Heguri,Hidaka,Higashiagatsuma,Higashiura,Hiranai,Hirogawa,Hiroo,Hodatsushimizu,Hoki,Hokuei,Hokuryu,Horokanai,Ibigawa,Ichikai,Ichikawamisato,Ichinohe,Iide,Iijima,Iizuna,Ikawa,Inagawa,Itakura,Iwaizumi,Iwate,Kagamino,Kaisei,Kamifurano,Kamiita,Kamijima,Kamikawa,Kamikawa,Kamikawa,Kaminokawa,Kamishihoro,Kamitonda,Kamiyama,Kanda,Kanna,Kasagi,Kasuya,Katsuura,Kawabe,Kawagoe,Kawajima,Kawamata,Kawamoto,Kawanehon,Kawanishi,Kawara,Kawasaki,Kawasaki,Kawatana,Kawazu,Kihoku,Kikonai,Kin,Kiso,Kitagata,Kitajima,Kiyama,Kiyosato,Kofu,Koge,Kohoku,Kokonoe,Kora,Kosa,Kosaka,Kotohira,Kudoyama,Kumejima,Kumenan,Kumiyama,Kunitomi,Kurate,Kushimoto,Kutchan,Kyonan,Kyotamba,Mashike,Matsumae,Mifune,Mihama,Minabe,Minami,Minamiechizen,Minamioguni,Minamiosumi,Minamitane,Misaki,Misasa,Misato,Miyashiro,Miyoshi,Mori,Moseushi,Mutsuzawa,Nagaizumi,Nagatoro,Nagayo,Nagomi,Nakadomari,Nakanojo,Nakashibetsu,Nakatosa,Namegawa,Namie,Nanbu,Nanporo,Naoshima,Nasu,Niseko,Nishihara,Nishiizu,Nishikatsura,Nishikawa,Nishinoshima,Nishiwaga,Nogi,Noto,Nyuzen,Oarai,Obuse,Odai,Ogawara,Oharu,Oi,Oirase,Oishida,Oiso,Oizumi,Oji,Okagaki,Oketo,Okutama,Omu,Ono,Osaki,Osakikamijima,Otobe,Otsuki,Owani,Reihoku,Rifu,Rikubetsu,Rishiri,Rokunohe,Ryuo,Saka,Sakuho,Samani,Satsuma,Sayo,Saza,Setana,Shakotan,Shibayama,Shikama,Shimamoto,Shimizu,Shimokawa,Shintomi,Shirakawa,Shisui,Shitara,Sobetsu,Sue,Sumita,Suooshima,Suttsu,Tabuse,Tachiarai,Tadami,Tadaoka,Taiji,Taiki,Takachiho,Takahama,Taketoyo,Tako,Taragi,Tateshina,Tatsugo,Tawaramoto,Teshikaga,Tobe,Toin,Tokigawa,Toma,Tomioka,Tonosho,Tosa,Toyo,Toyokoro,Toyotomi,Toyoyama,Tsubata,Tsubetsu,Tsukigata,Tsunan,Tsuno,Tsuwano,Umi,Wakasa,Yamamoto,Yamanobe,Yamatsuri,Yanaizu,Yasuda,Yoichi,Yonaguni,Yoro,Yoshino,Yubetsu,Yugawara,Yuni,Yusuhara,Yuza"},
	  {name: "Portuguese", i: 13, min: 5, max: 11, d: "", m: .1, b: "Abrigada,Afonsoeiro,Agueda,Aguiar,Aguilada,Alagoas,Alagoinhas,Albufeira,Alcacovas,Alcanhoes,Alcobaca,Alcochete,Alcoutim,Aldoar,Alexania,Alfeizerao,Algarve,Alenquer,Almada,Almagreira,Almeirim,Alpalhao,Alpedrinha,Alvalade,Alverca,Alvor,Alvorada,Amadora,Amapa,Amieira,Anapolis,Anhangueira,Ansiaes,Apelacao,Aracaju,Aranhas,Arega,Areira,Araguaina,Araruama,Arganil,Armacao,Arouca,Asfontes,Assenceira,Avelar,Aveiro,Azambuja,Azinheira,Azueira,Bahia,Bairros,Balsas,Barcarena,Barreiras,Barreiro,Barretos,Batalha,Beira,Beja,Benavente,Betim,Boticas,Braga,Braganca,Brasilia,Brejo,Cabecao,Cabeceiras,Cabedelo,Cabofrio,Cachoeiras,Cadafais,Calheta,Calihandriz,Calvao,Camacha,Caminha,Campinas,Canidelo,Canha,Canoas,Capinha,Carmoes,Cartaxo,Carvalhal,Carvoeiro,Cascavel,Castanhal,Castelobranco,Caueira,Caxias,Chapadinha,Chaves,Celheiras,Cocais,Coimbra,Comporta,Coentral,Conde,Copacabana,Coqueirinho,Coruche,Corumba,Couco,Cubatao,Curitiba,Damaia,Doisportos,Douradilho,Dourados,Enxames,Enxara,Erada,Erechim,Ericeira,Ermidasdosado,Ervidel,Escalhao,Escariz,Esmoriz,Estombar,Espinhal,Espinho,Esposende,Esquerdinha,Estela,Estoril,Eunapolis,Evora,Famalicao,Famoes,Fanhoes,Fanzeres,Fatela,Fatima,Faro,Felgueiras,Ferreira,Figueira,Flecheiras,Florianopolis,Fornalhas,Fortaleza,Freiria,Freixeira,Frielas,Fronteira,Funchal,Fundao,Gaeiras,Gafanhadaboahora,Goa,Goiania,Gracas,Gradil,Grainho,Gralheira,Guarulhos,Guetim,Guimaraes,Horta,Iguacu,Igrejanova,Ilhavo,Ilheus,Ipanema,Iraja,Itaboral,Itacuruca,Itaguai,Itanhaem,Itapevi,Juazeiro,Lagos,Lavacolchos,Laies,Lamego,Laranjeiras,Leiria,Limoeiro,Linhares,Lisboa,Lomba,Lorvao,Lourencomarques,Lourical,Lourinha,Luziania,Macao,Macapa,Macedo,Machava,Malveira,Manaus,Mangabeira,Mangaratiba,Marambaia,Maranhao,Maringue,Marinhais,Matacaes,Matosinhos,Maxial,Maxias,Mealhada,Meimoa,Meires,Milharado,Mira,Miranda,Mirandela,Mogadouro,Montalegre,Montesinho,Moura,Mourao,Mozelos,Negroes,Neiva,Nespereira,Nilopolis,Niteroi,Nordeste,Obidos,Odemira,Odivelas,Oeiras,Oleiros,Olhao,Olhalvo,Olhomarinho,Olinda,Olival,Oliveira,Oliveirinha,Oporto,Ourem,Ovar,Palhais,Palheiros,Palmeira,Palmela,Palmital,Pampilhosa,Pantanal,Paradinha,Parelheiros,Paripueira,Paudalho,Pedrosinho,Penafiel,Peniche,Pedrogao,Pegoes,Pinhao,Pinheiro,Pinhel,Pombal,Pontal,Pontinha,Portel,Portimao,Poxim,Quarteira,Queijas,Queluz,Quiaios,Ramalhal,Reboleira,Recife,Redinha,Ribadouro,Ribeira,Ribeirao,Rosais,Roteiro,Sabugal,Sacavem,Sagres,Sandim,Sangalhos,Santarem,Santos,Sarilhos,Sarzedas,Satao,Satuba,Seixal,Seixas,Seixezelo,Seixo,Selmes,Sepetiba,Serta,Setubal,Silvares,Silveira,Sinhaem,Sintra,Sobral,Sobralinho,Sorocaba,Tabuacotavir,Tabuleiro,Taveiro,Teixoso,Telhado,Telheiro,Tomar,Torrao,Torreira,Torresvedras,Tramagal,Trancoso,Troviscal,Vagos,Valpacos,Varzea,Vassouras,Velas,Viana,Vidigal,Vidigueira,Vidual,Viladerei,Vilamar,Vimeiro,Vinhais,Vinhos,Viseu,Vitoria,Vlamao,Vouzela"},
	  {name: "Nahuatl", i: 14, min: 6, max: 13, d: "l", m: 0, b: "Acaltepec,Acaltepecatl,Acapulco,Acatlan,Acaxochitlan,Ajuchitlan,Atotonilco,Azcapotzalco,Camotlan,Campeche,Chalco,Chapultepec,Chiapan,Chiapas,Chihuahua,Cihuatlan,Cihuatlancihuatl,Coahuila,Coatepec,Coatlan,Coatzacoalcos,Colima,Colotlan,Coyoacan,Cuauhillan,Cuauhnahuac,Cuauhtemoc,Cuernavaca,Ecatepec,Epatlan,Guanajuato,Huaxacac,Huehuetlan,Hueyapan,Ixtapa,Iztaccihuatl,Iztapalapa,Jalisco,Jocotepec,Jocotepecxocotl,Matixco,Mazatlan,Michhuahcan,Michoacan,Michoacanmichin,Minatitlan,Naucalpan,Nayarit,Nezahualcoyotl,Oaxaca,Ocotepec,Ocotlan,Olinalan,Otompan,Popocatepetl,Queretaro,Sonora,Tabasco,Tamaulipas,Tecolotlan,Tenochtitlan,Teocuitlatlan,Teocuitlatlanteotl,Teotlalco,Teotlalcoteotl,Tepotzotlan,Tepoztlantepoztli,Texcoco,Tlachco,Tlalocan,Tlaxcala,Tlaxcallan,Tollocan,Tolutepetl,Tonanytlan,Tototlan,Tuchtlan,Tuxpan,Uaxacac,Xalapa,Xochimilco,Xolotlan,Yaotlan,Yopico,Yucatan,Yztac,Zacatecas,Zacualco"},
	  {name: "Hungarian", i: 15, min: 6, max: 13, d: "", m: 0.1, b: "Aba,Abadszalok,Abony,Adony,Ajak,Albertirsa,Alsozsolca,Aszod,Babolna,Bacsalmas,Baktaloranthaza,Balassagyarmat,Balatonalmadi,Balatonboglar,Balatonfured,Balatonfuzfo,Balkany,Balmazujvaros,Barcs,Bataszek,Batonyterenye,Battonya,Bekes,Berettyoujfalu,Berhida,Biatorbagy,Bicske,Biharkeresztes,Bodajk,Boly,Bonyhad,Budakalasz,Budakeszi,Celldomolk,Csakvar,Csenger,Csongrad,Csorna,Csorvas,Csurgo,Dabas,Demecser,Derecske,Devavanya,Devecser,Dombovar,Dombrad,Dorogullo,Dunafoldvar,Dunaharaszti,Dunavarsany,Dunavecse,Edeleny,Elek,Emod,Encs,Enying,Ercsi,Fegyvernek,Fehergyarmat,Felsozsolca,Fertoszentmiklos,Fonyod,Fot,Fuzesabony,Fuzesgyarmat,Gardony,God,Gyal,Gyomaendrod,Gyomro,Hajdudorog,Hajduhadhaz,Hajdunanas,Hajdusamson,Hajduszoboszlo,Halasztelek,Harkany,Hatvan,Heves,Heviz,Ibrany,Isaszeg,Izsak,Janoshalma,Janossomorja,Jaszapati,Jaszarokszallas,Jaszfenyszaru,Jaszkiser,Kaba,Kalocsa,Kapuvar,Karcag,Kecel,Kemecse,Kenderes,Kerekegyhaza,Kerepes,Keszthely,Kisber,Kiskoros,Kiskunmajsa,Kistarcsa,Kistelek,Kisujszallas,Kisvarda,Komadi,Komarom,Komlo,Kormend,Korosladany,Koszeg,Kozarmisleny,Kunhegyes,Kunszentmarton,Kunszentmiklos,Labatlan,Lajosmizse,Lenti,Letavertes,Letenye,Lorinci,Maglod,Mako,Mandok,Marcali,Martfu,Martonvasar,Mateszalka,Melykut,Mezobereny,Mezocsat,Mezohegyes,Mezokeresztes,Mezokovacshaza,Mezokovesd,Mezotur,Mindszent,Mohacs,Monor,Mor,Morahalom,Nadudvar,Nagyatad,Nagyecsed,Nagyhalasz,Nagykallo,Nagykata,Nagykoros,Nagymaros,Nyekladhaza,Nyergesujfalu,Nyiradony,Nyirbator,Nyirmada,Nyirtelek,Ocsa,Orkeny,Oroszlany,Paks,Pannonhalma,Paszto,Pecel,Pecsvarad,Pilis,Pilisvorosvar,Polgar,Polgardi,Pomaz,Puspokladany,Pusztaszabolcs,Putnok,Racalmas,Rackeve,Rakamaz,Rakoczifalva,Sajoszentpeter,Sandorfalva,Sarbogard,Sarkad,Sarospatak,Sarvar,Satoraljaujhely,Siklos,Simontornya,Solt,Soltvadkert,Sumeg,Szabadszallas,Szarvas,Szazhalombatta,Szecseny,Szeghalom,Szendro,Szentgotthard,Szentlorinc,Szerencs,Szigethalom,Szigetvar,Szikszo,Tab,Tamasi,Tapioszele,Tapolca,Tat,Tata,Teglas,Tet,Tiszacsege,Tiszafoldvar,Tiszafured,Tiszakecske,Tiszalok,Tiszaujvaros,Tiszavasvari,Tokaj,Tokol,Tolna,Tompa,Torokbalint,Torokszentmiklos,Totkomlos,Tura,Turkeve,Ujkigyos,ujszasz,Vamospercs,Varpalota,Vasarosnameny,Vasvar,Vecses,Velence,Veresegyhaz,Verpelet,Veszto,Zahony,Zalaszentgrot,Zirc,Zsambek"},
	  {name: "Turkish", i: 16, min: 4, max: 10, d: "", m: 0, b: "Adapazari,Adiyaman,Afshin,Afyon,Ari,Akchaabat,Akchakale,Akchakoca,Akdamadeni,Akhisar,Aksaray,Akshehir,Alaca,Alanya,Alapli,Alashehir,Amasya,Anamur,Antakya,Ardeshen,Artvin,Aydin,Ayvalik,Babaeski,Bafra,Balikesir,Bandirma,Bartin,Bashiskele,Batman,Bayburt,Belen,Bergama,Besni,Beypazari,Beyshehir,Biga,Bilecik,Bingul,Birecik,Bismil,Bitlis,Bodrum,Bolu,Bolvadin,Bor,Bostanichi,Boyabat,Bozuyuk,Bucak,Bulancak,Bulanik,Burdur,Burhaniye,Chan,Chanakkale,Chankiri,Charshamba,Chaycuma,Chayeli,Chayirova,Cherkezkuy,Cheshme,Ceyhan,Ceylanpinar,Chine,Chivril,Cizre,Chorlu,Chumra,Dalaman,Darica,Denizli,Derik,Derince,Develi,Devrek,Didim,Dilovasi,Dinar,Diyadin,Diyarbakir,Doubayazit,Durtyol,Duzce,Duzichi,Edirne,Edremit,Elazi,Elbistan,Emirda,Erbaa,Ercish,Erdek,Erdemli,Ereli,Ergani,Erzin,Erzincan,Erzurum,Eskishehir,Fatsa,Fethiye,Gazipasha,Gebze,Gelibolu,Gerede,Geyve,Giresun,Guksun,Gulbashi,Gulcuk,Gurnen,Gumushhane,Guroymak,Hakkari,Harbiye,Havza,Hayrabolu,Hilvan,Idil,Idir,Ilgin,Imamolu,Incirliova,Inegul,Iskenderun,Iskilip,Islahiye,Isparta,Izmit,Iznik,Kadirli,Kahramanmarash,Kahta,Kaman,Kapakli,Karabuk,Karacabey,Karadeniz Ereli,Karakupru,Karaman,Karamursel,Karapinar,Karasu,Kars,Kartepe,Kastamonu,Kemer,Keshan,Kilimli,Kilis,Kirikhan,Kirikkale,Kirklareli,Kirshehir,Kiziltepe,Kurfez,Korkuteli,Kovancilar,Kozan,Kozlu,Kozluk,Kulu,Kumluca,Kurtalan,Kushadasi,Kutahya,Luleburgaz,Malatya,Malazgirt,Malkara,Manavgat,Manisa,Mardin,Marmaris,Mersin,Merzifon,Midyat,Milas,Mula,Muratli,Mush,Mut,Nazilli,Nevshehir,Nide,Niksar,Nizip,Nusaybin,udemish,Oltu,Ordu,Orhangazi,Ortaca,Osmancik,Osmaniye,Patnos,Payas,Pazarcik,Polatli,Reyhanli,Rize,Safranbolu,Salihli,Samanda,Samsun,Sandikli,shanliurfa,Saray,Sarikamish,Sarikaya,sharkishla,shereflikochhisar,Serik,Serinyol,Seydishehir,Siirt,Silifke,Silopi,Silvan,Simav,Sinop,shirnak,Sivas,Siverek,Surke,Soma,Sorgun,Suluova,Sungurlu,Suruch,Susurluk,Tarsus,Tatvan,Tavshanli,Tekirda,Terme,Tire,Tokat,Tosya,Trabzon,Tunceli,Turgutlu,Turhal,Unye,Ushak,Uzunkurpru,Van,Vezirkurpru,Viranshehir,Yahyali,Yalova,Yenishehir,Yerkury,Yozgat,Yuksekova,Zile,Zonguldak"},
	  {name: "Berber", i: 17, min: 4, max: 10, d: "s", m: .2, b: "Abkhouch,Adrar,Agadir,Agelmam,Aghmat,Agrakal,Agulmam,Ahaggar,Almou,Anfa,Annaba,Aousja,Arbat,Argoub,Arif,Asfi,Assamer,Assif,Azaghar,Azmour,Azrou,Beccar,Beja,Bennour,Benslimane,Berkane,Berrechid,Bizerte,Bouskoura,Boutferda,Dar Bouazza,Darallouch,Darchaabane,Dcheira,Denden,Djebel,Djedeida,Drargua,Essaouira,Ezzahra,Fas,Fnideq,Ghezeze,Goubellat,Grisaffen,Guelmim,Guercif,Hammamet,Harrouda,Hoceima,Idurar,Ifendassen,Ifoghas,Imilchil,Inezgane,Izoughar,Jendouba,Kacem,Kelibia,Kenitra,Kerrando,Khalidia,Khemisset,Khenifra,Khouribga,Kidal,Korba,Korbous,Lahraouyine,Larache,Leyun,Lqliaa,Manouba,Martil,Mazagan,Mcherga,Mdiq,Megrine,Mellal,Melloul,Midelt,Mohammedia,Mornag,Mrrakc,Nabeul,Nadhour,Nador,Nawaksut,Nefza,Ouarzazate,Ouazzane,Oued Zem,Oujda,Ouladteima,Qsentina,Rades,Rafraf,Safi,Sefrou,Sejnane,Settat,Sijilmassa,Skhirat,Slimane,Somaa,Sraghna,Susa,Tabarka,Taferka,Tafza,Tagbalut,Tagerdayt,Takelsa,Tanja,Tantan,Taourirt,Taroudant,Tasfelalayt,Tattiwin,Taza,Tazerka,Tazizawt,Tebourba,Teboursouk,Temara,Testour,Tetouan,Tibeskert,Tifelt,Tinariwen,Tinduf,Tinja,Tiznit,Toubkal,Trables,Tubqal,Tunes,Urup,Watlas,Wehran,Wejda,Youssoufia,Zaghouan,Zahret,Zemmour,Zriba"},
	  {name: "Arabic", i: 18, min: 4, max: 9, d: "ae", m: .2, b: "Abadilah,Abayt,Abha,Abud,Aden,Ahwar,Ajman,Alabadilah,Alabar,Alahjer,Alain,Alaraq,Alarish,Alarjam,Alashraf,Alaswaaq,Alawali,Albarar,Albawadi,Albirk,Aldhabiyah,Alduwaid,Alfareeq,Algayed,Alhada,Alhafirah,Alhamar,Alharam,Alharidhah,Alhawtah,Alhazim,Alhrateem,Alhudaydah,Alhujun,Alhuwaya,Aljahra,Aljohar,Aljubail,Alkawd,Alkhalas,Alkhawaneej,Alkhen,Alkhhafah,Alkhobar,Alkhuznah,Alkiranah,Allisafah,Allith,Almadeed,Almardamah,Almarwah,Almasnaah,Almejammah,Almojermah,Almshaykh,Almurjan,Almuwayh,Almuzaylif,Alnaheem,Alnashifah,Alqadeimah,Alqah,Alqahma,Alqalh,Alqouz,Alquaba,Alqunfudhah,Alqurayyat,Alradha,Alraqmiah,Alsadyah,Alsafa,Alshagab,Alshoqiq,Alshuqaiq,Alsilaa,Althafeer,Alwakrah,Alwasqah,Amaq,Amran,Annaseem,Aqbiyah,Arafat,Arar,Ardah,Arrawdah,Asfan,Ashayrah,Ashshahaniyah,Askar,Assaffaniyah,Ayaar,Aziziyah,Baesh,Bahrah,Baish,Balhaf,Banizayd,Baqaa,Baqal,Bidiyah,Bisha,Biyatah,Buqhayq,Burayda,Dafiyat,Damad,Dammam,Dariyah,Daynah,Dhafar,Dhahran,Dhalkut,Dhamar,Dhubab,Dhurma,Dibab,Dirab,Doha,Dukhan,Duwaibah,Enaker,Fadhla,Fahaheel,Fanateer,Farasan,Fardah,Fujairah,Ghalilah,Ghar,Ghizlan,Ghomgyah,Ghran,Hababah,Habil,Hadiyah,Haffah,Hajanbah,Hajrah,Halban,Haqqaq,Haradh,Hasar,Hathah,Hawarwar,Hawaya,Hawiyah,Hebaa,Hefar,Hijal,Husnah,Huwailat,Huwaitah,Irqah,Isharah,Ithrah,Jamalah,Jarab,Jareef,Jarwal,Jash,Jazan,Jeddah,Jiblah,Jihanah,Jilah,Jizan,Joha,Joraibah,Juban,Jubbah,Juddah,Jumeirah,Kamaran,Keyad,Khab,Khabtsaeed,Khaiybar,Khasab,Khathirah,Khawarah,Khulais,Khulays,Klayah,Kumzar,Limah,Linah,Mabar,Madrak,Mahab,Mahalah,Makhtar,Makshosh,Manfuhah,Manifah,Manshabah,Mareah,Masdar,Mashwar,Masirah,Maskar,Masliyah,Mastabah,Maysaan,Mazhar,Mdina,Meeqat,Mirbah,Mirbat,Mokhtara,Muharraq,Muladdah,Musandam,Musaykah,Muscat,Mushayrif,Musrah,Mussafah,Mutrah,Nafhan,Nahdah,Nahwa,Najran,Nakhab,Nizwa,Oman,Qadah,Qalhat,Qamrah,Qasam,Qatabah,Qawah,Qosmah,Qurain,Quraydah,Quriyat,Qurwa,Rabigh,Radaa,Rafha,Rahlah,Rakamah,Rasheedah,Rasmadrakah,Risabah,Rustaq,Ryadh,Saabah,Saabar,Sabtaljarah,Sabya,Sadad,Sadah,Safinah,Saham,Sahlat,Saihat,Salalah,Salmalzwaher,Salmiya,Sanaa,Sanaban,Sayaa,Sayyan,Shabayah,Shabwah,Shafa,Shalim,Shaqra,Sharjah,Sharkat,Sharurah,Shatifiyah,Shibam,Shidah,Shifiyah,Shihar,Shoqra,Shoqsan,Shuwaq,Sibah,Sihmah,Sinaw,Sirwah,Sohar,Suhailah,Sulaibiya,Sunbah,Tabuk,Taif,Taqah,Tarif,Tharban,Thumrait,Thuqbah,Thuwal,Tubarjal,Turaif,Turbah,Tuwaiq,Ubar,Umaljerem,Urayarah,Urwah,Wabrah,Warbah,Yabreen,Yadamah,Yafur,Yarim,Yemen,Yiyallah,Zabid,Zahwah,Zallaq,Zinjibar,Zulumah"},
	  {name: "Inuit", i: 19, min: 5, max: 15, d: "alutsn", m: 0, b: "Aaluik,Aappilattoq,Aasiaat,Agdleruussakasit,Aggas,Akia,Akilia,Akuliaruseq,Akuliarutsip,Akunnaaq,Agissat,Agssaussat,Alluitsup,Alluttoq,Aluit,Aluk,Ammassalik,Amarortalik,Amitsorsuaq,Anarusuk,Angisorsuaq,Anguniartarfik,Annertussoq,Annikitsoq,Anoraliuirsoq,Appat,Apparsuit,Apusiaajik,Arsivik,Arsuk,Ataa,Atammik,Ateqanngitsorsuaq,Atilissuaq,Attu,Aukarnersuaq,Augpalugtoq, Aumat,Auvilikavsak,Auvilkikavsaup,Avadtlek,Avallersuaq,Bjornesk,Blabaerdalen,Blomsterdalen,Brattalhid,Bredebrae,Brededal,Claushavn,Edderfulegoer,Egger,Eqalugalinnguit,Eqalugarssuit,Eqaluit,Eqqua,Etah,Graah,Hakluyt,Haredalen,Hareoen,Hundeo,Igdlorssuit,Igaliku,Igdlugdlip,Igdluluarssuk,Iginniafik,Ikamiuk,Ikamiut,Ikarissat,Ikateq,Ikeq,Ikerasak,Ikerasaarsuk,Ikermiut,Ikermoissuaq,Ikertivaq,Ikorfarssuit,Ikorfat,Ilimanaq,Illorsuit,Iluileq,Iluiteq,Ilulissat,Illunnguit,Imaarsivik,Imartunarssuk,Immikkoortukajik,Innaarsuit,Ingjald,Inneruulalik,Inussullissuaq,Iqek,Ikerasakassak,Iperaq,Ippik,Isortok,Isungartussoq,Itileq,Itivdleq,Itissaalik,Ittit,Ittoqqortoormiit,Ivingmiut,Ivittuut,Kanajoorartuut,Kangaamiut,Kangaarsuk,Kangaatsiaq,Kangeq,Kangerluk,Kangerlussuaq,Kanglinnguit,Kapisillit,Karrat,Kekertamiut,Kiatak,Kiatassuaq,Kiataussaq,Kigatak,Kigdlussat,Kinaussak,Kingittorsuaq,Kitak,Kitsissuarsuit,Kitsissut,Klenczner,Kook,Kraulshavn,Kujalleq,Kullorsuaq,Kulusuk,Kuurmiit,Kuusuaq,Laksedalen,Maniitsoq,Marrakajik,Mattaangassut,Mernoq,Mittivakkat,Moriusaq,Myggbukta,Naajaat,Nako,Nangissat,Nanortalik,Nanuuseq,Nappassoq,Narsarmijt,Narssaq,Narsarsuaq,Narssarssuk,Nasaussaq,Nasiffik,Natsiarsiorfik,Naujanguit,Niaqornaarsuk,Niaqornat,Nordfjordspasset,Nugatsiaq,Nuluuk,Nunaa,Nunarssit,Nunarsuaq,Nunataaq,Nunatakavsaup,Nutaarmiut,Nuugaatsiaq,Nuuk,Nuukullak,Nuuluk,Nuussuaq,Olonkinbyen,Oqaatsut,Oqaitsúnguit,Oqonermiut,Oodaaq,Paagussat,Palungataq,Pamialluk,Paamiut,Paatuut,Patuersoq,Perserajoq,Paornivik,Pituffik,Puugutaa,Puulkuip,Qaanaq,Qaarsorsuaq,Qaarsorsuatsiaq,Qaasuitsup,Qaersut,Qajartalik,Qallunaat,Qaneq,Qaqaarissorsuaq,Qaqit,Qaqortok,Qasigiannguit,Qasse,Qassimiut,Qeertartivaq,Qeertartivatsiaq,Qeqertaq,Qeqertarssdaq,Qeqertarsuaq,Qeqertasussuk,Qeqertarsuatsiaat,Qeqertat,Qeqqata,Qernertoq,Qernertunnguit,Qianarreq,Qilalugkiarfik,Qingagssat,Qingaq,Qoornuup,Qorlortorsuaq,Qullikorsuit,Qunnerit,Qutdleq,Ravnedalen,Ritenbenk,Rypedalen,Sarfannguit,Saarlia,Saarloq,Saatoq,Saatorsuaq,Saatup,Saattut,Sadeloe,Salleq,Salliaruseq,Sammeqqat,Sammisoq,Sanningassoq,Saqqaq,Saqqarlersuaq,Saqqarliit,Sarqaq,Sattiaatteq,Savissivik,Serfanguaq,Sermersooq,Sermersut,Sermilik,Sermiligaaq,Sermitsiaq,Simitakaja,Simiutaq,Singamaq,Siorapaluk,Sisimiut,Sisuarsuit,Skal,Skarvefjeld,Skjoldungen,Storoen,Sullorsuaq,Suunikajik,Sverdrup,Taartoq,Takiseeq,Talerua,Tarqo,Tasirliaq,Tasiusak,Tiilerilaaq,Timilersua,Timmiarmiut,Tingmjarmiut,Traill,Tukingassoq,Tuttorqortooq,Tuujuk,Tuttulissuup,Tussaaq,Uigordlit,Uigorlersuaq,Uilortussoq,Uiivaq,Ujuaakajiip,Ukkusissat,Umanat,Upernavik,Upernattivik,Upepnagssivik,Upernivik,Uttorsiutit,Uumannaq,Uummannaarsuk,Uunartoq,Uvkusigssat,Ymer"},
	  {name: "Basque", i: 20, min: 4, max: 11, d: "r", m: .1, b: "Abadio,Abaltzisketa,Abanto Zierbena,Aduna,Agurain,Aia,Aiara,Aizarnazabal,Ajangiz,Albiztur,Alegia,Alkiza,Alonsotegi,Altzaga,Altzo,Amezketa,Amorebieta,Amoroto,Amurrio,Andoain,Anoeta,Antzuola,Arakaldo,Arama,Aramaio,Arantzazu,Arbatzegi ,Areatza,Aretxabaleta,Arraia,Arrankudiaga,Arrasate,Arratzu,Arratzua,Arrieta,Arrigorriaga,Artea,Artzentales,Artziniega,Asparrena,Asteasu,Astigarraga,Ataun,Atxondo,Aulesti,Azkoitia,Azpeitia,Bakio,Baliarrain,Balmaseda,Barakaldo,Barrika,Barrundia,Basauri,Bastida,Beasain,Bedia,Beizama,Belauntza,Berango,Berantevilla,Berastegi,Bergara,Bermeo,Bernedo,Berriatua,Berriz,Berrobi,Bidania,Bilar,Bilbao,Burgelu,Busturia,Deba,Derio,Dima,Donemiliaga,Donostia,Dulantzi,Durango,Ea,Eibar,Elantxobe,Elduain,Elgeta,Elgoibar,Elorrio,Erandio,Ereno,Ermua,Errenteria,Errezil,Erribera Beitia,Erriberagoitia,Errigoiti,Eskoriatza,Eskuernaga,Etxebarri,Etxebarria,Ezkio,Fika,Forua,Fruiz,Gabiria,Gaintza,Galdakao,Galdames,Gamiz,Garai,Gasteiz,Gatika,Gatzaga,Gaubea,Gauna,Gautegiz Arteaga,Gaztelu,Gernika,Gerrikaitz,Getaria,Getxo,Gizaburuaga,Goiatz,Gordexola,Gorliz,Harana,Hernani,Hernialde,Hondarribia,Ibarra,Ibarrangelu,Idiazabal,Iekora,Igorre,Ikaztegieta,Iruna Oka,Irun,Irura,Iruraiz,Ispaster,Itsaso,Itsasondo,Iurreta,Izurtza,Jatabe,Kanpezu,Karrantza Harana,Kortezubi,Kripan,Kuartango,Lanestosa,Lantziego,Larrabetzu,Larraul,Lasarte,Laudio,Laukiz,Lazkao,Leaburu,Legazpi,Legorreta,Legutio,Leintz,Leioa,Lekeitio,Lemoa,Lemoiz,Leza,Lezama,Lezo,Lizartza,Loiu,Lumo,Manaria,Maeztu,Mallabia,Markina,Maruri,Manueta,Menaka,Mendaro,Mendata,Mendexa,Moreda Araba,Morga,Mundaka,Mungia,Munitibar,Murueta,Muskiz,Mutiloa,Mutriku,Muxika,Nabarniz,Onati,Oiartzun,Oion,Okondo,Olaberria,Ondarroa,Ordizia,Orendain,Orexa,Oria,Orio,Ormaiztegi,Orozko,Ortuella,Otxandio,Pasaia,Plentzia,Portugalete,Samaniego,Santurtzi,Segura,Sestao,Sondika,Sopela,Sopuerta,Soraluze,Sukarrieta,Tolosa,Trapagaran,Turtzioz,Ubarrundia,Ubide,Ugao,Urdua,Urduliz,Urizaharra,Urkabustaiz,Urnieta,Urretxu,Usurbil,Xemein,Zaia,Zaldibar,Zaldibia,Zalduondo,Zambrana,Zamudio,Zaratamo,Zarautz,Zeanuri,Zeberio,Zegama,Zerain,Zestoa,Zierbena,Zigoitia,Ziortza,Zizurkil,Zuia,Zumaia,Zumarraga"},
	  {name: "Nigerian", i: 21, min: 4, max: 10, d: "", m: .3, b: "Abadogo,Abafon,Abdu,Acharu,Adaba,Adealesu,Adeto,Adyongo,Afaga,Afamju,Afuje,Agbelagba,Agigbigi,Agogoke,Ahute,Aiyelaboro,Ajebe,Ajola,Akarekwu,Akessan,Akunuba,Alawode,Alkaijji,Amangam,Amaoji,Amgbaye,Amtasa,Amunigun,Anase,Aniho,Animahun,Antul,Anyoko,Apekaa,Arapagi,Asamagidi,Asande,Ataibang,Awgbagba,Awhum,Awodu,Babanana,Babateduwa,Bagu,Bakura,Bandakwai,Bangdi,Barbo,Barkeje,Basa,Basabra,Basansagawa,Bieleshin,Bilikani,Birnindodo,Braidu,Bulakawa,Buriburi,Burisidna,Busum,Bwoi,Cainnan,Chakum,Charati,Chondugh,Dabibikiri,Dagwarga,Dallok,Danalili,Dandala,Darpi,Dhayaki,Dokatofa,Doma,Dozere,Duci,Dugan,Ebelibri,Efem,Efoi,Egudu,Egundugbo,Ekoku,Ekpe,Ekwere,Erhua,Eteu,Etikagbene,Ewhoeviri,Ewhotie,Ezemaowa,Fatima,Gadege,Galakura,Galea,Gamai,Gamen,Ganjin,Gantetudu,Garangamawa,Garema,Gargar,Gari,Garinbode,Garkuwa,Garu Kime,Gazabu,Gbure,Gerti,Gidan,Giringwe,Gitabaremu,Giyagiri,Giyawa,Gmawa,Golakochi,Golumba,Guchi,Gudugu,Gunji,Gusa,Gwambula,Gwamgwam,Gwodoti,Hayinlere,Hayinmaialewa,Hirishi,Hombo,Ibefum,Iberekodo,Ibodeipa,Icharge,Ideoro,Idofin,Idofinoka,Idya,Iganmeji,Igbetar,Igbogo,Ijoko,Ijuwa,Ikawga,Ikekogbe,Ikhin,Ikoro,Ikotefe,Ikotokpora,Ikpakidout,Ikpeoniong,Ilofa,Imuogo,Inyeneke,Iorsugh,Ipawo,Ipinlerere,Isicha,Itakpa,Itoki,Iyedeame,Jameri,Jangi,Jara,Jare,Jataudakum,Jaurogomki,Jepel,Jibam,Jirgu,Jirkange,Kafinmalama,Kamkem,Katab,Katanga,Katinda,Katirije,Kaurakimba,Keffinshanu,Kellumiri,Kiagbodor,Kibiare,Kingking,Kirbutu,Kita,Kogbo,Kogogo,Kopje,Koriga,Koroko,Korokorosei,Kotoku,Kuata,Kujum,Kukau,Kunboon,Kuonubogbene,Kurawe,Kushinahu,Kwaramakeri,Ladimeji,Lafiaro,Lahaga,Laindebajanle,Laindegoro,Lajere,Lakati,Ligeri,Litenswa,Lokobimagaji,Lusabe,Maba,Madarzai,Magoi,Maialewa,Maianita,Maijuja,Mairakuni,Maleh,Malikansaa,Mallamkola,Mallammaduri,Marmara,Masagu,Masoma,Mata,Matankali,Mbalare,Megoyo,Meku,Miama,Mige,Mkporagwu,Modi,Molafa,Mshi,Msugh,Muduvu,Murnachehu,Namnai,Nanumawa,Nasudu,Ndagawo,Ndamanma,Ndiebeleagu,Ndiwulunbe,Ndonutim,Ngaruwa,Ngbande,Nguengu,Nto Ekpe,Nubudi,Nyajo,Nyido,Nyior,Obafor,Obazuwa,Odajie,Odiama,Ofunatam,Ogali,Ogan,Ogbaga,Ogbahu,Ogultu,Ogunbunmi,Ogunmakin,Ojaota,Ojirami,Ojopode,Okehin,Olugunna,Omotunde,Onipede,Onisopi,Onma,Orhere,Orya,Oshotan,Otukwang,Otunade,Pepegbene,Poros,Rafin,Rampa,Rimi,Rinjim,Robertkiri,Rugan,Rumbukawa,Sabiu,Sabon,Sabongari,Sai,Salmatappare,Sangabama,Sarabe,Seboregetore,Seibiri,Sendowa,Shafar,Shagwa,Shata,Shefunda,Shengu,Sokoron,Sunnayu,Taberlma,Tafoki,Takula,Talontan,Taraku,Tarhemba,Tayu,Ter,Timtim,Timyam,Tindirke,Tirkalou,Tokunbo,Tonga,Torlwam,Tseakaadza,Tseanongo,Tseavungu,Tsebeeve,Tsekov,Tsepaegh,Tuba,Tumbo,Tungalombo,Tungamasu,Tunganrati,Tunganyakwe,Tungenzuri,Ubimimi,Uhkirhi,Umoru,Umuabai,Umuaja,Umuajuju,Umuimo,Umuojala,Unchida,Ungua,Unguwar,Unongo,Usha,Ute,Utongbo,Vembera,Vorokotok,Wachin,Walebaga,Wurawura,Wuro,Yanbashi,Yanmedi,Yenaka,Yoku,Zamangera,Zarunkwari,Zilumo,Zulika"},
	  {name: "Celtic", i: 22, min: 4, max: 12, d: "nld", m: 0, b: "Aberaman,Aberangell,Aberarth,Aberavon,Aberbanc,Aberbargoed,Aberbeeg,Abercanaid,Abercarn,Abercastle,Abercegir,Abercraf,Abercregan,Abercych,Abercynon,Aberdare,Aberdaron,Aberdaugleddau,Aberdeen,Aberdulais,Aberdyfi,Aberedw,Abereiddy,Abererch,Abereron,Aberfan,Aberffraw,Aberffrwd,Abergavenny,Abergele,Aberglasslyn,Abergorlech,Abergwaun,Abergwesyn,Abergwili,Abergwynfi,Abergwyngregyn,Abergynolwyn,Aberhafesp,Aberhonddu,Aberkenfig,Aberllefenni,Abermain,Abermaw,Abermorddu,Abermule,Abernant,Aberpennar,Aberporth,Aberriw,Abersoch,Abersychan,Abertawe,Aberteifi,Aberthin,Abertillery,Abertridwr,Aberystwyth,Achininver,Afonhafren,Alisaha,Antinbhearmor,Ardenna,Attacon,Beira,Bhrura,Boioduro,Bona,Boudobriga,Bravon,Brigant,Briganta,Briva,Cambodunum,Cambra,Caracta,Catumagos,Centobriga,Ceredigion,Chalain,Dinn,Diwa,Dubingen,Duro,Ebora,Ebruac,Eburodunum,Eccles,Eighe,Eireann,Ferkunos,Genua,Ghrainnse,Inbhear,Inbhir,Inbhirair,Innerleithen,Innerleven,Innerwick,Inver,Inveraldie,Inverallan,Inveralmond,Inveramsay,Inveran,Inveraray,Inverarnan,Inverbervie,Inverclyde,Inverell,Inveresk,Inverfarigaig,Invergarry,Invergordon,Invergowrie,Inverhaddon,Inverkeilor,Inverkeithing,Inverkeithney,Inverkip,Inverleigh,Inverleith,Inverloch,Inverlochlarig,Inverlochy,Invermay,Invermoriston,Inverness,Inveroran,Invershin,Inversnaid,Invertrossachs,Inverugie,Inveruglas,Inverurie,Kilninver,Kirkcaldy,Kirkintilloch,Krake,Latense,Leming,Lindomagos,Llanaber,Lochinver,Lugduno,Magoduro,Monmouthshire,Narann,Novioduno,Nowijonago,Octoduron,Penning,Pheofharain,Ricomago,Rossinver,Salodurum,Seguia,Sentica,Theorsa,Uige,Vitodurum,Windobona"},
	  {name: "Mesopotamian", i: 23, min: 4, max: 9, d: "srpl", m: .1, b: "Adab,Akkad,Akshak,Amnanum,Arbid,Arpachiyah,Arrapha,Assur,Babilim,Badtibira,Balawat,Barsip,Borsippa,Carchemish,Chagar Bazar,Chuera,Ctesiphon ,Der,Dilbat,Diniktum,Doura,Durkurigalzu,Ekallatum,Emar,Erbil,Eridu,Eshnunn,Fakhariya ,Gawra,Girsu,Hadatu,Hamoukar,Haradum,Harran,Hatra,Idu,Irisagrig,Isin,Jemdet,Kahat,Kartukulti,Khaiber,Kish ,Kisurra,Kuara,Kutha,Lagash,Larsa ,Leilan,Marad,Mardaman,Mari,Mashkan,Mumbaqat ,Nabada,Nagar,Nerebtum,Nimrud,Nineveh,Nippur,Nuzi,Qalatjarmo,Qatara,Rawda,Seleucia,Shaduppum,Shanidar,Sharrukin,Shemshara,Shibaniba,Shuruppak,Sippar,Tarbisu,Tellagrab,Tellessawwan,Tellessweyhat,Tellhassuna,Telltaya,Telul,Terqa,Thalathat,Tutub,Ubaid ,Umma,Ur,Urfa,Urkesh,Uruk,Urum,Zabalam,Zenobia"},
	  {name: "Iranian", i: 24, min: 5, max: 11, d: "", m: .1, b: "Abali,Abrisham,Absard,Abuzeydabad,Afus,Alavicheh,Alikosh,Amol,Anarak,Anbar,Andisheh,Anshan,Aran,Ardabil,Arderica,Ardestan,Arjomand,Asgaran,Asgharabad,Ashian,Awan,Babajan,Badrud,Bafran,Baghestan,Baghshad,Bahadoran,Baharan Shahr,Baharestan,Bakun,Bam,Baqershahr,Barzok,Bastam,Behistun,Bitistar,Bumahen,Bushehr,Chadegan,Chahardangeh,Chamgardan,Chermahin,Choghabonut,Chugan,Damaneh,Damavand,Darabgard,Daran,Dastgerd,Dehaq,Dehaqan,Dezful,Dizicheh,Dorcheh,Dowlatabad,Duruntash,Ecbatana,Eslamshahr,Estakhr,Ezhiyeh,Falavarjan,Farrokhi,Fasham,Ferdowsieh,Fereydunshahr,Ferunabad,Firuzkuh,Fuladshahr,Ganjdareh,Ganzak,Gaz,Geoy,Godin,Goldasht,Golestan,Golpayegan,Golshahr,Golshan,Gorgab,Guged,Habibabad,Hafshejan,Hajjifiruz,Hana,Harand,Hasanabad,Hasanlu,Hashtgerd,Hecatompylos,Hormirzad,Imanshahr,Isfahan,Jandaq,Javadabad,Jiroft,Jowsheqan ,Jowzdan,Kabnak,Kahriz Sang,Kahrizak,Kangavar,Karaj,Karkevand,Kashan,Kelishad,Kermanshah,Khaledabad,Khansar,Khorramabad,Khur,Khvorzuq,Kilan,Komeh,Komeshcheh,Konar,Kuhpayeh,Kul,Kushk,Lavasan,Laybid,Liyan,Lyan,Mahabad,Mahallat,Majlesi,Malard,Manzariyeh,Marlik,Meshkat,Meymeh,Miandasht,Mish,Mobarakeh,Nahavand,Nain,Najafabad,Naqshe,Narezzash,Nasimshahr,Nasirshahr,Nasrabad,Natanz,Neyasar,Nikabad,Nimvar,Nushabad,Pakdasht,Parand,Pardis,Parsa,Pasargadai,Patigrabana,Pir Bakran,Pishva,Qahderijan,Qahjaverestan,Qamsar,Qarchak,Qods,Rabat,Ray-shahr,Rezvanshahr,Rhages,Robat Karim,Rozveh,Rudehen,Sabashahr,Safadasht,Sagzi,Salehieh,Sandal,Sarvestan,Sedeh,Sefidshahr,Semirom,Semnan,Shadpurabad,Shah,Shahdad,Shahedshahr,Shahin,Shahpour,Shahr,Shahreza,Shahriar,Sharifabad,Shemshak,Shiraz,Shushan,Shushtar,Sialk,Sin,Sukhteh,Tabas,Tabriz,Takhte,Talkhuncheh,Talli,Tarq,Temukan,Tepe,Tiran,Tudeshk,Tureng,Urmia,Vahidieh,Vahrkana,Vanak,Varamin,Varnamkhast,Varzaneh,Vazvan,Yahya,Yarim,Yasuj,Zarrin Shahr,Zavareh,Zayandeh,Zazeran,Ziar,Zibashahr,Zranka"},
	  {name: "Hawaiian", i: 25, min: 5, max: 10, d: "auo", m: 1, b: "Aapueo,Ahoa,Ahuakaio,Ahuakamalii,Ahuakeio,Ahupau,Aki,Alaakua,Alae,Alaeloa,Alaenui,Alamihi,Aleamai,Alena,Alio,Aupokopoko,Auwahi,Hahakea,Haiku,Halakaa,Halehaku,Halehana,Halemano,Haleu,Haliimaile,Hamakuapoko,Hamoa,Hanakaoo,Hanaulu,Hanawana,Hanehoi,Haneoo,Haou,Hikiaupea,Hoalua,Hokuula,Honohina,Honokahua,Honokala,Honokalani,Honokeana,Honokohau,Honokowai,Honolua,Honolulu,Honolulunui,Honomaele,Honomanu,Hononana,Honopou,Hoolawa,Hopenui,Hualele,Huelo,Hulaia,Ihuula,Ilikahi,Kaalaea,Kaalelehinale,Kaapahu,Kaehoeho,Kaeleku,Kaeo,Kahakuloa,Kahalawe,Kahalawe,Kahalehili,Kahana,Kahilo,Kahuai,Kaiaula,Kailihiakoko,Kailua,Kainehe,Kakalahale,Kakanoni,Kakio,Kakiweka,Kalena,Kalenanui,Kaleoaihe,Kalepa,Kaliae,Kalialinui,Kalihi,Kalihi,Kalihi,Kalimaohe,Kaloi,Kamani,Kamaole,Kamehame,Kanahena,Kanaio,Kaniaula,Kaonoulu,Kaopa,Kapaloa,Kapaula,Kapewakua,Kapohue,Kapuaikini,Kapunakea,Kapuuomahuka,Kauau,Kauaula,Kaukuhalahala,Kaulalo,Kaulanamoa,Kauluohana,Kaumahalua,Kaumakani,Kaumanu,Kaunauhane,Kaunuahane,Kaupakulua,Kawaipapa,Kawaloa,Kawaloa,Kawalua,Kawela,Keaa,Keaalii,Keaaula,Keahua,Keahuapono,Keakuapauaela,Kealahou,Keanae,Keauhou,Kekuapawela,Kelawea,Keokea,Keopuka,Kepio,Kihapuhala,Kikoo,Kilolani,Kipapa,Koakupuna,Koali,Koananai,Koheo,Kolea,Kolokolo,Kooka,Kopili,Kou,Kualapa,Kuhiwa,Kuholilea,Kuhua,Kuia,Kuiaha,Kuikui,Kukoae,Kukohia,Kukuiaeo,Kukuioolu,Kukuipuka,Kukuiula,Kulahuhu,Kumunui,Lapakea,Lapalapaiki,Lapueo,Launiupoko,Loiloa,Lole,Lualailua,Maalo,Mahinahina,Mahulua,Maiana,Mailepai,Makaakini,Makaalae,Makaehu,Makaiwa,Makaliua,Makapipi,Makapuu,Makawao,Makila,Mala,Maluaka,Mamalu,Manawaiapiki,Manawainui,Maulili,Mehamenui,Miana,Mikimiki,Moalii,Moanui,Mohopili,Mohopilo,Mokae,Mokuia,Mokupapa,Mooiki,Mooloa,Moomuku,Muolea,Nahuakamalii,Nailiilipoko,Nakaaha,Nakalepo,Nakaohu,Nakapehu,Nakula,Napili,Niniau,Niumalu,Nuu,Ohia,Oloewa,Olowalu,Omaopio,Onau,Onouli,Opaeula,Opana,Opikoula,Paakea,Paeahu,Paehala,Paeohi,Pahoa,Paia,Pakakia,Pakala,Palauea,Palemo,Panaewa,Paniau,Papaaea,Papaanui,Papaauhau,Papahawahawa,Papaka,Papauluana,Pauku,Paunau,Pauwalu,Pauwela,Peahi,Piapia,Pohakanele,Pohoula,Polaiki,Polanui,Polapola,Polua,Poopoo,Popoiwi,Popoloa,Poponui,Poupouwela,Puaa,Puaaluu,Puahoowali,Puakea,Puako,Pualaea,Puehuehu,Puekahi,Pueokauiki,Pukaauhuhu,Pukalani,Pukuilua,Pulehu,Pulehuiki,Pulehunui,Punaluu,Puolua,Puou,Puuhaehae,Puuhaoa,Puuiki,Puuki,Puukohola,Puulani,Puumaneoneo,Puunau,Puunoa,Puuomaiai,Puuomaile,Uaoa,Uhao,Ukumehame,Ulaino,Ulumalu,Wahikuli,Waiahole,Waiakoa,Waianae,Waianu,Waiawa,Waiehu,Waieli,Waihee,Waikapu,Wailamoa,Wailaulau,Wailua,Wailuku,Wainee,Waiohole,Waiohonu,Waiohue,Waiohuli,Waiokama,Waiokila,Waiopai,Waiopua,Waipao,Waipio,Waipioiki,Waipionui,Waipouli,Wakiu,Wananalua"},
	  {name: "Karnataka", i: 26, min: 5, max: 11, d: "tnl", m: 0, b: "Adityapatna,Adyar,Afzalpur,Aland,Alnavar,Alur,Ambikanagara,Anekal,Ankola,Annigeri,Arkalgud,Arsikere,Athni,Aurad,Badami,Bagalkot,Bagepalli,Bail,Bajpe,Bangalore,Bangarapet,Bankapura,Bannur,Bantval,Basavakalyan,Basavana,Belgaum,Beltangadi,Belur,Bhadravati,Bhalki,Bhatkal,Bhimarayanagudi,Bidar,Bijapur,Bilgi,Birur,Bommasandra,Byadgi,Challakere,Chamarajanagar,Channagiri,Channapatna,Channarayapatna,Chik,Chikmagalur,Chiknayakanhalli,Chikodi,Chincholi,Chintamani,Chitapur,Chitgoppa,Chitradurga,Dandeli,Dargajogihalli,Devadurga,Devanahalli,Dod,Donimalai,Gadag,Gajendragarh,Gangawati,Gauribidanur,Gokak,Gonikoppal,Gubbi,Gudibanda,Gulbarga,Guledgudda,Gundlupet,Gurmatkal,Haliyal,Hangal,Harapanahalli,Harihar,Hassan,Hatti,Haveri,Hebbagodi,Heggadadevankote,Hirekerur,Holalkere,Hole,Homnabad,Honavar,Honnali,Hoovina,Hosakote,Hosanagara,Hosdurga,Hospet,Hubli,Hukeri,Hungund,Hunsur,Ilkal,Indi,Jagalur,Jamkhandi,Jevargi,Jog,Kadigenahalli,Kadur,Kalghatgi,Kamalapuram,Kampli,Kanakapura,Karkal,Karwar,Khanapur,Kodiyal,Kolar,Kollegal,Konnur,Koppa,Koppal,Koratagere,Kotturu,Krishnarajanagara,Krishnarajasagara,Krishnarajpet,Kudchi,Kudligi,Kudremukh,Kumta,Kundapura,Kundgol,Kunigal,Kurgunta,Kushalnagar,Kushtagi,Lakshmeshwar,Lingsugur,Londa,Maddur,Madhugiri,Madikeri,Mahalingpur,Malavalli,Mallar,Malur,Mandya,Mangalore,Manvi,Molakalmuru,Mudalgi,Mudbidri,Muddebihal,Mudgal,Mudhol,Mudigere,Mulbagal,Mulgund,Mulki,Mulur,Mundargi,Mundgod,Munirabad,Mysore,Nagamangala,Nanjangud,Narasimharajapura,Naregal,Nargund,Navalgund,Nipani,Pandavapura,Pavagada,Piriyapatna,Pudu,Puttur,Rabkavi,Raichur,Ramanagaram,Ramdurg,Ranibennur,Raybag,Robertson,Ron,Sadalgi,Sagar,Sakleshpur,Saligram,Sandur,Sankeshwar,Saundatti,Savanur,Sedam,Shahabad,Shahpur,Shaktinagar,Shiggaon,Shikarpur,Shirhatti,Shorapur,Shrirangapattana,Siddapur,Sidlaghatta,Sindgi,Sindhnur,Sira,Siralkoppa,Sirsi,Siruguppa,Somvarpet,Sorab,Sringeri,Srinivaspur,Sulya,Talikota,Tarikere,Tekkalakote,Terdal,Thumbe,Tiptur,Tirthahalli,Tirumakudal,Tumkur,Turuvekere,Udupi,Vijayapura,Wadi,Yadgir,Yelandur,Yelbarga,Yellapur,Yenagudde"},
	  {name: "Quechua", i: 27, min: 6, max: 12, d: "l", m: 0, b: "Altomisayoq,Ancash,Andahuaylas,Apachekta,Apachita,Apu ,Apurimac,Arequipa,Atahuallpa,Atawalpa,Atico,Ayacucho,Ayllu,Cajamarca,Carhuac,Carhuacatac,Cashan,Caullaraju,Caxamalca,Cayesh,Chacchapunta,Chacraraju,Champara,Chanchan,Chekiacraju,Chinchey,Chontah,Chopicalqui,Chucuito,Chuito,Chullo,Chumpi,Chuncho,Chuquiapo,Churup,Cochapata,Cojup,Collota,Conococha,Copa,Corihuayrachina,Cusichaca,Despacho,Haika,Hanpiq,Hatun,Haywarisqa,Huaca,Hualcan,Huamanga,Huamashraju,Huancarhuas,Huandoy,Huantsan,Huarmihuanusca,Huascaran,Huaylas,Huayllabamba,Huichajanca,Huinayhuayna,Huinioch,Illiasca,Intipunku,Ishinca,Jahuacocha,Jirishanca,Juli,Jurau,Kakananpunta,Kamasqa,Karpay,Kausay,Khuya ,Kuelap,Llaca,Llactapata,Llanganuco,Llaqta,Llupachayoc,Machu,Mallku,Matarraju,Mikhuy,Milluacocha,Munay,Ocshapalca,Ollantaytambo,Pacamayo,Paccharaju,Pachacamac,Pachakamaq,Pachakuteq,Pachakuti,Pachamama  ,Paititi,Pajaten,Palcaraju,Pampa,Panaka,Paqarina,Paqo,Parap,Paria,Patallacta,Phuyupatamarca,Pisac,Pongos,Pucahirca,Pucaranra,Puscanturpa,Putaca,Qawaq ,Qayqa,Qochamoqo,Qollana,Qorihuayrachina,Qorimoqo,Quenuaracra,Queshque,Quillcayhuanca,Quillya,Quitaracsa,Quitaraju,Qusqu,Rajucolta,Rajutakanan,Rajutuna,Ranrahirca,Ranrapalca,Raria,Rasac,Rimarima,Riobamba,Runkuracay,Rurec,Sacsa,Saiwa,Sarapo,Sayacmarca,Sinakara,TamboColorado,Tamboccocha,Taripaypacha,Taulliraju,Tawantinsuyu,Taytanchis,Tiwanaku,Tocllaraju,Tsacra,Tuco,Tullparaju,Tumbes,Ulta,Uruashraju,Vallunaraju,Vilcabamba,Wacho ,Wankawillka,Wayra,Yachay,Yahuarraju,Yanamarey,Yanesha,Yerupaja"},
	  {name: "Swahili", i: 28, min: 4, max: 9, d: "", m: 0, b: "Abim,Adjumani,Alebtong,Amolatar,Amuria,Amuru,Apac,Arua,Arusha,Babati,Baragoi,Bombo,Budaka,Bugembe,Bugiri,Buikwe,Bukedea,Bukoba,Bukomansimbi,Bukungu,Buliisa,Bundibugyo,Bungoma,Busembatya,Bushenyi,Busia,Busia,Busolwe,Butaleja,Butambala,Butere,Buwenge,Buyende,Dadaab,Dodoma,Dokolo,Eldoret,Elegu,Emali,Embu,Entebbe,Garissa,Gede,Gulu,Handeni,Hima,Hoima,Hola,Ibanda,Iganga,Iringa,Isingiro,Isiolo,Jinja,Kaabong,Kabale,Kaberamaido,Kabuyanda,Kabwohe,Kagadi,Kahama,Kajiado,Kakamega,Kakinga,Kakira,Kakiri,Kakuma,Kalangala,Kaliro,Kalisizo,Kalongo,Kalungu,Kampala,Kamuli,Kamwenge,Kanoni,Kanungu,Kapchorwa,Kapenguria,Kasese,Kasulu,Katakwi,Kayunga,Kericho,Keroka,Kiambu,Kibaale,Kibaha,Kibingo,Kiboga,Kibwezi,Kigoma,Kihiihi,Kilifi,Kira,Kiruhura,Kiryandongo,Kisii,Kisoro,Kisumu,Kitale,Kitgum,Kitui,Koboko,Korogwe,Kotido,Kumi,Kyazanga,Kyegegwa,Kyenjojo,Kyotera,Lamu,Langata,Lindi,Lodwar,Lokichoggio,Londiani,Loyangalani,Lugazi,Lukaya,Luweero,Lwakhakha,Lwengo,Lyantonde,Machakos,Mafinga,Makambako,Makindu,Malaba,Malindi,Manafwa,Mandera,Maralal,Marsabit,Masaka,Masindi,MasindiPort,Masulita,Matugga,Mayuge,Mbale,Mbarara,Mbeya,Meru,Mitooma,Mityana,Mombasa,Morogoro,Moroto,Moshi,Moyale,Moyo,Mpanda,Mpigi,Mpondwe,Mtwara,Mubende,Mukono,Mumias,Muranga,Musoma,Mutomo,Mutukula,Mwanza,Nagongera,Nairobi,Naivasha,Nakapiripirit,Nakaseke,Nakasongola,Nakuru,Namanga,Namayingo,Namutumba,Nansana,Nanyuki,Narok,Naromoru,Nebbi,Ngora,Njeru,Njombe,Nkokonjeru,Ntungamo,Nyahururu,Nyeri,Oyam,Pader,Paidha,Pakwach,Pallisa,Rakai,Ruiru,Rukungiri,Rwimi,Sanga,Sembabule,Shimoni,Shinyanga,Singida,Sironko,Songea,Soroti,Ssabagabo,Sumbawanga,Tabora,Takaungu,Tanga,Thika,Tororo,Tunduma,Vihiga,Voi,Wajir,Wakiso,Watamu,Webuye,Wobulenzi,Wote,Wundanyi,Yumbe,Zanzibar"},
	  {name: "Vietnamese", i: 29, min: 3, max: 12, d: "", m: 1, b: "An Khe,An Nhon,Ayun Pa,Ba Don,Ba Ria,Bac Giang,Bac Kan,Bac Lieu,Bac Ninh,Bao Loc,Ben Cat,Ben Tre,Bien Hoa,Bim Son,Binh Long,Binh Minh,Buon Ho,Buon Ma Thuot,Ca Mau,Cai Lay,Cam Pha,Cam Ranh,Can Tho,Cao Bang,Cao Lanh,Chau Doc,Chi Linh,Cua Lo,Da Lat,Da Nang,Di An,Dien Ban,Dien Bien Phu,Dong Ha,Dong Hoi,Dong Trieu,Duyen Hai,Gia Nghia,Gia Rai,Go Cong,Ha Giang,Ha Long,Ha Noi,Ha Tinh,Hai Duong,Hai Phong,Hoa Binh,Hoang Mai,Hoi An,Hong Linh,Hong Ngu,Hue,Hung Yen,Huong Thuy,Huong Tra,Kien Tuong,Kon Tum,Ky Anh,La Gi,Lai Chau,Lang Son,Lao Cai,Long Khanh,Long My,Long Xuyen,Mong Cai,Muong Lay,My Hao,My Tho,Nam Dinh,Nga Bay,Nga Nam,Nghia Lo,Nha Trang,Ninh Binh,Ninh Hoa,Phan Rang Thap Cham,Phan Thiet,Pho Yen,Phu Ly,Phu My,Phu Tho,Phuoc Long,Pleiku,Quang Ngai,Quang Tri,Quang Yen,Quy Nhon,Rach Gia,Sa Dec,Sam Son,Soc Trang,Son La,Son Tay,Song Cau,Song Cong,Tam Diep,Tam Ky,Tan An,Tan Chau,Tan Uyen,Tay Ninh,Thai Binh,Thai Hoa,Thai Nguyen,Thanh Hoa,Thu Dau Mot,Thuan An,Tra Vinh,Tu Son,Tuy Hoa,Tuyen Quang,Uong Bi,Vi Thanh,Viet Tri,Vinh,Vinh Chau,Vinh Long,Vinh Yen,Vung Tau,Yen Bai"},
	  {name: "Cantonese", i: 30, min: 5, max: 11, d: "", m: 0, b: "Chaiwan,Chekham,Cheungshawan,Chingchung,Chinghoi,Chingsen,Chingshing,Chiunam,Chiuon,Chiuyeung,Chiyuen,Choihung,Chuehoi,Chuiman,Chungfa,Chungfu,Chungsan,Chunguktsuen,Dakhing,Daopo,Daumun,Dingwu,Dinpak,Donggun,Dongyuen,Duenchau,Fachau,Fado,Fanling,Fatgong,Fatshan,Fotan,Fuktien,Fumun,Funggong,Funghoi,Fungshun,Fungtei,Gamtin,Gochau,Goming,Gonghoi,Gongshing,Goyiu,Hanghau,Hangmei,Hashan,Hengfachuen,Hengon,Heungchau,Heunggong,Heungkiu,Hingning,Hohfuktong,Hoichue,Hoifung,Hoiping,Hokong,Hokshan,Homantin,Hotin,Hoyuen,Hunghom,Hungshuikiu,Jiuling,Kamping,Kamsheung,Kamwan,Kaulongtong,Keilun,Kinon,Kinsang,Kityeung,Kongmun,Kukgong,Kwaifong,Kwaihing,Kwongchau,Kwongling,Kwongming,Kwuntong,Laichikok,Laiking,Laiwan,Lamtei,Lamtin,Leitung,Leungking,Limkong,Linchau,Linnam,Linping,Linshan,Loding,Lokcheong,Lokfu,Lokmachau,Longchuen,Longgong,Longmun,Longping,Longwa,Longwu,Lowu,Luichau,Lukfung,Lukho,Lungmun,Macheung,Maliushui,Maonshan,Mauming,Maunam,Meifoo,Mingkum,Mogong,Mongkok,Muichau,Muigong,Muiyuen,Naiwai,Namcheong,Namhoi,Namhong,Namo,Namsha,Namshan,Nganwai,Ngchuen,Ngoumun,Ngwa,Nngautaukok,Onting,Pakwun,Paotoishan,Pingshan,Pingyuen,Poklo,Polam,Pongon,Poning,Potau,Puito,Punyue,Saiwanho,Saiyingpun,Samshing,Samshui,Samtsen,Samyuenlei,Sanfung,Sanhing,Sanhui,Sanwai,Sanwui,Seiwui,Shamshuipo,Shanmei,Shantau,Shatin,Shatinwai,Shaukeiwan,Shauking,Shekkipmei,Shekmun,Shekpai,Sheungshui,Shingkui,Shiuhing,Shundak,Shunyi,Shupinwai,Simshing,Siuhei,Siuhong,Siukwan,Siulun,Suikai,Taihing,Taikoo,Taipo,Taishuihang,Taiwai,Taiwo,Taiwohau,Tinhau,Tinho,Tinking,Tinshuiwai,Tiukengleng,Toishan,Tongfong,Tonglowan,Tsakyoochung,Tsamgong,Tsangshing,Tseungkwano,Tsihing,Tsimshatsui,Tsinggong,Tsingshantsuen,Tsingwun,Tsingyi,Tsingyuen,Tsiuchau,Tsuenshekshan,Tsuenwan,Tuenmun,Tungchung,Waichap,Waichau,Waidong,Wailoi,Waishing,Waiyeung,Wanchai,Wanfau,Wanon,Wanshing,Wingon,Wongchukhang,Wongpo,Wongtaisin,Woping,Wukaisha,Yano,Yaumatei,Yauoi,Yautong,Yenfa,Yeungchun,Yeungdong,Yeunggong,Yeungsai,Yeungshan,Yimtin,Yingdak,Yiuping,Yongshing,Yongyuen,Yuenlong,Yuenshing,Yuetsau,Yuknam,Yunping,Yuyuen"},
	  {name: "Mongolian", i: 31, min: 5, max: 12, d: "aou", m: .3, b: "Adaatsag,Airag,Alag Erdene,Altai,Altanshiree,Altantsogts,Arbulag,Baatsagaan,Batnorov,Batshireet,Battsengel,Bayan Adarga,Bayan Agt,Bayanbulag,Bayandalai,Bayandun,Bayangovi,Bayanjargalan,Bayankhongor,Bayankhutag,Bayanlig,Bayanmonkh,Bayannuur,Bayan Ondor,Bayan Ovoo,Bayantal,Bayantsagaan,Bayantumen,Bayan Uul,Bayanzurkh,Berkh,Biger,Binder,Bogd,Bombogor,Bor Ondor,Bugat,Bulgan,Buregkhangai,Burentogtokh,Buutsagaan,Buyant,Chandmani,Chandmani Ondor,Choibalsan,Chuluunkhoroot,Chuluut,Dadal,Dalanjargalan,Dalanzadgad,Darkhan,Darvi,Dashbalbar,Dashinchilen,Delger,Delgerekh,Delgerkhaan,Delgerkhangai,Delgertsogt,Deluun,Deren,Dorgon,Duut,Erdene,Erdenebulgan,Erdeneburen,Erdenedalai,Erdenemandal,Erdenetsogt,Galshar,Galt,Galuut,Govi Ugtaal,Gurvan,Gurvanbulag,Gurvansaikhan,Gurvanzagal,Ikhkhet,Ikh Tamir,Ikh Uul,Jargalan,Jargalant,Jargaltkhaan,Jinst,Khairkhan,Khalhgol,Khaliun,Khanbogd,Khangai,Khangal,Khankh,Khankhongor,Khashaat,Khatanbulag,Khatgal,Kherlen,Khishig Ondor,Khokh,Kholonbuir,Khongor,Khotont,Khovd,Khovsgol,Khuld,Khureemaral,Khurmen,Khutag Ondor,Luus,Mandakh,Mandal Ovoo,Mankhan,Manlai,Matad,Mogod,Monkhkhairkhan,Moron,Most,Myangad,Nogoonnuur,Nomgon,Norovlin,Noyon,Ogii,Olgii,Olziit,Omnodelger,Ondorkhaan,Ondorshil,Ondor Ulaan,Orgon,Orkhon,Rashaant,Renchinlkhumbe,Sagsai,Saikhan,Saikhandulaan,Saikhan Ovoo,Sainshand,Saintsagaan,Selenge,Sergelen,Sevrei,Sharga,Sharyngol,Shine Ider,Shinejinst,Shiveegovi,Sumber,Taishir,Tarialan,Tariat,Teshig,Togrog,Tolbo,Tomorbulag,Tonkhil,Tosontsengel,Tsagaandelger,Tsagaannuur,Tsagaan Ovoo,Tsagaan Uur,Tsakhir,Tseel,Tsengel,Tsenkher,Tsenkhermandal,Tsetseg,Tsetserleg,Tsogt,Tsogt Ovoo,Tsogttsetsii,Tunel,Tuvshruulekh,Ulaanbadrakh,Ulaankhus,Ulaan Uul,Uyench,Yesonbulag,Zag,Zamyn Uud,Zereg"},
	  // fantasy bases by Dopu:
	  {name: "Human Generic", i: 32, min: 6, max: 11, d: "peolst", m: 0, b: "Grimegrove,Cliffshear,Eaglevein,Basinborn,Whalewich,Faypond,Pondshade,Earthfield,Dustwatch,Houndcall,Oakenbell,Wildwell,Direwallow,Springmire,Bayfrost,Fearwich,Ghostdale,Cursespell,Shadowvein,Freygrave,Freyshell,Tradewick,Grasswallow,Kilshell,Flatwall,Mosswind,Edgehaven,Newfalls,Flathand,Lostcairn,Grimeshore,Littleshade,Millstrand,Snowbay,Quickbell,Crystalrock,Snakewharf,Oldwall,Whitvalley,Stagport,Deadkeep,Claymond,Angelhand,Ebonhold,Shimmerrun,Honeywater,Gloomburn,Arrowburgh,Slyvein,Dawnforest,Dirtshield,Southbreak,Clayband,Oakenrun,Graypost,Deepcairn,Lagoonpass,Cavewharf,Thornhelm,Smoothwallow,Lightfront,Irongrave,Stonespell,Cavemeadow,Millbell,Shimmerwell,Eldermere,Roguehaven,Dogmeadow,Pondside,Springview,Embervault,Dryhost,Bouldermouth,Stormhand,Oakenfall,Clearguard,Lightvale,Freyshear,Flameguard,Bellcairn,Bridgeforest,Scorchwich,Mythgulch,Maplesummit,Mosshand,Iceholde,Knightlight,Dawnwater,Laststar,Westpoint,Goldbreach,Falsevale,Pinegarde,Shroudrock,Whitwharf,Autumnband,Oceanstar,Rosedale,Snowtown,Chillstrand,Saltmouth,Crystalsummit,Redband,Thorncairn,Beargarde,Pearlhaven,Lostward,Northpeak,Sandhill,Cliffgate,Sandminster,Cloudcrest,Mythshear,Dragonward,Coldholde,Knighttide,Boulderharbor,Faybarrow,Dawnpass,Pondtown,Timberside,Madfair,Crystalspire,Shademeadow,Dragonbreak,Castlecross,Dogwell,Caveport,Wildlight,Mudfront,Eldermere,Midholde,Ravenwall,Mosstide,Everborn,Lastmere,Dawncall,Autumnkeep,Oldwatch,Shimmerwood,Eldergate,Deerchill,Fallpoint,Silvergulch,Cavemire,Deerbrook,Pinepond,Ravenside,Thornyard,Scorchstall,Swiftwell,Roguereach,Cloudwood,Smoothtown,Kilhill,Ironhollow,Stillhall,Rustmore,Ragefair,Ghostward,Deadford,Smallmire,Barebreak,Westforest,Bonemouth,Evercoast,Sleekgulch,Neverfront,Lostshield,Icelight,Quickgulch,Brinepeak,Hollowstorm,Limeband,Basinmore,Steepmoor,Blackford,Stormtide,Wildyard,Wolfpass,Houndburn,Pondfalls,Pureshell,Silvercairn,Houndwallow,Dewmere,Fearpeak,Bellstall,Diredale,Crowgrove,Moongulf,Kilholde,Sungulf,Baremore,Bleakwatch,Farrun,Grimeshire,Roseborn,Heartford,Scorchpost,Cloudbay,Whitlight,Timberham,Cloudmouth,Curseminster,Basinfrost,Maplevein,Sungarde,Cloudstar,Bellport,Silkwich,Ragehall,Bellreach,Swampmaw,Snakemere,Highbourne,Goldyard,Lakemond,Shadeville,Mightmouth,Nevercrest,Pinemount,Claymouth,Rosereach,Oldreach,Brittlehelm,Heartfall,Bonegulch,Silkhollow,Crystalgulf,Mutewell,Flameside,Blackwatch,Greenwharf,Moonacre,Beachwick,Littleborough,Castlefair,Stoneguard,Nighthall,Cragbury,Swanwall,Littlehall,Mudford,Shadeforest,Mightglen,Millhand,Easthill,Amberglen,Nighthall,Cragbury,Swanwall,Littlehall,Mudford,Shadeforest,Mightglen,Millhand,Easthill,Amberglen,Smoothcliff,Lakecross,Quicklight,Eaglecall,Silentkeep,Dragonshear,Ebonfront,Oakenmeadow,Cliffshield,Stormhorn,Cavefell,Wildedenn,Earthgate,Brittlecall,Swangarde,Steamwallow,Demonfall,Sleethallow,Mossstar,Dragonhold,Smoothgrove,Sleetrun,Flamewell,Mistvault,Heartvault,Newborough,Deeppoint,Littlehold,Westshell,Caveminster,Swiftshade,Grimwood,Littlemire,Bridgefalls,Lastmere,Fayyard,Madham,Curseguard,Earthpass,Silkbrook,Winterview,Grimeborough,Dustcross,Dogcoast,Dirtstall,Oxlight,Pondstall,Sleetglen,Ghostpeak,Snowshield,Loststar,Chillwharf,Sleettide,Millgulch,Whiteshore,Sunmond,Moonwell,Grassdrift,Westmeadow,Crowvault,Everchill,Bearmire,Bronzegrasp,Oxbrook,Cursefield,Steammouth,Smoothham,Arrowdenn,Stillstrand,Mudwich"},
	  {name: "Elven", i: 33, min: 6, max: 12, d: "lenmsrg", m: 0, b: "Adrindest,Aethel,Afranthemar,Aggar,Aiqua,Alari,Allanar,Allanbelle,Almalian,Alora,Alyanasari,Alyelona,Alyran,Amenalenora,Ammar,Amymabelle,Ancalen,AnhAlora,Anore,Anyndell,Arasari,Aren,Ashesari,Ashletheas,Ashmebel,Asrannore,Athelle,Aymlume,Baethei,Bel-Didhel,Belanore,Borethanil,Brinorion,Caelora,Chaggaust,Chaulssad,Chaundra,ChetarIthlin,Cyhmel,Cyla,Cyonore,Cyrangroth,Doladress,Dolarith,Dolasea,Dolonde,Dorthore,Dorwine,Draethe,Dranzan,Draugaust,Dreghei,Drelhei,Dryndlu,E'ana,E'ebel,Eahil,Edhil,Edraithion,Efho,Efranluma,Efvanore,Einyallond,Elathlume,Eld-Sinnocrin,Elddrinn,Elelthyr,Elheinn,Ellanalin,Ellena,Ellheserin,Ellnlin,Ellorthond,Elralara,Elstyr,Eltaesi,Elunore,Eman,EmneLenora,Emyel,Emyranserine,Enhethyr,Ennore,Entheas,Eriargond,Erranlenor,ErrarIthinn,Esari,Esath,Eserius,Eshsalin,Eshthalas,Esseavad,Esyana,EsyseAiqua,Evraland,Faellenor,Faladhell,Famelenora,Fethalas,Filranlean,Filsaqua,Formarion,Ferdor,Gafetheas,GafSerine,Gansari,Geliene,Gondorwin,Guallu,Haeth,Hanluna,Haulssad,Helatheas,Hellerien,Heloriath,Himlarien,Himliene,Hinnead,Hlaughei,Hlinas,Hloireenil,Hluihei,Hluitar,Hlurthei,Hlynead,Iaenarion,Ifrennoris,IllaAncalen,Illanathaes,Illfanora,Imlarlon,Imyfaluna,Imyse,Imyvelian,Inferius,Inhalon,Inllune,Inlurth,innsshe,Inransera,Iralserin,Irethtalos,Irholona,Ishal,Ishlashara,Isyenshara,Ithelion,Iymerius,Iaron,Iulil,Jaal,Jamkadi,Kaalume,Kaansera,Kalthalas,Karanthanil,Karnosea,Kasethyr,Keatheas,Kelsya,KethAiqua,Kmlon,Kyathlenor,Kyhasera,Lahetheas,Lammydr,Lefdorei,Lelhamelle,Lelon,Lenora,Lilean,Lindoress,Lindeenil,Lirillaquen,Litys,Llaughei,Llurthei,Lya,Lyenalon,Lyfa,Lylharion,Lylmhil,Lynathalas,Lir,Machei,Masenoris,Mathathlona,Mathethil,Mathntheas,Meethalas,Melelume,Menyamar,Menzithl,Minthyr,Mithlonde,Mornetheas,Mytha,Mythnserine,Mythsemelle,Mythsthas,Myvanas,Naahona,Nalore,NasadIlaurth,Nasin,Nathemar,Navethas,Neadar,Neanor,Neilon,Nelalon,Nellean,Nelnetaesi,Nfanor,Nilenathyr,Nionande,Nurtaleewe,Nylm,Nytenanas,Nythanlenor,Nythfelon,Nythodorei,Nytlenor,Nidiel,Noruiben,O'anlenora,O'lalona,Obeth,Ofaenathyr,Oflhone,Ollethlune,Ollmarion,Ollmnaes,Ollsmel,Olranlune,Olyaneas,Olynahil,Omanalon,Omyselon,Onelion,Onelond,Onylanor,Orlormel,Orlynn,Ormrion,Oshana,Oshmahona,Oshvamel,Raethei,Raineas,Rauguall,Rauthe,Rauthei,Reisera,Reslenora,Rrharrvhei,Ryanasera,Rymaserin,Sahnor,Saselune,Sel-Zedraazin,Selananor,Sellerion,Selmaluma,Serin,Serine,Shaeras,Shemnas,Shemserin,Sheosari,Sileltalos,Siriande,Siriathil,Sohona,Srannor,Sshanntyr,Sshaulssin,Sshaulu,Syholume,Sylharius,Sylranbel,Symdorei,Syranbel,Szoberr,Silon,Taesi,Thalas,Thalor,Thalore,Tharenlon,Tharlarast,Thelethlune,Thelhohil,Thelnora,Themar,Thene,Thilfalean,Thilnaenor,Thvethalas,Thylathlond,Tiregul,Tirion,Tlauven,Tlindhe,Ulal,Ullallanar,Ullmatalos,Ullve,Ulmetheas,Ulrenserine,Ulssin,Umnalin,Umye,Umyheserine,Unanneas,Unarith,Undraeth,Unysarion,Vel-Shonidor,Venas,Vinargothr,Waethe,Wasrion,Wlalean,Y'maqua,Yaeluma,Yeelume,Yele,Yethrion,Ymserine,Yueghed,Yuereth,Yuerran,Yuethin,Nandeedil,Olwen,Yridhremben"},
	  {name: "Dark Elven", i: 34, min: 6, max: 14, d: "nrslamg", m: .2, b: "Abaethaggar,Abburth,Afranthemar,Aharasplit,Aidanat,Ald'ruhn,Ashamanu,Ashesari,Ashletheas,Baerario,Baereghel,Baethei,Bahashae,Balmora,Bel-Didhel,Borethanil,Buiyrandyn,Caellagith,Caellathala,Caergroth,Caldras,Chaggar,Chaggaust,Channtar,Charrvhel'raugaust,Chaulssin,Chaundra,ChedNasad,ChetarIthlin,ChethRrhinn,Chymaer,Clarkarond,Cloibbra,Commoragh,Cyrangroth,Cilben,D'eldarc,Daedhrog,Dalkyn,Do'Urden,Doladress,Dolarith,Dolonde,Draethe,Dranzan,Dranzithl,Draugaust,Dreghei,Drelhei,Dryndlu,Dusklyngh,DyonG'ennivalz,Edraithion,Eld-Sinnocrin,Ellorthond,Enhethyr,Entheas,ErrarIthinn,Eryndlyn,Faladhell,Faneadar,Fethalas,Filranlean,Formarion,Ferdor,Gafetheas,Ghrond,Gilranel,Glamordis,Gnaarmok,Gnisis,Golothaer,Gondorwin,Guallidurth,Guallu,Gulshin,Haeth,Haggraef,Harganeth,Harkaldra,Haulssad,Haundrauth,Heloriath,Hlammachar,Hlaughei,Hloireenil,Hluitar,Inferius,innsshe,Ithilaughym,Iz'aiogith,Jaal,Jhachalkhyn,Kaerabrae,Karanthanil,Karondkar,Karsoluthiyl,Kellyth,Khuul,Lahetheas,Lidurth,Lindeenil,Lirillaquen,LithMy'athar,LlurthDreier,Lolth,Lothuial,Luihaulen'tar,Maeralyn,Maerimydra,Mathathlona,Mathethil,Mellodona,Menagith,Menegwen,Menerrendil,Menzithl,Menzoberranzan,Mila-Nipal,Mithryn,Molagmar,Mundor,Myvanas,Naggarond,NasadIlaurth,Nauthor,Navethas,Neadar,Nurtaleewe,Nidiel,Noruiben,O'lalona,Obeth,Ofaenathyr,Orlormel,Orlytlar,Pelagiad,Raethei,Raugaust,Rauguall,Rilauven,Rrharrvhei,Sadrith,Sel-Zedraazin,Seydaneen,Shaz'rir,Skaal,Sschindylryn,Shamath,Shamenz,Shanntur,Sshanntynlan,Sshanntyr,Shaulssin,SzithMorcane,Szithlin,Szobaeth,Sirdhemben,T'lindhet,Tebh'zhor,Telmere,Telnarquel,Tharlarast,Thylathlond,Tlaughe,Trizex,Tyrybblyn,Ugauth,Ughym,Ullmatalos,Ulmetheas,Ulrenserine,Uluitur,Undraeth,Undraurth,Undrek'Thoz,Ungethal,UstNatha,V'elddrinnsshar,Vaajha,Vel-Shonidor,Velddra,Velothi,Venead,Vhalth'vha,Vinargothr,Vojha,Waethe,Waethei,Xaalkis,Yakaridan,Yeelume,Yuethin,Yuethindrynn,Zirnakaynin,Nandeedil,olwen,Uhaelben,Uthaessien,Yridhremben"},
	  {name: "Dwarven", i: 35, min: 4, max: 11, d: "dk", m: 0, b: "Addundad,Ahagzad,Ahazil,Akil,Akzizad,Anumush,Araddush,Arar,Arbhur,Badushund,Baragzig,Baragzund,Barakinb,Barakzig,Barakzinb,Barakzir,Baramunz,Barazinb,Barazir,Bilgabar,Bilgatharb,Bilgathaz,Bilgila,Bilnaragz,Bilnulbar,Bilnulbun,Bizaddum,Bizaddush,Bizanarg,Bizaram,Bizinbiz,Biziram,Bunaram,Bundinar,Bundushol,Bundushund,Bundushur,Buzaram,Buzundab,Buzundush,Gabaragz,Gabaram,Gabilgab,Gabilgath,Gabizir,Gabunal,Gabunul,Gabuzan,Gatharam,Gatharbhur,Gathizdum,Gathuragz,Gathuraz,Gila,Giledzir,Gilukkhath,Gilukkhel,Gunala,Gunargath,Gunargil,Gundumunz,Gundusharb,Gundushizd,Kharbharbiln,Kharbhatharb,Kharbhela,Kharbilgab,Kharbuzadd,Khatharbar,Khathizdin,Khathundush,Khazanar,Khazinbund,Khaziragz,Khaziraz,Khizdabun,Khizdusharbh,Khizdushath,Khizdushel,Khizdushur,Kholedzar,Khundabiln,Khundabuz,Khundinarg,Khundushel,Khuragzig,Khuramunz,Kibarak,Kibilnal,Kibizar,Kibunarg,Kibundin,Kibuzan,Kinbadab,Kinbaragz,Kinbarakz,Kinbaram,Kinbizah,Kinbuzar,Nala,Naledzar,Naledzig,Naledzinb,Naragzah,Naragzar,Naragzig,Narakzah,Narakzar,Naramunz,Narazar,Nargabad,Nargabar,Nargatharb,Nargila,Nargundum,Nargundush,Nargunul,Narukthar,Narukthel,Nula,Nulbadush,Nulbaram,Nulbilnarg,Nulbunal,Nulbundab,Nulbundin,Nulbundum,Nulbuzah,Nuledzah,Nuledzig,Nulukkhaz,Nulukkhund,Nulukkhur,Sharakinb,Sharakzar,Sharamunz,Sharbarukth,Shatharbhizd,Shatharbiz,Shathazah,Shathizdush,Shathola,Shaziragz,Shizdinar,Shizdushund,Sholukkharb,Shundinulb,Shundushund,Shurakzund,Shuramunz,Tumunzadd,Tumunzan,Tumunzar,Tumunzinb,Tumunzir,Ukthad,Ulbirad,Ulbirar,Ulunzar,Ulur,Umunzad,Undalar,Undukkhil,Undun,Undur,Unduzur,Unzar,Unzathun,Usharar,Zaddinarg,Zaddushur,Zaharbad,Zaharbhizd,Zarakib,Zarakzar,Zaramunz,Zarukthel,Zinbarukth,Zirakinb,Zirakzir,Ziramunz,Ziruktharbh,Zirukthur,Zundumunz"},
	  {name: "Goblin", i: 36, min: 4, max: 9, d: "eag", m: 0, b: "Crild,Cielb,Srurd,Fruict,Xurx,Crekork,Strytzakt,Ialsirt,Gnoklig,Kleardeek,Gobbledak,Thelt,Swaxi,Ulm,Shaxi,Thult,Jasheafta,Kleabtong,Bhiagielt,Kuipuinx,Hiszils,Nilbog,Gneabs,Stiolx,Esz,Honk,Veekz,Vohniots,Bratliaq,Slehzit,Diervaq,Zriokots,Buyagh,Treaq,Phax,Ilm,Blus,Srefs,Biokvish,Gigganqi,Watvielx,Katmelt,Slofboif,gobbok,Klilm,Blix,Qosx,Fygsee,Moft,Asinx,Joimtoilm,Styrzangai,Prolkeh,Stioskurt,Mogg,Cel,Far,Rekx,Chalk,Paas,Brybsil,Utiarm,Eebligz,Iahzaarm,Stuikvact,Gobbrin,Ish,Suirx,Utha,Taxai,Onq,Stiaggaltia,Dobruing,Breshass,Cosvil,Traglila,Felhob,Hobgar,Preang,Sios,Wruilt,Chox,Pyreazzi,Glamzofs,Froihiofz,Givzieqee,Vreagaald,Bugbig,Kluirm,Ulb,Driord,Stroir,Croibieq,Bridvelb,Wrogdilk,Slukex,Ozbiard,Gagablin,Heszai,Kass,Chiafzia,Thresxea,Een,Oimzoishai,Enissee,Glernaahx,Qeerags,Phigheldai,Ziggek"},
	  {name: "Orc", i: 37, min: 4, max: 8, d: "gzrcu", m: 0, b: "ModhOdod,BodRugniz,Rildral,Zalbrez,Bebugh,Grurro,Ibruzzed,Goccogmurd,CheganKhed,BedgezGraz,IkhUgnan,NoGolkon,Dhezza,Chuccuz,Dribor,Khezdrugh,Uzdriboz,Nolgazgredh,KrogvurOz,ZrucraBi,ErLigvug,OkhUggekh,Vrobrun,Raggird,Adgoz,Chugga,Ghagrocroz,Khuldrerradh,IrmekhBhor,KuzgrurdDedh,ZunBergrord,AdhKhorkol,Alzokh,Mubror,Bozdra,Brugroz,Nuzecro,Qidzodkakh,GharedKrin,OrkudhBhur,EkhKrerdrugh,KrarZurmurd,Nuccag,Rezegh,Lorgran,Grergran,Nadguggez,Mocculdrer,BrorkrilZrog,RurguzVig,CharRodkeg,UghBhelgag,Zulbriz,Rodrekh,Erbragh,Bhicrur,Arkugzo,Arrordri,MiccolBurd,OddighKrodh,UghVruron,VrughNardrer,Dhoddud,Murmad,Chuzar,Vrazin,Ridgozedh,Lazzogno,MughakhChil,VrolburNur,KrighBhurdin,GhadhDrurzan,Adran,Chazgro,Krorgrug,Grodzakh,Ugrudraz,Iggulzaz,KudrukhLi,QuccuBan,GrighKaggaz,ArdGrughokh,Zolbred,Drozgrir,Agkadh,Zuggedh,Lulkore,Dhulbazzol,DhazonNer,ZrazzuzVaz,BrurKorre,EkhMezred,Vaddog,Drirdradh,Qashnagh,Arad,Zadarord,Khorbriccord,NelzorZroz,DruccoRad,DhodhBrerdrodh,BhakhZradgukh,Qirrer,Uzord,Bulbredh,Khuzdraz,Churgrorgadh,Legvicrodh,GazdrakhVrard,VagordKhod,GidhUcceg,BhogKirgol,Brogved,Aga,Kudzal,Brolzug,Ughudadh,Noshnogradh,ZubodUr,ZrulbukhDekh,ReVurkog,RoghChirzaz,Kharkiz,Bhogug,Bozziz,Vuccidh,Ruddirgrad,Zordrordud,GrirkrunQur,IbulBrad,AdAdzurd,GaghDruzred,Acran,Morbraz,Drurgin,Chogidh,Nogvolkar,Uzaggor,KazzuzZrar,ArrulChukh,DiChudun,GhoUgnud,Uzron,Uzdroz,Gholgard,Zragmukh,Qiddolzog,Reradgri,QiccadChal,NubudId,ZrardKrodog,KrudhKhogzokh,Vizdrun,Orrad,Darmon,Ulkin,Zigmorbredh,Bizzadurd,MuccugGhuz,MabraghBhard,DurKhaddol,BheghGegnod,Qazzudh,Drobagh,Zorrudh,Dodkakh,Gribrabrokh,Quggidkad,DududhAkh,DrizdedhAd,GhordBhozdrokh,ZadEzzedh,Larud,Ashnedh,Gridkog,Qirzodh,Bhirgoshbel,Ghirmarokh,ArizDru,AgzilGhal,DrodhAshnugh,UghErrod,Lugekh,Buccel,Rarurd,Verrugh,Qommorbrord,Bagzildre,NazadLudh,IbaghChol,GrazKhulgag,QigKrorkodh,Rozzez,Koggodh,Ruzgrin,Zrigud,Zragrizgrakh,Irdrelzug,VrurzarMol,KezulBruz,GurGhogkagh,KigRadkodh,Ulgor,Kroddadh,Eldrird,Bozgrun,Digzagkigh,Azrurdrekh,KhuzdordDugh,DhurkighGrer,MeGheggor,KoGerkradh,Bashnud,Nirdrukh,Adog,Egmod,Vruzzegvukh,Nagrubagh,DugkegVuz,MorkirZrudh,NudhKuldra,DhodhGhigin,Graldrodh,Rero,Merkraz,Ummo,Largraragh,Brordeggeg,UldrukhBhudh,DregvekhOg,GughZozgrod,GhidZrogiz,Khebun,Ordol,Ghadag,Dredagh,Bhiccozdur,Chizeril,KarkorZrid,EmmanMaz,LiBogzel,EkhBeccon,Dashnukh,Kacruz,Krummel,Dirdrurd,Khalbammedh,Dhizdrermodh,GharuZrug,BhurkrukhLen,ZuZredzokh,BralLazogh,Velgrudh,Dorgri,Irbraz,Udral,Bigkurel,Zarralkod,DhoggunBhogh,AdgrilGha,DrukhQodgoz,KaNube,Vrurgu,Mazgar,Lalga,Bolkan,Kudgroccukh,Zraldrozzuz,VorordUz,ZacradLe,BrukhZrabrul,GagDrugmag,Kraghird,Bhummagh,Brazadh,Kalbrugh,Brogzozir,Mugmodror,RezgrughErd,UmmughEkh,GuNuccul,VunGaghukh,Ghizgil,Arbran,Bulgragh,Negvidh,Girodgrurd,Ghedgrolbrol,DrogvukhDrodh,DhalgronMog,MulDhazzug,ChazCharard,Drurkuz,Niddeg,Bagguz,Ogkal,Rordrushnokh,Gorkozzil,KorkrirGrar,RigaghZrad"},
	  {name: "Giant", i: 38, min: 5, max: 10, d: "kdtng", m: 0, b: "Kostand,Throtrek,Solfod,Shurakzund,Heimfara,Anumush,Dulkun,Sigbeorn,Velhera,Glumvat,Khundinarg,Shathizdush,Baramunz,Nargunul,Magald,Noluch,Yotane,Tumunzar,Giledzir,Nurkel,Khizdabun,Yudgor,Hartreo,Galfald,Vigkan,Kibarak,Girkun,Gomruch,Guddud,Darnaric,Botharic,Gunargath,Oldstin,Rizen,Marbold,Nargundush,Hargarth,Kengord,Maerdis,Brerstin,Sigbi,Zigez,Umunzad,Nelkun,Yili,Usharar,Ranhera,Mistoch,Nuledzah,Nulbilnarg,Nulukkhur,Tulkug,Kigine,Marbrand,Gagkake,Khathizdin,Geru,Nagu,Grimor,Kaltoch,Koril,Druguk,Khatharbar,Debuch,Eraddam,Neliz,Brozu,Morluch,Enuz,Gatal,Beratira,Gurkale,Gluthmark,Iora,Tozage,Agane,Kegkez,Nuledzig,Bahourg,Jornangar,Kilfond,Dankuc,Rurki,Eldond,Barakzig,Olane,Gostuz,Grimtira,Brildung,Nulbaram,Nargabar,Narazar,Natan,oci,Khaziragz,Gabuzan,Orga,Addundad,Yulkake,Nulukkhaz,Bundushund,Guril,Barakinb,Sadgach,Vylwed,Vozig,Hildlaug,Chergun,Dagdhor,Kibizar,Shundushund,Mornkin,Jaldhor,inez,Lingarth,Churtec,Naragzah,Gabizir,Zugke,Ranava,Minu,Barazinb,Fynwyn,Talkale,Widhyrde,Sidga,Velfirth,Varkud,Shathola,Duhal,Srokvan,Guruge,Lindira,Rannerg,Kilkan,Gudgiz,Baragzund,Aerora,Inginy,Kharbharbiln,Theoddan,Rirkan,Undukkhil,Borgbert,Dina,Gortho,Kinbuzar,Kuzake,Drard,Gorkege,Nargatharb,Diru,Shatharbiz,Sgandrol,Sharakzar,Barakzinb,Dinez,Jarwar,Khizdushel,Wylaeya,Khazanar,Beornelde,Arangrim,Sholukkharb,Stighere,Gulwo,Irkin,Jornmoth,Gundusharb,Gabaram,Shizdinar,Memron,Guzi,Naramunz,Morntaric,Somrud,Norginny,Bremrol,Rurkoc,Zugkan,Vorkige,Kinbadab,Gila,Sulduch,Natil,Idgurth,Gabaragz,Tolkeg,Eradhelm,Dugfast,Froththorn,Galgrim,Theodgrim,Valdhere,Gazin,Tigkiz,Burthug,Chazruc,Kakkek,Toren"},
	  {name: "Draconic", i: 39, min: 6, max: 14, d: "aliuszrox", m: 0, b: "Aaronarra,Adalon,Adamarondor,Aeglyl,Aerosclughpalar,Aghazstamn,Aglaraerose,Agoshyrvor,Alduin,Alhazmabad,Altagos,Ammaratha,Amrennathed,Anaglathos,Andrathanach,Araemra,Araugauthos,Arauthator,Arharzel,Arngalor,Arveiaturace,Athauglas,Augaurath,Auntyrlothtor,Azarvilandral,Azhaq,Balagos,Baratathlaer,Bleucorundum,BrazzPolis,Canthraxis,Capnolithyl,Charvekkanathor,Chellewis,Chelnadatilar,Cirrothamalan,Claugiyliamatar,Cragnortherma,Dargentum,Dendeirmerdammarar,Dheubpurcwenpyl,Domborcojh,Draconobalen,Dragansalor,Dupretiskava,Durnehviir,Eacoathildarandus,Eldrisithain,Enixtryx,Eormennoth,Esmerandanna,Evenaelorathos,Faenphaele,Felgolos,Felrivenser,Firkraag,Fll'Yissetat,Furlinastis,Galadaeros,Galglentor,Garnetallisar,Garthammus,Gaulauntyr,Ghaulantatra,Glouroth,Greshrukk,Guyanothaz,Haerinvureem,Haklashara,Halagaster,Halaglathgar,Havarlan,Heltipyre,Hethcypressarvil,Hoondarrh,Icehauptannarthanyx,Iiurrendeem,Ileuthra,Iltharagh,Ingeloakastimizilian,Irdrithkryn,Ishenalyr,Iymrith,Jaerlethket,Jalanvaloss,Jhannexydofalamarne,Jharakkan,Kasidikal,Kastrandrethilian,Khavalanoth,Khuralosothantar,Kisonraathiisar,Kissethkashaan,Kistarianth,Klauth,Klithalrundrar,Krashos,Kreston,Kriionfanthicus,Krosulhah,Krustalanos,Kruziikrel,Kuldrak,Lareth,Latovenomer,Lhammaruntosz,Llimark,Ma'fel'no'sei'kedeh'naar,MaelestorRex,Magarovallanthanz,Mahatnartorian,Mahrlee,Malaeragoth,Malagarthaul,Malazan,Maldraedior,Maldrithor,MalekSalerno,Maughrysear,Mejas,Meliordianix,Merah,Mikkaalgensis,Mirmulnir,Mistinarperadnacles,Miteach,Mithbarazak,Morueme,Moruharzel,Naaslaarum,Nahagliiv,Nalavarauthatoryl,Naxorlytaalsxar,Nevalarich,Nolalothcaragascint,Nurvureem,Nymmurh,Odahviing,Olothontor,Ormalagos,Otaaryliakkarnos,Paarthurnax,Pelath,Pelendralaar,Praelorisstan,Praxasalandos,Protanther,Qiminstiir,Quelindritar,Ralionate,Rathalylaug,Rathguul,Rauglothgor,Raumorthadar,Relonikiv,Ringreemeralxoth,Roraurim,Ruuthundrarar,Rylatar'ralah'tyma,Rynnarvyx,Sablaxaahl,Sahloknir,Sahrotaar,Samdralyrion,Saryndalaghlothtor,Sawaka,Shalamalauth,Shammagar,Sharndrel,Shianax,Skarlthoon,Skurge,Smergadas,Ssalangan,Sssurist,Sussethilasis,Sylvallitham,Tamarand,Tantlevgithus,Taraunramorlamurla,Tarlacoal,Tenaarlaktor,Thalagyrt,Tharas'kalagram,Thauglorimorgorus,Thoklastees,Thyka,Tsenshivah,Ueurwen,Uinnessivar,Urnalithorgathla,Velcuthimmorhar,Velora,Vendrathdammarar,Venomindhar,Viinturuth,Voaraghamanthar,Voslaarum,Vr'tark,Vrondahorevos,Vuljotnaak,Vulthuryol,Wastirek,Worlathaugh,Xargithorvar,Xavarathimius,Yemere,Ylithargathril,Ylveraasahlisar,Za-Jikku,Zarlandris,Zellenesterex,Zilanthar,Zormapalearath,Zundaerazylym,Zz'Pzora"},
	  {name: "Arachnid", i: 40, min: 4, max: 10, d: "erlsk", m: 0, b: "Aaqok'ser,Acah,Aiced,Aisi,Aizachis,Allinqel,As'taq,Ashrash,Caaqtos,Caq'zux,Ceek'sax,Ceezuq,Cek'siereel,Cen'qi,Ceqru,Ceqzocer,Cezeed,Chachocaq,Charis,Chashar,Chashilieth,Checib,Chen'qal,Chernul,Cherzoq,Chezi,Chiazu,Chikoqal,Chishros,Chixhi,Chizhi,Chizoser,Chollash,Choq'sha,Chouk'rix,Cinchichail,Collul,Ecush'taid,Eenqachal,Ekiqe,El'zos,El'zur,Ellu,Eq'tur,Eqa,Eqas,Er'uria,Erikas,Ertu,Es'tase,Esrub,Evirrot,Exha,Haqsho,Heekath,Hiavheesh,Hitha,Hok'thi,Hossa,Iacid,Iciever,Ik'si,Illuq,Iri,Isicer,Isnir,Ivrid,Kaalzux,Keezut,Kheellavas,Kheizoh,Khellinqesh,Khiachod,Khika,Khinchi,Khirzur,Khivila,Khonrud,Khontid,Khosi,Khrakku,Khraqshis,Khrerrith,Khrethish'ti,Khriashus,Khrika,Khrirni,Khrocoqshesh,Klashirel,Klassa,Kleil'sha,Kliakis,Klishuth,Klith'osha,Krarnit,Kras'tex,Kreelzi,Krivas,Krotieqas,Laco,Lairta,Lais'tid,Laizuh,Lasnoth,Lekkol,Len'qeer,Leqanches,Lezad,Lhezsi,Lhilir,Lhivhath,Lhok'thu,Lialliesed,Liaraq,Liarisriq,Liceva,Lichorro,Lilla,Livorzish,Lokieqib,Nakar,Nakur,Naros,Natha,Necuk'saih,Neerhaca,Neet'er,Neezoh,Nenchiled,Nerhalneth,Nir'ih,Nizus,Noreeqo,Novalsher,On'qix,Qailloncho,Qak'sovo,Qalitho,Qartori,Qas'tor,Qasol,Qavrud,Qavud,Qazar,Qazieveq,Qazru,Qeik'thoth,Qekno,Qeqravee,Qes'tor,Qhaaviq,Qhaik'sal,Qhak'sish,Qhazsakais,Qhechorte,Qheliva,Qhenchaqes,Qherazal,Qhesoh,Qhiallud,Qhon'qos,Qhoshielleed,Qish'tur,Qisih,Qollal,Qorhoci,Qouxet,Qranchiq,Racith,Rak'zes,Ranchis,Rarhie,Rarzi,Rarzisiaq,Ras'tih,Ravosho,Recad,Rekid,Relshacash,Reqishee,Rernee,Rertachis,Rezhokketh,Reziel,Rhacish,Rhail'shel,Rhairhizse,Rhakivex,Rhaqeer,Rhartix,Rheciezsei,Rheevid,Rhel'shir,Rhetovraix,Rhevhie,Rhialzub,Rhiavekot,Rhikkos,Rhiqese,Rhiqi,Rhiqracar,Rhisned,Rhokno,Rhousnateb,Rhouvaqid,Riakeesnex,Rik'sid,Rintachal,Rir'ul,Rorrucis,Rosharhir,Rourk'u,Rouzakri,Sailiqei,Sanchiqed,Sanqad,Saqshu,Sat'ier,Sazi,Seiqas,Shieth'i,Shiqsheh,Shizha,Shrachuvo,Shranqo,Shravhos,Shravuth,Shreerhod,Shrethuh,Shriantieth,Shronqash,Shrovarhir,Shrozih,Siacaqoh,Siezosh,Silrul,Siq'sha,Sirro,Sornosi,Srachussi,Sreqrud,Srirnukaaq,Szaca,Szacih,Szaqova,Szasu,Szazhilos,Szeerrud,Szeezsad,Szeknur,Szesir,Szet'as,Szetirrar,Szezhirros,Szilshith,Szon'qol,Szornuq,Xaax'uq,Xeekke,Xosax,Yaconchi,Yacozses,Yazrer,Yeek'su,Yeeq'zox,Yeqil,Yeqroq,Yeveed,Yevied,Yicaveeh,Yirresh,Yisie,Yithik'thaih,Yorhaqshes,Zacheek'sa,Zakkasa,Zaqi,Zelraq,Zeqo,Zhaivoq,Zharuncho,Zhath'arhish,Zhavirrit,Zhazilraq,Zhazot,Zhazsachiel,Zhek'tha,Zhequ,Zhias'ted,Zhicat,Zhicur,Zhiese,Zhirhacil,Zhizri,Zhochizses,Zhorkir,Ziarih,Zirnib,Zis'teq,Zivezeh"},
	  {name: "Serpents", i: 41, min: 5, max: 11, d: "slrk", m: 0, b: "Aj'ha,Aj'i,Aj'tiss,Ajakess,Aksas,Aksiss,Al'en,An'jeshe,Apjige,Arkkess,Athaz,Atus,Azras,Caji,Cakrasar,Cal'arrun,Capji,Cathras,Cej'han,Ces,Cez'jenta,Cij'te,Cinash,Cizran,Coth'jus,Cothrash,Culzanek,Cunaless,Ej'tesh,Elzazash,Ergek,Eshjuk,Ethris,Gan'jas,Gapja,Gar'thituph,Gopjeguss,Gor'thesh,Gragishaph,Grar'theness,Grath'ji,Gressinas,Grolzesh,Grorjar,Grozrash,Guj'ika,Harji,Hej'hez,Herkush,Horgarrez,Illuph,Ipjar,Ithashin,Kaj'ess,Kar'kash,Kepjusha,Ki'kintus,Kissere,Koph,Kopjess,Kra'kasher,Krak,Krapjez,Krashjuless,Kraz'ji,Krirrigis,Krussin,Ma'lush,Mage,Maj'tak,Mal'a,Mapja,Mar'kash,Mar'kis,Marjin,Mas,Mathan,Men'jas,Meth'jaresh,Mij'hegak,Min'jash,Mith'jas,Monassu,Moss,Naj'hass,Najugash,Nak,Napjiph,Nar'ka,Nar'thuss,Narrusha,Nash,Nashjekez,Nataph,Nij'ass,Nij'tessiph,Nishjiss,Norkkuss,Nus,Olluruss,Or'thi,Or'thuss,Paj'a,Parkka,Pas,Pathujen,Paz'jaz,Pepjerras,Pirkkanar,Pituk,Porjunek,Pu'ke,Ragen,Ran'jess,Rargush,Razjuph,Rilzan,Riss,Rithruz,Rorgiss,Rossez,Rraj'asesh,Rraj'tass,Rrar'kess,Rrar'thuph,Rras,Rrazresh,Rrej'hish,Rrigelash,Rris,Rris,Rroksurrush,Rukrussush,Rurri,Russa,Ruth'jes,Sa'kitesh,Sar'thass,Sarjas,Sazjuzush,Ser'thez,Sezrass,Shajas,Shas,Shashja,Shass,Shetesh,Shijek,Shun'jaler,Shurjarri,Skaler,Skalla,Skallentas,Skaph,Skar'kerriz,Skath'jeruk,Sker'kalas,Skor,Skoz'ji,Sku'lu,Skuph,Skur'thur,Slalli,Slalt'har,Slelziress,Slil'ar,Sloz'jisa,Sojesh,Solle,Sorge,Sral'e,Sran'ji,Srapjess,Srar'thazur,Srash,Srath'jess,Srathrarre,Srerkkash,Srus,Sruss'tugeph,Sun,Suss'tir,Uzrash,Vargush,Vek,Vess'tu,Viph,Vult'ha,Vupjer,Vushjesash,Xagez,Xassa,Xulzessu,Zaj'tiss,Zan'jer,Zarriss,Zassegus,Zirres,Zsor,Zurjass"}
	];
  };

  return {getBase, getCulture, getCultureShort, getBaseShort, getState, updateChain, clearChains, getNameBases, getMapName, calculateChain};
})();

*/