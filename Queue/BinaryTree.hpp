#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include <iostream>
#include <stack>
#include <vector>

template <class T>
class BinarySearchTree
{
public:
	template <class T>
	struct Node
	{
		T  key_;
		Node<T>* left_;
		Node<T>* right_;
		Node<T>* p_;

		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
			key_(key), left_(left), right_(right), p_(p)
		{  }
	};

	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& src);

	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree<T>& operator= (BinarySearchTree<T>&& src);

	virtual ~BinarySearchTree();

	bool operator== (const BinarySearchTree<T>& src);

	Node<T>* iterativeSearch(const T& key) const;
	Node<T>* recursiveSearch(Node<T>* x, const T& key) const;
	Node<T>* findMinimum(Node<T>* subtree) const;
	Node<T>* findMaximum(Node<T>* subtree) const;


	bool insert(const T& key);

	bool deleteKey(const T& key);

	void print(std::ostream& out) const;

	int getCount() const;

	Node<T>* getRoot() const;

	int getHeight() const;

	 
	void iterativeInorderWalk() const;

	
	void inorderWalk() const;  //  void (*visit)(T)

	
	void wideWalk() const;

	bool isEmpty();

private:
	Node<T>* root_;

	bool insertNode(Node<T>* key, Node<T>* start);

	void swap(BinarySearchTree <T>& left, BinarySearchTree <T>& right);

	void deleteSubtree(Node<T>* node);

	Node<T>* iterativeSearchNode(const T& key) const;
	Node<T>* recursiveSearchNode(Node<T>* x, const T& key) const;
	Node<T>* findMinimumNode(Node<T>* subtree) const;
	Node<T>* findMaximumNode(Node<T>* subtree) const;

	void printNode(std::ostream& out, Node<T>* root) const;

	int getCountSubTree(const Node<T>* node) const;

	int getHeightSubTree(Node<T>* node) const;

	void inorderWalk(Node<T>* node) const;  
	void iterativeInorderWalk(Node<T>* node) const;
	void wideWalk(Node<T>* node) const;

};


template <class T>
bool BinarySearchTree<T>::isEmpty()
{
	if (this->root_ == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src)
{
	root_ = src.root_;
	src.root_ = nullptr;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	deleteSubtree(root_);
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator= (BinarySearchTree <T>&& src)
{
	deleteSubtree(root_);
	root_ = src.root_;
	src.root_ = nullptr;
}

template <class T>
bool BinarySearchTree<T>::operator== (const BinarySearchTree <T>& src)
{
	std::vector<T> vL;
	std::vector<T> vR;

	Node<T>* nodeL = root_;
	Node<T>* nodeR = src.root_;

	std::stack<Node<T>*> nodeStackL;
	std::stack<Node<T>*> nodeStackR;

	
	while ((nodeStackL.size() != 0) || (nodeL != nullptr))
	{
		if (nodeL != nullptr)
		{
			nodeStackL.push(nodeL);
			nodeL = nodeL->left_;
		}
		else
		{
			nodeL = nodeStackL.top();
			nodeStackL.pop();
			vL.push_back(nodeL->key_);
			nodeL = nodeL->right_;
		}
	}
	while ((nodeStackR.size() != 0) || (nodeR != nullptr))
	{
		if (nodeR != nullptr)
		{
			nodeStackR.push(nodeR);
			nodeR = nodeR->left_;
		}
		else
		{
			nodeR = nodeStackR.top();
			nodeStackR.pop();
			vR.push_back(nodeR->key_);
			nodeR = nodeR->right_;
		}
	}

	
	return vL == vR;
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
	return (1 + getCountSubTree(node->left_) +
		getCountSubTree(node->right_));
}

template <class T>
bool BinarySearchTree<T>::insert(const T & key)
{
	Node<T>* leaf = new Node<T>(key, nullptr, nullptr, nullptr);
	if (insertNode(leaf, getRoot()))
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

template <class T>
bool BinarySearchTree<T>::insertNode(Node<T> * key, Node<T> * start)
{
	if (isEmpty())
	{
		this->root_ = key;
		
	}
	else
	{
		if (start == nullptr)
		{
			start = key;
			
			return true;
		}
		else
		{
			if (key->key_ < start->key_)
			{
				if (start->left_ == nullptr)
				{
					start->left_ = key;
					(start->left_)->p_ = start;
					
					return true;
				}
				else
				{
					insertNode(key, start->left_);
				}
			}
			else
			{
				if (start->right_ == nullptr)
				{
					start->right_ = key;
					(start->right_)->p_ = start;
					
					return true;
				}
				else
				{
					insertNode(key, start->right_);
				}
			}
		}

	}
	return false;
}

template <class T>
int BinarySearchTree<T>::getHeight() const
{
	return getHeightSubTree(this->root_) - 1;
}

template <class T>
int BinarySearchTree<T>::getHeightSubTree(Node<T> * node) const
{
	if (node == nullptr)
	{
		return 0;
	}

	return (getHeightSubTree(node->right_) < getHeightSubTree(node->left_)) ? 1 + getHeightSubTree(node->left_) : 1 + getHeightSubTree(node->right_);
	
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::getRoot() const
{
	return (this->root_);
}

template <class T>
void BinarySearchTree<T>::swap(BinarySearchTree <T> & left, BinarySearchTree <T> & right)
{
	std::swap(left.root_, right.root_);
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearch(const T & key)  const
{
	return (iterativeSearchNode(key));
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::recursiveSearch(Node<T> * x, const T & key)  const
{
	return (recursiveSearchNode(x, key));
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::findMinimum(Node<T> * subtree)  const
{
	return (findMinimumNode(subtree));
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::findMaximum(Node<T> * subtree)  const
{
	return (findMaximumNode(subtree));
}

template <class T>
void BinarySearchTree<T>::inorderWalk() const  
{
	return inorderWalk(this->root_);  
}

template <class T>
void BinarySearchTree<T>::iterativeInorderWalk() const
{
	iterativeInorderWalk(this->root_);
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T & key) const
{
	Node<T>* current = this->root_;
	do
	{
		if (key < current->key_)
		{
			current = current->left_;
		}
		else
		{
			current = current->right_;
		}
	} while (current != nullptr && current->key_ != key);

	return current;
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::recursiveSearchNode(Node<T> * x, const T & key) const
{
	Node<T>* current = x;

	if ((current == nullptr) || (key == current->key_))
	{
		return current;
	}
	if (key < current->key_)
	{
		return recursiveSearchNode(current->left_, key);
	}
	else
	{
		return recursiveSearchNode(current->right_, key);
	}

	return current;
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::findMinimumNode(Node<T> * subtree) const
{
	Node<T>* current = subtree;

	do
	{
		current = current->left_;
	} while (current->left_ != nullptr);

	return current;
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::findMaximumNode(Node<T> * subtree) const
{
	Node<T>* current = subtree;

	do
	{
		current = current->right_;
	} while (current->right_ != nullptr);

	return current;
}

template <class T>
void BinarySearchTree<T>::deleteSubtree(Node<T> * node)
{
	if (node == nullptr)
	{
		//std::cout << "������\\���� ��� ���������� ��� �����\n";
	}
	else
	{
		if (node->right_ == nullptr)
		{
			//std::cout << "������ ����� �����";
		}
		else
		{
			//std::cout << "������ ������ �����";
			deleteSubtree(node->right_);
		}
		delete node->right_;
		node->right_ = nullptr;

		if (node->left_ == nullptr)
		{
			//std::cout << "����� ����� �����";
		}
		else
		{
			//std::cout << "������ ����� �����";
			deleteSubtree(node->left_);
		}
		delete node->left_;
		node->left_ = nullptr;

		if (node->p_ == nullptr) // node - ������
		{
			root_ = nullptr;
			delete node;
		}
	}

}

template <class T>
void BinarySearchTree<T>::print(std::ostream& out) const
{
	printNode(out, root_);
	out << std::endl;
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

template <class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	Node<T>* current = this->iterativeSearch(key);
	if (current == nullptr)
	{
		// ������/���� ��� �������� ��� �����
		return false;
	}

	if ((current->left_ == nullptr) && (current->right_ == nullptr))  
	{
		if (current->p_ == nullptr) 
		{
			root_ = nullptr;
			delete current;
			return true;
		}
		else
		{
			if ((current->p_->left_ != nullptr) && (current->p_->left_->key_ == current->key_)) 
			{
				current->p_->left_ = nullptr;
				delete current;
				return true;
			}
			if ((current->p_->right_ != nullptr) && (current->p_->right_->key_ == current->key_)) 
			{
				current->p_->right_ = nullptr;
				delete current;
				return true;
			}
		}
	}
	else if ((current->left_ != nullptr) && (current->right_ == nullptr))  
	{
		if (current->p_ == nullptr) 
		{
			current->left_->p_ = nullptr;
			root_ = current->left_;
			delete current;
			return true;
		}
		else
		{
			if ((current->p_->left_ != nullptr) && (current->p_->left_->key_ == current->key_)) 
			{
				current->left_->p_ = current->p_;
				current->p_->left_ = current->left_;
				delete current;
				return true;
			}
			if ((current->p_->right_ != nullptr) && (current->p_->right_->key_ == current->key_)) 
			{
				current->left_->p_ = current->p_;
				current->p_->right_ = current->left_;
				delete current;
				return true;
			}
		}
	}
	else if ((current->left_ == nullptr) && (current->right_ != nullptr))  
	{
		if (current->p_ == nullptr) 
		{
			current->right_->p_ = nullptr;
			root_ = current->right_;
			delete current;
			return true;
		}
		else
		{
			if ((current->p_->left_ != nullptr) && (current->p_->left_->key_ == current->key_)) 
			{
				current->right_->p_ = current->p_;
				current->p_->left_ = current->right_;
				delete current;
				return true;
			}
			if ((current->p_->right_ != nullptr) && (current->p_->right_->key_ == current->key_)) 
			{
				current->right_->p_ = current->p_;
				current->p_->right_ = current->right_;
				delete current;
				return true;
			}
		}
	}
	else if ((current->left_ != nullptr) && (current->right_ != nullptr))  
	{
		Node<T>* x = current->right_; 
		while (x->left_ != nullptr)
		{
			x = x->left_;
		}

		
		x->p_->left_ = x->right_;
		if (x->right_ != nullptr)
		{
			x->right_->p_ = x->p_;
		}

		current->key_ = x->key_;
		delete x;
		return true;
	}

	return false;
}

template <class T>
void BinarySearchTree<T>::inorderWalk(Node<T> * node) const //, void(*visit)(T)
{
	if (node != nullptr)
	{
		inorderWalk(node->left_);
		//(*visit)(node->key_); - ����� ����� ���� ����������� ������������� �������
		std::cout << node->key_ << " "; 
		inorderWalk(node->right_);
	}
}

template <class T>
void BinarySearchTree<T>::iterativeInorderWalk(Node<T> * node) const
{
	std::stack<Node<T>*> vault;
	while ((vault.size() != 0) || (node != nullptr))
	{
		if (node != nullptr)
		{
			vault.push(node);
			node = node->left_;
		}
		else
		{
			node = vault.top();
			vault.pop();
			std::cout << node->key_;
			std::cout << " ";
			node = node->right_;
		}
	}
}

template <class T>
void BinarySearchTree<T>::wideWalk() const
{
	return wideWalk(this->root_);
}

template <class T>
void BinarySearchTree<T>::wideWalk(Node<T>* node) const
{
	if (node != nullptr)
	{
		Node<T>* head = nullptr; 
		QueueArray<Node<T>*> treeIntoQueue(this->getCount() + 1);
		treeIntoQueue.enQueue(getRoot());

		while (!treeIntoQueue.isEmpty())
		{
			head = treeIntoQueue.deQueue();
			std::cout << head->key_;  
			std::cout << " ";
			if (head->left_ != nullptr)
			{
				treeIntoQueue.enQueue(head->left_);
			}
			if (head->right_ != nullptr)
			{
				treeIntoQueue.enQueue(head->right_);
			}
		}
	}

	std::cout << "\n";
}

#endif
