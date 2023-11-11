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


namespace neo {
	template<typename T>
	class ndarray {

	private:
		std::size_t _size{1};
		shape _shape{};
		ndarray<T>** _array{};
		array<T>* _prim_array{};

	public:
		// Default
		ndarray(shape shape);

		// Copy
		ndarray(const ndarray<T>& copy);

		// Assignment
		ndarray<T>& operator=(const ndarray<T>& ndarray) {
			// self-assignment check
			std::cout<<"assignment operator called"<<std::endl;
//			if (this == &ndarray)
//				return *this;

//			// if data exists in the current string, delete it
//			delete[] _array;
//			delete[] _prim_values;
//
//			_size = ndarray.size();
//			_shape = ndarray.shape();
//			_array = nullptr;
//			_prim_values = nullptr;
//
//			// check if dim is 1
//			if (_shape.dim() == 1){
//
//				// copy the data from str to the implicit object
//				if (_size)
//					_prim_values = new T[_shape.list()[0]];
//
//				for (int i { 0 }; i < _size; ++i)
//					_prim_values[i] = ndarray.prim_values()[i];
//
//			} else {
//				// copy the data from str to the implicit object
//				if (_size)
//					_array = new class ndarray[_shape.list()[0]];
//
//				for (int i { 0 }; i < _size; ++i)
//					_array[i] = ndarray.values()[i];
//			}
//
//
//			// return the existing object so we can chain this operator
//			return *this;
		}

		~ndarray();


		ndarray lower_dim(int index);


		// Getters
		std::size_t size() const{ return _size; }
		shape shape() const{ return _shape; }
		ndarray<T>** values() const{ return _array; };
		array<T> array() const{ return *_prim_array; }

		//    Array Assignment/Access []
		ndarray& operator[](std::size_t index);


	};
}
// Output Operator <<
template <typename T>
std::ostream &operator<<(std::ostream &s, const neo::ndarray<int> &ndarray);

/*
 * Definitions
 */

// Default Constructor
template <typename T>
inline neo::ndarray<T>::ndarray(neo::shape shape) {
	std::cout<<"Creating NDarray: Shape: "<<shape<<std::endl;
	_shape = shape;

	if (_shape.dim()-1 != 0){
		_array = new neo::ndarray<T>*[_shape.upper_dim()];

		for (std::size_t i{}; i<_shape.upper_dim(); i++){
			neo::shape new_shape(_shape.list()+1, _shape.dim()-1);

			std::cout<<new_shape<<std::endl;
			neo::ndarray<T>* new_array{new neo::ndarray<T>(new_shape)};
			std::cout<<"new arr: "<<new_array<<std::endl;

			_array[i] = new_array;
		}
	} else{
		std::cout<<"else: "<<_shape<<std::endl;
		neo::array<T>* new_arr {new neo::array<T>(_shape)};
		_prim_array = new_arr;
		std::cout<<"PRIM: "<<_prim_array<<std::endl;
	}
	std::cout<<"Created NDarray"<<std::endl;


}

// Copy Constructor
template <typename T>
inline neo::ndarray<T>::ndarray(const neo::ndarray<T>& copy) {
	std::cout<<"Copy Constructor"<<std::endl;
	_shape = copy.shape();
	_array = copy.values();
	_size = copy.size();

}


// Destructor
template <typename T>
inline neo::ndarray<T>::~ndarray(){
	std::cout<<"NDArray Destructor Called"<<std::endl;

	delete[] _array;
	_array = nullptr;
}

template <typename T>
inline neo::ndarray<T> neo::ndarray<T>::lower_dim(int index){
	if (index >= _shape.upper_dim()) {
		std::cout<<"Error: index is out of bounds for the dimension"<<std::endl;
		exit(1);
	}


}

/*
 * Operator Overloads
 */
// Output Operator <<
template <typename T>
inline std::ostream &operator<<(std::ostream &s, const neo::ndarray<T> &array){

	std::cout<<"IN"<<std::endl;
	neo::ndarray<T>** arr = array.values();
	neo::shape sh = array.shape();
	std::cout<<sh<<std::endl;

	unsigned int size_dim_1{sh.upper_dim()};
	std::cout<<"neo::ndrray"<<std::endl;
	std::cout<<"Type: "<<typeid(T).name()<<"  Dim: "<<size_dim_1<<std::endl;
	s<<"[";
	for (std::size_t i{}; i<size_dim_1; i++){
		if (i != size_dim_1-1)
			s<<&arr[i]<<", ";
		else
			s<<&arr[i];
	}
	s<<"]";

	return s;
}



// Array Assignment/Access []

template<typename T>
inline neo::ndarray<T>& neo::ndarray<T>::operator[](std::size_t index) {
	if (index >= _shape.upper_dim()) {
		std::cout<<"Error: Array index out of bounds. Index: "<<index<<", Size: "<<_size<<std::endl;
		exit(0);
	}
	return *_array[index];
}


#endif //NEO_NDARRAY_HPP
