#include <iostream>
#include "include/neo.hpp"

int main() {
	neo::tensor<int> tens({2,2,3});
  neo::tensor<int> tens2({2,2,3});
  tens = 3;
  tens2 = 5;


  tens += tens;

  std::cout<<tens<<std::endl;

	return 0;
}
