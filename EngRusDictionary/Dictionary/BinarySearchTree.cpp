#include "BinarySearchTree.h"

BinarySearchTree::~BinarySearchTree()
{
	delete_subtree(root_);
}

bool BinarySearchTree::insert(const std::string& key, std::string* words, int n)
{
	Node* x = root_;
	Node* y = nullptr;

	while (x != nullptr)
	{
		y = x;

		if (key.compare(x->key_) < 0)
			x = x->left_;
		else if (key.compare(x->key_) > 0)
			x = x->right_;
		else
			return false;
	}

	BinarySearchTree::ListItem* items = form_list(words, n);

	Node* p = new Node(key, items, n);
	if (y == nullptr)
		root_ = p;
	else if (key < y->key_) {
		y->left_ = p;
	}
	else {
		y->right_ = p;
	}

	return true;
}

bool BinarySearchTree::add(const std::string& key, const std::string& word)
{
	Node* x = find(key);
	if (x == nullptr) {
		insert(key, new std::string[]{ word }, 1);
	}
	else {
		bool success;
		x->words_ = add_word(x->words_, word, success);
		if (!success)
			return false;
		x->count_translate_++;
	}
	return true;
}

void BinarySearchTree::search(const std::string& key) const
{
	Node* x = find(key);

	if (x != nullptr) {
		BinarySearchTree::ListItem* p = x->words_;
		while (p != nullptr)
		{
			std::cout << p->data_;
			if (p->next_ != nullptr)
				std::cout << ", ";
			p = p->next_;
		}
	}
	else {
		std::cout << "Нет перевода для указанного слова";
	}
	std::cout << std::endl;
}

bool BinarySearchTree::delete_word(const std::string& key)
{
	Node* curr = root_;
	Node* prev = nullptr;

	while (curr != nullptr && curr->key_.compare(key) != 0) {
		prev = curr;
		if (key < curr->key_)
			curr = curr->left_;
		else
			curr = curr->right_;
	}

	if (curr == nullptr) {
		return false;
	}

	if (curr->left_ == NULL || curr->right_ == NULL) {

		Node* newCurr;

		if (curr->left_ == NULL)
			newCurr = curr->right_;
		else
			newCurr = curr->left_;

		if (prev == nullptr)
		{
			delete curr;
			root_ = newCurr;
			return true;
		}

		if (curr == prev->left_)
			prev->left_ = newCurr;
		else
			prev->right_ = newCurr;

		delete curr;
	}

	else {
		Node* p = NULL;
		Node* temp;

		temp = curr->right_;
		while (temp->left_ != NULL) {
			p = temp;
			temp = temp->left_;
		}

		if (p != nullptr)
			p->left_ = temp->right_;
		else
			curr->right_ = temp->right_;

		curr->key_ = temp->key_;
		delete temp;
	}
	return true;
}

void BinarySearchTree::save_file()
{
	std::ofstream file("words.txt");
	save_file(root_, file);
	file.close();
}

void BinarySearchTree::load_file()
{
	std::ifstream file("words.txt");
	if (file.is_open()) {
		while (!file.eof())
		{
			std::string key;
			if (!std::getline(file, key, ';'))
				break;
			std::string count;
			std::getline(file, count, ';');
			int n = stoi(count);
			std::string* words = new std::string[n];
			for (int i = 0; i < n; i++)
			{
				std::getline(file, words[i], ';');
			}
			file.get();

			insert(key, words, n);
		}
		file.close();
	}
}

BinarySearchTree::ListItem* BinarySearchTree::form_list(std::string* words, int& n)
{
	BinarySearchTree::ListItem* head = new BinarySearchTree::ListItem(words[0]);
	bool success;

	for (size_t i = 1; i < n; i++)
	{
		head = add_word(head, words[i], success);
		if (!success)
			n--;
	}

	return head;
}

void BinarySearchTree::delete_subtree(Node* node)
{
	if (node != nullptr) {
		delete_subtree(node->left_);
		delete_subtree(node->right_);
		delete node;
	}
}

void BinarySearchTree::save_file(Node* node, std::ofstream& file)
{
	if (node != nullptr) {
		save_file(node->left_, file);
		file << node->key_ << ";" << node->count_translate_ << ";";
		BinarySearchTree::ListItem* p = node->words_;
		while (p != nullptr)
		{
			file << p->data_ << ";";
			p = p->next_;
		}
		file << std::endl;
		save_file(node->right_, file);
	}
}

BinarySearchTree::Node* BinarySearchTree::find(const std::string& key) const
{
	Node* x = root_;

	while (x != nullptr && key.compare(x->key_) != 0)
	{
		if (key < x->key_)
			x = x->left_;
		else
			x = x->right_;
	}

	return x;
}

BinarySearchTree::ListItem* BinarySearchTree::add_word(ListItem* head, const std::string& word, bool& success)
{
	success = true;

	if (word.compare(head->data_) < 0) {
		head = new BinarySearchTree::ListItem(word, head);
	}
	else {
		BinarySearchTree::ListItem* p = head;
		BinarySearchTree::ListItem* pred = head;
		while (p != nullptr && p->data_.compare(word) < 0)
		{
			pred = p;
			p = p->next_;
		}
		if (p != nullptr && p->data_.compare(word) == 0)
		{
			success = false;
			return head;
		}

		pred->next_ = new BinarySearchTree::ListItem(word, pred->next_);
	}
	return head;
}

BinarySearchTree::Node::~Node()
{
	if (words_) {
		BinarySearchTree::ListItem* p = words_;
		BinarySearchTree::ListItem* t;
		while (p != nullptr)
		{
			t = p->next_;
			delete p;
			p = t;
		}
	}
}
