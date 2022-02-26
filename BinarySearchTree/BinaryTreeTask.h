#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include <iostream>
#include <stack>

template <class T>
class BinarySearchTree
{
public:

	
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& scr);

	
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src);

	
	virtual ~BinarySearchTree();

	
	bool iterativeSearch(const T& key) const;

	
	bool insert(const T& key);

	
	bool deleteKey(const T& key);

	
	void print(std::ostream& out) const;

	void show(std::ostream& out) const;

	
	int getCount() const;

	
	int getHeight() const;


	void iterativeInorderWalk() const;

	
	void inorderWalk() const;

	
	bool operator== (const BinarySearchTree <T>& src);

private:

	
	template <class T>
	struct Node {
		T  key_;         
		Node<T>* left_;     
		Node<T>* right_;    
		Node<T>* p_;        

		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
			key_(key), left_(left), right_(right), p_(p)
		{  }
	};

	
	Node<T>* root_;

	void swap(BinarySearchTree <T>& left, BinarySearchTree <T>& right);

	
	void deleteSubtree(Node<T>* node);

	
	Node<T>* iterativeSearchNode(const T& key) const;

	
	void printNode(std::ostream& out, Node<T>* root) const;

	void show(std::ostream& out, Node<T>* root, int level) const;

	
	int getCountSubTree(const Node<T>* node) const;

	
	int getHeightSubTree(Node<T>* node) const;

	
	void inorderWalk(Node<T>* node) const;

}; 


template <class T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr)
{}



template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator= (BinarySearchTree <T>&& src)
{
	return *this;
}


template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	deleteSubtree(root_);
}


template <class T>
void BinarySearchTree<T>::deleteSubtree(Node<T>* node)
{
	if (node != nullptr) {
		deleteSubtree(node->left_);
		deleteSubtree(node->right_);
		delete node;
	}
}

template <class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key)  const
{
	return (iterativeSearchNode(key) != nullptr);
}


template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	Node<T>* x = root_;

	while (x != nullptr && key != x->key_)
	{
		if (key < x->key_)
			x = x->left_;
		else
			x = x->right_;
	}
	
	
	return x; 
}


template <class T>
bool BinarySearchTree<T>::insert(const T& key)
{
	Node<T>* x = root_;
	Node<T>* y = nullptr;

	while (x != nullptr)
	{
		y = x;

		if (key < x->key_)
			x = x->left_;
		else if (key > x->key_)
			x = x->right_;
		else
			return false;
	}

	Node<T>* p = new Node<T>(key);
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


template <class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	Node<T>* curr = root_;
	Node<T>* prev = nullptr;

	while (curr != nullptr && curr->key_ != key) {
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

		
		Node<T>* newCurr;

		
		if (curr->left_ == NULL)
			newCurr = curr->right_;
		else
			newCurr = curr->left_;

		
		if (prev == nullptr)
			return newCurr;

	
		if (curr == prev->left_)
			prev->left_ = newCurr;
		else
			prev->right_ = newCurr;

		
		delete curr;
	}

	
	else {
		Node<T>* p = NULL;
		Node<T>* temp;

		
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


template <class T>
void BinarySearchTree<T>::print(std::ostream& out) const
{
	printNode(out, root_);
	out << std::endl;
}

template<class T>
void BinarySearchTree<T>::show(std::ostream& out) const
{
	show(out, root_, 0);
}


template <class T>
void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const
{
	
	out << '(';
	if (root != nullptr) {
		
		out << root->key_;
		printNode(out, root->left_);
		printNode(out, root->right_);
	}
	out << ')';
}

template<class T>
void BinarySearchTree<T>::show(std::ostream& out, Node<T>* root, int level) const
{
	if (root != nullptr) {
		show(out, root->right_, level + 1);
		for (int i = 0; i < level; i++)
		{
			out << "    ";
		}
		out << root->key_ << std::endl;
		show(out, root->left_, level + 1);
	}
}


template <class T>
int BinarySearchTree<T>::getCount() const
{
	return getCountSubTree(this->root_);
}


template <class T>
int BinarySearchTree<T>::getCountSubTree(const Node<T>* node) const
{
	if (node == nullptr)
		return 0;
	return (1 + getCountSubTree(node->left_) + getCountSubTree(node->right_));
}


template <class T>
int BinarySearchTree<T>::getHeight() const
{
	return getHeightSubTree(this->root_);
}


template <class T>
int BinarySearchTree<T>::getHeightSubTree(Node<T>* node) const
{
	if (node != nullptr) {
		int l = getHeightSubTree(node->left_);
		int r = getHeightSubTree(node->right_);

		if (l > r)
			return l + 1;
		else
			return r + 1;
	}
	return 0; 
}


template <class T>
void BinarySearchTree<T>::iterativeInorderWalk() const
{
	std::stack<Node<T>*> s;
	Node<T>* curr = root_;

	while (curr != NULL || s.empty() == false)
	{
		while (curr != NULL)
		{
			s.push(curr);
			curr = curr->left_;
		}

		curr = s.top();
		s.pop();

		std::cout << curr->key_ << " ";

		curr = curr->right_;
	}
}


template <class T>
void BinarySearchTree<T>::inorderWalk(Node<T>* node) const
{
	if (node != nullptr) {
		inorderWalk(node->left_);
		std::cout << node->key_ << " ";
		inorderWalk(node->right_);
	}
}


template <class T>
bool BinarySearchTree<T>::operator== (const BinarySearchTree <T>& src)
{
	if (getCountSubTree() != src.getCountSubTree())
		return false;

	std::stack<Node<T>*> s;
	Node<T>* curr = root_;

	while (curr != NULL || s.empty() == false)
	{
		while (curr != NULL)
		{
			s.push(curr);
			curr = curr->left_;
		}

		curr = s.top();
		s.pop();

		if (!src.iterativeSearch(curr->key_))
			return false;

		curr = curr->right_;
	}
	return true;
}

#endif