//
// Created by alial on 2023-11-10.
//

#ifndef NEO_ARRAY_HPP
#define NEO_ARRAY_HPP


#include <iostream>

/*
 * Declarations
 *
 */

template <typename T>
class Array{
  private:
		unsigned int _size{};
		T _array[];

  public:
    Array(std::initializer_list<T> list);
    unsigned int size() const;
};

template <typename T>
std::ostream &operator<<(std::ostream &s, const Array<int> &array);



/*
 * Definitions
 *
 */

template <typename T>
inline Array<T>::Array(std::initializer_list<T> list) {
	_size = list.size();
	std::cout << _size << std::endl;
}


template <typename T>
inline unsigned int Array<T>::size() const{
	return _size;
}

template <typename T>
inline std::ostream &operator<<(std::ostream &s, const Array<T> &array){
	int hi= array.size();
	s << "obj";
	return s;
}







#endif //NEO_ARRAY_HPP
