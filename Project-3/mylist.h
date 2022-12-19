/********************************************************************/
/*                                                                  */
/*  Put your linked list code from A1 into                          */
/*  this file                                                       */
/*                                                                  */
/********************************************************************/

template <typename T>

class CacheList {
private:
	struct Node {
		T data_;
		Node* next_;
		Node* prev_;
		unsigned int access_ = 0;
		Node() {
			data_;
			next_ = nullptr;
			prev_ = nullptr;
			access_ = 0;
		}
		Node(T data, Node* next, Node* prev, int access) {
			data_ = data;
			next_ = next;
			prev_ = prev;
			access_ = access;
		}
	};
	Node* head_ = nullptr;
	Node* tail_ = nullptr;



public:
	class const_iterator {
		friend class CacheList;
	protected:
		const CacheList* list_;
		Node* curr_;
		const_iterator(Node* curr, const CacheList* otherList) {
			curr_ = curr;
			list_ = otherList;
		}

	public:
		const_iterator() {
			list_ = new CacheList<T>();
			curr_ = nullptr;
		}
		const_iterator operator++() {
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator it = *this;
			curr_ = curr_->next_;
			return it;
		}
		const_iterator operator--() {
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				if (list_) {
					curr_ = list_->tail_;
				}
			}
			return *this;
		}
		const_iterator operator--(int) {
			const_iterator it = *this;
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				curr_ = list_->tail_;
			}
			return it;
		}
		bool operator==(const_iterator rhs) {
			return list_ == rhs.list_ && curr_ == rhs.curr_;
		}
		bool operator!=(const_iterator rhs) {
			return !(*this == rhs);
		}
		const T& operator*()const {
			return curr_->data_;
		}
	};
	class iterator :public const_iterator {
		friend class CacheList;
		iterator(Node* curr, CacheList* list) : const_iterator(curr, list) {};
	public:
		iterator() :const_iterator() {};
		iterator operator++() {
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int) {
			iterator it = *this;
			this->curr_ = this->curr_->next_;
			return it;
		}
		iterator operator--() {
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->list_) {
					this->curr_ = this->list_->tail_;
				}
			}
			return *this;
		}
		iterator operator--(int) {
			iterator it = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				this->curr_ = this->list_->tail_;
			}
			return it;
		}
		T& operator*() {
			return this->curr_->data_;
		}
		const T& operator*()const {
			return this->curr_->data_;
		}
	};
	CacheList();
	~CacheList();
	CacheList(const CacheList& rhs);
	CacheList& operator=(const CacheList& rhs);
	CacheList(CacheList&& rhs);
	CacheList& operator=(CacheList&& rhs);
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
	iterator insert(const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);

	bool empty() const;
	int size() const;
};

template <typename T>
CacheList<T>::CacheList() {
	head_ =  nullptr;
	tail_ = head_;
	
}
template <typename T>
CacheList<T>::~CacheList() {
	auto temp = head_;
	while (temp != nullptr) {
		auto next = temp->next_;
		delete temp;
		temp = next;
	}
}
//Copoy Constructor
template <typename T>
CacheList<T>::CacheList(const CacheList & rhs) {
	if (rhs.head_ != nullptr) {
		head_ = new Node();
		head_->data_ = rhs.head_->data_;
		head_->next_ = nullptr;
		head_->prev_ = nullptr;
		head_->access_ = 0;
		tail_ = head_;

		Node* current = rhs.head_->next_;
		while (current != nullptr) {
			tail_ = tail_->next_ = new Node(current->data_, nullptr, tail_, 0);
			current = current->next_;
		}
	}
}//Copy Assignment
template <typename T>
CacheList<T>& CacheList<T>::operator=(const CacheList & rhs) {
	//Empty current list
	auto temp = head_;
	while (temp != nullptr) {
		auto next = temp->next_;
		delete temp;
		temp = next;
	}
	//Copy rhs
	if (rhs.head_) {
		head_ = tail_ = new Node(rhs.head_->data_, nullptr, nullptr, 0);
		Node* current = rhs.head_->next_;
		while (current != nullptr) {
			tail_ = tail_->next_ = new Node(current->data_, nullptr, tail_, 0);
			current = current->next_;
		}
	}

	return *this;
}
template <typename T>
CacheList<T>::CacheList(CacheList && rhs) {
	head_ = rhs.head_;
	tail_ = rhs.tail_;
	rhs.head_ = nullptr;
	rhs.tail_ = nullptr;
}

template <typename T>
CacheList<T>& CacheList<T>::operator=(CacheList && rhs) {
	Node* tempHead = head_;
	Node* tempTail = tail_;
	head_ = rhs.head_;
	tail_ = rhs.tail_;

	rhs.head_ = tempHead;
	rhs.tail_ = tempTail;

	return *this;
}


template <typename T>
typename CacheList<T>::iterator CacheList<T>::begin() {
	return iterator(head_, this);
}
template <typename T>
typename CacheList<T>::iterator CacheList<T>::end() {
	return iterator(nullptr, this);
}

template <typename T>
typename CacheList<T>::const_iterator CacheList<T>::cbegin() const {
	return const_iterator(head_, this);
}
template <typename T>
typename CacheList<T>::const_iterator CacheList<T>::cend() const {
	return const_iterator(nullptr, this);
}

template <typename T>
typename CacheList<T>::iterator CacheList<T>::insert(const T & data) {
	// create a new node with data
	Node* newNode = new Node(data, nullptr, nullptr, 0);
	bool found = false;
	// determine where to insert the data
	iterator it = begin();
	// if the list is empty, insert the single item
	if (it == end())
	{
		head_ = tail_ = newNode;
	}
	else
	{	// look for position where access is 0
		while (it != end() && !found)
		{
			// when found, place at the left of that node
			if (it.curr_->access_ == 0)
			{
				// check if head
				if (it.curr_ == head_)
				{
					it.curr_->prev_ = newNode;
					newNode->next_ = it.curr_;
					head_ = newNode;
				}
				else
				{
					it.curr_->prev_->next_ = newNode;
					newNode->prev_ = it.curr_->prev_;
					newNode->next_ = it.curr_;
					it.curr_->prev_ = newNode;
				}
				found = true;
			}
			++it;
		}
		// if not found, place at the tail
		if (!found)
		{
			tail_->next_ = newNode;
			newNode->prev_ = tail_;
			tail_ = newNode;
		}
	}
	// return iterator pointed at the inserted node
	it.curr_ = newNode;
	return it;
}

template <typename T>
typename CacheList<T>::iterator CacheList<T>::search(const T & data) {
	Node* found = nullptr;
	bool didFind = false;

	iterator it = begin();
	while (it != end() && !didFind) {
		if (it.curr_->data_ == data) {
			it.curr_->access_++;
			found = it.curr_;
			didFind = true;
			if (found != tail_ && found != head_) {
				//unlink found node
				Node* prevOfFound = found->prev_;
				Node* nextOfFound = found->next_;

				found->next_ = nullptr;
				found->prev_ = nullptr;

				prevOfFound->next_ = nextOfFound;
				nextOfFound->prev_ = prevOfFound;
			}
			else if (found == head_)
			{
				break;
			}
			else if (found == tail_)
			{
				tail_ = found->prev_;
				found->prev_ = nullptr;
				tail_->next_ = nullptr;
			}
			break;
		}
		if (!didFind)
		{
			it++;
		}
	}
	//Find new spot for found node
	iterator it2 = begin();
	while (it2 != end() && didFind) {
		if (it2.curr_->access_ <= found->access_) {
			// if head, do nothing
			if (it2.curr_ == head_ && found != head_)
			{
				head_->prev_ = found;
				found->next_ = head_;
				found->prev_ = nullptr;
				head_ = found;
			}
			// if tail, link to the back
			if (it2.curr_ == tail_) {
				tail_->next_ = found;
				found->prev_ = tail_;
				found->next_ = nullptr;
				tail_ = found;
			}
			// if neither, link front and back
			else if (it2.curr_ != head_)
			{
				Node* position = it2.curr_;
				position->prev_->next_ = found;
				found->next_ = position;
				found->prev_ = position->prev_;
				position->prev_ = found;
			}
			break;
		}
		it2++;
	}
	return it;
}

template <typename T>
typename CacheList<T>::iterator CacheList<T>::erase(iterator it) {
	if (head_ == nullptr || it.curr_ == nullptr) return it;

	if (head_ == it.curr_) {
		head_ = it.curr_->next_;
	}

	if (it.curr_->next_ != nullptr) {
		it.curr_->next_->prev_ = it.curr_->prev_;
	}

	if (it.curr_->prev_ != nullptr) {
		it.curr_->prev_->next_ = it.curr_->next_;
	}
	//delete it.curr_;
	return it;
}


template <typename T>
bool CacheList<T>::empty() const {
	return size() == 0;
}
template <typename T>
int CacheList<T>::size() const {
	const_iterator it = cbegin();
	int size = 0;
	while (it != cend()) {
		size += 1;
		it++;
	}
	return size;
}