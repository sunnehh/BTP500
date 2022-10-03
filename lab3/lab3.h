#include <iostream>
#include <typeinfo>

template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* _head;
	Node* _tail;
public:
	DList(){
		_head=nullptr;
		_tail=nullptr;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	int getData(int data[]) const;
	int getReverseData(int data[]) const;
	~DList();
};


template <typename T>
void DList<T>::push_front(const T& data) {
	Node* newNode = new Node(data);
	// check for empty list
	if (this->_head == nullptr)
	{
		// if empty, head is data, back is data - prev and next are nullptr
		this->_head = newNode;
		this->_tail = newNode;
	}
	else
	{
		// not empty, currenthead.prev = newnode, newnode.next = currenthead, head = newnode;
		this->_head->prev_ = newNode;
		newNode->next_ = _head;
		_head = newNode;
	}
}

template <typename T>
void DList<T>::push_back(const T& data){
	Node* newNode = new Node(data);
	// check for empty list
	if (this->_head == nullptr)
	{
		// if empty, head is data, back is data - prev and next are nullptr
		this->_head = newNode;
		this->_tail = newNode;
	}
	else
	{
		this->_tail->next_ = newNode;
		newNode->prev_ = _tail;
		_tail = newNode;
	}
}

template <typename T>
void DList<T>::pop_front(){
	if (_head != nullptr)
	{
		_head = _head->next_;
		if (_head != nullptr)
		{
			_head->prev_ = nullptr;
		}
		else
		{
			_tail = nullptr;
		}
	}
}

template <typename T>
void DList<T>::pop_back(){
	if (_tail != nullptr)
	{
		_tail = _tail->prev_;
		if (_tail != nullptr)
		{
			_tail->next_ = nullptr;
		}
		else
		{
			_head = nullptr;
		}
	}
}
template <typename T>
int DList<T>::getData(int data[]) const{
	Node* curr=_head;
	int numData=0;
	while(curr!=nullptr){
		data[numData++]=curr->data_;
		curr=curr->next_;
	}
	return numData;
}
template <typename T>
int DList<T>::getReverseData(int data[]) const{
	Node* curr = _tail;
	int numData=0;
	while(curr!=nullptr){
		data[numData++]=curr->data_;
		curr=curr->prev_;
	}
	return numData;
}
template <typename T>
DList<T>::~DList(){
}

template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* _head;
	Node* _tail;
public:
	Sentinel(){
		_head=new Node();
		_tail=new Node();
		_head->next_=_tail;
		_tail->prev_=_head;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	int getData(int data[]) const;
	int getReverseData(int data[]) const;
	~Sentinel();
};


template <typename T>
void Sentinel<T>::push_front(const T& data){
	Node* newnode = new Node(data, _head->next_, _head);
	if (_head->next_ == _tail)
	{
		_head->next_ = newnode;
		_tail->prev_ = newnode;
	}
	else
	{
		_head->next_->prev_ = newnode;
		_head->next_ = newnode;
	}
}

template <typename T>
void Sentinel<T>::push_back(const T& data){
	Node* newnode = new Node(data, _tail, _tail->prev_);
	if (_head->next_ == _tail)
	{
		_head->next_ = newnode;
		_tail->prev_ = newnode;
	}
	else
	{
		_tail->prev_->next_ = newnode;
		_tail->prev_ = newnode;
	}
}

template <typename T>
void Sentinel<T>::pop_front(){
	if (_head != _tail)
	{
		if (_head->next_->next_ != _tail && _head->next_->next_ != nullptr)
		{
			_head->next_ = _head->next_->next_;
			_head->next_->prev_ = _head;
		}
		else {
			_head->next_ = _tail;
			_tail->prev_ = _head;
		}
	}
}

template <typename T>
void Sentinel<T>::pop_back(){
	if (_head != _tail)
	{
		if (_tail->prev_->prev_ != _head && _tail->prev_->prev_ != nullptr)
		{
			_tail->prev_ = _tail->prev_->prev_;
			_tail->prev_->next_ = _tail;
		}
		else {
			_head->next_ = _tail;
			_tail->prev_ = _head;
		}
	}
}

template <typename T>
int Sentinel<T>::getData(int data[]) const{
	Node* curr=_head->next_;
	int numData=0;
	while(curr!=_tail){
		data[numData++]=curr->data_;
		curr=curr->next_;
	}
	return numData;
}

template <typename T>
int Sentinel<T>::getReverseData(int data[]) const{
	Node* curr=_tail->prev_;
	int numData=0;
	while(curr!=_head){
		data[numData++]=curr->data_;
		curr=curr->prev_;
	}
	return numData;
}

template <typename T>
Sentinel<T>::~Sentinel(){

}
