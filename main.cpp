#include <iostream>
#include "include/neo.hpp"

int main() {
	neo::tensor<int> tens({3,3,2});


	int* arr = new int[1]{2};
	tens.loc_interval(arr, 1);


	return 0;
}
