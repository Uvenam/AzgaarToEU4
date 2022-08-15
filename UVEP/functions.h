#pragma once
#include "../UVEP/head.h"

void make_uppercase(std::string& data);
void make_lowercase(std::string& data);
int yn_isVowel(char possible_vowel);
void make_lowercase_any(std::wstring& data);

void WriteToFile(const std::string& message, const std::string& file_path);
void YELL(const std::string& message);
int RenderIntFromStringTimes100(const std::string& message);
short StringToShort(const std::string& message);



void ReadFromPlaceInto(std::string wanted_file, std::string& file_info);


void EnsureDirectory(std::string desired_dir);



