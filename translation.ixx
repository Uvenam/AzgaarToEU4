export module translation;


// Parses text file or string into frame language (ITU-ENG) from known language (ENG)
export int Parser () {
	// https://aggslanguage.wordpress.com/clause-analysis-for-students/

	/*
	
	1.  The type of sentence it is:
			Simple
			Compound
			Complex
			Compound Complex

	2.The function of the sentence:
			Declarative
			Interrogative
			Exclamatory
			Imperative

 

	3.The make up of the sentence, labelling the sentence’s components:
			Main Clause
			Subordinate Clause
			Prepositional Phrase / Adverbial
			Non-Finite Clause
			Relative Clause
			Noun Phrase
			Embedded/Parenthetic Phrase
			Embedded/Parenthetic Clause
			Subject
			Object
			Complement
			Verb Phrase


	4.The order of the sentence’s components:


–          Which component is put at the front of the sentence = Fronting, Front Loading, Front Focus
–          Which component is hidden away inside the sentence = Embedded
–          Which component is tagged on at the end = End Focus

This skill has to be practised slavishly to reinforce the kinds of things that you can say about sentences, clauses and phrases – in terms of how the author is drawing the reader’s attention a certain way or create a specific impact.

Every phrase or clause will have a specific reason for
a)       its inclusion
b)       its position

	*/




	// Running through the tall grass, with the morning’s dew clinging to her skin, Bingo thought of Rex, of his long hair and of his jagged looks until she felt a sharper wetness on her forehead and lost her sight as the blood from the wound streamed into her eyes.   
	/*
	a)       Running through the tall grass – Non-Finite Clause
	b)       with the morning’s dew clinging to her skin – Non-Finite Clause
	c)       Bingo thought of Rex – Main Clause
	d)       of his long hair and of his jagged looks – Prepositional Phrases
	e)       until she felt a sharper wetness – Subordinate Clause
	f)         on her forehead – Prepositional Phrase / Adverbial
	g)       then she lost her vision – Subordinate Clause
	h)       as the blood from the wound streamed into her eyes – Subordinate Clause

	*/


	//Madonna finished the North American leg of her Sticky and Sweet tour last week in front of 50,000 people at Dolphin Stadium in Miami, before heading south to Mexico City.                    (bbc.co.uk)
	/*
	a)       Madonna finished the North American leg –Main Clause
	b)       of her Sticky and Sweet tour – Prepositional Phrase / Adverbia
	c)       last week – Prepositional Phrase / Adverbial
	d)       in front of 50,000 people – Prepositional Phrase/ Adverbial
	e)       at Dolphin Stadium – Prepositional Phrase/ Adverbial
	f)         in Miami– Prepositional Phrase/ Adverbial
	g)       before heading south – Non-Finite Clause
	h)       to Mexico City– Prepositional Phrase / Adverbial
	i)         Madonna – subject
	j)         the North American leg – object & noun phrase
	
	
	
	
	
	
	
	
	
	*/


	/// Variables: source_language,	text_source, text_string)
	// source_language = "ENG" or "SPA"
	// text_source = file location (C:\roses.txt) or 0
	// text_string = "I am going out tonight" or 0
	// examples will be using ENG parsing
	/*
		check text_source
			if 0, then check text_string
				if 0, then return 1 -> issue with processing request. no text specified
				if not 0, it is a string. go do parsing
			if 1, then go get file, turn into string, and do parsing

	[SENTENCE].
	[[CLAUSE], [CLAUSE]].
	[[[NOUN][VERB]],[[NOUN][VERB][NOUN]]].
	clause termination words/symbols (examples, need full list):
		,		with		and		as		then		of		until



	*/

	// WORD PASRE
	/*
		find word in string

		check if word is noun
		check if word is verb
		check if word is adjective
		check if word is adverb
		check if word is connecting word (like,as,with, etc.)

		move to next word
	
	
	*/

	// FORMAT PARSE
	/*
		estimate clause 1, from word 1 to clause start (of, " , ", like, with, and, etc.)

			is word 1 a clause starter/ender? -> prolly not the main clause
				is word 1 a time relational one? -> prolly a subordinate clause
				is word 1 a locational one -> prolly a prepositional clause
			Noun
			Verb
			Noun - Verb
			Noun - Verb - Noun
			Verb - Noun

			does verb end in ing/is it ongoing? -> prolly a non-finite clause if V or VN
			is it NVN? -> prolly main clause


		is there a clause after?


	*/




	return 0;

}