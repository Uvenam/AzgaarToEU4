#include "functions.h"
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
