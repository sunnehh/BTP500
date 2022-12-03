#ifndef LAB7_H
#define LAB7_H

#include <iostream>
#include <iomanip>

/*forward declaration*/
template <class T>
class Queue;

template <class T>
class BST {
	struct Node {
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data, Node* lt = nullptr, Node* rt = nullptr) {
			data_ = data;
			left_ = lt;
			right_ = rt;
		}
	};
	Node* root_;

	void printPreOrder(Node* subroot)const {
		if (subroot) {
			std::cout << subroot->data_ << " ";
			printPreOrder(subroot->left_);
			printPreOrder(subroot->right_);
		}
	}
	void printInOrder(Node* subroot)const {
		if (subroot) {
			printInOrder(subroot->left_);
			std::cout << subroot->data_ << " ";
			printInOrder(subroot->right_);
		}
	}
	void destroy(Node* subroot) {
		if (subroot) {
			destroy(subroot->left_);
			destroy(subroot->right_);
			delete subroot;
		}
	}

	bool isSame(const Node* left, const Node* right) const;

	/*used by print() to print all nodes at same level*/
	void printLine(Node* data[], int numNodes, int width) const {
		int half = width / 2;
		int firsthalf = width % 2 ? half + 1 : half;

		if (numNodes > 1) {
			for (int i = 0;i < numNodes;i++) {
				if (i % 2 == 0) {
					if (data[i]) {
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << "-";
						std::cout << std::left << std::setfill('-') << std::setw(half) << "-";
					}
					else {
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
					}
				}
				else {
					if (data[i]) {
						std::cout << std::right << std::setfill('-') << std::setw(firsthalf) << "-";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << "-";
					}
					else {
						std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
						std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
					}
				}
			}
			std::cout << std::endl;
		}
		for (int i = 0;i < numNodes;i++) {
			if (data[i]) {
				if (i % 2 == 0) {
					std::cout << std::right << std::setw(firsthalf) << "|";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
				}
				else {
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << "|";
				}
			}
			else {
				std::cout << std::left << std::setfill(' ') << std::setw(width) << " ";
			}
		}
		std::cout << std::endl;
		for (int i = 0;i < numNodes;i++) {
			if (data[i]) {
				if (i % 2 == 0) {
					std::cout << std::right << std::setw(firsthalf) << data[i]->data_;
					std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
				}
				else {
					std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
					std::cout << std::left << std::setfill(' ') << std::setw(half) << data[i]->data_;
				}
			}
			else {
				std::cout << std::left << std::setfill(' ') << std::setw(width) << " ";
			}
		}
		std::cout << std::endl;

	}


public:
	BST() {
		root_ = nullptr;
	}
	Node* getroot() {
		return root_;
	}

	/* Lab 7: Implement these 3 functions. */

	// return the parent of the node containing data
	Node* searchParent(const T& data) {
		Node* current = root_;
		Node* current_parent = current;
		bool found = false;
		while (current != nullptr && !found) {
			if (current->data_ == data)
			{
				found = true;
			}
			else if (current->data_ > data)
			{
				current_parent = current;
				current = current->left_;
			}
			else
			{
				current_parent = current;
				current = current->right_;
			}
		}
		if (found)
		{
			return current_parent;
		}
		else
		{
			return nullptr;
		}
	}

	Node* getSuccessorParent(Node* node) {
		Node* current = node;
		Node* current_parent = node;
		if (current->right_ != nullptr)
		{
			current = current->right_;
			current_parent = current;
			while (current->left_ != nullptr)
			{
				current = current->left_;
			}
			while (current_parent->left_ != nullptr && current_parent->left_ != current)
			{
				current_parent = current_parent->left_;
			}
		}
		else
		{
			return nullptr;
		}
		return current_parent;
	}

	BST(const BST& rhs) {
		if (rhs.root_ == nullptr)
		{
			this->root_ = nullptr;
		}
		else
		{
			this->root_ = cloneSubtree(rhs.root_);
		}
	}

	Node* cloneSubtree(Node* current) {
		if (current == nullptr)
		{
			return nullptr;
		}
		else
		{
			Node* clonedNode = new Node(current->data_);
			clonedNode->right_ = cloneSubtree(current->right_);
			clonedNode->left_ = cloneSubtree(current->left_);
			return clonedNode;
		}
	}

	void remove(const T& data) {
		// get the parent of the node to unlink
		Node* parentofNode = searchParent(data);
		Node* dataNode = nullptr;
		bool isleft = false;
		bool isroot = false;
		if (parentofNode != nullptr)
		{
			if (parentofNode == root_ && root_->data_ == data)
			{
				// we are trying to remove the root
				isroot = true;
				dataNode = parentofNode;
			}
			else if (parentofNode->right_->data_ == data)
			{
				dataNode = parentofNode->right_;
				isleft = false;
			}
			else if (parentofNode->left_->data_ == data)
			{
				dataNode = parentofNode->left_;
				isleft = true;
			}
			// case 1: data is a leaf
			if (dataNode->right_ == nullptr && dataNode->left_ == nullptr)
			{
				if (isleft) {
					parentofNode->left_ = nullptr;
					delete dataNode;
				}
				else
				{
					parentofNode->right_ = nullptr;
					delete dataNode;
				}
				if (isroot)
				{
					root_ = nullptr;
				}
			}
			// case 2: data has a right child but no left
			else if (dataNode->right_ != nullptr && dataNode->left_ == nullptr)
			{
				if (isleft) {
					parentofNode->left_ = dataNode->right_;
				}
				else
				{
					parentofNode->right_ = dataNode->right_;
				}
				//dataNode->right_->left_ = dataNode->left_;
				if (isroot)
				{
					root_ = dataNode->right_;
				}
				delete dataNode;
			}
			// case 3: data has a left child but no right
			else if (dataNode->right_ == nullptr && dataNode->left_ != nullptr)
			{
				if (isleft) {
					parentofNode->left_ = dataNode->left_;
				}
				else
				{
					parentofNode->right_ = dataNode->left_;
				}
				//dataNode->left_->right_ = dataNode->right_;
				if (isroot)
				{
					root_ = dataNode->right_;
				}
				delete dataNode;
			}
			// case 4: data has both left and right children
			else
			{
				Node* successorparent = getSuccessorParent(dataNode);
				Node* successor = nullptr;
				if (successorparent->left_ == nullptr)
				{
					successor = successorparent;
				}
				else
				{
					successor = successorparent->left_;
				}
				// unlink the successor
				successorparent->left_ = successor->right_;
				// successor takes datanodes position
				successor->left_ = dataNode->left_;
				if (successor != dataNode->right_)
				{
					successor->right_ = dataNode->right_;
					
				}
				if (isleft) {
					parentofNode->left_ = successor;

				}
				else
				{
					parentofNode->right_ = successor;
				}
				if (isroot)
				{
					root_ = successor;
				}
				// delete datanode
				delete dataNode;
			}
		}
	}



	int depth(const T& data) {
		int count = 0;

		Node* current = root_;
		bool found = false;
		while (current != nullptr && !found) {
			count++;
			if (current->data_ == data)
			{
				count--;
				found = true;
			}
			else if (current->data_ > data)
			{
				current = current->left_;
			}
			else
			{
				current = current->right_;
			}
		}
		if (!found)
		{
			count = -1;
		}

		return count;
	}


	void printPreOrder() const {
		printPreOrder(root_);
		std::cout << std::endl;
	}
	void printInOrder() const {
		printInOrder(root_);
		std::cout << std::endl;
	}


	void insert(const T& data) {
		if (root_ == nullptr) {
			root_ = new Node(data);
		}
		else {

			Node* curr = root_;
			while (curr != nullptr) {
				if (data < curr->data_) {
					//go left
					if (curr->left_) {
						curr = curr->left_;
					}
					else {
						curr->left_ = new Node(data);
						curr = nullptr;
					}
				}
				else {
					//go right
					if (curr->right_) {
						curr = curr->right_;
					}
					else {
						curr->right_ = new Node(data);
						curr = nullptr;
					}
				}
			}

		}

	}

	bool operator==(const BST& rhs) const;
	void print() const {
		struct Output {
			Node* node_;
			int lvl_;
			int position_;
			Output(Node* n = nullptr, int l = 0, int p = 0) {
				node_ = n;
				lvl_ = l;
				position_ = p;
			}
			void set(Node* n = nullptr, int l = 0, int p = 0) {
				node_ = n;
				lvl_ = l;
				position_ = p;
			}
		};
		Queue<Output> theNodes;
		Node* line[16];
		if (root_) {
			for (int i = 0;i < 16;i++) {
				line[i] = nullptr;
			}
			theNodes.enqueue(Output(root_, 0, 0));
			int currline = 0;
			int width = 80;
			int numInLine = 1;
			while (theNodes.isEmpty() == false) {
				Output curr = theNodes.front();
				if (curr.node_->left_)
					theNodes.enqueue(Output(curr.node_->left_, curr.lvl_ + 1, curr.position_ * 2));
				if (curr.node_->right_)
					theNodes.enqueue(Output(curr.node_->right_, curr.lvl_ + 1, curr.position_ * 2 + 1));
				theNodes.dequeue();


				if (curr.lvl_ > currline) {
					printLine(line, numInLine, width);
					width = width / 2;
					numInLine = numInLine * 2;
					for (int i = 0;i < 16;i++) {
						line[i] = nullptr;
					}
					currline++;

				}
				line[curr.position_] = curr.node_;
			}
			printLine(line, numInLine, width);
			std::cout << std::endl;

		}
		else {
			std::cout << "tree is empty" << std::endl;
		}
	}
	~BST() {
		destroy(root_);
	}
};

template <class T>
class Queue {
	T* theQueue_;
	int capacity_;
	int used_;
	int front_;
	int back_;
	void grow() {
		T* tmp = new T[capacity_ * 2];
		int j;
		for (int i = 0, j = front_;i < used_;i++, j = (j + 1) % capacity_) {
			tmp[i] = theQueue_[j];
		}
		delete[] theQueue_;
		theQueue_ = tmp;
		capacity_ = capacity_ * 2;
		front_ = 0;
		back_ = used_;
	}
public:
	Queue() {
		theQueue_ = new T[50];
		capacity_ = 50;
		used_ = 0;
		front_ = 0;
		back_ = 0;
	}
	void enqueue(const T& data) {
		if (used_ == capacity_) {
			grow();
		}
		theQueue_[back_] = data;
		back_ = (back_ + 1) % capacity_;
		used_++;
	}
	void dequeue() {
		if (!isEmpty()) {
			used_--;
			front_ = (front_ + 1) % capacity_;
		}
	}
	T front() const {
		if (!isEmpty()) {
			return theQueue_[front_];
		}
		return T{};

	}
	bool isEmpty() const {
		return used_ == 0;
	}
	~Queue() {
		delete[] theQueue_;
	}
};


#endif // !LAB7_H


