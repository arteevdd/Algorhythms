#pragma once
#include <iostream>
#include <string>
#include <fstream>

class BinarySearchTree
{
public:
	BinarySearchTree() : root_(nullptr){}
	~BinarySearchTree();

	bool insert(const std::string& key, std::string* words, int n);
	bool add(const std::string& key, const std::string& word);
	void search(const std::string& key) const;
	bool delete_word(const std::string& key);
	void save_file();
	void load_file();

private:
	struct ListItem
	{
		std::string data_;
		ListItem* next_;

		ListItem(std::string data, ListItem* next = nullptr) : data_(data), next_(next){}
	};

	struct Node {
		std::string key_;
		ListItem*  words_;        
		int count_translate_;
		Node* left_;     
		Node* right_;    

		Node(std::string key, ListItem* words, int count_translate, Node* left = nullptr, Node* right = nullptr) :
			key_(key), words_(words), count_translate_(count_translate), left_(left), right_(right)
		{  }

		~Node();
	};

	Node* root_;

	ListItem* form_list(std::string* words, int& n);
	void delete_subtree(Node* node);
	void save_file(Node* node, std::ofstream& file);
	Node* find(const std::string& key) const;
	ListItem* add_word(ListItem* head, const std::string& word, bool& success);
};

