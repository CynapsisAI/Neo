#include <iostream>
#include "include/neo.hpp"
#include <string>

int main()
{
	neo::ndarray<int> arr({3, 2, 3});

	std::cout << arr.shape() << std::endl;

	return 0;
}
