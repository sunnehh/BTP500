#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;


void unguardedInsertionSort(int arr[], int first, int last);
void shiftdown(int arr[], int idx, int size);
void heapify(int arr[], int size) {
   int i = (size / 2) - 1;
   for (; i >= 0; --i)
   {
      shiftdown(arr, i, size);
   }
}

void shiftdown(int arr[], int idx, int size) {
   while (idx < size)
   {
      auto idx_small = idx;
      auto c1 = (2 * idx) + 1;
      auto c2 = c1 + 1;
      if (c1 < size && arr[c1] < arr[idx_small])
      {
         idx_small = c1;
      }
      if (c2 < size && arr[c2] < arr[idx_small])
      {
         idx_small = c2;
      }
      if (idx_small == idx) return;
      std::swap(arr[idx], arr[idx_small]);
      idx = idx_small;
   }
}

/*Only modify this function*/
void insertionSortModified(int arr[],int size){
   heapify(arr, size);
   unguardedInsertionSort(arr, 1, size);
}

void unguardedInsertionSort(int arr[],int first, int last) {
   int size = last - first + 1;
   int curr;
   int i, j;
   for (i = 1;i < size;i++) {
      curr = arr[i];
      for (j = i;j > 0 && arr[j - 1] > curr;j--) {
         arr[j] = arr[j - 1];
      }
      arr[j] = curr;
 
   }
}



/*performs the insertion sort algorithm on array from index
left to index right inclusive.  You don't need to change this function*/
void insertionSortStandard(int arr[], int size) {
   int curr;
   int i, j;
   for (i = 1;i < size;i++) {
      curr = arr[i];
      for (j = i;j > 0 && arr[j - 1] > curr;j--) {
         arr[j] = arr[j - 1];
      }
      arr[j] = curr;
   }
}