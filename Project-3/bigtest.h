#pragma once

#include "linkedlist.h"

template <typename T>
class MyClass
{
public:
   template <typename TYPE>
   struct BucketEntry {
      TYPE data_;
      std::string key_;

      BucketEntry() {
         data_ = TYPE();
         key_ = "";
      }

      BucketEntry(std::string key) {
         data_ = TYPE();
         key_ = key;
      }

      BucketEntry(std::string key, TYPE data) {
         data_ = data;
         key_ = key;
      }

      bool operator==(BucketEntry rhs) {
         return key_ == rhs.key_;
      }

      bool operator!=(BucketEntry rhs) {
         return key_ != rhs.key_;
      }

      bool operator<(BucketEntry rhs) {
         return key_ < rhs.key_;
      }

   };
	
	MyClass();
	~MyClass();

private:
   LinkedList<BucketEntry>* records;

public:
   void insert(std::string& key, T value);
};

template<typename T>
MyClass<T>::MyClass() :{
   records = new LinkedList<BucketEntry>[3];
}

template<typename T>
void MyClass<T>::insert(std::string& key, T value) {
   records[0] = new LinkedList<BucketEntry>;
}