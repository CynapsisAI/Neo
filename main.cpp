#include <iostream>
#include "include/neo.hpp"
#include "structs.hpp"
#include "ndarray.hpp"
#include <string>

int main() {
	neo::ndarray<int> arr({2,2});


  arr.get(1,3,6,4,5);

	return 0;
}
