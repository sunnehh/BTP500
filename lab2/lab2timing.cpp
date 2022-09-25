// Workshop 2
// Sunny Qi - 2022/09/25

#include <iostream>
#include "Timer.h"


namespace sdds {
	using namespace std;
	Timer::Timer() : m_start{}, m_finish{}, m_duration{} {
	}

	void Timer::start() {
		m_start = chrono::high_resolution_clock::now();
	}

	long long Timer::stop() {
		m_finish = chrono::high_resolution_clock::now();
		m_duration = m_finish - m_start;
		return chrono::duration_cast<chrono::microseconds>(m_duration).count();
	}
}

unsigned long long fibonacci(unsigned int n) {
	//base case 1
	if (n == 0)
	{
		return 0;
	}
	//base case 2;
	else if (n == 1) {
		return 1;
	}
	else
	{
		return fibonacci(n - 2) + fibonacci(n - 1);
	}
}

using namespace sdds;

int main(void){
	unsigned int n = 40;
	unsigned long long rc;
	Timer t;

	for (int  i = 0; i < 9; i++)
	{
		t.start();
		rc = fibonacci(n);
		long long nanosecs = t.stop();
		//cout << "fibonacci (" << n << ") = " << rc << endl;
		cout << "fibonacci (" << n << ") took " << nanosecs << " microseconds " << endl;
		++n;
	}
	t.start();
	rc=fibonacci(n);
	long long nanosecs = t.stop();
	//cout << "fibonacci (" << n << ") = " << rc << endl;
	cout << "fibonacci (" << n << ") took " << nanosecs << " microseconds " << endl;
	return 0;
}
