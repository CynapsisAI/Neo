//
// Created by Ali A on 2023-11-13.
//

#ifndef NEO_TENSOR_HPP
#define NEO_TENSOR_HPP

#include <iostream>
#include <numeric>


namespace neo {

  template <typename T>
  class tensor {
  private:

    unsigned int _size{1};
    unsigned int *_shape{};
    unsigned int _dim{};
    T* _array;


  public:
    // Default
    tensor(std::initializer_list<unsigned int> shape);
    tensor(unsigned int *shape, int dim);
    tensor(T* array, unsigned int *shape, int dim);

		// Copy constructor
		tensor(const tensor<T>& tensor);


    // Destructor
    ~tensor();

		// Assignment operator
		tensor<T>& operator= (const tensor<T>& tensor);
	  tensor<T>& operator= (const T val);

    // Get function
    template<typename... Ta>
    tensor<T>& get(Ta... args) const;

		// Locate interval function
    std::pair<unsigned int, unsigned int> loc_interval(int* args, unsigned int cap) const;

		// Flatten
		tensor<T>& flatten(bool in_place = false);

		// Getters
		unsigned int dim() const {return _dim;}
		unsigned int size() const {return _size;}
		unsigned int* shape() const {return _shape;}
		T* array() const {return _array;}


  };
}
// Output Operator <<
template <typename T>
std::ostream &operator<<(std::ostream &s, const neo::tensor<T> &tensor);


// Default Constructor
template <typename T>
neo::tensor<T>::tensor(std::initializer_list<unsigned int> shape) {
  _dim = shape.size();
  _shape = new unsigned int[_dim];
  std::copy(shape.begin(), shape.end(), _shape);
  _size = std::accumulate( shape.begin(), shape.end(), 1, std::multiplies<unsigned int>() );

  // Initialize to 0s
  _array = new T[_size]{0};

}

// Constructor
template <typename T>
neo::tensor<T>::tensor(unsigned int *shape, int dim) {
  _dim = dim;
  _shape = shape;
  for (std::size_t i{}; i < dim; i++) {
    _size *= _shape[i];
  }

  // Initialize to 0s
  _array = new T[_size]{0};

}

// Constructor
template <typename T>
neo::tensor<T>::tensor(T* array, unsigned int* shape, int dim) {
  _dim = dim;
  _shape = shape;
  for (std::size_t i{}; i < dim; i++) {
    _size *= _shape[i];
  }

  _array = array;
}

// Copy constructor
template <typename T>
neo::tensor<T>::tensor(const tensor<T>& tensor) {
	_dim = tensor.dim();
	_shape = tensor.shape();
	_array = tensor.array();
	_size = tensor.size();
}


// Destructor
template <typename T>
neo::tensor<T>::~tensor() {
  std::cout<<"Tensor Destructor Called"<<std::endl;
  delete[] _array;
  _array = nullptr;
}

// Return a tuple of <starting index, ending index>
template <typename T>
inline std::pair<unsigned int, unsigned int> neo::tensor<T>::loc_interval(int* args, unsigned int cap) const{
  unsigned int width{_size/_shape[0]};
	std::cout<<"width: "<<width<<std::endl;

  unsigned int running_index{0};
  for(std::size_t i{}; i < cap; i++){
		unsigned int x = (args[i]*_shape[i]);
		std::cout<<x<<std::endl;
    running_index += x;
  }

  running_index -= 1;
  running_index *= width;
	std::cout<<"running index: "<<running_index<<std::endl;

  std::pair<unsigned int, unsigned int> range(running_index, running_index+width-1);
  return range;

}


template <typename T>
inline neo::tensor<T>& neo::tensor<T>::operator=(const tensor <T> &tensor) {
	// Self assignment check
	if (this == &tensor){
		return *this;
	}

	// Check if tensor is same size
	assert_check(_dim == tensor.dim(), "Tensors must be the same size & dimension");
	unsigned int* tensor_shape = tensor.shape();

	for (std::size_t i{}; i < _dim; i++){
		assert_check(_shape[i] == tensor_shape[i], "Tensors must be the same size & dimension");
	}

	T* new_array = tensor.array();

	for (std::size_t i{}; i < _size; i++)
		_array[i] = new_array[i];

	return *this;
}


template <typename T>
inline neo::tensor<T>& neo::tensor<T>::operator=(const T val) {
	for (std::size_t i{}; i < _size; i++){
		_array[i] = val;
	}

	return *this;
}


template <typename T>
template <typename... Ta>
inline neo::tensor<T>& neo::tensor<T>::get(Ta... args) const{
	std::cout<<"getting"<<std::endl;
  constexpr unsigned int n = sizeof...(Ta);
  assert_check(n >= 1, "Must pass at least one argument");
  assert_check(n <= _dim, "Indexing deeper than number of dimensions");
  int arr[n]{args...};

	std::cout<<"arg: "<<arr[0]<<std::endl;
	std::cout<<_size<<std::endl;
	std::cout<<_dim<<std::endl;
  std::pair<unsigned int, unsigned int> range = loc_interval(arr, n);
	std::cout<<"range: "<<range.first<<std::endl;

  neo::tensor<T>* new_tensor = new neo::tensor<T>(_array+range.first, _shape+n, _dim-n);
	T* test = new_tensor->array();
	std::cout<<"test: "<<test[0]<<std::endl;

  return *new_tensor;
}

template <typename T>
inline neo::tensor<T>& neo::tensor<T>::flatten(bool in_place){

	if (in_place) {
		delete[] _shape;
		_shape = new unsigned int[1]{_size};
		return *this;
	}

	// Create copy of array
	T* new_array = new T[_size];
	unsigned int* new_shape = new unsigned int[1]{_size};
	for (std::size_t i{}; i < _size; i++)
		new_array[i] = _array[i];


	neo::tensor<T>* new_tensor = new neo::tensor<T>(new_array, new_shape, 1);
	return *new_tensor;
}


// Output Operator <<
template <typename T>
std::ostream &operator<<(std::ostream &s, const neo::tensor<T> &tensor) {

	unsigned int* shape = tensor.shape();
	T* tensor_array = tensor.array();
	std::cout<<"arr1:"<<tensor_array[0]<<std::endl;

	unsigned int dim = tensor.dim();
	std::cout<<"dim:"<<dim<<std::endl;

	if (dim == 1){
		std::cout<<"in"<<std::endl;
		s<<"[";
		std::cout<<"tensorsize:"<<tensor.size()<<std::endl;
		std::cout<<"arr2:"<<tensor_array[0]<<std::endl;
		for (std::size_t i{}; i < tensor.size(); i++){
			s<<tensor_array[i];
			if (i != (tensor.size()-1)){
				s<<", ";
			}
		}
		s<<"]";
		return s;
	}

	std::size_t width = shape[0];
	for (std::size_t i{}; i < width; i++){
		s<<"[";
		neo::tensor<T>lower_tensor = tensor.get(i);
		std::cout<<&lower_tensor<<std::endl;
		//s<<lower_tensor;
		s<<"]";
		if (i != (width-1)){
			s<<", ";
		}
	}


	return s;
}

#endif //NEO_TENSOR_HPP
