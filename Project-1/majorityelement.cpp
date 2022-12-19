/*******************************************************************/
/*                                                                 */
/*  A1 Part 3: Majority Element starter file                       */
/*                                                                 */
/*  Author1 Name: <Sunny Qi>                                       */
/*      - function list                                            */
/*        - majorityElement, partition, quicksort, copyarray       */
/*  Author2 Name: <Alex Cucos>                                     */
/*      - function list                                            */
/*        - findCandidate                                          */
/*                                                                 */
/*******************************************************************/
#define MAGICNUMBER -2147483646
#include <algorithm>


bool findCandidate(int array[],int& candidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);
// sorting helpers
int partition(int array[], int start, int end);
void quicksort(int array[], int left, int right);



// Find the final position of a Pivot in a given array.
// Pivot is defined as: every element to the left of the pivot has a lesser value
// final position is defined as: after the array is sorted in non-descending order, the pivot will be at an index where:
//		every element at a lesser index will have a lesser or equal value than the pivot
//		every element at a greater index will have a greater value
// Every element to the right of the pivot has a greater value
// Takes 3 parameters, Array, start and end - where start is the starting index of the array and end is the last index of the array
// Returns the index of the pivot
int partition(int arr[], int start, int end)
{	// set the pivot to the first element of the array
	int pivot = arr[start];
	// get the position to move the pivot to
	// ie. move parse the array until an element greater than the pivot appears and keep track of the count
	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}
	// Giving pivot element its correct position
	// ie. every element to the left of the pivot is smaller than it
	int pivotIdx = start + count;
	std::swap(arr[pivotIdx], arr[start]);
	// Pivot the left and right of the Pivot
	int i = start, j = end;
	while (i < pivotIdx && j > pivotIdx) {
		// check for values less than or equal to pivot
		while (arr[i] <= pivot) {
			i++;
		}
		// check for values greater than or equal to pivot
		while (arr[j] > pivot) {
			j--;
		}
		// Swap the pivot to its final position
		if (i < pivotIdx && j > pivotIdx) {
			std::swap(arr[i++], arr[j--]);
		}
	}

	return pivotIdx;
}

// Recursive quicksort using partitioning to find the pivot of every element of the array
void quicksort(int arr[], int start, int end)
{
	// base case
	if (start >= end)
		return;
	// partitioning the array
	int p = partition(arr, start, end);
	// Sorting the left part
	quicksort(arr, start, p - 1);
	// Sorting the right part
	quicksort(arr, p + 1, end);
}


// Find the majority element in a given array
// A majority element is defined as: If a given value appears in greater than half of the array
// ie. in a sorted array, if the median+1 is equal to either the head or the tail, it is the majority
//	Takes 3 parameters, the array to find the majority, a reference to an int to store the value of the majority
// and the size of the array. 
bool majorityElement(const int arr[], int& majority, int sz){
	bool hasMajority = false;
	int* duplicate = new int[sz];
	// create copy of the array
	for (int i = 0; i < sz; i++)
	{
		duplicate[i] = arr[i];
	}
	// sort the array
	quicksort(duplicate, 0, sz-1);
	// check whether the median is occurs > sz/2 times.
	// binary search for first occurance of the median
	int median = (sz) / 2;
	int target = duplicate[median];
	int low = 0;
	int high = median;
	bool found = false;
	int mid = 0;
	while (low <= high && !found)
	{
		mid = low + (high - low) / 2;
		if ((mid == 0 || duplicate[mid-1] < target) && duplicate[mid] == target)
		{
			found = true;
		}
		else if (target > duplicate[mid])
		{
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	// remember the index
	int startidx = mid;
	// binary search for last occurance of the index
	if (found)
	{
		low = median;
		high = sz - 1;
		found = false;
		mid = low + (high - low) / 2;
		while (low <= high && !found)
		{
			mid = low + (high - low) / 2;
			if ((mid == sz-1 || duplicate[mid+1] > target) && duplicate[mid] == target)
			{
				found = true;
			}
			else if (target < duplicate[mid]) {
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
	}
	if (found)
	{
		// check if the last and first occurance of the index cause a majority
		int endidx = mid;
		if (endidx - startidx >= median)
		{
			hasMajority = true;
			majority = duplicate[median];
		}
	}
	else
	{
		hasMajority = false;
		majority = MAGICNUMBER;
	}
	delete[] duplicate;
	return hasMajority;
}


// Finds a majority element candidate.
// Recursively compares tuple pairs of array elements - if they match, they proceed to the next iteration
// ie. compare array[0] == array[1], array[2] == array[3], etc.
// Keep track of the odd element in the case the array length is uneven
// Recurse until there is only one element
// The odd one out becomes the candidate if no candidate was previously found
bool findCandidate(int array[],int& candidate, int sz){
	bool candidateFound = false;
	int* subArray = nullptr;
	int lastElem = MAGICNUMBER; // variable to store the dropped element incase the length of array is uneven
	// base case: array of a single item. This is the majority candidate
	if (sz == 1)
	{
		candidate = array[0];
		candidateFound = true;
	}
	// recursive case: split the array into pairs and compare them with eachother.
	//						 pairs will make it to the next round of comparisons while non pairs will be discarded
	else if (sz > 1)
	{
		// create space to store the results of the next recursive call. At most, it will have size/2 pairs (ie whole array is the same number)
		subArray = new int[sz / 2];
		// keep track of the last element incase array length is uneven
		if (sz % 2 == 1) {
			lastElem = array[sz - 1];
		}
		int subArrayIndex = 0;
		// compare the pairs
		for (int i = 0; i < (sz/2); i++)
		{
			if (array[i*2] == array[i*2 + 1]) {
				// matching pairs are added to the new array for future calls
				subArray[subArrayIndex++] = array[i * 2];
			}
		}
		// recursive call
		candidateFound = findCandidate(subArray, candidate, subArrayIndex);
	}
	if (!candidateFound)
	{
		candidate = MAGICNUMBER;
	}
	// deal with the last element
	// the odd one out is the candidate if one could not be determined
	if (!candidateFound && lastElem != MAGICNUMBER)
	{
		candidate = lastElem;
		candidateFound = true;
	}
	return candidateFound;
}
