#include "../UVEP/classes.h"


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
	void cell_info::add_coord( int x_coord, int y_coord ) {
		//this->verticies.push_back(std::make_tuple(x_coord, y_coord));
		this->verticies.push_back( RPoint( x_coord, y_coord ) );
	}
/*############################################################################################################*/







// culture_namebase Class
/*############################################################################################################*/
	void culture_namebase::fn_makeWord(int length_ele, int depth_ele)
	{
		// DEPRECATED
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
		//DEPRECATED
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









		VUCO(nm, word_str,act);
		this->unique_names.insert(word_str);




	}
	std::string culture_namebase::getName()
	{
		//DEPRECATED
		std::unordered_set<std::string> ::iterator going_through = this->unique_names.begin();
		return *going_through;
	}
	void culture_namebase::fn_make_vector_of_unique_names()
	{
		//DEPRECATED
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
			VUCO("fnMM Word", eachword, act);
			for (int eachchar = 0; eachchar <= original_list[eachword].length() - 2; eachchar++)
			{
				VUCO("fnMM Characters", eachchar,act);
				try
				{
					// get 2 characters
					onset_building = original_list[eachword].substr(eachchar, 2);	// from original list element (i.e. a word), get the first two characters, copy them and place them into onsets
					//std::cout << "\n" << "[mMC] BUILT ONSET " << onset_building;
					VUCO("fnMM Get Onset", onset_building,act);

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
							//std::cout << "\n" << "[ISSUE] ONSET_BUILDING ONLY LENGTH 1, SOMEHOW REACHED FURTHER THAN INTENDED";
							VUCO( "ISSUE", "ONSET_BUILDING ONLY LENGTH 1, SOMEHOW REACHED FURTHER THAN INTENDED" );
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

		VUCO( nm, "END OF FUNCTION", act);
	} // end funct

	void culture_namebase::fn_AzgaarNamebaseGeneration( std::vector<std::string> original_list )
	{
		// [9-24-22][13:46]
		/*
		Will use null key and input syllable up to five char.
		*/
		// ISSUE: Empty key, 5 chars. Somehow got "micha" as syllable, should have just been mich
		//		key of m, somehow got "ichae" as syllable
		//			Empty key, somehow got "ezeki" as syllable


		bool act = FALSE;
		std::string fnn = "AzgNamebaseGen";

		
		VUCO( fnn, "\rMaking Namebase...", act );


		VUCO( fnn, "Get size of og_list", act );
		int list_size = original_list.size();
		std::smatch m;
		VUCO( fnn, "Regex matches", act );
		std::regex latinize ("\[^ -~\]");	// match from space to tilde (ASCII decimal 33 to 126)
		// For every word in original_list
		for (int eachword = 0; eachword < list_size; eachword++) {
			VUCO( fnn, "Iterating through og_list", act );
			VUCO( fnn, eachword, act );

			// std::string t_name;
			std::string t_name;
			// set t_name = lowercase (original_list) item
			t_name = original_list[eachword];
			make_lowercase( t_name );
			int t_name_size = t_name.length();
			// test if characters are US-keyboard (i.e. from UCS-2 unicode 0x0020 to 0x007E (essentially all letters on English keyboard, no special chars like accented e), and store truth value in bool BASIC;
			std::regex_search( t_name, m, latinize );
			bool BASIC = m.empty();
			// for (int i = 0; std::string syllable= ""; i < name.length(); i += syllable.length() || 1, syllable = "")
			std::string syllable = "";
			unsigned char v = 0; // 0 if no vowels in syllable
			for (signed char i = -1; i < t_name_size; i += (syllable.length() || 1), syllable = "") {
				VUCO( fnn, "Iterating through each character in word", act );
				// char prev = name[-1] (need prev to be equal to previous char. so for start of word, it will be "", for middle of word it'll be previous and so on
				char prev;
				//VUCO( fnn, "Attempting to u", act );
				try {
					prev = t_name.at( i );
				}
				catch (std::out_of_range& e) {
					VUCO( fnn, "\nOutofRange!", act );
					prev = '\0';
				}

				v = 0; // 0 if no vowels in syllable
				// for (int c = i+1; name.at(c) && syllable.length() < 5; c++)
				for (int c = i + 1; (syllable.length() < 5) && (c < t_name_size); c++) {
					VUCO( fnn, "Iterating through each syllable in a word", act );
					VUCO( fnn, c, act );
					VUCO( fnn, "Accessing that element of word", act );
					char that = t_name[c];
					char next;
					if (c + 1 < t_name_size) { 
						VUCO( fnn, "Able to access next char", act );
						next = t_name[c + 1]; 
					}
					else { 
						VUCO( fnn, "Next char is NULL as its the end of the word", act );
						next = '\0'; 
					}

					syllable += that;


					if (syllable == " " || syllable == "-") break; // syllable starts with space or hyphen

					if ( next == '\0' || next == ' ' || next == '-') break; // no need to check

					if (yn_isVowel(that)) v = 1; // check if letter is vowel

					if (that == 'y' && next == 'e') continue; // 'ye'

					if (BASIC) {
					// English-like
						if (that == 'o' && next == 'o') continue; // 'oo'
						if (that == 'e' && next == 'e') continue; // 'ee'
						if (that == 'a' && next == 'e') continue; // 'ae'
						if (that == 'c' && next == 'h') continue; // 'ch'
					}

					if (yn_isVowel( that ) && (that == next)) break; // two same vowels in a row

					//if (v && vowel( name[c + 2] )) break; // syllable has vowel and additional	vowel is expected soon
				}
				// if chains[prev] == undefined) chains[prev] = [];
				VUCO( fnn, "Emplace using prev char as hash key", act );
				VUCO( fnn, prev , act);
				VUCO( fnn, syllable , act);
				five_letter_syllable_map[prev].push_back( syllable );

				// chains[prev].push(syllable);
			}
		}
		VUCO( fnn, "End of funct", act );
	}

	std::string culture_namebase::fn_MakeWordAzgaar( int min, int max, std::string dupl )
	{
		// The one that works, using it as such
		// if five_letter_syllables_map is empty, thow error

		// ISSUE: Created word oana, zekike, oananan, and ikekiel. None of these used null key

		bool act = FALSE;
		std::string fnn = "MWA";

		VUCO( fnn, "Begin Making word and creating", act );
		

		std::vector<std::string> v;
		
		v = this->five_letter_syllable_map['\0'];
		VUCO( fnn, "Generating Randomness...", act );
		std::random_device rd;
		std::mt19937 gen( rd() );
		std::uniform_int_distribution<> distrib( 0, 7829 );	// 7829 is a prime number (assuming there will be 4000 provinces with unique names and potentially 100 states -> 500 potential names per state?)
		VUCO( fnn, "Getting random onset syllable", act );
		std::string cur = v[distrib( gen ) % v.size()];
		//std::cout << "\n\tGot: " << cur << std::endl;
		std::string w = "";

		for (int i = 0; i < 20; i++) {
			
			if (cur == "") {
				if (w.length() < min) {
					VUCO( fnn, "Empty CUR and word too small", act );
					cur = "";
					w = "";
					v = this->five_letter_syllable_map['\0'];
				}
				else { break; }
			}
			else {
				if ((w.length() + cur.length()) > max) {
					if (w.length() < min) w += cur;
					break;
				}
				else { v = five_letter_syllable_map[cur.back()];
					if (v.size() == 0) { v = five_letter_syllable_map['\0']; }
				}
			}
			w += cur;
		
			cur = v[distrib( gen ) % v.size()];
		}

		char l = w.back();

		if (l == '\'' || l == ' ' || l == '-') { w.pop_back(); }

		//std::string name = "";
		char c;
		std::size_t found;


		// Configure W such that
			/*
			// duplication of non duplicated characters is not allowed
			for (int letter = 0; letter < w.length(); letter++) {
				c = w[letter];
				if (letter + 1 < w.length()) {
					if (c == w[letter + 1]) {
						if (dupl.find( c ) == std::string::npos) {
							found = w.find( c );
							w.replace( found, 1, "");
						}
					}
				}
			}
			// remove space after hyphen
			found = w.find( "- " );
			if (found != std::string::npos) { w.replace( found, 2, "-" ); }
			// capitalize letter after space
			found = w.find( " " );
			if (found != std::string::npos) { w[found + 1] = toupper( w[found + 1] ); }
			// capitalize letter after hyphen
			found = w.find( "-" );
			if (found != std::string::npos) { w[found + 1] = toupper( w[found + 1] ); }
			// if a character is a and the next character is e, turn it into e
			found = w.find( "ae" );
			if (found != std::string::npos) { w.replace( found, 2, "e" ); }
			// remove 3 same letters in a row
			for (int letter = 0; letter < w.length(); letter++) {
				c = w[letter];
				if (letter + 2 < w.length()) {
					if (c == w[letter + 1] && c == w[letter+2]) {
							found = w.find( c );
							w.replace( found, 2, "" );
					}
				}
			}
			*/
		std::string summ = "";
		for (int letter = 0; letter < w.length(); letter++) {
			c = w[letter];
			// if duplicate;
			if (letter + 1 < w.length()) {
				if (c == w[letter + 1]) {
					if (dupl.find( c ) == std::string::npos) {
						continue;
					}
				}
				// if ae, turn into e
				if (c == 'a' && w[letter + 1] == 'e') { continue; }
			}
			if (summ.length() > 1) {
				// if "x- x", skip
				if (summ.back() == '-' && c == ' ') { continue; }
				// if "x x", make "x X"
				if (summ.back() == ' ') { summ += toupper( c ); continue; }
				// if "x-x", make "x-X"
				if (summ.back() == '-') { summ += toupper( c ); continue; }
			}
			// if "xxx", skip first x
			if (letter + 2 < w.length()) {
				if (c == w[letter + 1] && c == w[letter + 2]) { continue; }
			}

			summ += c;

		}

		// if there is a part with only 1 letter, join the word
		found = summ.find( " " );
		if (found != std::string::npos) {
			std::string first_half = summ.substr( 0, found );
			std::string second_half = summ.substr( found );	// includes space
			if (second_half.length() < 2 || first_half.length() == 1) {
				summ = first_half + second_half.substr( 1 ); // excludes space
			}
		}
		// if the name is less than 2, name will be randomly picked from the original list
		if (summ.length() < 2) {
			//std::cout << "\n[ERROR] Picking jimothy as name as name was too short";
			VUCO( "ERROR", "Picking jimothy as name, name was too short" );

			int source_list_size = source_list.size ();
			int pick = distrib ( gen ) % source_list_size;



			summ = source_list[pick];
		}

		VUCO( fnn, "Summ is: ", act );
		//std::cout << "\n\t" << summ << std::endl;
		// first char is made upper case
		summ[0] = toupper( summ[0] );
		VUCO( fnn, "Capitalized word", act );


		return summ;
	}

  
  
  
 /*############################################################################################################*/



// Extra Functions working with relevant classes
	std::tuple<int, int, int, int> ParseStringUpdateCells(std::vector<cell_info>& all_cells, std::string& example_data) {

		//std::cout << "\nParsing string, updating cells...";
		VUCO( "", "Parsing string, updating cells..." );
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

				Xcoord = RenderIntFromStringTimes100(CellVertex_itr->str(0));
				CellVertex_itr++;


				Ycoord = RenderIntFromStringTimes100(CellVertex_itr->str(0));
				all_cells[cell_index].add_coord(Xcoord, Ycoord);
				CellVertex_itr++;

				if (Xcoord < left_most) { left_most = Xcoord; }
				if (Xcoord > right_most) { right_most = Xcoord; }
				if (Ycoord < bottom_most) { bottom_most = Ycoord; }
				if (Ycoord > top_most) { top_most = Ycoord; }
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
		VUCO_WAN( "Cells updated" );
		return std::make_tuple(left_most, right_most, top_most, bottom_most);



	}

    void NamebaseParse( std::vector<std::string> read_list, std::vector<culture_namebase>& all_namebases )
    {
		// For each item in read_list
		const std::string regex_namebase_delimited = "\[^,^\|\]+\|(\\|\\|)"; // Matches 0,1,2,3,4 will be header info
		std::regex regex_chunk( regex_namebase_delimited );
		//std::smatch namebase_string;
		
		std::sregex_iterator sreg_end;
		std::string tempmatch;
		for (int i = 0; i < read_list.size(); i++) {
			std::sregex_iterator namebase_strings_itr( read_list[i].cbegin(), read_list[i].cend(), regex_chunk );
			all_namebases.push_back( culture_namebase() );
			int namebase_tracker = all_namebases.size() - 1;
			// every item delimited by |
			// get the name of that specific namebase (so start of line to first |)
			all_namebases[namebase_tracker].name = namebase_strings_itr->str();
			namebase_strings_itr++;
			// get the min_length of words generated (so a # between first | and second |)
			tempmatch = "";
			tempmatch = namebase_strings_itr->str();
			//std::cout << "\n\tGOT: " << tempmatch << std::endl;
			all_namebases[namebase_tracker].min_length = stoi( tempmatch );
			namebase_strings_itr++;
			// get the max_length of words generated (# between second | and third |)
			tempmatch = "";
			tempmatch = namebase_strings_itr->str();
			//std::cout << "\n\tGOT: " << tempmatch << std::endl;
			all_namebases[namebase_tracker].max_length = stoi( tempmatch );
			namebase_strings_itr++;
			// get the string of chars allowed to be doubled, and the split them into char and into char vector
			all_namebases[namebase_tracker].doubled_letters = namebase_strings_itr->str();
			namebase_strings_itr++;
			// get the float (can be 0, is within 0-1 range, reads like 0.1 or something) for double word
	//		all_namebases[namebase_tracker].multi_word_names = std::stof( namebase_strings_itr->str() );
			tempmatch = "";
			tempmatch = namebase_strings_itr->str();
			//std::cout << "\n\tGOT: " << tempmatch << std::endl;
			all_namebases[namebase_tracker].multi_word_names = std::stof( tempmatch );
			namebase_strings_itr++;
			// (between fourth | and fifth (final) |)
			std::vector<std::string> word_list;
			while (namebase_strings_itr != sreg_end) {
				// get all words in sample list (everything after fifth |, format is "STRING ," w/out quotes. Final word has no following comma
				// place all words into a vector
				word_list.push_back( namebase_strings_itr->str() );
				namebase_strings_itr++;
			}
			all_namebases[namebase_tracker].fn_AzgaarNamebaseGeneration( word_list );
			all_namebases[namebase_tracker].source_list = word_list;
		}
		return;
    }

	std::vector<state_info> StateParse( std::string state_path )
	{
		VUCO ( "", "Parsing states..." );
		bool act = FALSE;
		std::vector<state_info> all_states;
		std::vector<std::string> state_strs;
		state_strs = ReadFromLineByLine( state_path );
		state_strs.erase( state_strs.begin() );
		int all_states_size = state_strs.size();
		if (all_states_size <= 1) { throw std::runtime_error( "# of states too small!" ); }
		all_states.reserve( all_states_size );	// Rough estimate,
		std::regex comma_separated( "\[^,\]+" );
		std::sregex_iterator sreg_end;
		for (int state_itr = 0; state_itr < all_states_size; state_itr++) {
			std::sregex_iterator State_Track( state_strs[state_itr].cbegin(), state_strs[state_itr].cend(), comma_separated );
			all_states.push_back( state_info() );
			while (State_Track != sreg_end) {
				// ID ####################################################################################
				all_states[state_itr].ID = std::stoi( State_Track->str() );
				VUCO( "", all_states[state_itr].ID, act );
				if (all_states[state_itr].ID == 0) { break; } // neutrals have nothing
				State_Track++;
				// STATE #################################################################################
				all_states[state_itr].name = (State_Track->str());
				VUCO( "", all_states[state_itr].name, act );
				State_Track++;
				// FULL NAME #############################################################################
				std::string vvtemp = State_Track->str();
				VUCO( "", vvtemp, act );
				State_Track++;
				// FORM ##################################################################################
				all_states[state_itr].form = State_Track->str();
				State_Track++;
				//COLOR ###################################################################################
				std::string bbtemp = State_Track->str();
				int hexified;
				bbtemp.erase( bbtemp.begin() );
				std::stringstream hexifier;
				hexifier << std::hex << bbtemp;
				hexifier >> hexified;
				//all_states[state_itr].color = hexified;
				all_states[state_itr].color_rgb[0] = static_cast<unsigned char>((hexified & 0xFF0000) >> 16);
				all_states[state_itr].color_rgb[1] = static_cast<unsigned char>((hexified & 0x00FF00) >> 8);
				all_states[state_itr].color_rgb[2] = static_cast<unsigned char>((hexified & 0x0000FF) >> 0);

				State_Track++;
				//CAPITAL ################################################################################
				all_states[state_itr].capital = State_Track->str();
				State_Track++;
				//CULTURE ################################################################################
				all_states[state_itr].culture = State_Track->str();
				State_Track++;
				//TYPE ###################################################################################
				all_states[state_itr].type = State_Track->str();
				State_Track++;
				//EXPANSIONISM ###########################################################################
				all_states[state_itr].expansionism = std::stof( State_Track->str() );
				State_Track++;
				//CELLS / cell count #####################################################################
				State_Track++;
				//BURGS / burg count #####################################################################
				State_Track++;
				// AREA MI2 ##############################################################################
				State_Track++;
				//TOTAL POPULATION #######################################################################
				State_Track++;
				// RURAL POPULATION ######################################################################
				State_Track++;
				//URBAN POPULATION #######################################################################
				vvtemp = State_Track->str();
				VUCO( "", vvtemp, act );
				State_Track++;



			}
		}
		VUCO_WAN ( "States parsed." );

		return all_states;
	}

	std::vector<culture> CultureParse( std::string culture_path )
	{
		VUCO ( "", "Parsing cultures..." );
		std::vector<culture> all_cultures;
		bool act = FALSE;
		std::vector<std::string> culture_strs;
		culture_strs = ReadFromLineByLine( culture_path );
		culture_strs.erase( culture_strs.begin() ); // gets rid of format example
		int all_culture_size = culture_strs.size();
		if (all_culture_size <= 1) { throw std::runtime_error( "# of cultures too small!" ); }
		all_cultures.reserve( all_culture_size );	// Rough estimate,
		std::regex comma_separated( "\[^,\]+" );
		std::sregex_iterator sreg_end;
		for (int culture_itr = 0; culture_itr < all_culture_size; culture_itr++) {
			std::sregex_iterator Culture_Track( culture_strs[culture_itr].cbegin(), culture_strs[culture_itr].cend(), comma_separated );
			all_cultures.push_back( culture() );
			while (Culture_Track != sreg_end) {
				// ID ####################################################################################
				all_cultures[culture_itr].id = std::stoi( Culture_Track->str() );
				VUCO( "", all_cultures[culture_itr].id, act );
				if (all_cultures[culture_itr].id == 0)
				{
					Culture_Track++; Culture_Track++; Culture_Track++; Culture_Track++; Culture_Track++;
					all_cultures[culture_itr].namesbase = Culture_Track->str();
					break;
				}	//neutrals mess it up, but keep namesbase
				Culture_Track++;
				// Name #################################################################################
				all_cultures[culture_itr].name = Culture_Track->str();
				Culture_Track++;
				// Color #################################################################################
				Culture_Track++;
				// Cells #################################################################################
				Culture_Track++;
				// Expansion #################################################################################
				Culture_Track++;
				// Type #################################################################################
				all_cultures[culture_itr].type = Culture_Track->str();
				Culture_Track++;
				// Area #################################################################################
				Culture_Track++;
				// Population #################################################################################
				Culture_Track++;
				// Namesbase #################################################################################
				all_cultures[culture_itr].namesbase = Culture_Track->str();
				Culture_Track++;
				// Emblems #################################################################################
				Culture_Track++;
				// Origins #################################################################################
				if (Culture_Track == sreg_end) { break; }	// origins sometimes empty
				Culture_Track++;

			}
		}
		VUCO_WAN ( "Cultures parsed." );
		return all_cultures;
	}

    std::vector<burg_info> BurgParse( std::string burg_path )
	{
		VUCO ("","Parsing burgs...", TRUE );
		std::vector<burg_info> all_burgs;
		bool act = FALSE;
		std::string fn = "BurgParse";
		std::vector<std::string> burg_strs;
		burg_strs = ReadFromLineByLine( burg_path );
		burg_strs.erase( burg_strs.begin() ); // gets rid of format example
		int all_burg_size = burg_strs.size();
		if (all_burg_size <= 1) { throw std::runtime_error( "# of burgs too small!" ); }
		all_burgs.reserve( all_burg_size );	// Rough estimate,
		std::regex comma_separated( "\[^,\]*," );
		std::sregex_iterator sreg_end;
		for (int burg_itr = 0; burg_itr < all_burg_size; burg_itr++) {
			std::sregex_iterator burg_Track( burg_strs[burg_itr].cbegin(), burg_strs[burg_itr].cend(), comma_separated );
			all_burgs.push_back( burg_info() );
			while (burg_Track != sreg_end) {
				// ID ####################################################################################
				//all_burgs[burg_itr].id = std::stoi( burg_Track->str() );
				//VUCO( "", all_burgs[burg_itr].id, act );
				//if (all_burgs[burg_itr].id == 0)
				//{
				//	burg_Track++; burg_Track++; burg_Track++; burg_Track++; burg_Track++;
				//	all_burgs[burg_itr].namesbase = burg_Track->str();
				//	break;
				//}	//neutrals mess it up, but keep namesbase
				//burg_Track++;
				//// Name #################################################################################
				//all_burgs[burg_itr].name = burg_Track->str();
				//burg_Track++;
				//// Color #################################################################################
				//burg_Track++;
				//// Cells #################################################################################
				//burg_Track++;
				//// Expansion #################################################################################
				//burg_Track++;
				//// Type #################################################################################
				//all_burgs[burg_itr].type = burg_Track->str();
				//burg_Track++;
				//// Area #################################################################################
				//burg_Track++;
				//// Population #################################################################################
				//burg_Track++;
				//// Namesbase #################################################################################
				//all_burgs[burg_itr].namesbase = burg_Track->str();
				//burg_Track++;
				//// Emblems #################################################################################
				//burg_Track++;
				//// Origins #################################################################################
				//if (burg_Track == sreg_end) { break; }	// origins sometimes empty
				//burg_Track++;

				// ID
				//VUCO ( fn, "Parsing...", act );
				all_burgs[burg_itr].id = std::stoi ( burg_Track->str ().substr ( 0, burg_Track->str ().length () - 1 ) );
				burg_Track++;
				VUCO ( "ID", all_burgs[burg_itr].id, act );
				// BURG
				all_burgs[burg_itr].name = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				VUCO ( "NAME", all_burgs[burg_itr].name, act );
				// PROVINCE
				burg_Track++;
				// PROVINCE FULL NAME
				burg_Track++;
				// STATE
				burg_Track++;
				// STATE FULL NAME
				burg_Track++;
				// CULTURE
				all_burgs[burg_itr].culture = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				//VUCO ( "CULTURE", all_burgs[burg_itr].culture, act );
				// RELIGION
				all_burgs[burg_itr].religion = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				//VUCO ( "RELIGION", all_burgs[burg_itr].religion, act );
				// POPULATION
				all_burgs[burg_itr].pop = std::stoi( burg_Track->str().substr( 0, burg_Track->str().length() - 1 ) );
				burg_Track++;
				//VUCO ( "POP", all_burgs[burg_itr].pop, act );
				// LATITUDE
				all_burgs[burg_itr].y_latitude = static_cast<int>(100*(std::stof( burg_Track->str().substr( 0, burg_Track->str().length() - 1 ) )));
				burg_Track++;
				VUCO ( "LATITUDE", all_burgs[burg_itr].y_latitude, act );
				// LONGITUDE
				all_burgs[burg_itr].x_longitude = static_cast<int>(100 * (std::stof( burg_Track->str().substr( 0, burg_Track->str().length() - 1 ) )));
				burg_Track++;
				VUCO ( "LONG", all_burgs[burg_itr].x_longitude, act );
				// ELEVATION(ft)
				burg_Track++;
				// CAPITAL
				all_burgs[burg_itr].capital = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				// PORT
				all_burgs[burg_itr].port = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				// CITADEL
				all_burgs[burg_itr].citadel = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				// WALLS
				all_burgs[burg_itr].walls = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				// PLAZA
				all_burgs[burg_itr].plaza = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				// TEMPLE
				all_burgs[burg_itr].temple = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;
				// SHANTY TOWN
				all_burgs[burg_itr].shanty = (burg_Track->str().substr( 0, burg_Track->str().length() - 1 ));
				burg_Track++;

			}
		}
		VUCO_WAN ( "Burgs parsed" );
		return all_burgs;
	}


	void GenericOutput(std::vector<cell_info> all_cells, std::string output_file) {


		//std::cout << "\nOutputting to log.txt...";
		VUCO( "output_file", "Outputting..." );
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
					outputLog << (all_cells[proll].verticies[pion].x_pos);
					outputLog << " , ";
					outputLog << (all_cells[proll].verticies[pion].y_pos);
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

			VUCO("","write complete");



		}//end of if for outputLog
		else {
			throw std::runtime_error("Cannot open log.txt");
		}//else if couldn't open file


	}

	void TransformPoints ( int desired_width, int desired_height, std::vector<burg_info>& all_burgs, std::vector<cell_info>& all_cells, std::tuple<int, int, int, int>& extents )
	{

		/*
		//################################################################################################//
											ISSUE - TEMPORARY FIXED, so don't worry
			Transform Points
			? What if map provided is an island? So the map could be like 5000 x 2000, but the cells only
			exist within (2500,1000), (2500,1500), (2000,1000), (2000,1500)

			? Is there a need for stretching? Or even, how do you know you should stretch the points?
			Would like to store +- DD.DD floats to unsigned int (or even unsigned short)



		//################################################################################################//

		Not all burgs are getting mapped to a cell

		*/
		VUCO ("","Transforming points...", TRUE );

		bool act = FALSE;
		std::string fn = "TransformPoints";

		int tp_cell_count;
		int tp_vertex_amount;
		int tp_vertex_itr;
		tp_cell_count = all_cells.size();

		int horiz_shift_addend = std::abs( std::get<0>( extents ) );
		int vertical_shift_addend = std::abs( std::get<3>( extents ) );

		double horiz_stretch_factor =
			static_cast<double>(desired_width) / (horiz_shift_addend + std::get<1>( extents ));
		double vertical_stretch_factor =
			static_cast<double>(desired_height) / (vertical_shift_addend + std::get<2>( extents ));


		for (int tp_itr = 0; tp_itr < tp_cell_count; tp_itr++) {
			tp_vertex_amount = all_cells[tp_itr].verticies.size();
			for (tp_vertex_itr = 0; tp_vertex_itr < tp_vertex_amount; tp_vertex_itr++) {

				all_cells[tp_itr].verticies[tp_vertex_itr].x_pos += horiz_shift_addend;
				all_cells[tp_itr].verticies[tp_vertex_itr].x_pos *= horiz_stretch_factor;
				all_cells[tp_itr].verticies[tp_vertex_itr].y_pos += vertical_shift_addend;
				all_cells[tp_itr].verticies[tp_vertex_itr].y_pos *= vertical_stretch_factor;

			}
		}
		for (auto& each_burg : all_burgs) {
			VUCO ( fn, "Was:", act );
			VUCO ( "Y", each_burg.y_latitude, act );
			VUCO ( "X", each_burg.x_longitude, act );

			each_burg.x_longitude += horiz_shift_addend;
			each_burg.x_longitude *= horiz_stretch_factor;
			each_burg.y_latitude += vertical_shift_addend;
			each_burg.y_latitude *= vertical_stretch_factor;

			VUCO ( fn, "Now:", act );
			VUCO ( "Y", each_burg.y_latitude, act );
			VUCO ( "X", each_burg.x_longitude, act );
			if (each_burg.y_latitude < 0 || each_burg.x_longitude < 0) {

				throw std::runtime_error ( "IMPROPER MAPPING OF BURG AND CELLS!" );
			}


		}


		
	}

	void TransformPoints_NoStretch ( std::vector<burg_info>& all_burgs, std::vector<cell_info>& all_cells, std::tuple<int, int, int, int>& extents )
	{

		/*
		//################################################################################################//
											ISSUE - Use other
			Transform Points
			? What if map provided is an island? So the map could be like 5000 x 2000, but the cells only
			exist within (2500,1000), (2500,1500), (2000,1000), (2000,1500)

			? Is there a need for stretching? Or even, how do you know you should stretch the points?
			Would like to store +- DD.DD floats to unsigned int (or even unsigned short)

		//################################################################################################//

		Not all burgs are getting mapped to a cell

		*/


		bool act = TRUE;
		std::string fn = "TransformPoints";

		int tp_cell_count;
		int tp_vertex_amount;
		int tp_vertex_itr;
		tp_cell_count = all_cells.size ();

		VUCO ( "", "Extents are", act );
		VUCO ( "Left", std::get<0> ( extents ), act );
		VUCO ( "Right", std::get<1> ( extents ), act );
		VUCO ( "Top", std::get<2> ( extents ), act );
		VUCO ( "Bottom", std::get<3> ( extents ), act );

		int horiz_shift_addend = std::abs ( std::get<0> ( extents ) );
		int vertical_shift_addend = std::abs ( std::get<3> ( extents ) );

		VUCO ( "Horiz_shift", horiz_shift_addend, act );
		VUCO ( "Vertical_shift", vertical_shift_addend, act );

		//double horiz_stretch_factor = static_cast<double>(desired_width) / (horiz_shift_addend + std::get<1> ( extents ));
		//double vertical_stretch_factor = static_cast<double>(desired_height) / (vertical_shift_addend + std::get<2> ( extents ));


		for (int tp_itr = 0; tp_itr < tp_cell_count; tp_itr++) {
			tp_vertex_amount = all_cells[tp_itr].verticies.size ();
			for (tp_vertex_itr = 0; tp_vertex_itr < tp_vertex_amount; tp_vertex_itr++) {

				all_cells[tp_itr].verticies[tp_vertex_itr].x_pos += horiz_shift_addend;
				//all_cells[tp_itr].verticies[tp_vertex_itr].x_pos *= horiz_stretch_factor;
				all_cells[tp_itr].verticies[tp_vertex_itr].y_pos += vertical_shift_addend;
				//all_cells[tp_itr].verticies[tp_vertex_itr].y_pos *= vertical_stretch_factor;

				if (all_cells[tp_itr].verticies[tp_vertex_itr].x_pos > 100000 || all_cells[tp_itr].verticies[tp_vertex_itr].y_pos > 100000) {

					throw std::runtime_error ( "IMPROPER MAPPING OF BURG AND CELLS!" );
				}

			}
		}
		for (auto& each_burg : all_burgs) {
			VUCO ( fn, "Was:", act );
			VUCO ( "Y", each_burg.y_latitude, act );
			VUCO ( "X", each_burg.x_longitude, act );

			each_burg.x_longitude += horiz_shift_addend;
			
			each_burg.y_latitude += vertical_shift_addend;
			

			VUCO ( fn, "Now:", act );
			VUCO ( "Y", each_burg.y_latitude, act );
			VUCO ( "X", each_burg.x_longitude, act );
			if (each_burg.y_latitude < 0 || each_burg.x_longitude < 0) {

				throw std::runtime_error ( "IMPROPER MAPPING OF BURG AND CELLS!" );
			}


		}
	}

	std::vector<int> AssignBurgsToCells ( std::vector<burg_info> all_burgs, std::vector<cell_info> & all_cells )
	{
		std::vector<burg_info> all_burgs_copy = all_burgs;
		std::vector<int> index_list;
		int index = -1;
		//int total_burg_count = all_burgs_copy.size ();
		bool FNACT = FALSE;
		std::string fname = "AssignBurgToCells";
		VUCO ( fname, "Getting all_cells...", FNACT );
		int total_burg_count = all_burgs_copy.size ();
		VUCO ( "Have this many burgs:", total_burg_count, FNACT );
		int temp_burg_size = all_burgs_copy.size ();
		for (auto& each_cell : all_cells) {
			index++;
			// Don't care about water cells
			if (each_cell.biome == 0) { continue; }
			// Find cell X-min, X-max, Y-min, Y-max
			int Xmin, Xmax, Ymin, Ymax;
			Xmin = each_cell.verticies[0].x_pos;
			Xmax = each_cell.verticies[1].x_pos;
			Ymin = each_cell.verticies[0].y_pos;
			Ymax = each_cell.verticies[1].y_pos;
			for (auto& each_vertex : each_cell.verticies) {
				Xmax = (each_vertex.x_pos > Xmax) ? each_vertex.x_pos : Xmax;
				Xmin = (each_vertex.x_pos < Xmin) ? each_vertex.x_pos : Xmin;

				Ymax = (each_vertex.y_pos > Ymax) ? each_vertex.y_pos : Ymax;
				Ymin = (each_vertex.y_pos < Ymin) ? each_vertex.y_pos : Ymin;
			}
			//VUCO ( fname, "Extents are", FNACT );
			//VUCO ( "Xmin", Xmin, FNACT );
			//VUCO ( "Xmax", Xmax, FNACT );
			//VUCO ( "Ymin", Ymin, FNACT );
			//VUCO ( "Ymax", Ymax, FNACT );
			temp_burg_size = all_burgs_copy.size ();
			VUCO ( "Have X Burgs left", temp_burg_size, FNACT );
			if (temp_burg_size == 0) { VUCO ( fname, "No more burgs!", FNACT ); break; }
			//VUCO ( fname, "Checking burg...", FNACT );
			for (int i = 0; i < temp_burg_size; i++) {
				// Is this burg within the confines of the cell?
				// If yes, add burg ID to cell ID
				//VUCO ( fname, "Burg is at", FNACT );
				//VUCO ( "X", all_burgs_copy[i].x_longitude );
				//VUCO ( "Y", all_burgs_copy[i].y_latitude );
				//VUCO_WAN ( all_burgs_copy[i].y_latitude); VUCO_WAN (all_burgs_copy[i].x_longitude);
				if ((all_burgs_copy[i].y_latitude >= Ymin && all_burgs_copy[i].y_latitude <= Ymax) && (all_burgs_copy[i].x_longitude >= Xmin && all_burgs_copy[i].x_longitude <= Xmax)) {
					VUCO ( fname, "Burg assigned!", FNACT );
					VUCO ( all_burgs_copy[i].name, each_cell.id, FNACT );
					each_cell.burg_id = all_burgs_copy[i].id;
					index_list.push_back ( index );
					all_burgs_copy.erase ( all_burgs_copy.begin () + i );
					break;
				}
			}

		}
		if (temp_burg_size != 0) {
			for (auto& each_burg : all_burgs_copy) {
				std::string temp_name = std::to_string ( each_burg.id );
				VUCO ( temp_name, each_burg.name, FNACT );
				VUCO ( temp_name, each_burg.x_longitude, FNACT );
				VUCO ( temp_name, each_burg.y_latitude, FNACT );
			}

			throw std::runtime_error ( "UNASSIGNED BURGS!" );
		}
		return index_list;
	}
	
    std::vector<state_info> Breakdown( state_info parent, int option ) 
    {
        return std::vector<state_info>();
    }

	std::unordered_set<std::string> TAGParse( std::vector<state_info>& all_states )
	{
		VUCO ( "", "Parsing tags..." );
		// Iterate through each state, take name and translate into a unique 3 char TAG and update each state
		std::unordered_set<std::string> all_TAGS;
		bool acto = FALSE;
		for (auto& elem : all_states) {
			VUCO( "full name is:", elem.name, acto );
			std::string temporary_tag;
			int while_count = 0;
			char c = 'E';
			do {
				temporary_tag = "";
				VUCO( "Temp Clear", temporary_tag, acto );
				// Try to use just first three letters
				if (while_count == 0) {
					temporary_tag = elem.name.substr( 0, 3 );
					if (temporary_tag.size() < 1) { temporary_tag += "A"; } // if name is 0 char (neutrals prolly)
					if (temporary_tag.size() < 2) { temporary_tag += "0"; } // if name is 1 char
					if (temporary_tag.size() < 3) { temporary_tag += "0"; } // if name is 2 char
					// need 3 char in temporary_tag
				}
				// First try didn't work, try to use first, second, and last characters
				if (while_count == 1) {
					if (elem.name.size() < 3) {
						while_count++; continue;
					}
					if (elem.name.size() >= 3) {
						temporary_tag = elem.name.substr( 0, 1 ) + elem.name.substr( 1, 1 ) + elem.name.back();
					}
				}
				// Second try didn't work, try to use first, third, last
				if (while_count == 2) {
					if (elem.name.size() < 4) {
						while_count++; continue;
					}
					if (elem.name.size() >= 4) {
						temporary_tag = elem.name.substr( 0, 1 ) + elem.name.substr( 2, 1 ) + elem.name.back();
					}

				}
				// Just use E03,E04,E05 and so on.
				if (while_count >= 3) {

					if (while_count < 99) {
						if (while_count >= 10) { temporary_tag = std::string( 1, c ) + std::to_string( while_count ); }
						if (while_count < 10) { temporary_tag = std::string( 1, c ) + std::to_string( 0 ) + std::to_string( while_count ); }
					}
					if (while_count >= 99) {
						c += 1; while_count = 3;
						if (c >= 'Z') { throw std::runtime_error( "WAY too many TAGS!" ); break; }
					}
				}
				transform( temporary_tag.begin(), temporary_tag.end(), temporary_tag.begin(), ::toupper );
				VUCO( "Got temp tag", temporary_tag, acto );
				// Check if its NAT, REB, or PIR. Can't be those
				if (!(temporary_tag.compare( 0, 3, "NAT" )) || !(temporary_tag.compare( 0, 3, "PIR" )) || !(temporary_tag.compare( 0, 3, "REB" ))) {
					VUCO( "", "GOT BAD TAG, TRY AGAIN", acto );
					while_count++;
					continue;
				}
				while_count++;
			} while (!std::get<1>( all_TAGS.emplace( temporary_tag ) ));
			elem.TAG = temporary_tag;
		}
		VUCO_WAN ( "Tags parsed." );
		return all_TAGS;
	}

	std::vector<province_info> CreateProvinces ( std::vector<cell_info> all_cells )
	{
		VUCO ( "", "Creating provinces..." );
		std::vector<province_info> all_provinces;
		short prov_id_itr = 1;
		for (auto& each_cell : all_cells) {
			if (each_cell.biome == 0) { continue; }	// If biome = 0, then type is either ocean or lake. That should be handled elsewhere
			province_info new_province;
			new_province.prov_id = prov_id_itr++;
			new_province.cell_ids.push_back ( each_cell.id );

			all_provinces.push_back ( new_province );
		}
		VUCO_WAN ( "Created provinces." );
		return all_provinces;
	}




