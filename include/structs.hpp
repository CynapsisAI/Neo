//
// Created by alial on 2023-11-10.
//

#ifndef NEO_STRUCTS_HPP
#define NEO_STRUCTS_HPP

#include <iostream>
#include <typeinfo>

namespace neo
{

	class shape_obj
	{
	private:
		unsigned int _dim{};
		unsigned int *_shape{};

	public:
		unsigned int *getShape() const { return _shape; }
		unsigned int getDim() const { return _dim; }
		shape_obj(unsigned int dim, unsigned int *shape)
		{
			_dim = dim;
			_shape = shape;
		}
	};

}

// Output Operator <<
std::ostream &operator<<(std::ostream &s, const neo::shape_obj &shape_obj)
{
	s << "(";

	for (int i = 0; i < (shape_obj.getDim()); ++i)
	{
		s << (shape_obj.getShape()[i]);

		// Print a comma and space if it's not the last element
		if (i < shape_obj.getDim() - 1)
		{
			s << ", ";
		}
	}

	s << ")" << std::endl;

	return s;
}
// 	struct shape {
// 	private:
// 		unsigned int* _shape{};
// 		unsigned int _dim{};
// 		unsigned int _size{1};

// 	public:
// 		shape(std::initializer_list<unsigned int> shape){
// 			_dim = shape.size();

// 			for (auto i : shape)
// 				_size *= i;

// 			_shape = new unsigned int[_size];
// 			std::copy(shape.begin(), shape.end(), _shape);

// 		}

// 		shape(unsigned int* shape, unsigned int dim){
// 			_shape = shape;
// 			_dim = dim;

// 			for (std::size_t i{}; i < _dim; i++)
// 				_size *= _shape[i];
// 		}

// 		~shape(){
// 			std::cout<<"Destroying Shape. Dim: "<<_dim<<std::endl;
// 			delete[] _shape;
// 			_shape = nullptr;
// 		}

// 		unsigned int* list() const{ return _shape; }

// 		unsigned int dim() const{ return _dim; }

// 		unsigned int size() const{ return _size; }

// 		unsigned int upper_dim() const { return _shape[0]; }

// 	};
// }

// // Output Operator <<
// std::ostream &operator<<(std::ostream &s, const neo::shape &shape);

#endif // NEO_STRUCTS_HPP
