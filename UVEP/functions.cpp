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

void WriteToFile(const std::string&  message, const std::string& file_path) {
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
//void YELL(const std::string& message) {
//	std::cout << '\n' << message << std::endl;
//}//end of YELL
int RenderIntFromStringTimes100(const std::string& message) {
	float temp;
	int remp;
	temp = std::stof(message);
	remp = static_cast<int>(temp * 100);
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
}
std::string OpenFileReturnString( std::string desired_dir )
{
	// Trying to read for specific file (end in .geojson) within the dir_cells AND that there is only one file in it
	int ONLY_ONE_ITEM = 0;
	std::string str_path;
	//std::fstream fileStream;
	for (const auto& entry : std::filesystem::directory_iterator( desired_dir )) {
		//std::cout << '\n' << entry.path();
		str_path = entry.path().string();
		ONLY_ONE_ITEM++;
		//std::cout << "\nCONVERTED TO STRING: " << str_path;
		//fileStream.open(entry.path(),std::ios::in);
		//if (fileStream) {
		//	std::cout << "SUCCESS";
		//}
		//else {
		//	std::cout << "FAILURE";
		//}
		//fileStream.close();
	}
	if (ONLY_ONE_ITEM > 1) {
		throw (std::exception("MORE THAN ONE ITEM IN THE FOLDER!"));
	}
	return str_path;
}
// end of StringToShort


void ReadFromPlaceInto(std::string wanted_file, std::string& file_info) {
	std::stringstream buffer{};
	std::fstream fileStream;
	fileStream.open(wanted_file, std::ios::in);	// read contents (don't want to output to this file)
	if (fileStream) {
		//std::cout << wanted_file << " opened" << std::endl;
		{std::string vuco_temp = wanted_file + " opened";
		VUCO( "", vuco_temp );
		}
		// File is open, Want to get line for future usage and save (IO expensive) / Copy file contents into string
		buffer << fileStream.rdbuf();	// read entire file content
		file_info = buffer.str();		// stringify it, put it into string variable
		VUCO("","File info retrieved");
		//YELL(file_info);

	}//end of if for fileStream
	else {		// couldn't open file, some sort of error
		std::string error_specific = "Cannot open " + wanted_file;
		throw std::runtime_error(error_specific);
	}//couldn't open fileStream else


}
std::vector<std::string> ReadFromLineByLine( std::string wanted_file ) {

		bool act = FALSE;
		std::string nm = "ReadFromLbL";



		VUCO( nm, "Creating vector...", act );
		std::vector<std::string> every_file_line;
		VUCO( nm, "Creating filestream...", act );
		std::ifstream fileStream;
		VUCO( nm, "Opening file...", act );
		fileStream.open( wanted_file, std::ios::in );	// read contents (don't want to output to this file)
		
		if (fileStream) {
			VUCO( nm, "File Opened", act );
			VUCO( nm, "Get each line...", act );
			//int i = 0;
			for (std::string line = ""; std::getline(fileStream, line);) {
				//std::cout << "\nLine " << i++ << ":";
				//std::cout << line;
				every_file_line.push_back( line );
			}// end of for loop

		}//end of if for fileStream
		else {		// couldn't open file, some sort of error
			throw std::runtime_error( "Cannot open file" );
		}//couldn't open fileStream else

		return every_file_line;

}


void EnsureDirectory(std::string desired_dir) {
	if (std::filesystem::create_directory(desired_dir))	// returns false if it exists, true if it doesn't
	{
		//std::cout << '\n' << desired_dir << " created successfully!" << std::endl;
		{std::string vuco_temp = desired_dir + " created successfully!";
		VUCO( "", vuco_temp );
		}
	}
	//std::cout << '\n' << desired_dir << " directory exists" << std::endl;
	{std::string vuco_temp = desired_dir + " directory exists";
	VUCO( "", vuco_temp );
	}
}
std::string FindFileDirectory(std::string base_directory, std::regex filter )
{
	VUCO( "", "Retrieving File Path..." );
	std::smatch matches;
	std::string temp;
	for (const auto& entry : std::filesystem::directory_iterator( base_directory )) {
		temp = entry.path().string();
		std::regex_search( temp, matches, filter );
		if (matches.empty() == FALSE) {
			break;
		}
	}
	if (matches.empty() == TRUE) {
		throw std::runtime_error( std::string("Couldn't find desired file in ") + base_directory);
	}
	{std::string vuco_temp = "File " + temp + " found";
	VUCO_WAN( vuco_temp );
	}

    return temp;
}
short PromptYNX ()
{
	std::string input;
	std::cout << " [Y]es/[n]o?: ";
	std::getline ( std::cin, input );
	if (DoesCharExist ( input, 'Y' )) { return 1; }
	else { 
		if (DoesCharExist ( input, 'n' )) { return	-1; }
	}
	return 0;
}
int PromptINT ()
{
	std::string input;
	int num;
	std::cout << " #?: ";
	std::getline ( std::cin, input );

	try {
		auto value = std::stoi ( input );
		//std::cout << "Thanks for the " << value << " (but the string was \"" << input << "\")\n";
		num = value;
	}
	catch (std::invalid_argument const&) {
		std::cout << "Provide number!\n";
		num = PromptINT ();
	}
	catch (std::out_of_range const&) {
		std::cout << "Provide smaller value!\n";
		num = PromptINT ();
	}

	return num;

}
std::string PromptSTRING ()
{
	std::string input;
	std::cout << " : ";
	std::getline ( std::cin, input );
	return input;
}
bool DoesCharExist ( std::string input_string, char X ) {
	std::size_t found = input_string.find ( X );
	if (found != std::string::npos) //if X found
	{
		return TRUE;
	}
	else // if X not found
	{
		return FALSE;
	}


}