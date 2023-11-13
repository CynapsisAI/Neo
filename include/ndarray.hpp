//
// Created by alial on 2023-11-10.
//

#ifndef NEO_NDARRAY_HPP
#define NEO_NDARRAY_HPP

#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include "structs.hpp"
#include "array.hpp"
#include <cstdarg>
#include <cassert>
#include "stdarg.h"
#include <string>



namespace neo {
	template<typename T>
	class ndarray {

	private:
		std::size_t _size{1};
		unsigned int *_shape{};
		unsigned int _dim{};
		ndarray<T> **_array{};
		array<T> *_base_array{};

		ndarray<T> **recursive_helper(unsigned int *shape, unsigned int dim);

	public:
		// Default
		ndarray(std::initializer_list<unsigned int> shape);

		ndarray(unsigned int *shape, int dim);

		// Destructor
		~ndarray();




		// Getters
		std::size_t size() const { return _size; }
		shape_obj shape() { return shape_obj(_dim, _shape); }
		unsigned int dim() { return _dim; }
		ndarray<T> **values() const { return _array; };
		array<T> base_array() const { return *_base_array; };

    template<typename... Ta>
    int get(Ta... args);
		//    Array Assignment/Access []
    ndarray<T>& operator[](std::size_t index);



	};


}
// Output Operator <<
template <typename T>
std::ostream &operator<<(std::ostream &s, const neo::ndarray<int> &ndarray);

/*
 * Definitions
 */

template<typename T>
neo::ndarray<T> **neo::ndarray<T>::recursive_helper(unsigned int* shape, unsigned int dim) {
	std::size_t upper_size = shape[0];

	if (dim <= 1) return nullptr;

	neo::ndarray<T>** array = new neo::ndarray<T>*[upper_size];

	for (std::size_t i{}; i < upper_size; i++){
		array[i] = new neo::ndarray<T>(shape+1, dim-1);

	}
	return array;
}

// Default Constructor
template <typename T>
inline neo::ndarray<T>::ndarray(std::initializer_list<unsigned int> shape) {
	_dim = shape.size();
	_shape = new unsigned int[_size];
	std::copy(shape.begin(), shape.end(), _shape);

	int upper_dim = _shape[0];

	if (_dim > 1) {
		neo::ndarray<T>** arr = recursive_helper(_shape, _dim);
		_array = arr;

	} else {
		neo::array<T>* base_array = new neo::array<T>(_shape[0]);
		_base_array = base_array;

	}

}

// Default Constructor
template <typename T>
inline neo::ndarray<T>::ndarray(unsigned int* shape, int dim) {
	_dim = dim;
	_shape = shape;

	int upper_dim = _shape[0];

	if (_dim > 1) {
		neo::ndarray<T>** arr = recursive_helper(_shape, _dim);
		_array = arr;

	} else {
		neo::array<T>* base_array = new neo::array<T>(_shape[0]);
		_base_array = base_array;

	}

}





// Destructor
template <typename T>
inline neo::ndarray<T>::~ndarray(){
	std::cout<<"NDArray Destructor Called"<<std::endl;

	delete[] _array;
	_array = nullptr;
}

/*
 * Operator Overloads
 */

template <typename T>
inline void recursive_output(neo::ndarray<T> &array){

}


// Output Operator <<
template <typename T>
inline std::ostream &operator<<(std::ostream &s, neo::ndarray<T> &array){

	unsigned int *shape = array.shape().getShape();
	unsigned int dim = array.dim();

	if (dim <= 1){
		neo::array<T> arr = array.base_array();
		s<<arr;
	}
	else{
		std::size_t cap = shape[0];
		s<<"[";
		for (std::size_t i{}; i < cap; i++){
			neo::ndarray<T>** values = array.values();
			s<<*values[i];
			if (i != (cap-1)){
				s<<", ";
			}
		}
		s<<"]";

	}

	return s;
}

void assert_check(bool expr, std::string message){
  if(expr) return;

  std::cout<<"Error: "<<message<<std::endl;
  exit(0);
}

void check_bounds(std::size_t cap, std::size_t index){
  assert_check(index < cap, "Index out of bounds");
}

template <typename T>
template <typename... Ta>
inline int neo::ndarray<T>::get(Ta... args) {
  constexpr std::size_t n = sizeof...(Ta);
  assert_check(n >= 1, "Must pass at least one argument");
  assert_check(n <= _dim, "Indexing deeper than number of dimensions");
  int arr[n]{args...};

  if (_dim == 1) {
    check_bounds(_base_array->size(), arr[0]);
    std::cout<<_base_array[arr[0]]<< std::endl;
    return 0;
  }

  check_bounds(_shape[0], arr[0]);
  ndarray<T>* running_array{_array[arr[0]]};

  for (std::size_t i{1}; i < n; i++){
    std::size_t index = arr[i];
    std::size_t cap = running_array->_shape[0];
    check_bounds(cap, index);


    if (running_array->_dim == 1){
      array<T> base = *running_array->_base_array;
      std::cout<<base[index]<<std::endl;
      return 0;
    }
    running_array = running_array->_array[index];
  }
  std::cout<<*running_array<<std::endl;

  return 0;
}

// Array Assignment/Access []
//
//template<typename T>
//inline neo::ndarray<T>& neo::ndarray<T>::operator[](std::size_t i) {
//	constexpr std::size_t n = sizeof...(indices);
//	std::cout<<n<<std::endl;
//	static_assert(n >= 1, "must pass at least one argument");
//	std::cout << n << std::endl;
//	auto&& tuple = std::tie(indices...);
//	std::cout<<std::get<0>(tuple)<<std::endl;
//
//}

#endif // NEO_NDARRAY_HPP
