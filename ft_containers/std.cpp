#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <ctime>
#include <chrono>
#include <sys/time.h>

using namespace std::chrono;

#define VECTOR

int main()
{
#if defined(VECTOR)
	std::__1::chrono::steady_clock::time_point start = high_resolution_clock::now();

	std::vector<int> v;
	std::vector<int> v2;

	for (int i(1); i <= 10; ++i)
		v.push_back(i);

	v2 = v;

	std::vector<int>::iterator it2 = v2.begin();
	std::vector<int>::iterator ite2 = v2.end();
	std::vector<int>::reverse_iterator rit2 = v2.rbegin();
	std::vector<int>::reverse_iterator rite2 = v2.rend();
	std::cout << "\033[0;32m"
			  << "// Forward iterator"
			  << "\033[0m" << std::endl;
	for (; it2 != ite2; ++it2)
		std::cout << *it2 << " ";
	std::cout << std::endl;
	std::cout << "\033[0;32m"
			  << "// Reverse iterator"
			  << "\033[0m" << std::endl;
	for (; rit2 != rite2; ++rit2)
		std::cout << *rit2 << " ";
	std::cout << std::endl
			  << std::endl;

	std::cout << "v.size() = " << v.size() << std::endl;
	std::cout << "v2.size() = " << v2.size() << std::endl;
	std::cout << "v.capacity() = " << v.capacity() << std::endl;
	std::cout << "v2.capacity() = " << v2.capacity() << std::endl;

	std::cout << std::endl
			  << "\033[0;32m"
			  << "// Reserve 200"
			  << "\033[0m" << std::endl;
	v.reserve(200);
	std::cout << "v.size() = " << v.size() << std::endl;
	std::cout << "v.capacity() = " << v.capacity() << std::endl;

	std::cout << std::endl
			  << "v.at(5):	" << v.at(5) << std::endl;

	std::cout << std::endl
			  << "\033[0;32m"
			  << "// clear v"
			  << "\033[0m" << std::endl;
	v.clear();

	std::cout << std::endl
			  << "\033[0;32m"
			  << "// swap(v, v2)"
			  << "\033[0m" << std::endl;
	swap(v, v2);

	std::cout << "v.size() = " << v.size() << std::endl;
	std::cout << "v2.size() = " << v2.size() << std::endl;
	std::cout << "v.capacity() = " << v.capacity() << std::endl;
	std::cout << "v2.capacity() = " << v2.capacity() << std::endl;

	std::__1::chrono::steady_clock::time_point end = high_resolution_clock::now();
	std::cout << "duration:	" << duration_cast<microseconds>(end - start).count() << std::endl;
#elif defined(STACK)
	std::stack<std::string> s;
	std::stack<std::string> s2;
	s.push("Hello");
	s.push("World");
	s.push("!");

	if (s == s2)
		std::cout << "s == s2" << std::endl;
	else
		std::cout << "s != s2" << std::endl;
	std::cout << std::endl;

	std::cout << "s.top() = " << s.top() << std::endl;
	std::cout
		<< "\033[0;32m"
		<< "// pop()"
		<< "\033[0m" << std::endl;
	s.pop();
	std::cout << "s.top() = " << s.top() << std::endl;
#elif defined(MAP)
	std::__1::chrono::steady_clock::time_point start = high_resolution_clock::now();
	std::string arr[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
	std::map<int, std::string> m;
	for (int i(0); i < 1e6; ++i)
		m.insert(std::make_pair(i, std::string()));

	std::cout << "m.size() = " << m.size() << std::endl;

	std::map<int, std::string>::iterator it = m.begin();
	std::map<int, std::string>::iterator ite = m.end();
	std::cout << "\033[0;32m"
			  << "// Forward iterator"
			  << "\033[0m" << std::endl;
	for (; it != ite; ++it)
		std::cout << it->first << " " << it->second << std::endl;
	std::cout << std::endl;

	std::cout << "\033[0;32m"
			  << "// find(5)"
			  << "\033[0m" << std::endl;
	std::map<int, std::string>::iterator it5 = m.find(5);
	std::cout << "it5->first = " << it5->first << std::endl;
	std::cout << "it5->second = " << it5->second << std::endl;
	std::cout << "\033[0;32m"
			  << "// find(50)"
			  << "\033[0m" << std::endl;
	std::map<int, std::string>::iterator it50 = m.find(50);
	std::cout << "it50->first = " << it50->first << std::endl;
	std::cout << "it50->second = " << it50->second << std::endl;
	std::cout << std::endl;

	std::cout << "\033[0;32m"
			  << "// count()"
			  << "\033[0m" << std::endl;
	std::cout << "m.count(5):	" << m.count(5) << std::endl;
	std::cout << "m.count(50):	" << m.count(50) << std::endl;
	std::cout << std::endl;

	std::cout << "\033[0;32m"
			  << "// lower_bound(10)"
			  << "\033[0m" << std::endl;
	std::map<int, std::string>::iterator it_lower = m.lower_bound(10);
	std::cout << "it_lower->first = " << it_lower->first << std::endl;
	std::cout << "it_lower->second = " << it_lower->second << std::endl;
	std::cout << std::endl;

	std::cout << "\033[0;32m"
			  << "// upper_bound(10)"
			  << "\033[0m" << std::endl;
	std::map<int, std::string>::iterator it_upper = m.upper_bound(10);
	std::cout << "it_upper->first = " << it_upper->first << std::endl;
	std::cout << "it_upper->second = " << it_upper->second << std::endl;
	std::cout << std::endl;

	std::__1::chrono::steady_clock::time_point end = high_resolution_clock::now();
	std::cout << "duration:	" << duration_cast<microseconds>(end - start).count() << std::endl;
#endif
	return 0;
}
