#include <iostream>
#include "Queue.hpp"
#include "BinaryTree.hpp"

int main()
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Ограниченная очередь:\n";
	QueueArray<int> sus(4);

	sus.enQueue(1);
	sus.enQueue(2);
	sus.enQueue(3);
	sus.enQueue(4);

	std::cout << "\nПроверка исключения OverFlow:\n";
	try
	{
		sus.enQueue(5);
	}
	catch (const QueueOverflow & error)
	{
		std::cout << error.what() << "\n";
	}

	std::cout << sus.deQueue() << "\n";
	std::cout << sus.deQueue() << "\n";
	std::cout << sus.deQueue() << "\n";
	std::cout << sus.deQueue() << "\n";

	std::cout << "Проверка исключения UnderFlow:\n";
	try
	{
		sus.deQueue();
	}
	catch (const QueueUnderflow & error)
	{
		std::cout << error.what() << "\n";
	}

	std::cout << "Проверка закольцованности очереди:\n";
	for (int i = 5; i <= 17; i++) 
	{
		sus.enQueue(i);
		std::cout << sus.deQueue() << "; ";
	}
	
	std::cout << "\n\nДеревья:\n";
	BinarySearchTree<int> treeCasual;
	BinarySearchTree<int> treeEmpty;
	BinarySearchTree<int> treeDegenerated;

	treeCasual.insert(5);
	treeCasual.insert(4);
	treeCasual.insert(6);
	treeCasual.insert(7);
	treeCasual.print(std::cout);

	treeEmpty.print(std::cout);

	treeDegenerated.insert(5);
	treeDegenerated.insert(10);
	treeDegenerated.insert(25);
	treeDegenerated.insert(75);
	treeDegenerated.print(std::cout);

	std::cout << "\nИтеративный обход дерева в ширину:\n";
	std::cout << "Сбалансированное: ";
	treeCasual.wideWalk();
	std::cout << "Пустое: ";
	treeEmpty.wideWalk();
	std::cout << "Вырожденное: ";
	treeDegenerated.wideWalk();

	std::cout << "\nИтеративный обход дерева (инфиксный):\n";
	std::cout << "Сбалансированное: ";
	treeCasual.iterativeInorderWalk();
	std::cout << "\nПустое: ";
	treeEmpty.iterativeInorderWalk();
	std::cout << "\nВырожденное: ";
	treeDegenerated.iterativeInorderWalk();

	std::cout << "\n\nСравнение деревьев:\n\n";
	BinarySearchTree<int> treeEqual;
	treeEqual.insert(5);
	treeEqual.insert(4);
	treeEqual.insert(6);
	treeEqual.insert(7);
	BinarySearchTree<int> treeNotEqual;
	treeNotEqual.insert(5);
	treeNotEqual.insert(4);
	treeNotEqual.insert(7);

	std::cout << "Пример №1:\n";
	treeCasual.print(std::cout);
	treeEqual.print(std::cout);
	std::cout << "Равны? " << ((treeCasual == treeEqual) ? "Да" : "Нет") << "\n\n";

	std::cout << "Пример №2:\n";
	treeCasual.print(std::cout);
	treeNotEqual.print(std::cout);
	std::cout << "Равны? " << ((treeCasual == treeNotEqual) ? "Да" : "Нет") << "\n\n";

	std::cout << "Пример №3:\n";
	treeCasual.print(std::cout);
	treeEmpty.print(std::cout);
	std::cout << "Равны? " << ((treeCasual == treeEmpty) ? "Да" : "Нет") << "\n\n";

	std::cout << "Пример №4:\n";
	treeCasual.print(std::cout);
	treeDegenerated.print(std::cout);
	std::cout << "Равны? " << ((treeCasual == treeDegenerated) ? "Да" : "Нет") << "\n\n";

	return 0;
}
