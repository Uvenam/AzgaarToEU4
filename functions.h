#pragma once
#include "head.h"
#include "classes.h"

void make_uppercase(std::string& data);
void make_lowercase(std::string& data);
int yn_isVowel(char possible_vowel);
void make_lowercase_any(std::wstring& data);

void WriteToFile(const std::string& message, const std::string& file_path);
void YELL(const std::string& message);
short RenderShortFromStringTimes100(const std::string& message);
short StringToShort(const std::string& message);

std::tuple<int, int, int, int> ParseStringUpdateCells(std::vector<cell_info>& all_cells, std::string& example_data);
