#pragma once
#include <iostream>

class SinglyLinkedOrderedList
{
	struct Node
	{
		int item_;
		Node* next_; 
		Node(int item, Node* next = nullptr) : item_(item), next_(next)
		{ }
	};

private:
	Node* head_;

public:
	SinglyLinkedOrderedList() : head_(nullptr){}
	SinglyLinkedOrderedList(const SinglyLinkedOrderedList& list);
	~SinglyLinkedOrderedList();

	bool add(int item);
	bool find(int item) const;
	bool remove(int item);
	bool is_empty() const;
	void clear();
	void union_list(SinglyLinkedOrderedList& list);
	void difference(const SinglyLinkedOrderedList& list);
	SinglyLinkedOrderedList intersect(const SinglyLinkedOrderedList& list);

	friend std::ostream& operator<<(std::ostream& out, const SinglyLinkedOrderedList& list);
};

