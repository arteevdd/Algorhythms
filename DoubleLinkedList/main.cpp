#include "DoubleLinkedList.h"
#include <iostream>

void test_insertTailList()
{
	std::cout << "�������� ������� ����  � ����� ������:  \n";

	DoubleLinkedList list1;   
	list1.insertTail(2);
	list1.insertTail(3);
	list1.insertTail(1);
	std::cout <<"\n������ �� �������: " << list1<< std::endl ;
	DoubleLinkedList list2;
	list2.insertTail(6);
	list2.insertTail(9);

	list1.insertTailList(list2);
	
	std::cout<< "������ ����� �������: " << list1 << std::endl << std::endl;
}

void test_constructor_copy()
{
	
	std::cout << "�������� ������������ �����������: \n";

	DoubleLinkedList list1;
	list1.insertTail(2);
	list1.insertTail(3);
	list1.insertTail(1);
	std::cout<<"\n������� ������,�� �������� ����� ��������� �����������: " << list1 << std::endl;
	DoubleLinkedList list2 = list1;
	list2.insertTail(22);

	
	std::cout<<"����� ������, �� ������ ������� ������: " << list2 << std::endl << std::endl;
}

void test_operator_prisv()
{
	std::cout << "�������� ��������� ������������ : \n";

	DoubleLinkedList list1;
	list1.insertTail(2);
	list1.insertTail(3);
	list1.insertTail(1);
	std::cout <<"\n������ ������: " << list1<< std::endl;
	DoubleLinkedList list2;
	list2.insertTail(5);
	std::cout<<"������ ������:  " << list2<< std::endl;
	list2 = list1;

	std::cout << "�������� ��� ������� ������:  " << list2 << std::endl<<std::endl;
}

void test_operator_srav() 
{
	std::cout << "�������� ��������� �������: \n\n";

	DoubleLinkedList list;   
	list.insertHead(2);      
	list.insertHead(3);
	list.insertHead(1);
	list.insertTail(5);
	list.insertTail(2);

	std::cout << "������ ������: \n";
	list.outAll(); 
	std::cout << std::endl;

	DoubleLinkedList list2;
	list2.insertHead(2);
	list2.insertHead(3);
	list2.insertHead(1);
	list2.insertTail(5);

	std::cout << "������  ������: \n";
	list2.outAll();
	std::cout << std::endl;

	DoubleLinkedList list3;
	list3.insertHead(2);
	list3.insertHead(3);
	list3.insertHead(1);
	list3.insertTail(5);
	list3.insertTail(2);

	std::cout << "������ ������: \n";
	list3.outAll();
	std::cout << std::endl;

	bool check = list == list3;
	if (check == true) {
		std::cout << "������ ���������! \n\n";
	}
	else {
		std::cout << "������ �� ���������!\n\n";
	}
}

void test_replace_item() 
{
	std::cout << "�������� ������ �������� ���� ��� ����� ������ �� ������:  \n\n";

	DoubleLinkedList list;
	list.insertHead(2);
	list.insertHead(3);
	list.insertHead(1);
	list.insertTail(5);
	list.insertTail(2);
	std::cout << "C�����: ";
	list.outAll();
	std::cout << std::endl;

	std::cout << "������ ����� ������: ";
	list.replaceItem(2, 6, true);
	list.outAll();
	std::cout << std::endl << std::endl;
}

void test_delitem() 
{
	std::cout << "�������� �������� ���������: \n\n";

	DoubleLinkedList list;
	list.insertHead(2);
	list.insertHead(3);
	list.insertHead(1);
	list.insertTail(5);
	list.insertTail(2);

	std::cout << "C�����: ";
	list.outAll();
	std::cout << std::endl;
	list.deleteItem(2, true);
	
	std::cout << "������ ����� �������� ������������ �����: ";
	list.outAll();
	std::cout << std::endl;
	std::cout << "������ ����� �������� ������: ";
	list.deleteTail();
	list.outAll();
	std::cout << std::endl << std::endl;
}

void test_search_item() 
{
	std::cout << "�������� ������ ��������� � ������: \n\n";

DoubleLinkedList list;  
	list.insertHead(2);      
	list.insertHead(0);
	list.insertHead(1);
	list.insertTail(5);
	list.insertTail(2);

	std::cout << "������: ";
	list.outAll();
	std::cout << std::endl;

	std::cout << ((list.searchItem(1)) ? "1 find" : "1 not find") << std::endl<< std::endl;
	std::cout << ((list.searchItem(8)) ? "8 find" : "8 not find") << std::endl;
}

int main() {
	setlocale(LC_ALL, "Rus");

	test_insertTailList();
	test_constructor_copy();
	test_operator_prisv();
	test_operator_srav();
	test_replace_item();
	test_delitem();
	test_search_item();

	
}