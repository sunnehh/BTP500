//#include "table.h"
#include <iostream>
#include <string>
#include "table.h"
//you need to include functional to use hash functions
#include <functional>
const int cap = 100;
using namespace std;
int main(void) {


	ChainingTable<int> test(1);
	test.insert("john", 100);
	test.insert("john2", 10);
	test.insert("john3", 10);
	test.insert("john4", 10);
	test.insert("john5", 10);
	test.modify("john5", 49);
	int value;
	cout<< test.find("john5", value) << endl;
	cout << test.remove("john5") << endl;
	ChainingTable<int> test2(2);
	ChainingTable<int> test3(3);
	test2 = test;

	test3 = std::move(test2);

	value = 0;
	test2.find("john", value);
	cout << value << endl;


	ChainingTable<int>test5(test3);
	test5.find("john", value);

	cout << value << endl;
}