#include <iostream>
#include "include/neo.hpp"

int main() {
	neo::tensor<int> tens({2,2,3});

  std::cout<<tens<<std::endl;

  neo::tensor<int> flattened = tens.flatten();
  std::cout<<flattened<<std::endl;

  tens.get(0,0,0) = 3;
  std::cout<<tens<<std::endl;


	return 0;
}
