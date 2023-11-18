#include <iostream>
#include "include/neo.hpp"

int main() {
	neo::tensor<int> tens({2,2,3});

  neo::tensor<int> scalar({1});
  std::cout<<tens.get(1,1,3)<<std::endl;


	return 0;
}
