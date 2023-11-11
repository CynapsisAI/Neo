#include <iostream>
#include "include/neo.hpp"
#include "structs.hpp"
#include "ndarray.hpp"
#include <string>

int main() {
	neo::ndarray<int> arr({3,2,3});


	std::cout<<arr<<std::endl;

	std::cout<<arr<<std::endl;

	return 0;
}
