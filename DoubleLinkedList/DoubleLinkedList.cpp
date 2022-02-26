#include "DoubleLinkedList.h"
#include <iostream>


void DoubleLinkedList::insertTail(Node* x) 
{
	if (head_ == nullptr)
		head_ = x;
	else {
		tail_->next_ = x;
		x->prev_ = tail_;
	}

	tail_ = x;
	count_++;
}


void DoubleLinkedList::insertHead(Node* x)  
{   
	x->next_ = head_;
	if (head_ != nullptr) {
		
		head_->prev_ = x;
	}
	else {
		
		tail_ = x;
	}
	head_ = x;
	count_++;  
}


void DoubleLinkedList::deleteNode(Node* x)
{
	if (x == nullptr) {
		throw ("DoubleLinkedList::deleteNode  - ������� ����� ����� ���������� ����");
	}
	if (x->prev_ != nullptr) {
		
		(x->prev_)->next_ = x->next_;
	}
	else {
		
		head_ = x->next_;
	}
	if (x->next_ != nullptr) {
		
		(x->next_)->prev_ = x->prev_;
	}
	else {
		
		tail_ = x->prev_;
	}
	delete x;       
	count_--;    

DoubleLinkedList::Node* DoubleLinkedList::searchNode(int item)
{
	Node* x = head_;
	while (x != nullptr && x->item_ != item) {
		x = x->next_;
	}
	return x;
}


DoubleLinkedList::Node* DoubleLinkedList::replaceNode(DoubleLinkedList::Node* x, int item)
{
	x->item_ = item;

	return x; 
}



DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& src)
{
	insertTailList(src);
}

DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& src) noexcept
{
	count_ = src.count_;
	head_ = src.head_;
	tail_ = src.tail_;

	src.count_ = 0;
	src.head_ = nullptr;
	src.tail_ = nullptr;
}

DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& src)
{
	if (this != &src)
	{
		DoubleLinkedList tmp(src);
		this->swap(tmp);
	}
	return *this;
}

DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& src)
{
	swap(src);
	return *this;
}

void DoubleLinkedList::swap(DoubleLinkedList& list) noexcept
{
	std::swap(list.count_, count_);
	std::swap(list.head_, head_);
	std::swap(list.tail_, tail_);
}


int DoubleLinkedList::headItem() const
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - ������ ����!");
}

int& DoubleLinkedList::headItem()
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - ������ ����!");
}


int DoubleLinkedList::tailItem() const
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - ������ ����!");
}
int& DoubleLinkedList::tailItem()
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - ������ ����!");
}


void DoubleLinkedList::insertHead(int item)
{   
	insertHead(new Node(item));
}


void DoubleLinkedList::insertTail(int item)
{   
	insertTail(new Node(item));
}


bool DoubleLinkedList::deleteHead()
{
	if (head_ == nullptr) {
		return 0;  
	}
	deleteNode(head_);
	return 1;      
}


bool DoubleLinkedList::deleteTail()
{
	if (head_ == nullptr) {
		return 0;
	}
	deleteNode(tail_);
	return 1; 
}


bool DoubleLinkedList::deleteItem(const int item, bool all)
{
	Node* x = head_;
	bool find = false;
	while (x != nullptr) {
		if (x->item_ == item)
		{
			Node* p = x->next_;
			deleteNode(x);
			x = p;
			find = true;
			if (!all)
				break;
		}
		else
			x = x->next_;
	}

	return find; 
}


bool DoubleLinkedList::searchItem(int item)
{   
	return (searchNode(item) != nullptr);
}



bool DoubleLinkedList::replaceItem(int itemOld, int itemNew, bool all)
{
	Node* x = head_;
	bool find = false;
	while (x != nullptr)
	{
		if (x->item_ == itemOld) {
			replaceNode(x, itemNew);
			find = true;
			if (!all)
				break;
		}
		x = x->next_;
	}

	return find;
}


void DoubleLinkedList::outAll()
{
	Node* current = head_;       
	while (current != nullptr) {
		std::cout << current->item_ << ' ';
		current = current->next_;  
	}
	std::cout << std::endl;
}


DoubleLinkedList::~DoubleLinkedList()
{
	Node* current = nullptr;   
	Node* next = head_;        
	while (next != nullptr) {  
		current = next;
		next = next->next_;    
		delete current;        
	}
}

bool DoubleLinkedList::operator==(const DoubleLinkedList& list)
{
	if (count_ != list.count_)
		return false;

	Node* t1 = head_;
	Node* t2 = list.head_;

	while (t1 != nullptr)
	{
		if (t1->item_ != t2->item_)
			return false;

		t1 = t1->next_;
		t2 = t2->next_;
	}

	return true;
}

void DoubleLinkedList::insertTailList(const DoubleLinkedList& list)
{
	Node* current = list.head_;
	while (current != nullptr)
	{
		insertTail(current->item_);

		current = current->next_;
	}
}

std::ostream& operator<<(std::ostream& out, const DoubleLinkedList& list)
{
	DoubleLinkedList::Node* current = list.head_;
	while (current != nullptr) {
		out << current->item_ << ' ';
		current = current->next_;
	}
	out << std::endl;

	return out;
}