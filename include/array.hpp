//
// Created by alial on 2023-11-10.
//

#ifndef NEO_ARRAY_HPP
#define NEO_ARRAY_HPP


#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include "structs.hpp"


/*
 * Declarations
 */

namespace neo{
  template <typename T>
  class array{
  private:
    std::size_t _size{};
    T* _array;

  public:
    // Construct + Destructor
    array(std::initializer_list<T> list);
	  array(T* list, std::size_t cap);
	  array(shape shape);
	  ~array();

    // Getters
    std::size_t size() const;
    T* values() const;

    // Operators
    //    Array Assignment/Access []
    T& operator[](std::size_t index);

    //    Scalar Multiply *
    template <typename type>
    array<T> operator*(type x) const;

    //    Scalar Addition +
    template <typename type>
    array<T> operator+(type x) const;

    //    Array Addition +
    template<typename U>
    array<T> operator+(array<U> &array2);

  };
}

// Output Operator <<
template <typename T>
std::ostream &operator<<(std::ostream &s, const neo::array<int> &array);



/*
 * Definitions
 */

// Constructor
template <typename T>
inline neo::array<T>::array(std::initializer_list<T> list) {
	_size = list.size();
  _array = new T[_size];
  std::copy(list.begin(), list.end(), _array);
}

// Constructor
template <typename T>
inline neo::array<T>::array(T* list, std::size_t cap) {
  _size = cap;
  _array = list;
}

// Constructor
template <typename T>
inline neo::array<T>::array(neo::shape shape) {
	_size = shape.upper_dim();
	_array = new T[_size];
	for (std::size_t i{}; i < _size; i++){
		_array[i] = 0;
	}
}

// Destructor
template <typename T>
inline neo::array<T>::~array(){
	std::cout<<"Array Destructor Called"<<std::endl;
  delete[] _array;
  _array = nullptr;
}

template <typename T>
inline std::size_t neo::array<T>::size() const{
	return _size;
}

template<typename T>
T *neo::array<T>::values() const{
  return _array;
}


/*
 * Operator Overloads
 */

// Array Assignment/Access []
template<typename T>
inline T &neo::array<T>::operator[](std::size_t index) {
  if (index >= _size) {
    std::cout<<"Error: Array index out of bounds. Index: "<<index<<", Size: "<<_size<<std::endl;
    exit(0);
  }
  return _array[index];
}

// Scalar Multiply *
template<typename T>
template<typename type>
inline neo::array<T> neo::array<T>::operator*(type x) const{
  T *tmp = new T[_size];
  for (std::size_t i{}; i < _size; i++) {
    tmp[i] = _array[i] * x;
  }
  return neo::array<T>(tmp, _size);
}

// Scalar Addition +
template<typename T>
template<typename type>
inline neo::array<T> neo::array<T>::operator+(type x) const{
  T *tmp = new T[_size];
  for (std::size_t i{}; i < _size; i++) {
    tmp[i] = _array[i] + x;
  }
  return neo::array<T>(tmp, _size);
}

// Array Addition +
template<typename T>
template<typename U>
inline neo::array<T> neo::array<T>::operator+(neo::array<U> &array2){
  // Ensure both arrays are same size
  if (_size != array2.size()){
    std::cout<<"Error: Arrays must be same size. Array1: "<<_size<<", Array2: "<<array2.size()<<std::endl;
    exit(0);
  }

  T *tmp = new T[_size];
  for (std::size_t i{}; i < _size; i++) {
    tmp[i] = _array[i] + array2[i];
  }
  return neo::array<T>(tmp, _size);
}


// Output Operator <<
template <typename T>
inline std::ostream &operator<<(std::ostream &s, const neo::array<T> &array){
  T* arr = array.values();
  std::cout<<"neo::array"<<std::endl;
  std::cout<<"Type: "<<typeid(T).name()<<"  Size: "<<array.size()<<std::endl;
  s<<"[";
  for (std::size_t i{}; i<array.size(); i++){
    if (i != array.size()-1)
      s<<arr[i]<<", ";
    else
      s<<arr[i];
  }
  s<<"]";

	return s;
}







#endif //NEO_ARRAY_HPP
