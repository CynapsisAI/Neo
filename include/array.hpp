//
// Created by alial on 2023-11-10.
//

#ifndef NEO_ARRAY_HPP
#define NEO_ARRAY_HPP


#include <iostream>
#include <cstdlib>

/*
 * Declarations
 */

namespace neo{
  template <typename T>
  class Array{
  private:
    std::size_t _size{};
    T* _array;

  public:
    // Construct + Destructor
    Array(std::initializer_list<T> list);
    ~Array();

    // Getters
    std::size_t size() const;
    T* array() const;

    // Operators
    T& operator[](std::size_t index);

  };
}

template <typename T>
std::ostream &operator<<(std::ostream &s, const neo::Array<int> &array);



/*
 * Definitions
 */

template <typename T>
inline neo::Array<T>::Array(std::initializer_list<T> list) {
	_size = list.size();
  _array = new T[_size];
  std::copy(list.begin(), list.end(), _array);
}

template <typename T>
inline neo::Array<T>::~Array(){
  delete[] _array;
  _array = nullptr;
}

template <typename T>
inline std::size_t neo::Array<T>::size() const{
	return _size;
}

template<typename T>
T *neo::Array<T>::array() const{
  return _array;
}


/*
 * Operator Overloads
 */
template<typename T>
inline T &neo::Array<T>::operator[](std::size_t index) {
  if (index >= _size) {
    std::cout << "Array index out of bound, exiting";
    exit(0);
  }
  return _array[index];
}

template <typename T>
inline std::ostream &operator<<(std::ostream &s, const neo::Array<T> &array){
  T* arr = array.array();
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
