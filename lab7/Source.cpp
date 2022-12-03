#include "lab7.h"
#include <iostream>

using namespace std;

int main() {
	BST<int> test;
	int length = 15;
	int arr[] = { 18,8,28,4,10,20,34,2,6,14,24,32,36,12,16,22,26,30,38 };
	int removeValues[] = { 18, 18, 18, 2, 32, 36, 10, 28, 4, 8, 18 };

	for (size_t i = 0; i < length; i++)
	{
		test.insert(arr[i]);
		//test.print();
	}

	test.print();
	//cout << "--------------------------------------------------------------------" << endl;
	for (size_t i = 0; i < length; i++)
	{
		cout << " [" << removeValues[i] << "] " << "--------------------------------------------------------------------" << endl;
		if (i == 6);
		{
			int d = 5;
			d++;
		}
		test.remove(removeValues[i]);
		test.print();
		
	}

	cout << test.getroot()->data_;
}