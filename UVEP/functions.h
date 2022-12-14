#pragma once
#include "../UVEP/head.h"
#include "../UVEP/VUCO.h"
void make_uppercase(std::string& data);
void make_lowercase(std::string& data);
int yn_isVowel(char possible_vowel);
void make_lowercase_any(std::wstring& data);

void WriteToFile(const std::string& message, const std::string& file_path);
//void YELL(const std::string& message);
int RenderIntFromStringTimes100(const std::string& message);
short StringToShort(const std::string& message);

std::string OpenFileReturnString(std::string desired_dir);
// Reads entire file contents
void ReadFromPlaceInto(std::string wanted_file, std::string& file_info);
std::vector<std::string> ReadFromLineByLine( std::string wanted_file );

// NOTE: CANNOT DO WITH SUB DIRECTORIES, HAVE TO DO IN ORDER!!!
void EnsureDirectory(std::string desired_dir);

// Returns the relative directory for a single file determined by filter
std::string FindFileDirectory( std::string base_directory, std::regex filter );


