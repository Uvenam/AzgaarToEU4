#include "../UVEP/classes.h"
#include "../UVEP/functions.h"

// progressBar Class
/*############################################################################################################*/
	void progressBar::update(int newProgress)
	{
		currentProgress += newProgress;
		if (currentProgress > items)
		{

			return;
		}
		amountOfFiller = pBarLength * ((double)currentProgress / items); // two int division returns int, MUST have one as a double to "upgrade" to double result

		std::cout << std::fixed << std::setprecision(0) << "\r" // bring cursor to start of line
			<< task << " "
			<< firstPartOfBar
			<< currentProgress << "/" << items << lastPartOfBar;
		std::cout << firstPartOfBar
			<< std::fixed << std::setprecision(1) << 100 * (double)currentProgress / items << "% ";

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
	void progressBar::updatePercent(double newPercent)
	{
		int increaseBy = newPercent * (items / 100);
		if ((increaseBy + currentProgress) > items)
		{
			return;
		}
		update(increaseBy);
	}
	void progressBar::reuse(int items1)
	{
		this->amountOfFiller = 0;

		this->currentProgress = 0;

		this->items = items1;

	}
	progressBar::progressBar(std::string task_ele, int elements)
	{
		task = task_ele;
		items = elements;
	}
	progressBar::progressBar(int elements)
	{
		items = elements;
	}
	progressBar::progressBar() {};
/*############################################################################################################*/

// cell_info Class
/*############################################################################################################*/
	void cell_info::add_coord(short x_coord, short y_coord) {
		this->verticies.push_back(std::make_tuple(x_coord, y_coord));
	}
/*############################################################################################################*/







// culture_namebase Class
/*############################################################################################################*/
void culture_namebase::fn_makeWord(int length_ele, int depth_ele)
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
void culture_namebase::fn_makeWord_VCVC(int length_ele, int min_ele)
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
std::string culture_namebase::getName()
{
	std::unordered_set<std::string> ::iterator going_through = this->unique_names.begin();
	return *going_through;
}
void culture_namebase::fn_make_vector_of_unique_names()
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
void culture_namebase::fn_makeMarkov(std::vector<std::string> original_list)
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
void culture_namebase::fn_getDias(std::vector<std::string> original_list)
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

	//std::string vowels_dia = "¿¡¬√ƒ≈∆»… ÀÃÕŒœ“”‘’÷ÿŸ⁄€‹›‡·‚„‰ÂÊËÈÍÎÏÌÓÔÚÛÙıˆ¯˘˙˚¸˝ˇ";
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
/*############################################################################################################*/



