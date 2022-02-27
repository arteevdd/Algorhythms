#include "util.h"

std::string str_tolower(std::string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] = tolower(s[i]);
		}
		else if (s[i] >= 'А' && s[i] <= 'Я') {
			s[i] = 'а' + (s[i] - 'А');
		}
	}
	return s;
}

bool check_eng_word(const std::string& word)
{
	bool contains_eng_letter = false;
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] >= 'а' && word[i] <= 'я') {
			return false;
		}
		if (word[i] >= 'a' && word[i] <= 'z') {
			contains_eng_letter = true;
		}
	}
	
	return contains_eng_letter;
}

bool check_rus_word(const std::string& word)
{
	bool contains_rus_letter = false;

	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] >= 'a' && word[i] <= 'z') {
			return false;
		}
		if (word[i] >= 'а' && word[i] <= 'я') {
			contains_rus_letter = true;
		}
	}
	return true;
}

std::string repair_eng_str(std::string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] < 'a' || s[i] > 'z') && s[i] != '-' && s[i] != '\'') {
			s.erase(i, 1);
			i--;
		}
	}

	return s;
}

std::string repair_rus_str(std::string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if ((s[i] < 'а' || s[i] > 'я') && s[i] != '-' && s[i] != '\'') {
			s.erase(i, 1);
			i--;
		}
	}

	return s;
}

bool check_digit(std::string s) {
	int start = 0;
	while (s[start] == ' ')
		s.erase(0, 1);
	while (s[s.length() - 1] == ' ')
		s.erase(s.length() - 1, 1);
	if (s[0] == '-')
		start = 1;

	for (int i = start; i < s.length(); i++)
	{
		if (!isdigit(s[i])) {
			return false;
		}
	}
	return true;
}