#include <iostream>
#include "include/neo.hpp"
#include "structs.hpp"
#include "ndarray.hpp"
#include <string>

int main() {
	neo::shape shape = neo::shape{1,2,3};
	neo::ndarray<int> arr(shape);

	//std::cout<<arr<<std::endl;

	return 0;
}
