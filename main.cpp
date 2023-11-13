#include <iostream>
#include "include/neo.hpp"
#include "structs.hpp"
#include "ndarray.hpp"
#include <string>

int main() {
	neo::ndarray<int> arr({2,2,3});
  std::cout<<arr<<std::endl;


  arr.get(1,1,1);

	return 0;
}
