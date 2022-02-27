#include <iostream>
#include <Windows.h>
#include "BinarySearchTree.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    BinarySearchTree tree;
	tree.load_file();

	int choose;
	do
	{
		std::cout << "1.Добавить слово в словарь" << std::endl;
		std::cout << "2.Найти перевод слова" << std::endl;
		std::cout << "3.Удалить слово" << std::endl;
		std::cout << "4.Добавить перевод" << std::endl;
		std::cout << "0.Выход" << std::endl;

		std::cin >> choose;

		if (choose == 1) {
			std::cout << "Введите английское слово: ";
			std::string eng_word;
			std::cin >> eng_word;

			int n;
			std::cout << "Введите кол-во переводов: ";
			std::cin >> n;

			std::string* words = new std::string[n];
			for (size_t i = 0; i < n; i++)
			{
				std::cout << "Введите перевод: ";
				std::cin >> words[i];
			}

			bool res = tree.insert(eng_word, words, n);
			if (res) {
				std::cout << "Слово успешно добавлено" << std::endl;
				tree.save_file();
			}
			else
			{
				std::cout << "Такое слово уже есть!" << std::endl;
			}
		}
		else if (choose == 2) {
			std::cout << "Введите английское слово: ";
			std::string eng_word;
			std::cin >> eng_word;

			tree.search(eng_word);
		}
		else if (choose == 3) {
			std::cout << "Введите английское слово: ";
			std::string eng_word;
			std::cin >> eng_word;

			bool res = tree.delete_word(eng_word);
			if (res)
			{
				std::cout << "Слово успешно удалено" << std::endl;
				tree.save_file();
			}
			else
				std::cout << "Нет такого слова" << std::endl;
		}
		else if (choose == 4) {
			std::cout << "Введите английское слово: ";
			std::string eng_word;
			std::cin >> eng_word;

			std::cout << "Введите русское слово: ";
			std::string rus_word;
			std::cin >> rus_word;

			bool res = tree.add(eng_word, rus_word);
			if (res)
			{
				std::cout << "Слово успешно добавлено" << std::endl;
				tree.save_file();
			}
			else
			{
				std::cout << "Такой перевод уже есть" << std::endl;
			}
		}
	} 
	while (choose != 0);
}

