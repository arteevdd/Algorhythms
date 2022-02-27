#pragma once
#include <iostream>
#include <string>

std::string str_tolower(std::string s);
bool check_eng_word(const std::string& word);
bool check_rus_word(const std::string& word);
std::string repair_eng_str(std::string s);
std::string repair_rus_str(std::string s);
bool check_digit(std::string s);