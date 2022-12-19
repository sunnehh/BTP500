#pragma once

template <typename T>
class Node {
public:
   T data;
   Node<T>* next;
   Node<T>* prev;
   Node() : next(nullptr), prev(nullptr), data() {}
   Node(const T& item, Node<T>* ptr = nullptr, Node<T>* ptr2 = nullptr) :
      data(item), next(ptr),prev(ptr2) {}
};

// Linked LinkedList class
template <typename T>
class LinkedList {
public:
   LinkedList() {
      // Create the dummy head Node
      head = tail = new Node<T>();
   }
   LinkedList(const LinkedList<T>& other);
   LinkedList(LinkedList<T>&& other);
   ~LinkedList() {
      while (head->next != nullptr) {
         Node<T>* temp = head;
         head = head->next;
         delete temp;
      }
      delete head;
   }

   LinkedList<T>& operator=(const LinkedList<T>& other) = delete;
   LinkedList<T>& operator=(LinkedList<T>&& other) = delete;

   // Inner class iterator
   class iterator {
      friend class LinkedList;
   private:
      Node<T>* NodePtr;
      // The constructor is private, so only our friends
      // can create instances of iterators.
      iterator(Node<T>* newPtr) : NodePtr(newPtr) {}
   public:
      iterator() : NodePtr(nullptr) {}

      bool operator!=(const iterator& itr) const {
         return NodePtr != itr.NodePtr;
      }
      bool operator==(const iterator& itr) const {
         return NodePtr == itr.NodePtr;
      }

      T& operator*() const {
         return NodePtr->next->data;
      }

      iterator operator++(int) {
         iterator temp = *this;
         NodePtr = NodePtr->next;
         return temp;
      }

      iterator operator--(int) {
         iterator temp = *this;
         NodePtr = NodePtr->prev;
         return temp;
      }
   }; // End of inner class iterator

   iterator begin() const {
      return iterator(head);
   }

   iterator end() const {
      return iterator(tail);
   }

   iterator insert(iterator position, const T& value) {
      Node<T>* newNode = new Node<T>(value, position.NodePtr->next, position.NodePtr->prev);
      if (position.NodePtr == tail) tail = newNode;
      position.NodePtr->next = newNode;
      return position;
   }

   iterator erase(iterator position) {
      Node<T>* toDelete = position.NodePtr->next;
      position.NodePtr->next = position.NodePtr->next->next;
      position.NodePtr->next->next->prev = position.NodePtr;
      if (toDelete == tail) tail = position.NodePtr;
      delete toDelete;
      return position;
   }
private:
   Node<T>* head;
   Node<T>* tail;
};
/*

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) {
   auto temp = head;
   while (temp != nullptr)
   {
      auto next
   }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& other);

*/