#include <iostream>
#include "include/neo.hpp"

int main() {
	neo::tensor<int> tens({2,2,3});

  int* arr = new int[2]{1,1};
  tens.loc_interval(arr, 2);


	return 0;
}
