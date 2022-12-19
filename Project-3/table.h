/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1 Name: <Sunny Qi >                                */
/*      - Linear Probing Main Author                         */
/*        - All methods associated with linear probing       */
/*          - completed 2022/11/23                           */
/*      - Chaining table Main Checker                        */
/*  Author2 Name: <name here>                                */
/*      - class/function list/main author or main checker    */
/*                                                           */
/*************************************************************/
#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <typename T>
class Table {
public:
   Table() {}
   virtual bool insert(const std::string& key, const T& value) = 0;
   virtual bool modify(const std::string& key, const T& value) = 0;
   virtual bool remove(const std::string& key) = 0;
   virtual bool find(const std::string& key, T& value) = 0;
   virtual int numRecords() const = 0;
   virtual bool isEmpty() const = 0;
   virtual int capacity() const = 0;
   virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {

   struct Record {
      TYPE data_;
      std::string key_;
      Record(const std::string& key, const TYPE& data) {
         key_ = key;
         data_ = data;
      }

   };

   Record** records_;   //the table
   int capacity_;       //capacity of the array

   void grow() {
      Record** newarray = new Record * [capacity_ * 2 + 1];
      int sz = numRecords();

      for (int i = 0;i < sz;i++) {
         newarray[i] = records_[i];
      }
      capacity_ *= 2;
      delete[] records_;
   }
public:
   SimpleTable(int capacity);
   SimpleTable(const SimpleTable& rhs);
   SimpleTable(SimpleTable&& rhs);
   virtual bool insert(const std::string& key, const TYPE& value);
   virtual bool modify(const std::string& key, const TYPE& value);
   virtual bool remove(const std::string& key);
   virtual bool find(const std::string& key, TYPE& value);
   virtual const SimpleTable& operator=(const SimpleTable& rhs);
   virtual const SimpleTable& operator=(SimpleTable&& rhs);
   virtual ~SimpleTable();
   virtual bool isEmpty() const { return numRecords() == 0; }
   virtual int numRecords() const;
   virtual int capacity() const { return capacity_; }

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const {
   int rc = 0;
   for (int i = 0;records_[i] != nullptr;i++) {
      rc++;
   }
   return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
   records_ = new Record * [capacity + 1];
   capacity_ = capacity;
   for (int i = 0;i < capacity_ + 1;i++) {
      records_[i] = nullptr;
   }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs) {
   records_ = new Record * [rhs.capacity_ + 1];
   capacity_ = rhs.capacity_;
   for (int i = 0;i < capacity_ + 1;i++) {
      records_[i] = nullptr;
   }
   for (int i = 0;i < rhs.numRecords();i++) {
      insert(rhs.records_[i]->key_, rhs.records_[i]->data_);
   }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs) {
   capacity_ = rhs.capacity_;
   records_ = rhs.records_;
   rhs.records_ = nullptr;
   rhs.capacity_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::insert(const std::string& key, const TYPE& value) {
   int idx = -1;
   int sz = numRecords();
   bool rc = false;
   for (int i = 0;i < sz;i++) {
      if (records_[i]->key_ == key) {
         idx = i;
      }
   }
   if (idx == -1) {
      if (sz == capacity_) {
         grow();
      }
      records_[numRecords()] = new Record(key, value);
      for (int i = 0; i < sz - 1; i++) {
         for (int j = 0; j < sz - 1 - i; j++) {
            if (records_[j + 1]->key_ < records_[j]->key_) {
               Record* tmp = records_[j];
               records_[j] = records_[j + 1];
               records_[j + 1] = tmp;
            }
         }
      }
      rc = true;
   }

   return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::modify(const std::string& key, const TYPE& value) {
   int idx = -1;
   bool rc = false;
   for (int i = 0;i < numRecords();i++) {
      if (records_[i]->key_ == key) {
         idx = i;
      }
   }
   if (idx != -1) {
      records_[idx]->data_ = value;
   }
   return rc;
}


template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key) {
   int idx = -1;
   for (int i = 0;i < numRecords();i++) {
      if (records_[i]->key_ == key) {
         idx = i;
      }
   }
   if (idx != -1) {
      delete records_[idx];
      for (int i = idx;i < numRecords() - 1;i++) {
         records_[i] = records_[i + 1];
      }
      records_[numRecords() - 1] = nullptr;
      return true;
   }
   else {
      return false;
   }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value) {
   int idx = -1;
   int size = numRecords();
   for (int i = 0;i < size;i++) {
      if (records_[i]->key_ == key) {
         idx = i;
      }
   }
   if (idx == -1) {
      return false;
   }
   else {
      value = records_[idx]->data_;
      return true;
   }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs) {
   if (this != &rhs) {
      if (records_) {
         while (numRecords() != 0) {
            remove(records_[0]->key_);
         }
         delete[] records_;
      }
      records_ = new Record * [rhs.capacity_ + 1];
      capacity_ = rhs.capacity_;
      for (int i = 0;i < capacity_;i++) {
         records_[i] = nullptr;
      }
      for (int i = 0;i < rhs.numRecords();i++) {
         insert(rhs.records_[i]->key_, rhs.records_[i]->data_);
      }

   }
   return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs) {
   if (records_) {
      while (numRecords() != 0) {
         remove(records_[0]->key_);
      }
      delete[] records_;
   }
   records_ = rhs.records_;
   capacity_ = rhs.capacity_;
   rhs.records_ = nullptr;
   rhs.capacity_ = 0;

   return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
   if (records_) {
      int sz = numRecords();
      for (int i = 0;i < sz;i++) {
         remove(records_[0]->key_);
      }
      delete[] records_;
   }
}




template <class TYPE>
class ChainingTable :public Table<TYPE> {

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

   CacheList<BucketEntry>** buckets; ;   //the table
   int capacity_;       //capacity of the array
   int numRecords_;
   double maxLoadFactor_;
   std::hash<std::string> hashFunc_;

   void grow() {
      //1. Store current buckets in a copy
      CacheList<BucketEntry>** oldBuckets = new CacheList<BucketEntry>*[capacity_];
      int oldCapacity = capacity_;
      //safe state
      for (int i = 0; i < oldCapacity; i++) oldBuckets[i] = nullptr;
      // Copy from buckets to oldBuckets
      for (int i = 0; i < oldCapacity; i++) {
         if (buckets[i] != nullptr)
            oldBuckets[i] = new CacheList<BucketEntry>(*buckets[i]);
         //buckets[i] = nullptr;
      }

      //2. Create a new list with double capacity
      //3. set this.buckets to the new list
      capacity_ *= 2;
      buckets = new CacheList<BucketEntry>*[capacity_];
      numRecords_ = 0;
      for (int i = 0; i < capacity_; i++) buckets[i] = nullptr;
      //4. insert all the old buckets into the new buckets
      for (int i = 0; i < oldCapacity; i++) {
         if (oldBuckets[i] != nullptr) {
            auto it = oldBuckets[i]->begin();
            while (it != oldBuckets[i]->end()) {
               BucketEntry entry = *it;
               insert(entry.key_, entry.data_);
               it++;
            }
         }
      }
   }

public:
   ChainingTable(int capacity, double maxLoadFactor = 1.0);
   ChainingTable(const ChainingTable& other);
   ChainingTable(ChainingTable&& other);
   double loadFactor() const;
   virtual bool insert(const std::string& key, const TYPE& value);
   virtual bool modify(const std::string& key, const TYPE& value);
   virtual bool remove(const std::string& key);
   virtual bool find(const std::string& key, TYPE& value);
   virtual const ChainingTable& operator=(const ChainingTable& other);
   virtual const ChainingTable& operator=(ChainingTable&& other);
   virtual ~ChainingTable();
   virtual bool isEmpty() const;
   virtual int numRecords() const;
   virtual int capacity() const;

};

// public method:: constructor
// initializes all all values to safe state    
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity, double maxLoadFactor) : Table<TYPE>() {
   capacity_ = capacity;
   maxLoadFactor_ = maxLoadFactor;
   buckets = new CacheList<BucketEntry>*[capacity_];
   for (int i = 0; i < capacity; i++)
   {
      buckets[i] = nullptr;
   }
   numRecords_ = 0;

}

template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) {
   // copy over the other's records
   capacity_ = other.capacity_;
   hashFunc_ = other.hashFunc_;
   maxLoadFactor_ = other.maxLoadFactor_;
   numRecords_ = other.numRecords_;
   // create a new records;
   buckets = new CacheList<BucketEntry>*[capacity_];
   for (size_t i = 0; i < capacity_; i++)
   {
      if (other.buckets[i] == nullptr)
      {
         buckets[i] = nullptr;
      }
      else
      {
         buckets[i] = new CacheList<BucketEntry>;
         buckets[i] = other.buckets[i];
      }
   }
}


template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) {
   // steal the other's records
   capacity_ = other.capacity_;
   hashFunc_ = other.hashFunc_;
   maxLoadFactor_ = other.maxLoadFactor_;
   numRecords_ = other.numRecords_;
   // create a new buckets of other's size
   buckets = new CacheList<BucketEntry>*[capacity_];
   for (size_t i = 0; i < capacity_; i++)
   {
      buckets[i] = std::move(other.buckets[i]);
   }
   // zero other's records
   for (size_t i = 0; i < capacity_; i++)
   {
      if (other.buckets[i] != nullptr) {
         other.buckets[i] = nullptr;
      }
   }
   other.capacity_ = 1;
   other.maxLoadFactor_ = 1.0;
   other.numRecords_ = 0;
}

// public method:  returns true on successful insert, false otherwise
template <class TYPE>
bool ChainingTable<TYPE>::insert(const std::string& key, const TYPE& value) {
   bool inserted = false;
   //1. Hash key and get hashIdx
   const size_t hash = hashFunc_(key);
   size_t hashIdx = hash % capacity_;


   //2. check if the bucket exists - create a new list if not
   if (buckets[hashIdx] == nullptr) {
      buckets[hashIdx] = new CacheList<BucketEntry>();
      BucketEntry* entry = new BucketEntry(key, value);
      buckets[hashIdx]->insert(*entry);
      inserted = true;
   }
   else {
      //3. Create an iterator over the bucket
      bool exists = false;
      auto it = buckets[hashIdx]->begin();
      //4. Iterate over the bucket 
      while (it != buckets[hashIdx]->end()) {
         BucketEntry entry = *it;
         if (entry.key_ == key) {
            exists = true;
            break;
         }
         it++;
      }

      //6. Key does not already exist - insert it and return true
      if (exists == false) {
         BucketEntry* entry = new BucketEntry(key, value);
         buckets[hashIdx]->insert(*entry);
         inserted = true;
      }
   }

   if (inserted == true) {
      numRecords_++;
      if (loadFactor() > maxLoadFactor_) {
         grow();
      }
   }

   return inserted;
}

template <class TYPE>
bool ChainingTable<TYPE>::modify(const std::string& key, const TYPE& value) {
   bool removed = false;
   //1. Hash key and get hashIdx
   const size_t hash = hashFunc_(key);
   const size_t hashIdx = hash % capacity_;
   //2. Check if bucket exists - return false if not
   if (buckets[hashIdx] == nullptr) return false;
   //3. If exists create iterator
   typename CacheList<BucketEntry>::iterator it;
   //4. Iterate until key is found
   it = buckets[hashIdx]->begin();
   while (it != buckets[hashIdx]->end()) {
      BucketEntry entry = *it;
      entry.data_ = value;
      if (entry.key_ == key) {
         //5. Erase entry and insert new entry -> return true
         buckets[hashIdx]->erase(it);
         buckets[hashIdx]->insert(entry);
         removed = true;
      }
      it++;
   }
   //6. if iterator reaches end return false
   return removed;
}

template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key) {
   bool removed = false;
   //1. Hash key and get hashIdx
   const size_t hash = hashFunc_(key);
   const size_t hashIdx = hash % capacity_;
   //2. Check if bucket exists - return false if not
   if (buckets[hashIdx] == nullptr) return false;
   //3. If exists create iterator
   typename CacheList<BucketEntry>::iterator it;
   //4. Iterate until key is found
   it = buckets[hashIdx]->begin();
   while (it != buckets[hashIdx]->end()) {
      BucketEntry entry = *it;
      if (entry.key_ == key) {
         //5. Erase entry and insert new entry -> return true
         buckets[hashIdx]->erase(it);
         removed = true;
      }
      it++;
   }
   //6. if iterator reaches end return false
   return removed;
}

template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value) {
   //1. Hash Key and get hashIdx
   const size_t hash = hashFunc_(key);
   const size_t hashIdx = hash % capacity_;
   //2. Check if bucket exists - return false if not
   if (buckets[hashIdx] == nullptr) return false;
   //3. if exists create iterator
   typename CacheList<BucketEntry>::iterator it;
   //4. iterate over bucket list until key is found
   it = buckets[hashIdx]->begin();
   while (it != buckets[hashIdx]->end()) {
      BucketEntry entry = *it;
      if (entry.key_ == key) {
         //5. set passed in value to data_ and return true
         value = entry.data_;
         return true;
      }
      it++;
   }

   /*
     6. if iterator reaches end return false
   */
   return false;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) {
   // self assignment check
   if (this != &other)
   {
      // free our records
      for (size_t i = 0; i < capacity_; i++)
      {
         delete buckets[i];
      }
      delete[] buckets;
      // copy over the other's records
      capacity_ = other.capacity_;
      hashFunc_ = other.hashFunc_;
      maxLoadFactor_ = other.maxLoadFactor_;
      numRecords_ = other.numRecords_;
      // create a new records;
      buckets = new CacheList<BucketEntry>*[capacity_];
      for (size_t i = 0; i < capacity_; i++)
      {
         if (other.buckets[i] == nullptr)
         {
            buckets[i] = nullptr;
         }
         else
         {
            buckets[i] = new CacheList<BucketEntry>;
            auto it = other.buckets[i]->begin();
            while (it != other.buckets[i]->end()) {
                BucketEntry entry = *it;
                buckets[i]->insert(entry);
                it++;
            }
         }
      }
   }
   return *this;
}

template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) {
   // free our records
   for (size_t i = 0; i < capacity_; i++)
   {
      delete buckets[i];
   }
   delete[] buckets;
   // steal the other's records
   capacity_ = other.capacity_;
   hashFunc_ = other.hashFunc_;
   maxLoadFactor_ = other.maxLoadFactor_;
   numRecords_ = other.numRecords_;
   // create a new buckets of other's size
   buckets = new CacheList<BucketEntry>*[capacity_];
   for (size_t i = 0; i < capacity_; i++)
   {
      buckets[i] = std::move(other.buckets[i]);
   }
   // zero other's records
   for (size_t i = 0; i < capacity_; i++)
   {
      if (other.buckets[i] != nullptr) {
         other.buckets[i] = nullptr;
      }
   }
   other.capacity_ = 1;
   other.maxLoadFactor_ = 1.0;
   other.numRecords_ = 0;
   return *this;
}

template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() {
   delete[] buckets;
}

template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {
   return numRecords_ == 0;
}

template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
   return numRecords_;
}
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
   return capacity_;
}

template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const {
   return (double)numRecords_ / (double)capacity_;
}




template <typename T>
class LPTable :public Table<T> {
private:
   struct Record {
      T data_;
      std::string key_;
      Record(const std::string& key, const T& data) {
         key_ = key;
         data_ = data;
      }
   };

   Record** m_records;   //the table
   size_t m_num_records;
   size_t m_cap;       //capacity of the array
   double m_loadfactor;
   std::hash<std::string> m_hash;

   void grow() {
      // create a copy of the old records
      size_t oldcap = m_cap;
      Record** oldrecords = new Record * [m_cap + 1];
      for (size_t i = 0; i < oldcap; i++)
      {
         oldrecords[i] = m_records[i];
         m_records[i] = nullptr;
      }
      // this records is a new records with double size and safe state
      delete[] m_records;
      this->m_num_records = 0;
      m_cap *= 2;
      this->m_records = new Record * [m_cap + 1];
      for (size_t i = 0; i < m_cap; i++)
      {
         this->m_records[i] = nullptr;
      }
      // for each of the old records, this.insert
      for (size_t i = 0; i < oldcap; i++)
      {
         if (oldrecords[i] != nullptr)
         {
            this->insert(oldrecords[i]->key_, oldrecords[i]->data_);
            delete oldrecords[i];
         }
      }
      // delete the resource
      delete[] oldrecords;
   }

public:
   LPTable(int capacity, double maxLoadFactor = 0.7);
   LPTable(const LPTable& other);
   LPTable(LPTable&& other) noexcept;
   double loadFactor() const;
   virtual bool insert(const std::string& key, const T& value);
   virtual bool modify(const std::string& key, const T& value);
   virtual bool remove(const std::string& key);
   virtual bool find(const std::string& key, T& value);
   virtual int search(const std::string& key) const;
   virtual const LPTable& operator=(const LPTable& other);
   virtual const LPTable& operator=(LPTable&& other) noexcept;
   virtual ~LPTable();
   virtual bool isEmpty() const;
   virtual int numRecords() const;
   virtual int capacity() const;

};

// public method:
// constructs a new LPTable with a capacity and default load factor 0.7
template <typename T>
LPTable<T>::LPTable(int capacity, double maxLoadFactor) : Table<T>() {
   this->m_cap = capacity;
   this->m_loadfactor = maxLoadFactor;
   // dynamically create an array of pointers to records
   this->m_records = new Record * [m_cap];
   // initialize each entry to safe state
   for (size_t i = 0; i < m_cap; i++)
   {
      m_records[i] = nullptr;
   }
   this->m_num_records = 0;
}

// copy constructor
template <typename T>
LPTable<T>::LPTable(const LPTable<T>& other) {
   this->m_cap = other.m_cap;
   this->m_hash = other.m_hash;
   this->m_loadfactor = other.m_loadfactor;
   this->m_num_records = other.m_num_records;
   // create a new empty records
   this->m_records = new Record * [m_cap];
   for (size_t i = 0; i < m_cap; i++)
   {
      if (other.m_records[i] == nullptr)
      {
         this->m_records[i] = nullptr;
      }
      else
      {
         this->m_records[i] = new Record(other.m_records[i]->key_, other.m_records[i]->data_);
      }
   }
}

// move constructor
template <typename T>
LPTable<T>::LPTable(LPTable<T>&& other)noexcept {
   // copy steal other's records
   this->m_cap = other.m_cap;
   this->m_hash = other.m_hash;
   this->m_loadfactor = other.m_loadfactor;
   this->m_num_records = other.m_num_records;
   this->m_records = other.m_records;
   for (size_t i = 0; i < m_cap; i++)
   {
      if (other.m_records[i] == nullptr)
      {
         this->m_records[i] = nullptr;
      }
      else
      {
         this->m_records[i] = other.m_records[i];
      }
   }
   // zero out other's records
   other.m_cap = 1;
   other.m_loadfactor = 0.7;
   other.m_num_records = 0;
   for (size_t i = 0; i < m_cap; i++)
   {
      other.m_records = nullptr;
   }
   other.m_records = nullptr;
}


// public method: returns true if successfully inserted. false otherwise
// Inserts a key/value pair into the map
template <typename T>
bool LPTable<T>::insert(const std::string& key, const T& value) {
   bool inserted = false;
   size_t hashvalue = m_hash(key);
   size_t hashidx = hashvalue % m_cap;
   size_t i = 0;
   // check if the record is already in the table
   if (this->search(key) == -1) {
      // traverse the array until an empty slot is found
      while ((m_records[(hashidx + i) % m_cap] != nullptr)) // no need for fullness check since we always grow
      {
         i++;
      }
      // insert the item at the empty slot
      m_records[(hashidx + i) % m_cap] = new Record(key, value);
      m_num_records++;
      inserted = true;
   }
   else // record with same key is already in the table
   {
      inserted = false;
   }
   if (m_num_records > (m_loadfactor * m_cap))
   {
      grow();
   }
   return inserted;
}

// public method: Returns the index at which a key is located in the table.
// -1 if not found
template <typename T>
int LPTable<T>::search(const std::string& key) const {
   int idxFound = -1;
   bool found = false;
   size_t hashvalue = m_hash(key);
   size_t hashidx = hashvalue % m_cap;
   size_t i = 0;
   bool stop = false;
   // traverse the entire map checking whether a key is found, starting at the hash value of key
   if (m_num_records > 0)
   {  // in case of collision, check if the key is the one we're looking for
      while (!found && i < m_cap && !stop)
      {
         if (m_records[(hashidx + i) % m_cap] != nullptr)
         {
            if (m_records[(hashidx + i) % m_cap]->key_ != key) { // if not, look at next key
               i++;
            }
            else
            {
               found = true;
            }
         }
         else // stop if we find an empty space
         {
            stop = true;
         }
      }
      if (found)
      {
         idxFound = hashidx + i % m_cap;
      }
   }
   return idxFound;
}

// public method: returns whether the entry was successfully found and modified
// searches through the map for an entry with the entered key
// changes the value to the value entered
template <typename T>
bool LPTable<T>::modify(const std::string& key, const T& value) {
   int idxfound = search(key);
   bool modded = idxfound != -1; // false if key not present;
   if (modded)
   {
      m_records[idxfound % m_cap]->data_ = value;
   }
   return modded;
}


// public method:: returns true if an entry is removed from the map. false otherwise
// traverse the map and remove the found member
template <typename T>
bool LPTable<T>::remove(const std::string& key) {
   int i = 1;
   // find index of the key
   int indexfound = search(key);
   // if found remove
   bool found = indexfound != -1; // true if found
   if (found)
   {
      delete m_records[indexfound % m_cap];
      m_records[indexfound % m_cap] = nullptr;
      m_num_records--;
      // if the next element is nullptr - we can stop
      // if not, delete that element and re-insert it
      while (m_records[(indexfound + i) % m_cap] != nullptr && i < m_cap)
      {
         const std::string keycpy = m_records[(indexfound + i) % m_cap]->key_;
         const T datacpy = m_records[(indexfound + i) % m_cap]->data_;
         //delete m_records[indexfound % m_cap];
         m_num_records--;
         m_records[(indexfound + i) % m_cap] = nullptr;
         this->insert(keycpy, datacpy);
         i++;
      }
   }

   return found;
}


// public method: returns true if key is found in table, false otherwise
// passes the data of the found key to the value parameter by value
template <typename T>
bool LPTable<T>::find(const std::string& key, T& value) {
   int indexfound = search(key);
   bool found = indexfound != -1; // true if found
   if (found)
   {
      value = m_records[indexfound % m_cap]->data_;

   }
   return found;
}

// copy operator
template <typename T>
const LPTable<T>& LPTable<T>::operator=(const LPTable<T>& other) {
   // self assignment check
   if (this != &other)
   {
      // free our records
      for (size_t i = 0; i < m_cap; i++)
      {
         delete m_records[i];
      }
      delete[] m_records;
      // copy over all contents
      this->m_cap = other.m_cap;
      this->m_hash = other.m_hash;
      this->m_loadfactor = other.m_loadfactor;
      this->m_num_records = other.m_num_records;
      // create a new empty records
      this->m_records = new Record * [m_cap];
      for (size_t i = 0; i < m_cap; i++)
      {
         if (other.m_records[i] == nullptr)
         {
            this->m_records[i] = nullptr;
         }
         else
         {
            this->m_records[i] = new Record(other.m_records[i]->key_, other.m_records[i]->data_);
         }
      }
   }
   return *this;
}

// move operator
template <typename T>
const LPTable<T>& LPTable<T>::operator=(LPTable<T>&& other)noexcept {
   if (this != &other)
   {
      // free our records
      for (size_t i = 0; i < m_cap; i++)
      {
         delete m_records[i];
      }
      delete[] m_records;
      // copy steal other's records
      this->m_cap = other.m_cap;
      this->m_hash = other.m_hash;
      this->m_loadfactor = other.m_loadfactor;
      this->m_num_records = other.m_num_records;
      this->m_records = other.m_records;
      for (size_t i = 0; i < m_cap; i++)
      {
         if (other.m_records[i] == nullptr)
         {
            this->m_records[i] = nullptr;
         }
         else
         {
            this->m_records[i] = other.m_records[i];
         }
      }

      other.m_cap = 1;
      other.m_loadfactor = 0.7;
      other.m_num_records = 0;

      other.m_records = nullptr;
   }
   return *this;
}

template <typename T>
LPTable<T>::~LPTable() {
   delete[] m_records;
}

template <typename T>
bool LPTable<T>::isEmpty() const {
   return this->m_num_records == 0;
}

template <typename T>
int LPTable<T>::numRecords() const {
   return this->m_num_records;
}
template <typename T>
int LPTable<T>::capacity() const {
   return this->m_cap;
}
template <typename T>
double LPTable<T>::loadFactor() const {
   return m_num_records / m_cap;
}

