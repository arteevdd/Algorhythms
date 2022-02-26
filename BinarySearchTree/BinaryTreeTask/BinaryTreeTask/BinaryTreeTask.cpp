#include <iostream>
#include "BinaryTreeTask.h"


int main()
{
	setlocale(LC_ALL, "rus");
	
	BinarySearchTree<int> tree2; 
	tree2.insert(20);
	tree2.insert(15);
	tree2.insert(60);
	tree2.insert(70);
	tree2.insert(30);
	tree2.insert(45);	
	tree2.insert(21);

	std::cout << "Первое дерево:\n";

	tree2.print(std::cout);

	/*tree2.deleteKey(60);
	tree2.insert(13);*/
	std::cout << "------------------------------------------------------------------"<<std::endl;

	std::cout << "Второе дерево:\n";
	
	/*std::cout<<"Узел со значением 11 не был найден: " << tree2.iterativeSearch(11) << std::endl;	
	std::cout << "Узел со значением 21 был найден: "  << tree2.iterativeSearch(21) << std::endl;*/
	std::cout << "Высота дерева: " << tree2.getHeight() << std::endl;


}

