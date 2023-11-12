//
// Created by alial on 2023-11-10.
//

#ifndef NEO_STRUCTS_HPP
#define NEO_STRUCTS_HPP

#include <iostream>
#include <typeinfo>

namespace neo {
	struct shape {
	private:
		unsigned int* _shape{};
		unsigned int _dim{};
		unsigned int _size{1};

	public:
		shape(std::initializer_list<unsigned int> shape){
			_dim = shape.size();

			for (auto i : shape)
				_size *= i;


			_shape = new unsigned int[_size];
			std::copy(shape.begin(), shape.end(), _shape);

		}


		shape(unsigned int* shape, unsigned int dim){
			_shape = shape;
			_dim = dim;

			for (std::size_t i{}; i < _dim; i++)
				_size *= _shape[i];
		}

		~shape(){
			std::cout<<"Destroying Shape. Dim: "<<_dim<<std::endl;
			delete[] _shape;
			_shape = nullptr;
		}

		unsigned int* list() const{ return _shape; }

		unsigned int dim() const{ return _dim; }

		unsigned int size() const{ return _size; }

		unsigned int upper_dim() const { return _shape[0]; }

	};
}

// Output Operator <<
std::ostream &operator<<(std::ostream &s, const neo::shape &shape);

#endif //NEO_STRUCTS_HPP
