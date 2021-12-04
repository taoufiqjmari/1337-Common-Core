#include <iostream>
#include "Array.hpp"

#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;
}

// int main() {
// 	Array<int> temp;
// 	try {
// 		std::cout << temp[0] << std::endl;
// 	} catch (std::exception &e) {
// 		std::cout << e.what() << std::endl;
// 	}
// 	std::cout << "--------------------------" << std::endl;

// 	Array<int>	arr(5);
// 	Array<int>	arr2(arr);

// 	std::cout << arr.size() << std::endl;
// 	std::cout << arr2.size() << std::endl;

// 	std::cout << "arr[2]:		" << arr[2] << std::endl;
// 	arr[2] = 97;
// 	std::cout << "arr[2]:		" << arr[2] << std::endl;
// 	std::cout << "arr2[2]:	" << arr2[2] << std::endl;

// 	std::cout << "--------------------------" << std::endl;
// 	try {
// 		std::cout << arr[-2] << std::endl;
// 	} catch (std::exception &e) {
// 		std::cout << e.what() << std::endl;
// 	}
// 	try {
// 		std::cout << arr[5] << std::endl;
// 	} catch (std::exception &e) {
// 		std::cout << e.what() << std::endl;
// 	}
// 	return 0;
// }
